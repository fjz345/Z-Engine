#ifndef APPLICATION_H
#define APPLICATION_H

#include "zepch.h"
#include "Core.h"


std::string globalVariable = "HEJ";

namespace ZE
{
	class Window;

	class ZE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();


	private:
		Window* _window = nullptr;

	};

	// To be defined in application
	Application* CreateApplication();
}


#endif