#include "PipelineState.h"

namespace ZE
{
	PipelineState::PipelineState(ID3D12Device5* device, RootSignature* rootSignature, LPCWSTR VSName, LPCWSTR PSName, D3D12_GRAPHICS_PIPELINE_STATE_DESC* gpsd)
	{
		this->name = L"GraphicsPSO";

		// Set the rootSignature in the pipeline state object descriptor
		this->gpsd = *gpsd;

		this->gpsd.pRootSignature = rootSignature->GetRootSig();

		this->CreateShader(VSName, ShaderType::VS);
		this->CreateShader(PSName, ShaderType::PS);

		ID3DBlob* vsBlob = this->VS->GetBlob();
		ID3DBlob* psBlob = this->PS->GetBlob();

		this->gpsd.VS.pShaderBytecode = vsBlob->GetBufferPointer();
		this->gpsd.VS.BytecodeLength = vsBlob->GetBufferSize();
		this->gpsd.PS.pShaderBytecode = psBlob->GetBufferPointer();
		this->gpsd.PS.BytecodeLength = psBlob->GetBufferSize();

		// Create pipelineStateObject
		HRESULT hr = device->CreateGraphicsPipelineState(&this->gpsd, IID_PPV_ARGS(&this->PSO));

		this->PSO->SetName(this->name);
		if (!SUCCEEDED(hr))
		{
			OutputDebugStringW(L"Failed to create GraphicsPSO");
		}
	}

	PipelineState::~PipelineState()
	{
		SAFE_RELEASE(&this->PSO);
	}

	void PipelineState::CreateShader(std::wstring fileName, ShaderType type)
	{
		// TODO: better path management
		fileName = L"../" + fileName;

		if (type == ShaderType::VS)
		{
			this->VS = new Shader(fileName, type);
		}
		else if (type == ShaderType::PS)
		{
			this->PS = new Shader(fileName, type);
		}
		else if (type == ShaderType::CS)
		{
			this->CS = new Shader(fileName, type);
		}
	}

	ID3D12PipelineState* PipelineState::GetPSO()
	{
		return this->PSO;
	}

	D3D12_GRAPHICS_PIPELINE_STATE_DESC* PipelineState::GetGpsd()
	{
		return &this->gpsd;
	}

	D3D12_COMPUTE_PIPELINE_STATE_DESC* PipelineState::GetCpsd()
	{
		return &this->cpsd;
	}

	Shader* PipelineState::GetShader(ShaderType type)
	{
		if (type == ShaderType::VS)
		{
			return this->VS;
		}
		else if (type == ShaderType::PS)
		{
			return this->PS;
		}
		else if (type == ShaderType::CS)
		{
			return this->CS;
		}

		return nullptr;
	}


}
