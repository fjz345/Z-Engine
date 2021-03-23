#ifndef RENDERTARGET_H
#define RENDERTARGET_H


namespace ZE
{
    class DescriptorHeap;

    class RenderTarget
    {
    public:
        RenderTarget(ID3D12Device5* device, unsigned int width, unsigned int height, unsigned int nrOfResources);
        RenderTarget() {} // Don't use
        virtual ~RenderTarget();

        inline D3D12_VIEWPORT* GetViewPort() { return &viewport; }
        inline D3D12_RECT* GetScissorRect() { return &scissorRect; }
        inline DescriptorHeap* GetDescriptorHeap() { return dHeap; }
        inline ID3D12Resource1* GetResourceAt(unsigned int index) { return resources[index]; }

        void SetViewport(unsigned int width, unsigned int height);
        void SetScissorRect(unsigned int width, unsigned int height);

    protected:
        DescriptorHeap* dHeap = nullptr;
        std::vector<ID3D12Resource1*> resources;

        D3D12_VIEWPORT viewport = {};
        D3D12_RECT scissorRect = {};

        unsigned int width = 0;
        unsigned int height = 0;
    };
}


#endif //RENDERTARGET_H