#pragma once

#include "../Renderer.h"

#include "DescriptorHeap.h"
#include "Resource.h"
#include "CommandRecorder.h"
#include "SwapChain.h"
#include "RootSignature.h"
#include "PipelineState.h"


namespace ZE
{
	class DX12Renderer : public Renderer
	{
	public:
		DX12Renderer(Window* renderTarget);
		~DX12Renderer() {}

		void Render(double dt);

	private:
		// Device
		ID3D12Device5* device = nullptr;

		// Command Queue
		ID3D12CommandQueue* commandQueue = nullptr;
		
		// CommandRecorder
		CommandRecorder* commandRecorder = nullptr;

		// DescriptorHeap
		DescriptorHeap* commonHeap = nullptr;

		// SwapChain
		SwapChain* swapChain = nullptr;

		// TEMP
		RootSignature* rootSig = nullptr;
		PipelineState* pipelineState = nullptr;
		DescriptorHeap* dsvHeap = nullptr;

		Resource* depthResource = nullptr;

		// Fences
		HANDLE eventHandle = nullptr;
		ID3D12Fence1* fenceFrame = nullptr;
		UINT64 fenceFrameValue = 0;

		void WaitForFrame(unsigned int framesToBeAhead);
		void WaitForGPU(); // Halts execution
	};

	

}


