#ifdef ANDROID
precision highp float;
precision mediump sampler2D;
precision mediump sampler2DArray;
#endif

#ifdef WIN

#endif

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2DArray texArray;
uniform vec3 cameraPosition;
uniform vec3 lightDirection;
uniform vec3 waterColor;
uniform vec3 continentalShelfColor;
uniform float amountSea;
uniform float waterContinentalShelf;
uniform vec3 landColor0;
uniform vec3 landColor1;
uniform float landColorOverlay;
uniform float landColorPower;
uniform float surfaceTopologyScale;
uniform float landColorBlendScale;

uniform float macroScale;
uniform float cloudScale;
uniform float cloudPower;
uniform float cloudOverlay;
uniform float cloudOpacity;
uniform vec3 cloudColor;
uniform float fresnelPowerClouds;
uniform float fresnelScaleClouds;
uniform float fresnelBiasClouds;
uniform float fresnelPowerAtmosphere;
uniform float fresnelScaleAtmosphere;
uniform float fresnelBiasAtmosphere;

uniform float noiseOctaveTexIndex0;
uniform float noiseOctaveTexIndex1;

float fresnel(float power, float scale, float bias){
    vec3 viewDir = normalize(cameraPosition - FragPos);
    float viewAngle = 1.0 - dot(viewDir, normalize(Normal));
    return smoothstep(power, bias, viewAngle) * scale;
}

float getSeaBlend(float albedo, float seaAmount){
    return step(albedo, seaAmount);
}

float getContinentalShelfBlend(float albedo, float seaAmount, float continentalShelf){
    continentalShelf = mix(seaAmount, 0.0, continentalShelf);
    return smoothstep(continentalShelf, seaAmount, albedo);
}

vec3 getWeight(vec3 normal){
    vec3 weight = abs(normal);
    return weight / (weight.x + weight.y + weight.z);
}

float getPoleBlend(vec3 normal){
    vec3 weight = abs(normal);
    return (weight / (weight.x + weight.y + weight.z)).y;
}

//float getCloudOctave(vec2 uv){
//    float offset = 123.45; // make it parameter
//    float noise = texture(texArray, vec3(vec2(uv.x, uv.y) * cloudScale + vec2(offset) * 1.0, 1.0)).r;
////    noise *= texture(texArray, vec3(vec2(uv.x, uv.y) * cloudScale * 0.25 + vec2(offset) * 16.0, 1.0)).r;
////    noise *= texture(texArray, vec3(vec2(uv.x, uv.y) * cloudScale * 0.05 + vec2(offset) * 256.0, 1.0)).r;
//    return noise;
//}
//
//float getCloudBlend(vec3 weight){
//    float noise = getCloudOctave(vec2(FragPos.y, FragPos.z)) * weight.x;
//    noise += getCloudOctave(vec2(FragPos.x, FragPos.z)) * weight.y;
//    noise += getCloudOctave(vec2(FragPos.x, FragPos.y)) * weight.z;
//    return clamp(pow(noise * cloudOverlay * amountSea, cloudPower), 0.0, 1.0) * cloudOpacity;
//}

float getCloudBorderBlend(float cloud){
    return step(0.01, cloud) * step(cloud, 0.03);
}

float getNoiseOctave(vec2 uv){
    float noise = texture(texArray, vec3(uv * surfaceTopologyScale, noiseOctaveTexIndex0)).r;
    return noise * texture(texArray, vec3(uv * surfaceTopologyScale * 0.33, noiseOctaveTexIndex1)).r;
}

float getNoise(float weight){
    vec2 texcoord = TexCoord;
    texcoord.x *= 2.0;
    float noiseFromUV = getNoiseOctave(texcoord);
    float noise = getNoiseOctave(vec2(FragPos.x, FragPos.z));
    return mix(noiseFromUV, noise, weight);
}

float getLandColorBlendNoiseOctave(vec2 uv){
    float offset = 0.143; // multiply with seed
    return texture(texArray, vec3(uv * landColorBlendScale + vec2(offset), 1.0)).r;
}

float getLandColorBlend(float weight){
    vec2 texcoord = TexCoord;
    texcoord.x *= 2.0;
    float noiseFromUV = getLandColorBlendNoiseOctave(texcoord);
    float noise = getLandColorBlendNoiseOctave(vec2(FragPos.x, FragPos.z));
    noise = mix(noiseFromUV, noise, weight);;
    return clamp(pow(noise * landColorOverlay, landColorPower), 0.0, 1.0);
}

float getMacro(vec2 uv){
    float offset = 0.468; // multiply with seed
    float albedo = texture(texArray, vec3(uv * macroScale + vec2(offset), 1.0)).r;
    albedo += texture(texArray, vec3(uv * macroScale * 0.15  + vec2(offset) * 4.0, 1.0)).r;
    return clamp(pow(albedo * 0.65, 2.5), 0.0, 1.0);
}

float getMacro(float weight){
    vec2 texcoord = TexCoord;
    texcoord.x *= 2.0;
    float macroFromUV = getMacro(texcoord);
    float macro = getMacro(vec2(FragPos.x, FragPos.z));
    return mix(macroFromUV, macro, weight);
}

void main()
{
    vec3 normal = normalize(Normal);
    float weight = getPoleBlend(normal);
    float height = getNoise(weight);
    float macro = getMacro(weight);

    float continentalShelfBlend = getContinentalShelfBlend(height, amountSea, waterContinentalShelf);
    vec3 wColor = mix(waterColor, continentalShelfColor, continentalShelfBlend);

    float blendNoise = getLandColorBlend(weight); // attention
    vec3 landColor = mix(landColor0, landColor1, blendNoise) * macro;

    float seaBlend = getSeaBlend(height, amountSea);
    vec3 albedo = mix(landColor, wColor, seaBlend); //  * macro

//    float cloudBlend = getCloudBlend(weight); // attention

//    albedo = mix(albedo, vec3(1.0), cloudBlend);
//    albedo *= (1.0 - cloudBorder);

    float fresnelClouds = fresnel(fresnelPowerClouds, fresnelScaleClouds, fresnelBiasClouds) * amountSea;
    float fresnelAtmosphre = fresnel(fresnelPowerAtmosphere, fresnelScaleAtmosphere, fresnelBiasAtmosphere) * clamp(amountSea * 1.5, 0.0, 1.0);
    vec3 color = mix(albedo, vec3(1.0), fresnelClouds);
    color = mix(color, waterColor, fresnelAtmosphre);

    // lighting
    float ambient = 0.0;
    float diffuse = max(dot(normal, -lightDirection), 0.0);
    color = color * (diffuse + ambient);
    // HDR tonemapping
    color = color / (color + vec3(1.0));
    // gamma correct
    color = pow(color, vec3(1.0/2.2));
    // out

    FragColor = vec4(vec3(color), 1.0);
}