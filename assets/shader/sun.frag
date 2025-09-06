#ifdef ANDROID
precision mediump float;
precision mediump sampler2DArray;
#endif

#ifdef WIN

#endif

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;
out vec4 FragColor;

uniform vec3 cameraPosition;
uniform vec3 color0;
uniform vec3 color1;
uniform vec3 color2;
uniform vec3 color3;
uniform float colorOverlay0;
uniform float colorOverlay1;
uniform float colorPower0;
uniform float colorPower1;
uniform float noiseScale;
uniform float noiseTexIndex;
uniform sampler2DArray texArray;
uniform float fresnelPower;
uniform float fresnelScale;
uniform float fresnelBias;

const float PI = 3.14159265359;

float getNoiseOctave(vec2 uv){
    return texture(texArray, vec3(uv * noiseScale, noiseTexIndex)).r;
    //float noise = texture(texArray, vec3(uv * noiseScale, noiseTexIndex)).r;
    //return noise * texture(texArray, vec3(uv * noiseScale * 0.15, noiseTexIndex)).r;
}

float getNoise(float weight){
    vec2 texcoord = TexCoord * 2.0;
    texcoord.x *= 2.0;
    float noiseFromUV = getNoiseOctave(texcoord);
    float noise = getNoiseOctave(vec2(FragPos.x, FragPos.z));
    return mix(noiseFromUV, noise, weight);
}

float getPoleBlend(vec3 normal){
    vec3 weight = abs(normal);
    return (weight / (weight.x + weight.y + weight.z)).y;
}

float applyFilter(float noise){
    return clamp(pow(noise, colorPower0) * colorOverlay0, 0.0, 1.0);
}

float applyFilter1(float noise){
    return clamp(pow(noise, colorPower1) * colorOverlay1, 0.0, 1.0);
}

float fresnel(float power, float scale, float bias){
    vec3 viewDir = normalize(cameraPosition - FragPos);
    float viewAngle = 1.0 - dot(viewDir, normalize(Normal));
    return smoothstep(power, bias, viewAngle) * scale;
}

void main()
{
    vec3 normal = normalize(Normal);
    float weight = getPoleBlend(normal);

    float height = getNoise(weight);

    height = applyFilter(height);


    vec3 col = mix(color0, color1, height);

    height = applyFilter1(height);

    col = mix(col, color2, height);

    float fresnelBlend = fresnel(fresnelPower, fresnelScale, fresnelBias);
    col = mix(col, color3, fresnelBlend);

    FragColor = vec4(vec3(col), 1.0);
}