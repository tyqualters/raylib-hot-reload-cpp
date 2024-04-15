#include "main.hpp"

#include <raylib.h>
#include <stdexcept>

EXPORT_LIB void libmain(void* args, size_t argc) {
    if(argc == 0) throw std::runtime_error("Hot Reload Library missing arguments");

    Shader shader = *static_cast<Shader*>(args);

    ClearBackground(BLUE); // Try changing this value with rltest running
    auto mousePos = GetMousePosition();
    auto bounds = Vector2{static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())};
    TraceLog(LOG_DEBUG, "Mouse Position: {%.00f, %.00f}", mousePos.x, mousePos.y);
    TraceLog(LOG_DEBUG, "Screen Size:    {%d, %d}", static_cast<int>(bounds.x), static_cast<int>(bounds.y));
    BeginShaderMode(shader);
    SetShaderValueV(shader, 1, &mousePos, SHADER_UNIFORM_VEC2, 1);
    SetShaderValueV(shader, 2, &bounds, SHADER_UNIFORM_VEC2, 1);
    DrawRectanglePro({0, 0, 100, 100},{0,0}, 0, WHITE);
    EndShaderMode();
}