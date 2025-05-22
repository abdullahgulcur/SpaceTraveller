#ifdef ANDROID
precision mediump float;
#endif

#ifdef WIN

#endif

layout(location = 0) in vec2 aLocalPos;
layout(location = 1) in vec3 aWorldPos;
layout(location = 2) in vec4 aColor;
layout(location = 3) in float aSize;

uniform mat4 projectionView;
uniform vec3 cameraRight;
uniform vec3 cameraUp;

out vec2 TexCoord;
out vec4 Color;

void main() {
    // Scale the local position
    vec2 offset = aLocalPos * aSize;

    // No rotation, so directly offset along camera right/up vectors
    vec3 finalPos = aWorldPos + cameraRight * offset.x + cameraUp * offset.y;

    gl_Position = projectionView * vec4(finalPos, 1.0);

    TexCoord = aLocalPos + 0.5;
    Color = aColor;
}