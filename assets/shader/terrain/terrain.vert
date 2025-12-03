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
uniform sampler2D heightmap;

out vec2 WorldPos2D;
out vec3 WorldPos;
out vec3 WorldNormal;

void main(void)
{
    vec2 worldPos2D = (posVert + posInstance * blockSize) * (1 << levelInstance);

    //vec2 uv = worldPos2D / vec2(1024.0, 1024.0);

    vec2 uv = worldPos2D / vec2(textureSize(heightmap, 0));
    //UV = uv;// / vec2(16.0, 16.0) ;

    float heightmapSample = texture(heightmap, uv).r;

    float heightF = heightmapSample * 30.0;

    WorldPos = vec3(worldPos2D.x, heightF, worldPos2D.y);
    WorldPos2D = worldPos2D;

    gl_Position = projectionView * vec4(WorldPos, 1.0);
}