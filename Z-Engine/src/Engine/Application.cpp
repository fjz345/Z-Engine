#include "Application.h"

#include "Window.h"
#include "DX12/DX12Renderer.h"
#include "Event.h"
#include "Timer.h"

namespace ZE
{

	Application::Application()
	{
		_window = Window::Create(L"Z-Engine", 800, 600);
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

		unsigned int fps_frameCounter = 0;
		double fps_last_shown = 0;
		const double fps_updateRate = 1; // seconds / update

		while (_isRunning && !_window->_isQuit)
		{
			fps_frameCounter++;

			// DT
			time_now = _appTimer->GetElapsedTime();
			dt = time_now - time_last;
			time_last = time_now;

			// FPS counter
			// If not updated fps in 2 seconds
			if (time_now - fps_last_shown >= fps_updateRate)
			{
				// Update it
				float avgFPS = fps_frameCounter / (float)(time_now - fps_last_shown);
				_window->SetWindowTitle(std::to_wstring((int)avgFPS));

				// Reset counters
				fps_frameCounter = 0;
				fps_last_shown = time_now;
			}

			// Events
			


			// Update
			Update(dt);

			// Render
			_renderer->Render(dt);
		}
	}

	void Application::Update(double dt)
	{
		_window->Update(dt);
	}
}

