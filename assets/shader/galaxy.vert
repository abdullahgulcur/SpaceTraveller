#version 320 es
layout(location = 0) in vec2 aLocalPos;
layout(location = 1) in mat4 aModel;
layout(location = 5) in vec4 aColor;

uniform mat4 view;
uniform mat4 projection;

out vec2 vUV;
out vec4 vColor;

void main() {
    vUV = aLocalPos + 0.5;
    vColor = aColor;
    gl_Position = projection * view * aModel * vec4(aLocalPos.x, 0, aLocalPos.y, 1.0);
}