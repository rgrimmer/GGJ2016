#ifndef __EXTENSION_H
#define __EXTENSION_H

#if defined(_WIN32)
#	if defined(ExtGGJ2016_EXPORTS)
#		define EXTENSION_GGJ2016_EXPORT __declspec(dllexport)
#	else
#		define EXTENSION_GGJ2016_EXPORT __declspec(dllimport)
#	endif // ExtGGJ2016_EXPORTS
#else // defined(_WIN32)
#	define EXTENSION_GGJ2016_EXPORT
#endif

extern "C"
{
	EXTENSION_GGJ2016_EXPORT void	ExtensionInitialize		(void);
	EXTENSION_GGJ2016_EXPORT void	ExtensionRelease		(void);
}

#endif // __EXTENSION_H
