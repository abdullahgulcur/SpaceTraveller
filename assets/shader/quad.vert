#version 320 es
layout(location = 0) in vec2 aLocalPos;

out vec2 vUV;

void main() {
    vUV = (aLocalPos + 1.0) * 0.5;
    gl_Position = vec4(aLocalPos.x, aLocalPos.y, 0.0, 1.0);
}