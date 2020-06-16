#ifndef CORE_H
#define CORE_H

#ifdef ZE_PLATFORM_WINDOWS
	#ifdef ZE_BUILD_DLL
		#define ZE_API __declspec(dllexport)
	#else
		#define ZE_API __declspec(dllimport)
	#endif
#else
	#error Only supports Windows!
#endif



#endif // CORE_H