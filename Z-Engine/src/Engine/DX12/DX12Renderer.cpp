#include "DX12Renderer.h"

namespace ZE
{
	Renderer* Renderer::Create(Window* renderTarget)
	{
		return new DX12Renderer(renderTarget);
	}

	DX12Renderer::DX12Renderer(Window* renderTarget)
	{
		this->_renderTarget = renderTarget;


		//INIT DX12

		// InitDevice
#ifdef _DEBUG
//Enable the D3D12 debug layer.
		ID3D12Debug* debugController = nullptr;

#ifdef STATIC_LINK_DEBUGSTUFF
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
		{
			debugController->EnableDebugLayer();
		}
		SafeRelease(debugController);
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
			//Create the actual device.
			if (SUCCEEDED(hr = D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&device))))
			{
				
			}

			SAFE_RELEASE(&adapter);
		}
		else
		{
			//Create warp device if no adapter was found.
			factory->EnumWarpAdapter(IID_PPV_ARGS(&adapter));
			D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device));
		}

		SAFE_RELEASE(&factory);









		
		// Direct
		D3D12_COMMAND_QUEUE_DESC desc = {};
		desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		HRESULT hr;
		hr = device->CreateCommandQueue(&desc, IID_PPV_ARGS(&this->commandQueues[D3D12_COMMAND_LIST_TYPE_DIRECT]));
		if (FAILED(hr))
		{
			OutputDebugStringW(L"ERROR: Failed to create Direct CommandQueue");
		}








		




		//swapChain = new SwapChain(device, hwnd, this->commandQueues[COMMAND_INTERFACE_TYPE::DIRECT_TYPE]);











		device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&this->fenceFrame));

		this->fenceFrameValue = 1;

		// Event handle to use for GPU synchronization
		this->eventHandle = CreateEvent(0, false, false, 0);





		// Create Main DepthBuffer
		//this->CreateDepthBuffer();








		// Create Rootsignature
		//this->CreateRootSignature();








		// Create DescriptorHeap
		//this->InitDescriptorHeap();

	}

	void DX12Renderer::Render(double dt)
	{

	}

}

