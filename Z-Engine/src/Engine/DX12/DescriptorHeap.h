#ifndef DESCRIPTORHEAP_H
#define DESCRIPTORHEAP_H

namespace ZE
{

    class DescriptorHeap
    {
    public:
        DescriptorHeap(ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors, bool bShaderVisible = false);

        inline ID3D12DescriptorHeap* GetID3D12DescriptorHeap() { return _dHeap; }
        inline D3D12_CPU_DESCRIPTOR_HANDLE GetCDHAt(UINT index)
        {
            D3D12_CPU_DESCRIPTOR_HANDLE atCPU;
            atCPU.ptr = _hCPUHeapStart.ptr + index * _handleIncrementSize;
            return atCPU;
        }

        inline D3D12_GPU_DESCRIPTOR_HANDLE GetGDHAt(UINT index)
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