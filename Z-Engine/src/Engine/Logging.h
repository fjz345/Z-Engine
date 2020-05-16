#pragma once

#include "zepch.h"

#define CreateLog(type, prefix)	void Log##type(std::string msg) {std::cout << ##prefix << msg << std::endl;}\
								void Log##type(std::wstring msg) {std::wcout << ##prefix << msg << std::endl;}

CreateLog(Error, "[ERROR]: ")
CreateLog(Warning, "[Warning]: ")
CreateLog(, "")


#ifdef _DEBUG
	#define ZE_ENABLE_ASSERTS 1

	#define ZE_ERROR(msg) LogError(msg);
	#define ZE_WARNING(msg) LogWarning(msg);
	#define ZE_LOG(msg) Log(msg);
#else
	#define ZE_ERROR(msg)
	#define ZE_WARNING(msg)
	#define ZE_LOG(msg)
#endif


#ifdef ZE_ENABLE_ASSERTS
	#define ZE_ASSERT(x, ...) { if(!(x)) { ZE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define ZE_ASSERT(x, ...)
#endif