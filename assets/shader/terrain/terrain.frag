#ifdef ANDROID
precision mediump float;
#endif

#ifdef WIN

#endif

out vec4 FragColor;
uniform sampler2D heightmap;
in vec2 WorldPos2D;


void main(){

    vec2 uv = WorldPos2D / vec2(textureSize(heightmap, 0));

    float heightmapSample = texture(heightmap, uv).r;

    FragColor = vec4(vec3(1.0), 1.0);
}