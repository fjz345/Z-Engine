#include "../Application.h"

#include "Win32Window.h"
#include "Win32Functions.h"

extern ZE::Application* ZE::CreateApplication();

int WINAPI main(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ZE::Application* app = ZE::CreateApplication();

	app->Run();

	delete app;
}
