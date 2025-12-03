#ifdef ANDROID

#endif

#ifdef WIN

#endif

layout (location = 0) in vec2 aLocalPos;

uniform float rotation;
uniform vec2 position;
uniform float scale;

out vec2 vUV;

void main(void)
{
    // Apply scale
    vec2 scaledPos = aLocalPos * scale;

    // Apply rotation
    float c = cos(rotation);
    float s = sin(rotation);
    vec2 rotatedPos = vec2(scaledPos.x * c - scaledPos.y * s, scaledPos.x * s + scaledPos.y * c);

    // Translate to final position
    vec2 worldPos = rotatedPos + position;

    // Convert to clip coordinates:
    // position is expected in screen coordinates (e.g. pixels)
    // so convert to range [-1, 1]
    vec2 clipPos = worldPos;

    gl_Position = vec4(clipPos, 0.0, 1.0);

    // UV coordinates from local position
    vUV = aLocalPos * 0.5 + 0.5;
}