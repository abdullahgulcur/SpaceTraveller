#ifdef ANDROID
precision mediump float;
#endif

#ifdef WIN

#endif

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;
out vec4 FragColor;

const float PI = 3.14159265359;

void main()
{
    FragColor = vec4(vec3(1.0, 0.0, 0.0), 1.0);
}