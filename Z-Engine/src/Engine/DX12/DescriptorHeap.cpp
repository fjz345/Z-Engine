#include "DescriptorHeap.h"

ZE::DescriptorHeap::DescriptorHeap(ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors, bool bShaderVisible)
{
    D3D12_DESCRIPTOR_HEAP_DESC _desc = {};
    _desc.Type = type;
    _desc.NumDescriptors = numDescriptors;
    _desc.Flags = (D3D12_DESCRIPTOR_HEAP_FLAGS)(bShaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : 0);

    HRESULT hr = device->CreateDescriptorHeap(&_desc, IID_PPV_ARGS(&this->_dHeap));

    _hCPUHeapStart = _dHeap->GetCPUDescriptorHandleForHeapStart();
    _hGPUHeapStart = _dHeap->GetGPUDescriptorHandleForHeapStart();

    _handleIncrementSize = device->GetDescriptorHandleIncrementSize(_desc.Type);
}

ZE::DescriptorHeap::~DescriptorHeap()
{
    SAFE_RELEASE(&_dHeap);
}
