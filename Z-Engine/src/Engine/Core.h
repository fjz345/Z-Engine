#ifndef CORE_H
#define CORE_H

#include "zepch.h"
#ifdef ZE_PLATFORM_WINDOWS
//HINSTANCE gHInstance;
//int gNCmdShow;
#endif

#ifdef ZE_PLATFORM_WINDOWS
	#ifdef ZE_BUILD_DLL
		#define ZE_API __declspec(dllexport)
	#else
		#define ZE_API __declspec(dllimport)
	#endif
#else
	#error Only supports Windows!
#endif




#define BIT(x) (1 << x)

#endif // CORE_H