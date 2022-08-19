#ifndef LOGGING_H
#define LOGGING_H

#include <string>
#include <iostream>


#define ZE_ASSERT(x, ...)

#define ZE_ERROR(msg) ()
#define ZE_WARNING(msg) ()
#define ZE_LOG(msg) ()


#ifdef _DEBUG
	#undef ZE_ERROR
	#undef ZE_WARNING
	#undef ZE_LOG

	#define ZE_ENABLE_ASSERTS

#define CreateLog(type, prefix)	static void ZE_Log##type(const std::string& msg) {std::cout << ##prefix << msg << std::endl;}\
								static void ZE_Log##type(const std::wstring& msg) {std::wcout << ##prefix << msg << std::endl;}

	CreateLog(Error, "[ERROR]: ")
	CreateLog(Warning, "[Warning]: ")
	CreateLog(, "")

	
#define ZE_ERROR(msg) ZE_LogError(msg);
#define ZE_WARNING(msg) ZE_LogWarning(msg);
#define ZE_LOG(msg) ZE_Log(msg);
#endif

#ifdef ZE_ENABLE_ASSERTS
	#undef ZE_ASSERT
	#define ZE_ASSERT(x, ...) { if(!(x)) { ZE_ERROR("Assertion Failed: {}"); __debugbreak(); } }
#endif


#endif