#ifndef SWAPCHAIN_H
#define SWAPCHAIN_H

#include "RenderTarget.h"

namespace ZE
{
	class SwapChain : public RenderTarget
	{
	public:
		SwapChain(ID3D12Device5* device, HWND* hwnd, ID3D12CommandQueue* commandQueue);
		~SwapChain();

		IDXGISwapChain4* GetDXGISwapChain();

	private:
		IDXGISwapChain4* swapChain = nullptr;
	};

}


#endif