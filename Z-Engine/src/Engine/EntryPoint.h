#pragma once

#include "zepch.h"
#include "Core.h"

#include "Application.h"
#include "Logging.h"

extern ZE::Application* ZE::CreateApplication();

#if 0//ZE_PLATFORM_WINDOWS

int WINAPI main(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
	//gHInstance = hInstance;
	//gNCmdShow = nCmdShow;

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
