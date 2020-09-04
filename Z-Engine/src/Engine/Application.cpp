#include "Application.h"

#include "Window.h"
#include "DX12/DX12Renderer.h"
#include "Event.h"
#include "Timer.h"

namespace ZE
{

	Application::Application()
	{
		Timer::Init();
		_window = Window::Create(L"HEJ", 800, 600);
		_renderer = Renderer::Create(_window);
	}

	Application::~Application()
	{
		delete _window;
	}

	void Application::Run()
	{
		this->_isRunning = true;

		Timer appTimer;
		appTimer.Start();
		double dt, last_dt = 0;

		while (_isRunning)
		{
			// DT
			double now_dt = appTimer.GetElapsedTime();
			dt = now_dt - last_dt;
			last_dt = now_dt;

			// Update

			_window->Update();

			// Render
			_renderer->Render(dt);

		}

	}

	void Application::Update(double dt)
	{

	}
}

