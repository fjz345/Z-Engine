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
	// Application->Run() is called at main()
	ZE::Application* application = new Sandbox();

	// Load assets
	// Add entities


	return application;
}