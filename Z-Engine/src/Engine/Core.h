#ifndef CORE_H
#define CORE_H

#include <iostream>

#ifdef ZE_PLATFORM_WINDOWS
	#ifdef ZE_BUILD_DLL
		#define ZE_API __declspec(dllexport)
	#else
		#define ZE_API __declspec(dllimport)
	#endif
#else
	#error Only supports Windows!
#endif


#ifdef _DEBUG
	#define ZE_ERROR(msg) std::cout << "[ERROR]: " << msg << std::endl;
#else
	#define ZE_ERROR(msg)
#endif





#endif