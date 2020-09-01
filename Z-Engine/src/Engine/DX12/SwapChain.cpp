#include "SwapChain.h"

#include "DescriptorHeap.h"

ZE::SwapChain::SwapChain(ID3D12Device5* device, HWND* hwnd, ID3D12CommandQueue* directQueue)
{
	this->dHeap = new DescriptorHeap(device, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, NUM_SWAP_BUFFERS);
	this->resources.resize(NUM_SWAP_BUFFERS);

	RECT rect;
	if (GetWindowRect(*hwnd, &rect))
	{
		this->width = rect.right - rect.left;
		this->height = rect.bottom - rect.top;
	}

	IDXGIFactory4* factory = nullptr;
	HRESULT hr = CreateDXGIFactory(IID_PPV_ARGS(&factory));

	if (hr != S_OK)
	{
		OutputDebugStringA("Error: Failed to create DXGIFactory!\n");
	}

	//Create descriptor
	
	DXGI_SWAP_CHAIN_DESC1 scDesc = {};
	scDesc.BufferCount = NUM_SWAP_BUFFERS;
	scDesc.Width = width;
	scDesc.Height = height;
	scDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	scDesc.SampleDesc.Count = 1;

	IDXGISwapChain1* swapChain1 = nullptr;
	HRESULT a = S_OK;
	
	a = factory->CreateSwapChainForHwnd(directQueue, *hwnd, &scDesc, nullptr, nullptr, &swapChain1);
	if (SUCCEEDED(a))
	{
		if (SUCCEEDED(swapChain1->QueryInterface(IID_PPV_ARGS(&swapChain))))
		{
			swapChain->Release();
		}
	}
	else
	{
		OutputDebugStringA("Error: Failed to create SwapChain!\n");
	}

	SAFE_RELEASE(&factory);

	// Connect the renderTargets to the swapchain, so that the swapchain can easily swap between these two renderTargets
	for (UINT i = 0; i < NUM_SWAP_BUFFERS; i++)
	{
		HRESULT hr = swapChain->GetBuffer(i, IID_PPV_ARGS(&this->resources[i]));
		if (hr != S_OK)
		{
			OutputDebugStringA("Error: Failed to GetBuffer from RenderTarget to Swapchain!\n");
		}

		D3D12_CPU_DESCRIPTOR_HANDLE cdh = this->dHeap->GetCDHAt(i);
		device->CreateRenderTargetView(this->resources[i], nullptr, cdh);
	}

	this->CreateViewport(this->width, this->height);
	this->CreateScissorRect(this->width, this->height);
}

ZE::SwapChain::~SwapChain()
{
	SAFE_RELEASE(&this->swapChain);
}

IDXGISwapChain4* ZE::SwapChain::GetDXGISwapChain()
{
	return this->swapChain;
}
