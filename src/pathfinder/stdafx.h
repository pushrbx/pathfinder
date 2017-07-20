#ifndef STDAFX_H
#define STDAFX_H

#ifdef _MSC_VER
#	ifdef ASECW_EXPORTS
#		define PF_API __declspec(dllexport)
#	else
#		define PF_API __declspec(dllimport)
#	endif
#else
#   ifdef __MINGW32__
#       define PF_API __declspec(dllexport)
#   else
#	    if defined(HAVE_GCCVISIBILITYPATCH) || __GNUC__ >= 4
#		    define PF_API __attribute__ ((visibility ("default")))
#	    else
#		    define PF_API
#	    endif
#   endif
#endif

// linker fix ref: http://stackoverflow.com/questions/2991927/how-to-force-inclusion-of-an-object-file-in-a-static-library-when-linking-into-e
#if defined(_WIN32)
# if defined(_WIN64)
#  define FORCE_UNDEFINED_SYMBOL(x) __pragma(comment (linker, "/export:" #x))
# else
#  define FORCE_UNDEFINED_SYMBOL(x) __pragma(comment (linker, "/export:_" #x))
# endif
#else
# define FORCE_UNDEFINED_SYMBOL(x) extern "C" void x(void); void (*__ ## x ## _fp)(void)=&x;
#endif

#ifdef _MSC_VER
	typedef unsigned __int8		_UInt8;
	typedef unsigned __int16	_UInt16;
	typedef unsigned __int32	_UInt32;
	typedef unsigned __int64	_UInt64;
#else
#	include <stdint.h>
	typedef uint8_t		_UInt8;
	typedef uint16_t	_UInt16;
	typedef uint32_t	_UInt32;
	typedef uint64_t	_UInt64;
#endif

#define _False			0
#define _True			1

#define __DEFAULT_VIEW_SIZE 131072
#define __DEFAULT_COPY_BUFFER_SIZE 131072

#ifndef NULL
#define NULL nullptr
#endif

#endif