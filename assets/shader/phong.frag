#version 320 es
precision mediump float;

uniform sampler2D albedoTexture;

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

uniform vec3 viewPos;

void main()
{
    float ambient = 0.5;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(vec3(-1.0, 1.0, -1.0));

    float diffuse = max(dot(norm, lightDir), 0.0);

    vec3 albedo = texture(albedoTexture, vec2(TexCoord * 1.f)).rgb;
    vec3 result = albedo * (ambient + diffuse);
    FragColor = vec4(result, 1.0);
}