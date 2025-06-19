#ifdef ANDROID

#endif

#ifdef WIN

#endif


layout (location = 0) in uvec2 posVert;
layout (location = 1) in uvec2 posInstance;
layout (location = 2) in uint levelInstance;

uniform mat4 projectionView;
uniform vec3 cameraPosition;
uniform uint blockSize;

out vec2 WorldPos2D;
out vec3 WorldPos;
out vec3 WorldNormal;

void main(void)
{
    vec2 worldPos2D = (posVert + posInstance * blockSize) * (1 << levelInstance);
    
    uint height = 0;
    float heightF = height * 0.01; 

    WorldPos = vec3(worldPos2D.x, heightF, worldPos2D.y);
    WorldPos2D = worldPos2D;

    gl_Position = projectionView * vec4(WorldPos, 1.0);
}