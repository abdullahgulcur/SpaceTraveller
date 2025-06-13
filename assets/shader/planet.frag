#ifdef ANDROID
precision mediump float;
#endif

#ifdef WIN

#endif

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D noiseTex0;
uniform sampler2D noiseTex1;
uniform vec3 cameraPosition;


const float PI = 3.14159265359;
// ----------------------------------------------------------------------------
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}
// ----------------------------------------------------------------------------
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}
// ----------------------------------------------------------------------------

float fresnel(float power, float scale, float bias){
    vec3 viewDir = normalize(cameraPosition - FragPos);
    return bias + scale * pow(1.0 - max(dot(viewDir, normalize(Normal)), 0.0), power);
}

float fresnelAtmosphre(float power, float scale, float bias){
    vec3 viewDir = normalize(cameraPosition - FragPos);
    float viewAngle = 1.0 - dot(viewDir, normalize(Normal));
    return smoothstep(0.75, 0.95, viewAngle);
}

float getNoiseOctave(vec2 uv){

    float scale = 0.2; // make it parameter
    float albedo0 = texture(noiseTex1, vec2(uv.x, uv.y) * scale).r;
    float albedo1 = texture(noiseTex0, vec2(uv.x, uv.y) * scale * 0.2).r;
    float albedo2 = texture(noiseTex1, vec2(uv.x, uv.y) * scale * 0.05).r;

    float albedo = (albedo0 + albedo1 + albedo2) * 0.33;
    //float albedo = albedo2;
    //float albedo = (albedo1 + albedo2) * 0.5;

    return albedo;
}

float getBlendNoiseOctave(vec2 uv){

    float scale = 0.4; // make it parameter
    float albedo0 = texture(noiseTex0, vec2(uv.x, uv.y) * scale).r;
    float albedo1 = texture(noiseTex0, vec2(uv.x, uv.y) * scale * 0.2).r;
    float albedo2 = texture(noiseTex0, vec2(uv.x, uv.y) * scale * 0.05).r;

    //float albedo = (albedo0 + albedo1 + albedo2) * 0.33;
    //float albedo = albedo2;
    float albedo = albedo0 * albedo1 * albedo2;

    return albedo;
}

float getSeaBlend(float albedo, float seaAmount){
    //float albedo = albedo0 * albedo1 * albedo2;
    //albedo = pow(albedo, 3.0);
    albedo = step(albedo, seaAmount);
    //albedo = clamp(albedo, 0.0, 1.0);
    return albedo;
}

float getContinentalShelfBlend(float albedo, float seaAmount, float continentalShelf){
    //albedo = step(albedo, seaAmount);

    continentalShelf = mix(seaAmount, 0.0, continentalShelf);
    //continentalShelf = (1 - continentalShelf) * seaAmount;
    return smoothstep(continentalShelf, seaAmount, albedo);
    //return clamp((albedo - continentalShelf) / (seaAmount - continentalShelf),0.0,1.0);
}

float getBrownBlend(float albedo, float seaAmount, float grassStartThreshold, float grassBlend){

    float grassStart = mix(seaAmount, 1.0, grassStartThreshold);
    float grassEnd = mix(seaAmount, 1.0, grassStartThreshold + grassBlend);
    return smoothstep(grassStart, grassEnd, albedo);
    //return clamp((albedo - grassStart) / (grassEnd - grassStart),0.0,1.0);
}

float getMacro(vec2 uv){
    float scale = 3.0; // make it parameter
    float albedo0 = texture(noiseTex1, vec2(uv.x, uv.y) * scale * 1.6).r;
    float albedo1 = texture(noiseTex1, vec2(uv.x, uv.y) * scale * 0.2).r * 0.5;
    float albedo2 = texture(noiseTex1, vec2(uv.x, uv.y) * scale * 0.05).r * 0.25;

    //albedo2 = mix(0.5, 1.0, albedo2);

    //float albedo = albedo0 * albedo1 * albedo2;
    float albedo = (albedo0 + albedo1 + albedo2) * (1.0 / 1.75);
    albedo = pow(albedo, 1.5);
    //float albedo = albedo2;
    //float albedo = (albedo1 + albedo2) * 0.5;

    //float albedo = albedo0 * albedo1 * albedo2;

    return clamp(mix(0.0, 1.0, albedo), 0.0, 1.0);
}


void main()
{
    float ambient = 0.1;
    vec3 normal = normalize(Normal);


    vec3 lightDir = normalize(vec3(-1.0, 1.0, -1.0));
    float diffuse = max(dot(normal, lightDir), 0.0);

    float albedoXY = getNoiseOctave(vec2(FragPos.x, FragPos.y));
    float albedoXZ = getNoiseOctave(vec2(FragPos.x, FragPos.z));
    float albedoYZ = getNoiseOctave(vec2(FragPos.y, FragPos.z));

    float macroXY = getMacro(vec2(FragPos.x, FragPos.y));
    float macroXZ = getMacro(vec2(FragPos.x, FragPos.z));
    float macroYZ = getMacro(vec2(FragPos.y, FragPos.z));

    float blendNoiseXY = getBlendNoiseOctave(vec2(FragPos.x, FragPos.y));
    float blendNoiseXZ = getBlendNoiseOctave(vec2(FragPos.x, FragPos.z));
    float blendNoiseYZ = getBlendNoiseOctave(vec2(FragPos.y, FragPos.z));

    vec3 weights = abs(normal);
    weights /= (weights.x + weights.y + weights.z); // normalize so weights sum to 1
    float height = weights.x * albedoYZ + weights.y * albedoXZ + weights.z * albedoXY;
    float macro = weights.x * macroYZ + weights.y * macroXZ + weights.z * macroXY;
    float blendNoise = weights.x * blendNoiseYZ + weights.y * blendNoiseXZ + weights.z * blendNoiseXY;
    blendNoise = clamp(pow(blendNoise * 4.0, 2.5), 0.0, 1.0);

    float seaAmount = 0.6;
    float continentalShelf = 0.1;
    vec3 seaColor = vec3(0.3, 0.1, 0.5);
    float fresnel0 = fresnel(3.0, 0.25, 0.0);
    float fresnel1 = fresnelAtmosphre(15.0, 2.0, 0.75);

    vec3 continentalShelfColor = seaColor + vec3(0.05, 0.15, 0.05);

    vec3 grassColor = vec3(0.33, 0.36, 0.11);
    vec3 desertColor = vec3(0.6, 0.6, 0.2);
    vec3 landColor = vec3(0.4, 0.35, 0.2);

    float seaBlend = getSeaBlend(height, seaAmount);
    float continentalShelfBlend = getContinentalShelfBlend(height, seaAmount, continentalShelf);
    float brownBlend = getBrownBlend(height, seaAmount, 0.3, 0.15);



    grassColor = mix(grassColor, desertColor, blendNoise);
    landColor = mix(grassColor, landColor, brownBlend); // baseLandColor;//

    vec3 waterColor = mix(seaColor, continentalShelfColor, continentalShelfBlend);

    vec3 albedo = mix(landColor * macro, waterColor, seaBlend);

    vec3 color = mix(albedo, vec3(1.0), fresnel0);
    color = mix(color, vec3(0.9, 0.1, 0.95), fresnel1);

//
//    vec3 N = normal;
//    vec3 V = normalize(cameraPosition - FragPos);
//
//    // calculate reflectance at normal incidence; if dia-electric (like plastic) use F0
//    // of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow)
//    vec3 F0 = vec3(0.04);
//    F0 = mix(F0, albedo, metallic);
//
//    // reflectance equation
//    vec3 Lo = vec3(0.0);
//    for(int i = 0; i < 4; ++i)
//    {
//        // calculate per-light radiance
//        vec3 L = normalize(lightPositions[i] - FragPos);
//        vec3 H = normalize(V + L);
//        float distance = length(lightPositions[i] - FragPos);
//        float attenuation = 1.0 / (distance * distance);
//        vec3 radiance = lightColors[i] * attenuation;
//
//        // Cook-Torrance BRDF
//        float NDF = DistributionGGX(N, H, roughness);
//        float G   = GeometrySmith(N, V, L, roughness);
//        vec3 F    = fresnelSchlick(clamp(dot(H, V), 0.0, 1.0), F0);
//
//        vec3 numerator    = NDF * G * F;
//        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001; // + 0.0001 to prevent divide by zero
//        vec3 specular = numerator / denominator;
//
//        // kS is equal to Fresnel
//        vec3 kS = F;
//        // for energy conservation, the diffuse and specular light can't
//        // be above 1.0 (unless the surface emits light); to preserve this
//        // relationship the diffuse component (kD) should equal 1.0 - kS.
//        vec3 kD = vec3(1.0) - kS;
//        // multiply kD by the inverse metalness such that only non-metals
//        // have diffuse lighting, or a linear blend if partly metal (pure metals
//        // have no diffuse light).
//        kD *= 1.0 - metallic;
//
//        // scale light by NdotL
//        float NdotL = max(dot(N, L), 0.0);
//
//        // add to outgoing radiance Lo
//        Lo += (kD * albedo / PI + specular) * radiance * NdotL;  // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
//    }
//
//    // ambient lighting (note that the next IBL tutorial will replace
//    // this ambient lighting with environment lighting).
//    vec3 ambient = vec3(0.03) * albedo * ao;
//
//    vec3 color = ambient + Lo;
//


    color = color * (diffuse + ambient);
    // HDR tonemapping
    color = color / (color + vec3(1.0));
    // gamma correct
    color = pow(color, vec3(1.0/2.2));

    FragColor = vec4(vec3(color), 1.0);
}