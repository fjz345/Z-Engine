#include "zepch.h"
#include "Application.h"

#include "Window.h"

namespace ZE
{

	Application::Application()
	{
		//_window = Window::Create(L"HEJ", 800, 600);
	}

	Application::~Application()
	{
		delete _window;
	}

	void Application::Run()
	{
		while (true)
		{
			//_window->Update();
		}
	}
}

