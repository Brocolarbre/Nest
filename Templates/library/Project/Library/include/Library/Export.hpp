#pragma once

#ifdef _WIN32
	#ifdef LIBRARY_STATIC
		#define LIBRARY_EXPORT
	#else
		#ifdef LIBRARY_EXPORT
			#define LIBRARY_EXPORT __declspec(dllexport)
		#else
			#define LIBRARY_EXPORT __declspec(dllimport)
		#endif
	#endif
#elif __linux__
	#define LIBRARY_EXPORT
#endif