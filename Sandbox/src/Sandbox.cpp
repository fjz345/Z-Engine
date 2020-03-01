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
	ZE_ERROR("hej");
	return new Sandbox();
}