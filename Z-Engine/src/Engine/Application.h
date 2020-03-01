#ifndef APPLICATION_H
#define APPLICATION_H

#include "Core.h"

namespace ZE
{
	class ZE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:


	};

	// To be defined in application
	Application* CreateApplication();
}


#endif