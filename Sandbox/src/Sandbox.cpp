#include "zepch.h"
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


	ZE_ERROR(h);
	ZE_WARNING(h);
	ZE_LOG(h);

	return new Sandbox();
}