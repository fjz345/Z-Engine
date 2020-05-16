#include "zepch.h"

#include "Application.h"
#include "Window.h"

extern ZE::Application* ZE::CreateApplication();

#ifdef ZE_PLATFORM_WINDOWS

HINSTANCE ZE::gHInstance;
int ZE::gNCmdShow;
int WINAPI main(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
	ZE::gHInstance = hInstance;
	ZE::gNCmdShow = nCmdShow;

	ZE::Application* app = ZE::CreateApplication();
	app->Run();
	delete app;
}
#else
int main()
{
	ZE::Application* app = ZE::CreateApplication();
	app->Run();
	delete app;
}
#endif
