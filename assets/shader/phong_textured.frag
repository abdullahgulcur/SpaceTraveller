#ifdef ANDROID
precision mediump float;
#endif

#ifdef WIN

#endif

uniform sampler2D tex;
uniform vec3 cameraPosition;


in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

out vec4 FragColor;

void main()
{
    float ambient = 0.5;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(vec3(-1.0, 1.0, -1.0));

    float diffuse = max(dot(norm, lightDir), 0.0);

    vec3 albedo = texture(tex, TexCoord).rgb;
    vec3 result = albedo * (ambient + diffuse);
    FragColor = vec4(result, 1.0);
}