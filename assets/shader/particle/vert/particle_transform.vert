#ifdef ANDROID

#endif

#ifdef WIN

#endif

layout(location = 0) in vec2 aLocalPos;
layout(location = 1) in vec3 aWorldPos;
layout(location = 2) in float aRotation;
layout(location = 3) in float aSize;

uniform mat4 projectionView;
uniform vec3 cameraRight;
uniform vec3 cameraUp;

out vec2 TexCoord;
out vec4 Color;

void main() {

    vec2 offset = aLocalPos * aSize;

    float cosR = cos(aRotation);
    float sinR = sin(aRotation);

    // Rotate the local position
    vec2 rotated;
    rotated.x = offset.x * cosR - offset.y * sinR;
    rotated.y = offset.x * sinR + offset.y * cosR;

    // Offset in world space
    vec3 finalPos = aWorldPos + cameraRight * rotated.x + cameraUp * rotated.y;

    gl_Position = projectionView * vec4(finalPos, 1.0);

    TexCoord = aLocalPos + 0.5;
    Color = vec4(1.0);
}