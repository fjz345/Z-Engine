#include "RenderTarget.h"

#include "DescriptorHeap.h"

ZE::RenderTarget::RenderTarget(ID3D12Device5* device, unsigned int width, unsigned int height, unsigned int nrOfResources)
{
	this->dHeap = new DescriptorHeap(device, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, nrOfResources);
	this->resources.resize(nrOfResources);
	this->width = width;
	this->height = height;

	D3D12_HEAP_PROPERTIES heapProp = {};
	heapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
	heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heapProp.CreationNodeMask = 1; //used when multi-gpu
	heapProp.VisibleNodeMask = 1; //used when multi-gpu
	heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

	D3D12_RESOURCE_DESC resourceDesc = {};
	resourceDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	resourceDesc.Width = width;
	resourceDesc.Height = height;
	resourceDesc.DepthOrArraySize = 1;
	resourceDesc.MipLevels = 0;
	resourceDesc.SampleDesc.Count = 1;
	resourceDesc.SampleDesc.Quality = 0;
	resourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;

	// View Desc
	D3D12_RENDER_TARGET_VIEW_DESC viewDesc = {};
	viewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	viewDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

	// Create resource
	for (int i = 0; i < nrOfResources; i++)
	{
		device->CreateCommittedResource(
			&heapProp,
			D3D12_HEAP_FLAG_NONE,
			&resourceDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&this->resources[i])
		);

		D3D12_CPU_DESCRIPTOR_HANDLE cdh = this->dHeap->GetCDHAt(i);
		device->CreateRenderTargetView(this->resources[i], &viewDesc, cdh);
	}

	this->CreateViewport(width, height);
	this->CreateScissorRect(width, height);
}

ZE::RenderTarget::~RenderTarget()
{
	for (int i = 0; i < this->resources.size(); i++)
	{
		SAFE_RELEASE(&this->resources[i]);
	}

	delete this->dHeap;
}

void ZE::RenderTarget::CreateViewport(unsigned int width, unsigned int height)
{
	this->viewport.TopLeftX = 0.0f;
	this->viewport.TopLeftY = 0.0f;
	this->viewport.Width = (float)width;
	this->viewport.Height = (float)height;
	this->viewport.MinDepth = 0.0f;
	this->viewport.MaxDepth = 1.0f;
}

void ZE::RenderTarget::CreateScissorRect(unsigned int width, unsigned int height)
{
	this->scissorRect.left = (long)0;
	this->scissorRect.right = (long)width;
	this->scissorRect.top = (long)0;
	this->scissorRect.bottom = (long)height;
}


