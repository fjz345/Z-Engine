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
	// ===================================================================================
	// TODO: RS::NUM_PARAMS = 16, fel skall vara 1
	D3D12_ROOT_PARAMETER rootParams[RS::NUM_PARAMS] {};

#pragma region RC32
	for (unsigned int i = 0; i < 16; i++)
	{
		rootParams[i].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
		rootParams[i].Constants.ShaderRegister = i; // b0 - b15
		rootParams[i].Constants.RegisterSpace = 1; // space0
		rootParams[i].Constants.Num32BitValues = 1;
		rootParams[i].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	}
#pragma endregion RC32



	// ===================================================================================

	// CBV Descriptor Table desc
	D3D12_DESCRIPTOR_RANGE dtRangesCBV[1] {};
	dtRangesCBV[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	dtRangesCBV[0].NumDescriptors = -1;
	dtRangesCBV[0].BaseShaderRegister = 0;	// b0
	dtRangesCBV[0].RegisterSpace = 0;		// space0

	D3D12_ROOT_DESCRIPTOR_TABLE dtCBV = {};
	dtCBV.NumDescriptorRanges = ARRAYSIZE(dtRangesCBV);
	dtCBV.pDescriptorRanges = dtRangesCBV;

	// RS::CBVS
	rootParams[RS::CBVS].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParams[RS::CBVS].DescriptorTable = dtCBV;
	rootParams[RS::CBVS].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	// ===================================================================================

	D3D12_ROOT_SIGNATURE_DESC rsDesc;
	rsDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_NONE;	// We dont use input layout... 
	rsDesc.NumParameters = ARRAYSIZE(rootParams);
	rsDesc.pParameters = rootParams;
	rsDesc.NumStaticSamplers = 0;

	// ===================================================================================

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

	// ===================================================================================

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
