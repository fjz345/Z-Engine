#pragma once

#include "../Renderer.h"

#include "DescriptorHeap.h"

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
		std::map<D3D12_COMMAND_LIST_TYPE, ID3D12CommandQueue*> commandQueues;
		
		// Command List
		std::vector<ID3D12CommandList*> directCommandLists[NUM_SWAP_BUFFERS];

		// Command Allocator


		// DescriptorHeap
		DescriptorHeap* descriptorHeap = nullptr;

		// Fences
		HANDLE eventHandle = nullptr;
		ID3D12Fence1* fenceFrame = nullptr;
		UINT64 fenceFrameValue = 0;
	};

	

}


