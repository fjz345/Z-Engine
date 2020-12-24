#include "CommandRecorder.h"

ZE::CommandRecorder::CommandRecorder(ID3D12Device5* device, D3D12_COMMAND_LIST_TYPE type)
{
	for (UINT i = 0; i < NUM_SWAP_BUFFERS; i++)
	{
		HRESULT hr = device->CreateCommandAllocator(type, IID_PPV_ARGS(&this->_commandAllocators[i]));

		hr = device->CreateCommandList(0,
			type,
			this->_commandAllocators[i],
			nullptr,
			IID_PPV_ARGS(&this->_commandLists[i]));

		this->_commandLists[i]->Close();
	}
}

ZE::CommandRecorder::~CommandRecorder()
{
	for (unsigned int i = 0; i < NUM_SWAP_BUFFERS; i++)
	{
		SAFE_RELEASE(&this->_commandAllocators[i]);
		SAFE_RELEASE(&this->_commandLists[i]);
	}
}

void ZE::CommandRecorder::Reset(int index)
{
	_commandAllocators[index]->Reset();
	_commandLists[index]->Reset(_commandAllocators[index], NULL);
}

ID3D12GraphicsCommandList5* ZE::CommandRecorder::GetCommandList(int index)
{
	return this->_commandLists[index];
}

ID3D12CommandAllocator* ZE::CommandRecorder::GetCommandAllocator(int index)
{
	return this->_commandAllocators[index];
}
