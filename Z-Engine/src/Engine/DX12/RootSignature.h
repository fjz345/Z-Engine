#ifndef ROOTSIGNATURE_H
#define ROOTSIGNATURE_H

namespace ZE
{
	enum RS
	{
		RC32_0, // 16 Root Constants
		RC32_1,
		RC32_2,
		RC32_3,
		RC32_4,
		RC32_5,
		RC32_6,
		RC32_7,
		RC32_8,
		RC32_9,
		RC32_10,
		RC32_11,
		RC32_12,
		RC32_13,
		RC32_14,
		RC32_15,
		CBVS,
		// Per Lampor // Per Scene
		// Per Object

		NUM_PARAMS
	};

	class RootSignature
	{
	public:
		RootSignature(ID3D12Device5* device);
		~RootSignature();

		inline ID3D12RootSignature* GetRootSig() { return this->rootSig; }
		inline ID3DBlob* GetBlob() { return this->blob; }

	private:
		// Rootsignature
		ID3D12RootSignature* rootSig;
		ID3DBlob* blob;
		void SetupRootParmas();
	};
}

#endif