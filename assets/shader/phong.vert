#version 320 es
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexcoord;
layout (location = 3) in mat4 aInstanceMatrix;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

//uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(aInstanceMatrix * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(aInstanceMatrix))) * aNormal;
    TexCoord = aTexcoord;

    gl_Position = projection * view * vec4(FragPos, 1.0);
}