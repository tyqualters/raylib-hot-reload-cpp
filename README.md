# raylib hot reload example

## About

Update 20 Apr 24: I uploaded [another repository](https://github.com/tyqualters/raylib-hot-reload-cpp-2) where I have a bit more detailed implementation, including some stuff for Windows. Likewise, it was only tested on Linux, but at least most of the groundwork was laid. Hope you enjoy :)

It's still not perfect, but it still might be nice for minor development.

--

This project is an example using raylib and C++ to showcase hot reloading.

In this case, hot reloading is **only supported on Linux** (and likely any other portable POSIX compliant operating system).

To support Windows, you would just have to replace `dlopen` with `LoadLibraryA`, `dlsym` with `GetProcAddress` and `dlclose` with `FreeLibrary` or `FreeLibraryAndExitThread`, and finally, instead of a `void*` it would be a `HMODULE` handle.

## Demonstration

Click to watch.

[![YouTube Video](https://i3.ytimg.com/vi/PaohNqYGpM4/maxresdefault.jpg)](https://www.youtube.com/watch?v=PaohNqYGpM4)
