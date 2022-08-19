#pragma once

#include "../Renderer.h"

#include "DescriptorHeap.h"
#include "Resource.h"
#include "CommandRecorder.h"
#include "SwapChain.h"
#include "RootSignature.h"
#include "PipelineState.h"

#if _DEBUG
#include "dxgidebug.h"
#endif

namespace ZE
{
	class DX12Renderer : public Renderer
	{
	public:
		DX12Renderer(Window* renderTarget);
		~DX12Renderer();

		void Render(double dt);

	private:
		// Device
		ID3D12Device5* _device = nullptr;

		// Command Queue
		ID3D12CommandQueue* _commandQueue = nullptr;
		
		// CommandRecorder
		CommandRecorder* _commandRecorder = nullptr;

		// DescriptorHeap
		DescriptorHeap* _commonHeap = nullptr;

		// SwapChain
		SwapChain* _swapChain = nullptr;

		// TEMP
		RootSignature* _rootSig = nullptr;
		PipelineState* _pipelineState = nullptr;
		DescriptorHeap* _dsvHeap = nullptr;

		Resource* _depthResource = nullptr;

		// Fences
		ID3D12Fence1* _fenceFrame = nullptr;
		UINT64 _fenceFrameValue = 0;
		HANDLE _eventHandle = nullptr;

		// Init functions
		void InitDevice();
		void InitCommandQueue();
		void InitDepthBuffer();
		void InitPipelineStates();

		void WaitForFrame(unsigned int framesToBeAhead);
		void WaitForGPU(); // Halts execution
	};

	

}


