#include "Application.h"

#include "Window.h"
#include "DX12/DX12Renderer.h"
#include "Event.h"
#include "Timer.h"

namespace ZE
{

	Application::Application()
	{
		_window = Window::Create(L"HEJ", 800, 600);
		_renderer = Renderer::Create(_window);

		Timer::Init();
		_appTimer = new Timer();
		_appTimer->Start();
	}

	Application::~Application()
	{
		delete _renderer;
		delete _window;
		delete _appTimer;
	}

	void Application::Run()
	{
		_isRunning = true;

		double dt = 0;
		double time_last = 0;
		double time_now = 0;

		while (_isRunning)
		{
			// DT
			time_now = _appTimer->GetElapsedTime();
			dt = time_now - time_last;
			time_last = time_now;

			// FPS counter
			_frameCounter++;
			float avgFPS = _frameCounter / time_now;
			_window->SetWindowTitle(std::to_wstring(avgFPS));

			// Events


			// Update
			Update(dt);
			_window->Update(dt);

			// Render
			_renderer->Render(dt);
		}
	}

	void Application::Update(double dt)
	{
		
	}
}

