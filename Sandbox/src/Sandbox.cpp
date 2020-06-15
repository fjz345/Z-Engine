#include <ZEngine.h>

class Sandbox : public ZE::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}

private:

};

ZE::Application* ZE::CreateApplication()
{
	std::wstring h = L"WSTRING";


	ZE::Application* a = new Sandbox();

	return a;
}