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

	// Application->Run() is called at main()
	ZE::Application* a = new Sandbox();

	// Load assets
	// Add entities


	return a;
}