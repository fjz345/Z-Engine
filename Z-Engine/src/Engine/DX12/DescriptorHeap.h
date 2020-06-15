#ifndef DESCRIPTORHEAP_H
#define DESCRIPTORHEAP_H

namespace ZE
{

    class DescriptorHeap
    {
    public:
        DescriptorHeap() { memset(this, 0, sizeof(*this)); }

        HRESULT Create(ID3D12Device* pDevice, D3D12_DESCRIPTOR_HEAP_TYPE Type, UINT NumDescriptors, bool bShaderVisible = false)
        {
            D3D12_DESCRIPTOR_HEAP_DESC Desc;
            Desc.Type = Type;
            Desc.NumDescriptors = NumDescriptors;
            Desc.Flags = (D3D12_DESCRIPTOR_HEAP_FLAGS)(bShaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : 0);

            HRESULT hr = pDevice->CreateDescriptorHeap(&Desc, IID_PPV_ARGS(&this->_dHeap));

            if (FAILED(hr)) return hr;

            _hCPUHeapStart = _dHeap->GetCPUDescriptorHandleForHeapStart();
            _hGPUHeapStart = _dHeap->GetGPUDescriptorHandleForHeapStart();

            _handleIncrementSize = pDevice->GetDescriptorHandleIncrementSize(Desc.Type);
            return hr;
        }

        //operator ID3D12DescriptorHeap* () { return _dHeap; }

        D3D12_CPU_DESCRIPTOR_HANDLE hCPUAt(UINT index)
        {
            D3D12_CPU_DESCRIPTOR_HANDLE atCPU;
            atCPU.ptr = _hCPUHeapStart.ptr + index * _handleIncrementSize;
            return atCPU;
        }
        D3D12_GPU_DESCRIPTOR_HANDLE hGPUAt(UINT index)
        {
            assert(_desc.Flags & D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE);
            D3D12_GPU_DESCRIPTOR_HANDLE atGPU;
            atGPU.ptr = _hGPUHeapStart.ptr + index * _handleIncrementSize;
            return atGPU;
        }

        ID3D12DescriptorHeap* _dHeap;
        D3D12_DESCRIPTOR_HEAP_DESC _desc;

        D3D12_CPU_DESCRIPTOR_HANDLE _hCPUHeapStart;
        D3D12_GPU_DESCRIPTOR_HANDLE _hGPUHeapStart;
        UINT _handleIncrementSize;
    };
}


#endif