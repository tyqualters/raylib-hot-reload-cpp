//
// Created by ty on 4/15/24.
//

#ifndef MAIN_HPP
#define MAIN_HPP

#ifndef EXTERN_C
#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C extern
#endif
#endif

#if defined(_WIN32)
#if defined(__TINYC__)
#define __declspec(x) __attribute__((x))
#endif

#if defined(BUILD_LIBTYPE_SHARED)
#define EXPORT_LIB EXTERN_C __declspec(dllexport)     // We are building the library as a Win32 shared library (.dll)
#elif defined(USE_LIBTYPE_SHARED)
#define EXPORT_LIB EXTERN_C __declspec(dllimport)     // We are using the library as a Win32 shared library (.dll)
#endif
#else
#if defined(BUILD_LIBTYPE_SHARED)
#define EXPORT_LIB EXTERN_C __attribute__((visibility("default"))) // We are building as a Unix shared library (.so/.dylib)
#endif
#endif

#ifndef EXPORT_LIB
#define EXPORT_LIB EXTERN_C
#endif

#include <cstddef> // size_t

// All the above code is just a bunch of dynamic lib export stuff.
// To export a function, just use EXPORT_LIB before the function declaration.

EXPORT_LIB void libmain(void* args, size_t argc);

#endif //MAIN_HPP
