#ifdef ANDROID

#endif

#ifdef WIN

#endif

layout(location = 0) in vec2 aLocalPos; // Local quad corner (e.g. [-0.5, 0.5])
layout(location = 1) in ivec3 aPos;
layout(location = 2) in uint aAlpha;
layout(location = 3) in uint aRotation;

uniform mat4 projectionView;
uniform vec3 cameraRight;
uniform vec3 cameraUp;
uniform vec3 cameraPosition;

uniform float aspectRatio;

//uniform float scale;

out vec2 TexCoord;
out vec4 Color;

//void main() {
//    // Decode scale from uint16 to float
//    float scale = 1.0;//float(aScale) / 655.35;
//
//    // Decode rotation from uint8 to radians
//    float rotation = float(aRotation) / 255.0 * 6.2831853;
//
//    //// Decode position from int + 1/127 fractional
//    vec3 worldPos = vec3(aPos);
//
//    // Apply size scaling
//    vec2 offset = aLocalPos * scale;
//
//    // Rotate the quad corners
//    float cosR = cos(rotation);
//    float sinR = sin(rotation);
//    vec2 rotated;
//    rotated.x = offset.x * cosR - offset.y * sinR;
//    rotated.y = offset.x * sinR + offset.y * cosR;
//
//    // Build final position
//    vec3 finalPos = worldPos + cameraRight * rotated.x + cameraUp * rotated.y;
//    gl_Position = projectionView * vec4(finalPos, 1.0);
//
//    TexCoord = aLocalPos + 0.5; // assuming local pos is in [-0.5, 0.5]
//    Color = vec4(1.0);
//}

void main() {
    vec3 worldPos = vec3(aPos);

    // Project world position to clip space
    vec4 clipCenter = projectionView * vec4(worldPos, 1.0);

    // Perspective divide to get normalized device coordinates (NDC)
    vec2 ndcCenter = clipCenter.xy / clipCenter.w;

    // Determine a fixed quad size in NDC units (screen size)
    //float scale = 0.005;

    float distance = distance(cameraPosition, worldPos);

    float scale = 0.1 - (distance / 500000.0);

    vec2 screenSize = vec2(scale, scale * aspectRatio); // tweak this (e.g. 0.05 NDC = ~100px on a 1080p screen)
    vec2 offset = aLocalPos * screenSize;

    // Rotate the offset (still in NDC space)
    float rotation = float(aRotation) / 255.0 * 6.2831853;
    float cosR = cos(rotation);
    float sinR = sin(rotation);
    vec2 rotated;
    rotated.x = offset.x * cosR - offset.y * sinR;
    rotated.y = offset.x * sinR + offset.y * cosR;

    // Apply offset in NDC
    vec2 finalNDC = ndcCenter + rotated;

    // Rebuild the clip position
    gl_Position = vec4(finalNDC * clipCenter.w, clipCenter.z, clipCenter.w);

    TexCoord = aLocalPos + 0.5;
    Color = vec4(1.0);
}