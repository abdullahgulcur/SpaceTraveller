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
uniform float amountWater;
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
uniform float specularStrength;
uniform float specularPower;

uniform float noiseOctaveTexIndex0;
uniform float noiseOctaveTexIndex1;

// ------------------- Ref: https://learnopengl.com/PBR/Lighting ----------------------
//
//const float PI = 3.14159265359;
//
//float DistributionGGX(vec3 N, vec3 H, float roughness)
//{
//    float a = roughness*roughness;
//    float a2 = a*a;
//    float NdotH = max(dot(N, H), 0.0);
//    float NdotH2 = NdotH*NdotH;
//
//    float nom   = a2;
//    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
//    denom = PI * denom * denom;
//
//    return nom / denom;
//}
//// ----------------------------------------------------------------------------
//float GeometrySchlickGGX(float NdotV, float roughness)
//{
//    float r = (roughness + 1.0);
//    float k = (r*r) / 8.0;
//
//    float nom   = NdotV;
//    float denom = NdotV * (1.0 - k) + k;
//
//    return nom / denom;
//}
//// ----------------------------------------------------------------------------
//float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
//{
//    float NdotV = max(dot(N, V), 0.0);
//    float NdotL = max(dot(N, L), 0.0);
//    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
//    float ggx1 = GeometrySchlickGGX(NdotL, roughness);
//
//    return ggx1 * ggx2;
//}
//// ----------------------------------------------------------------------------
//vec3 fresnelSchlick(float cosTheta, vec3 F0)
//{
//    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
//}
// ----------------------------------------------------------------------------

float fresnel(float power, float scale, float bias){
    vec3 viewDir = normalize(cameraPosition - FragPos);
    float viewAngle = 1.0 - dot(viewDir, normalize(Normal));
    return smoothstep(power, bias, viewAngle) * scale;
}

float getSeaBlend(float albedo, float seaAmount){
    return smoothstep(seaAmount,seaAmount - waterContinentalShelf,  albedo);
    //    return step(albedo, seaAmount);
}
//
//float getContinentalShelfBlend(float albedo, float seaAmount, float continentalShelf){
//    continentalShelf = mix(seaAmount, 0.0, continentalShelf);
//    return smoothstep(continentalShelf, seaAmount, albedo);
//}

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
//
//float getCloudBorderBlend(float cloud){
//    return step(0.01, cloud) * step(cloud, 0.03);
//}

float getNoiseOctave(vec2 uv){
    float noise = texture(texArray, vec3(uv * surfaceTopologyScale, noiseOctaveTexIndex0)).r;
    return noise * texture(texArray, vec3(uv * surfaceTopologyScale * 0.15, noiseOctaveTexIndex1)).r;
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

    vec3 albedo;

//    float continentalShelfBlend = getContinentalShelfBlend(height, amountWater, waterContinentalShelf);
    //vec3 colorWater = waterColor;//mix(waterColor, continentalShelfColor, continentalShelfBlend);

    float blendNoise = getLandColorBlend(weight); // attention
    vec3 colorLand = mix(landColor0, landColor1, blendNoise) * macro;

    float waterBlend = getSeaBlend(height, amountWater);
    albedo = mix(colorLand, waterColor, waterBlend);

//    float fresnelClouds = fresnel(fresnelPowerClouds, fresnelScaleClouds, fresnelBiasClouds);// * amountSea;
//    float fresnelAtmosphre = fresnel(fresnelPowerAtmosphere, fresnelScaleAtmosphere, fresnelBiasAtmosphere);// * clamp(amountSea * 1.5, 0.0, 1.0);
//    albedo = mix(albedo, vec3(1.0), fresnelClouds);
//    albedo = mix(albedo, vec3(1.0), fresnelAtmosphre);

    // lighting
//    float ambient = 0.0;
    float diffuse = max(dot(normal, -lightDirection), 0.0) * 2.0;

//    vec3 viewDir = normalize(cameraPosition - FragPos);
//    vec3 reflectDir = reflect(lightDirection, normal);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), specularPower);
//    float specular = specularStrength * spec * waterBlend;

    float fresnelClouds = fresnel(fresnelPowerClouds, fresnelScaleClouds, fresnelBiasClouds);
    albedo = mix(albedo, vec3(1.0), fresnelClouds);

    vec3 color = albedo * (diffuse); // + ambient + specular

    // lighting PBR

//    float metallic = mix(mix(0.2, 0.5, macro), 0.2, waterBlend);
//    float roughness = mix(mix(0.7, 0.9, (1.0 - macro)), 0.5, waterBlend);
//    float ao = 0.0;
//
//    vec3 N = normal;
//    vec3 V = normalize(cameraPosition - FragPos);
//    vec3 F0 = vec3(0.04);
//    F0 = mix(F0, albedo, metallic);
//    vec3 Lo = vec3(0.0);
//    vec3 L = normalize(-lightDirection);
//    vec3 H = normalize(V + L);
//    //float distance = length(lightPositions[i] - WorldPos);
//    float attenuation = 5.0;// / (distance * distance); TODO: do it according to the planet distance from sun
//    vec3 radiance = vec3(attenuation);
//    float NDF = DistributionGGX(N, H, roughness);
//    float G   = GeometrySmith(N, V, L, roughness);
//    vec3 F    = fresnelSchlick(clamp(dot(H, V), 0.0, 1.0), F0);
//    vec3 numerator    = NDF * G * F;
//    float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001; // + 0.0001 to prevent divide by zero
//    vec3 specular = numerator / denominator;
//    vec3 kS = F;
//    vec3 kD = vec3(1.0) - kS;
//    kD *= 1.0 - metallic;
//    float NdotL = max(dot(N, L), 0.0);
//    Lo = (kD * albedo / PI + specular) * radiance * NdotL;
//    vec3 ambient = albedo * ao;
//    vec3 color = ambient + Lo;


//    float fresnelClouds = fresnel(fresnelPowerClouds, fresnelScaleClouds, fresnelBiasClouds);
//    float fresnelAtmosphre = fresnel(fresnelPowerAtmosphere, fresnelScaleAtmosphere, fresnelBiasAtmosphere);
//    color = mix(color, vec3(1.0), fresnelClouds);
//    color = mix(color, vec3(1.0), fresnelAtmosphre);
//    color *= diffuse;

    // HDR tonemapping
    color = color / (color + vec3(1.0));
    // gamma correct
    color = pow(color, vec3(1.0/2.2));
    // out

    FragColor = vec4(vec3(color), 1.0);
}