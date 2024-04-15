#include <iostream>
#include <filesystem>
#include <raylib.h>
#include <raymath.h>

#include <dlfcn.h> // Only Linux right now. Windows would be a similar process with LoadLibraryA
#include <thread>

#define LIBNAME "Game/libhotreload.so" // This is the hot reload library

typedef void(*LIBMAIN_T)(void*, size_t);

LIBMAIN_T libmain = nullptr;

int main() {
    InitWindow(800, 600, "Test Window");

    // This shader is just used as a passthrough to the library to show that \
          it can be used in practically.
    const char* vertShader = nullptr, * fragShader = "../mousegradient.frag";
    Shader shader = LoadShader(vertShader, fragShader);

#ifndef NDEBUG
    SetTraceLogLevel(LOG_DEBUG);
#endif


    // Get the absolute path of the library (required for dlopen)
    auto libpath = std::filesystem::absolute({LIBNAME});

    TraceLog(LOG_INFO, "Configured library path is %s", libpath.c_str());

    auto lastUpdate = std::filesystem::last_write_time(libpath);
    void* handle = nullptr;
loadLibrary:

    // Open a handle to the dynamic library
    handle = dlopen(libpath.c_str(), RTLD_NOW);
    if(!handle) {
        TraceLog(LOG_WARNING, "Library unavailable. Waiting.");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        goto loadLibrary;
    }

    // Get the address of the library's libmain exported function
    libmain = reinterpret_cast<LIBMAIN_T>(dlsym(handle, "libmain"));
    if(!libmain) throw std::runtime_error("libmain not available.");

    auto lastChecked = std::chrono::system_clock::now();
    while(!WindowShouldClose()) {
        BeginDrawing();
        libmain(&shader, 1);
        EndDrawing();

        auto now = std::chrono::system_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastChecked).count();
        if(dur >= 5U) { // every 5 milliseconds check if the file had a write time change
            // make sure that the file is accessible before comparing the write time
            if(!std::filesystem::exists(libpath) || lastUpdate == std::filesystem::last_write_time(libpath)) continue;

            // close the handle and update the new write time
            dlclose(handle);
            lastUpdate = std::filesystem::last_write_time(libpath);
            // reopen the library
            goto loadLibrary;
        }
    }

    // Completely done with the application. Close the handle.
    dlclose(handle);

    CloseWindow();
    return 0;
}