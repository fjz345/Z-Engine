#ifndef LOGGING_H
#define LOGGING_H

#include <string>
#include <iostream>

#define ZE_ERROR(msg)
#define ZE_WARNING(msg)
#define ZE_LOG(msg)

#define ZE_ASSERT(x, ...)

#ifdef _DEBUG
#define CreateLog(type, prefix)	static void ZE_Log##type(std::string msg) {std::cout << ##prefix << msg << std::endl;}\
								static void ZE_Log##type(std::wstring msg) {std::wcout << ##prefix << msg << std::endl;}

	CreateLog(Error, "[ERROR]: ")
	CreateLog(Warning, "[Warning]: ")
	CreateLog(, "")

	#define ZE_ENABLE_ASSERTS

	#define ZE_ERROR(msg) ZE_LogError(msg);
	#define ZE_WARNING(msg) ZE_LogWarning(msg);
	#define ZE_LOG(msg) ZE_Log(msg);
#endif

#ifdef ZE_ENABLE_ASSERTS
	#define ZE_ASSERT(x, ...) { if(!(x)) { ZE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#endif


#endif