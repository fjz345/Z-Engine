#pragma once

namespace ZE
{
	class CommandRecorder
	{
	public:
		CommandRecorder(ID3D12Device5* device, D3D12_COMMAND_LIST_TYPE interfaceType);
		~CommandRecorder();

		void Reset(int index);

		ID3D12GraphicsCommandList5* GetCommandList(int index);
		ID3D12CommandAllocator* GetCommandAllocator(int index);

	private:
		ID3D12GraphicsCommandList5* _commandLists[NUM_SWAP_BUFFERS] { nullptr };
		ID3D12CommandAllocator* _commandAllocators[NUM_SWAP_BUFFERS] { nullptr };
	};
}