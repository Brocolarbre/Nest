#pragma once

#if defined(_WIN32)
	#if defined(LIBRARY_STATIC)
		#define LIBRARY_API
	#elif defined(LIBRARY_BUILD)
		#define LIBRARY_API __declspec(dllexport)
	#else
		#define LIBRARY_API __declspec(dllimport)
	#endif
#else
	#define LIBRARY_API __attribute__((visibility("default")))
#endif