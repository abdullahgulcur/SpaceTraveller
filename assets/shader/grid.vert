#ifdef ANDROID

#endif

#ifdef WIN

#endif

layout (location = 0) in vec3 aPos;

uniform mat4 projectionView;

void main()
{
    gl_Position = projectionView * vec4(aPos, 1.0);
}