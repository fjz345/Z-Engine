#ifndef APPLICATION_H
#define APPLICATION_H

#include "Core.h"

namespace ZE
{
	class Window;
	class Renderer;

	class ZE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void Update(double dt);

	private:
		Window* _window = nullptr;
		Renderer* _renderer = nullptr;
		bool _isRunning = false;

	};

	// To be defined in application
	Application* CreateApplication();
}


#endif