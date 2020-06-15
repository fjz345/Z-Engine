#include "CommandRecorder.h"

ZE::CommandRecorder::CommandRecorder(ID3D12Device5* device, D3D12_COMMAND_LIST_TYPE type)
{
	for (UINT i = 0; i < NUM_SWAP_BUFFERS; i++)
	{
		HRESULT hr = device->CreateCommandAllocator(type, IID_PPV_ARGS(&this->commandAllocators[i]));

		hr = device->CreateCommandList(0,
			type,
			this->commandAllocators[i],
			nullptr,
			IID_PPV_ARGS(&this->commandLists[i]));

		this->commandLists[i]->Close();
	}
}

ZE::CommandRecorder::~CommandRecorder()
{
	for (unsigned int i = 0; i < NUM_SWAP_BUFFERS; i++)
	{
		SAFE_RELEASE(&this->commandAllocators[i]);
		SAFE_RELEASE(&this->commandLists[i]);
	}
}

ID3D12GraphicsCommandList5* ZE::CommandRecorder::GetCommandList(int index)
{
	return this->commandLists[index];
}

ID3D12CommandAllocator* ZE::CommandRecorder::GetCommandAllocator(int index)
{
	return commandAllocators[index];
}
