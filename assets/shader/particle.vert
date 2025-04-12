#version 320 es
layout(location = 0) in vec2 aLocalPos;
layout(location = 1) in vec3 aWorldPos;
layout(location = 2) in float aRotation;
layout(location = 3) in vec4 aColor;
layout(location = 4) in float aSize;

uniform mat4 view;
uniform mat4 projection;

out vec2 vUV;
out vec4 vColor;

void main() {

    vec3 camRight = vec3(view[0][0], view[1][0], view[2][0]);
    vec3 camUp    = vec3(view[0][1], view[1][1], view[2][1]);

    vec2 offset = aLocalPos * aSize;

    float cosR = cos(aRotation);
    float sinR = sin(aRotation);
    vec2 rotated = vec2(offset.x * cosR - offset.y * sinR, offset.x * sinR + offset.y * cosR);

    vec3 worldOffset = camRight * rotated.x + camUp * rotated.y;
    vec3 finalPos = aWorldPos + worldOffset;

    gl_Position = projection * view * vec4(finalPos, 1.0);
    vUV = aLocalPos + 0.5;
    vColor = aColor;
}