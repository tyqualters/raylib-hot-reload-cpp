#version 430

layout(location = 0) in vec2 pos;
layout(location = 1) uniform vec2 mousePosition;
layout(location = 2) uniform vec2 bounds;
out vec4 fragColor;

void main() {
    fragColor = vec4(mousePosition.xy/bounds.xy, 0.0f, 1.0f);
}