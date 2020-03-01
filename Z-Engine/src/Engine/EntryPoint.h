#pragma once

#ifdef ZE_PLATFORM_WINDOWS

extern ZE::Application* ZE::CreateApplication();

int main()
{
	ZE::Application* app = ZE::CreateApplication();
	app->Run();
	delete app;
}

#endif