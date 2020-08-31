#include "RootSignature.h"

ZE::RootSignature::RootSignature(ID3D12Device5* device)
{
	this->SetupRootParmas();

	HRESULT hr = device->CreateRootSignature(
		0,
		this->blob->GetBufferPointer(),
		this->blob->GetBufferSize(),
		IID_PPV_ARGS(&this->rootSig));

	if (FAILED(hr))
	{
		OutputDebugStringA("Error: Failed to create RootSignature!\n");
	}
}

ZE::RootSignature::~RootSignature()
{
	SAFE_RELEASE(&this->rootSig);
	SAFE_RELEASE(&this->blob);
}

void ZE::RootSignature::SetupRootParmas()
{
	// TODO: RS::NUM_PARAMS = 16, fel skall vara 1
	D3D12_ROOT_PARAMETER rootParams[1] {};

	rootParams[RS::RC32_0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	rootParams[RS::RC32_0].Constants.ShaderRegister = 0; // b0 - b15
	rootParams[RS::RC32_0].Constants.RegisterSpace = 0; // space0
	rootParams[RS::RC32_0].Constants.Num32BitValues = RS::RC32_15 + 1;
	rootParams[RS::RC32_0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	D3D12_ROOT_SIGNATURE_DESC rsDesc;
	rsDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_NONE;	// We dont use input layout... 
	rsDesc.NumParameters = ARRAYSIZE(rootParams);
	rsDesc.pParameters = rootParams;
	rsDesc.NumStaticSamplers = 0;

	// HUR MAN SKA SAMPLA FRÅN TEXTUR: 
	// D3D12_STATIC_SAMPLER_DESC ssd{};
	// ssd.ShaderRegister = 0;
	// ssd.Filter = D3D12_FILTER_ANISOTROPIC;
	// ssd.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	// ssd.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	// ssd.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	// ssd.ComparisonFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
	// ssd.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	// rsDesc.pStaticSamplers = &ssd;

	ID3DBlob* errorMessages = nullptr;
	HRESULT hr = S_OK;
	hr = D3D12SerializeRootSignature(
		&rsDesc,
		D3D_ROOT_SIGNATURE_VERSION_1,
		&this->blob,
		&errorMessages);

	if (hr != S_OK)
	{
		OutputDebugStringA("Error: Failed to Serialize RootSignature!\n");
	}
}
