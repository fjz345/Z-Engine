#ifndef SHADER_H
#define SHADER_H


namespace ZE
{
	enum ShaderType
	{
		VS = 0, 
		PS = 1, 
		CS = 2
	};
	
	class Shader
	{
	public:
		Shader(std::wstring path, ShaderType type);
		~Shader();

		ID3DBlob* GetBlob();

	private:
		ID3DBlob* blob;
		ShaderType type;
		std::wstring path;

		void CompileShader();
	};

#endif
}
