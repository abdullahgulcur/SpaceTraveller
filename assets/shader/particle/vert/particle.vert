#ifdef ANDROID

#endif

#ifdef WIN

#endif

layout(location = 0) in vec2 aLocalPos; // Local quad corner (e.g. [-0.5, 0.5])
layout(location = 1) in uint aScale;             // Packed scale: uint16
layout(location = 2) in ivec3 aPosD;             // Integer part of position
layout(location = 3) in ivec3 aPosF;             // Fractional part of position (0–255)
layout(location = 4) in vec4 aColor;             // Normalized RGBA
layout(location = 5) in uint aRotation;          // Packed rotation: uint8

uniform mat4 projectionView;
uniform vec3 cameraRight;
uniform vec3 cameraUp;
uniform float scaleMin;
uniform float scaleMax;

out vec2 TexCoord;
out vec4 Color;

void main() {
    // Decode scale from uint16 to float
    float scale = float(aScale) / 655.35;

    // Decode rotation from uint8 to radians
    float rotation = float(aRotation) / 255.0 * 6.2831853;

    //// Decode position from int + 1/127 fractional
    vec3 worldPos = vec3(aPosD) + vec3(aPosF) / 127.0;

    // Apply size scaling
    vec2 offset = aLocalPos * scale;

    // Rotate the quad corners
    float cosR = cos(rotation);
    float sinR = sin(rotation);
    vec2 rotated;
    rotated.x = offset.x * cosR - offset.y * sinR;
    rotated.y = offset.x * sinR + offset.y * cosR;

    // Build final position
    vec3 finalPos = worldPos + cameraRight * rotated.x + cameraUp * rotated.y;
    gl_Position = projectionView * vec4(finalPos, 1.0);

    TexCoord = aLocalPos + 0.5; // assuming local pos is in [-0.5, 0.5]
    Color = aColor;
}