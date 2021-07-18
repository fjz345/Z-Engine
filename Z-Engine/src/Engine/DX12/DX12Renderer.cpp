#include "DX12Renderer.h"

#include "../win32/Win32Window.h"

namespace ZE
{
	Renderer* Renderer::Create(Window* renderTarget)
	{
		return new DX12Renderer(renderTarget);
	}

	DX12Renderer::DX12Renderer(Window* renderTarget)
		: Renderer(renderTarget)
	{
		//INIT DX12
		InitDevice();

		// TODO: Fence klass?
		_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&this->_fenceFrame));
		this->_fenceFrameValue = 0;

		// Event handle to use for GPU synchronization
		this->_eventHandle = CreateEvent(0, false, false, 0);

		// Create Main DescriptorHeap
		this->_commonHeap = new DescriptorHeap(_device, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 100, true);

		InitCommandQueue();


		// TODO: fix platform specific good
		_swapChain = new SwapChain(_device, ((Win32Window*)renderTarget)->GetHWND(), this->_commandQueue);


		InitDepthBuffer();


		// Create Command Allocator/Command List
		this->_commandRecorder = new CommandRecorder(this->_device, D3D12_COMMAND_LIST_TYPE_DIRECT);


		// Create Rootsignature
		_rootSig = new RootSignature(_device);

		InitPipelineStates();
		
	}

	DX12Renderer::~DX12Renderer()
	{
		WaitForGPU();

		delete _commonHeap;
		delete _swapChain;
		delete _dsvHeap;
		delete _commandRecorder;
		delete _rootSig;
		delete _depthResource;
		delete _pipelineState;

		SAFE_RELEASE(&_commandQueue);
		SAFE_RELEASE(&_fenceFrame);
		SAFE_RELEASE(&_device);
	}

	void DX12Renderer::Render(double dt)
	{
		_frameCounter++;

		IDXGISwapChain4* dx12SwapChain = this->_swapChain->GetDXGISwapChain();
		int backBufferIndex = dx12SwapChain->GetCurrentBackBufferIndex();
		int commandRecorderIndex = ++this->_frameCounter % 2;

		ID3D12GraphicsCommandList5* commandList = this->_commandRecorder->GetCommandList(commandRecorderIndex);
		_commandRecorder->Reset(commandRecorderIndex);

		D3D12_RESOURCE_BARRIER transition;

		RenderTarget* renderTarget = this->_swapChain;
		ID3D12Resource* renderTargetResource = renderTarget->GetResourceAt(backBufferIndex);
		
		commandList->SetGraphicsRootSignature(this->_rootSig->GetRootSig());
		
		ID3D12DescriptorHeap* bindlessHeap = this->_commonHeap->GetID3D12DescriptorHeap();
		commandList->SetDescriptorHeaps(1, &bindlessHeap);

		commandList->SetGraphicsRootDescriptorTable(RS::CBVS, this->_commonHeap->GetGDHAt(0));

		// Change state on front/backbuffer
		transition = CD3DX12_RESOURCE_BARRIER::Transition(
			renderTargetResource,
			D3D12_RESOURCE_STATE_PRESENT,
			D3D12_RESOURCE_STATE_RENDER_TARGET);
		commandList->ResourceBarrier(1, &transition);

		DescriptorHeap* renderTargetHeap = renderTarget->GetDescriptorHeap();
		DescriptorHeap* depthBufferHeap = this->_dsvHeap;

		D3D12_CPU_DESCRIPTOR_HANDLE cdh = renderTargetHeap->GetCDHAt(backBufferIndex);
		D3D12_CPU_DESCRIPTOR_HANDLE dsh = depthBufferHeap->GetCDHAt(0);

		commandList->OMSetRenderTargets(1, &cdh, true, &dsh);

		float clearColor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
		commandList->ClearRenderTargetView(cdh, clearColor, 0, nullptr);
		commandList->ClearDepthStencilView(dsh, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

		D3D12_VIEWPORT* viewPort = renderTarget->GetViewPort();
		D3D12_RECT* rect = renderTarget->GetScissorRect();
		commandList->RSSetViewports(1, viewPort);
		commandList->RSSetScissorRects(1, rect);

		commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		commandList->SetPipelineState(this->_pipelineState->GetPSO());


		// Draw -----------

		commandList->DrawInstanced(3, 1, 0, 0);

		// ----------------

		
		// Change state on buffer
		transition = CD3DX12_RESOURCE_BARRIER::Transition(
			renderTargetResource,
			D3D12_RESOURCE_STATE_RENDER_TARGET,
			D3D12_RESOURCE_STATE_PRESENT);
		commandList->ResourceBarrier(1, &transition);

		commandList->Close();





		ID3D12CommandList* commandLists[1] = { commandList };
		_commandQueue->ExecuteCommandLists(1, commandLists);

		WaitForGPU();

		dx12SwapChain->Present(0, DXGI_PRESENT_ALLOW_TEARING);
	}

	void DX12Renderer::InitDevice()
	{
		// InitDevice
#ifdef _DEBUG
//Enable the D3D12 debug layer.
		ID3D12Debug* debugController = nullptr;


#ifdef STATIC_LINK_DEBUGSTUFF
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
		{
			debugController->EnableDebugLayer();
		}
		SAFE_RELEASE(&debugController);
#else
		HMODULE mD3D12 = LoadLibrary(L"D3D12.dll"); // ist�llet f�r GetModuleHandle

		PFN_D3D12_GET_DEBUG_INTERFACE f = (PFN_D3D12_GET_DEBUG_INTERFACE)GetProcAddress(mD3D12, "D3D12GetDebugInterface");
		if (SUCCEEDED(f(IID_PPV_ARGS(&debugController))))
		{
			debugController->EnableDebugLayer();
		}
		SAFE_RELEASE(&debugController);
#endif
#endif

		IDXGIFactory6* factory = nullptr;
		IDXGIAdapter1* adapter = nullptr;

		CreateDXGIFactory(IID_PPV_ARGS(&factory));

		for (UINT adapterIndex = 0;; ++adapterIndex)
		{
			adapter = nullptr;
			if (DXGI_ERROR_NOT_FOUND == factory->EnumAdapters1(adapterIndex, &adapter))
			{
				break; // No more adapters
			}

			// Check to see if the adapter supports Direct3D 12, but don't create the actual device yet.
			if (SUCCEEDED(D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_12_1, __uuidof(ID3D12Device5), nullptr)))
			{
				break;
			}

			SAFE_RELEASE(&adapter);
		}

		if (adapter)
		{
			HRESULT hr = S_OK;
			hr = D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&this->_device));
			//Create the actual device.
			if (SUCCEEDED(hr))
			{

			}

			SAFE_RELEASE(&adapter);
		}
		else
		{
			//Create warp device if no adapter was found.
			factory->EnumWarpAdapter(IID_PPV_ARGS(&adapter));
			D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&_device));
		}

		SAFE_RELEASE(&factory);
	}

	void DX12Renderer::InitCommandQueue()
	{
		// Direct
		D3D12_COMMAND_QUEUE_DESC desc = {};
		desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		HRESULT hr;
		hr = _device->CreateCommandQueue(&desc, IID_PPV_ARGS(&this->_commandQueue));
		if (FAILED(hr))
		{
			OutputDebugStringW(L"ERROR: Failed to create Direct CommandQueue");
		}
	}

	void DX12Renderer::InitDepthBuffer()
	{
		// Create Main DepthBuffer
		// Create resource
		D3D12_RESOURCE_DESC resourceDesc = {};
		resourceDesc.Format = DXGI_FORMAT_D32_FLOAT;
		resourceDesc.Width = _renderTarget->GetWidth();
		resourceDesc.Height = _renderTarget->GetHeight();
		resourceDesc.DepthOrArraySize = 1;
		resourceDesc.MipLevels = 0;
		resourceDesc.SampleDesc.Count = 1;
		resourceDesc.SampleDesc.Quality = 0;
		resourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
		resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;

		D3D12_CLEAR_VALUE clearValue = {};
		clearValue.Format = DXGI_FORMAT_D32_FLOAT;
		clearValue.DepthStencil.Depth = 1;
		clearValue.DepthStencil.Stencil = 0;


		// Create descriptorHeap for the dsv
		this->_dsvHeap = new DescriptorHeap(this->_device, D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_DSV, 1, false);

		this->_depthResource = new Resource(
			_device,
			&resourceDesc,
			&clearValue,
			L"Resource_Depth",
			D3D12_RESOURCE_STATE_DEPTH_WRITE);

		D3D12_DEPTH_STENCIL_VIEW_DESC depthStencilDesc = {};
		depthStencilDesc.Format = DXGI_FORMAT_D32_FLOAT;
		depthStencilDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
		depthStencilDesc.Flags = D3D12_DSV_FLAG_NONE;

		D3D12_CPU_DESCRIPTOR_HANDLE cdh = _dsvHeap->GetCDHAt(0);
		_device->CreateDepthStencilView(_depthResource->GetID3D12Resource1(), &depthStencilDesc, cdh);
	}

	void DX12Renderer::InitPipelineStates()
	{
		// Create PipelineState
		D3D12_GRAPHICS_PIPELINE_STATE_DESC gpsd = {};
		gpsd.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

		// RenderTarget
		gpsd.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		gpsd.NumRenderTargets = 1;
		// Depthstencil usage
		gpsd.SampleDesc.Count = 1;
		gpsd.SampleMask = UINT_MAX;
		// Rasterizer behaviour
		gpsd.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
		gpsd.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;

		// Specify Blend descriptions
		D3D12_RENDER_TARGET_BLEND_DESC defaultRTdesc = {
			false, false,
			D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
			D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
			D3D12_LOGIC_OP_NOOP, D3D12_COLOR_WRITE_ENABLE_ALL };
		for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; i++)
			gpsd.BlendState.RenderTarget[i] = defaultRTdesc;

		// Depth descriptor
		D3D12_DEPTH_STENCIL_DESC dsd = {};
		dsd.DepthEnable = true;
		dsd.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
		dsd.DepthFunc = D3D12_COMPARISON_FUNC_LESS;	// Om pixels depth är lägre än den gamla så ritas den nya ut

		// Stencil
		dsd.StencilEnable = false;
		dsd.StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK;
		dsd.StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK;
		const D3D12_DEPTH_STENCILOP_DESC defaultStencilOP{ D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_COMPARISON_FUNC_ALWAYS };
		dsd.FrontFace = defaultStencilOP;
		dsd.BackFace = defaultStencilOP;

		gpsd.DepthStencilState = dsd;
		gpsd.DSVFormat = DXGI_FORMAT_D32_FLOAT;

		_pipelineState = new PipelineState(_device, _rootSig, L"HLSL/test.vs", L"HLSL/test.ps", &gpsd);
	}

	void DX12Renderer::WaitForFrame(unsigned int framesToBeAhead)
	{
		static constexpr unsigned int nrOfFenceChangesPerFrame = 1;
		unsigned int fenceValuesToBeAhead = framesToBeAhead * nrOfFenceChangesPerFrame;

		//Wait if the CPU is "framesToBeAhead" number of frames ahead of the GPU
		if (this->_fenceFrame->GetCompletedValue() < this->_fenceFrameValue - fenceValuesToBeAhead)
		{
			this->_fenceFrame->SetEventOnCompletion(this->_fenceFrameValue - fenceValuesToBeAhead, this->_eventHandle);
			WaitForSingleObject(this->_eventHandle, INFINITE);
		}
	}
	void DX12Renderer::WaitForGPU()
	{
		// Signal and increment the fence value.
		unsigned int oldFenceValue = this->_fenceFrameValue;
		this->_commandQueue->Signal(this->_fenceFrame, oldFenceValue);
		this->_fenceFrameValue++;

		// Wait until command queue is done.
		if (this->_fenceFrame->GetCompletedValue() < oldFenceValue)
		{
			this->_fenceFrame->SetEventOnCompletion(oldFenceValue, _eventHandle);
			WaitForSingleObject(_eventHandle, INFINITE);
		}
	}
}

