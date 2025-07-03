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
uniform vec3 lightDirection;
uniform vec3 waterColor;
uniform float amountSea;

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
    float albedo2 = texture(noiseTex0, vec2(uv.x, uv.y) * scale * 0.05).r;

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
    float ambient = 0.0;
    vec3 normal = normalize(Normal);


    vec3 lightDir = -lightDirection;
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

    float seaAmount = amountSea;
    float continentalShelf = 0.07;
    vec3 seaColor = vec3(0.0, 0.1, 0.9);
    float fresnel0 = fresnel(3.0, 0.25, 0.0);
    float fresnel1 = fresnelAtmosphre(15.0, 2.0, 0.75);

    vec3 continentalShelfColor = seaColor + vec3(0.05, 0.07, 0.05);

    vec3 grassColor = vec3(0.25, 0.3, 0.15);
    vec3 desertColor = vec3(0.6, 0.6, 0.2);
    vec3 landColor = vec3(0.4, 0.35, 0.2);

    float seaBlend = getSeaBlend(height, seaAmount);
    float continentalShelfBlend = getContinentalShelfBlend(height, seaAmount, continentalShelf);
    float brownBlend = getBrownBlend(height, seaAmount, 0.3, 0.15);



    grassColor = mix(grassColor, desertColor, blendNoise);
    landColor = mix(grassColor, landColor, brownBlend); // baseLandColor;//

    vec3 wColor = mix(waterColor, continentalShelfColor, continentalShelfBlend);

    vec3 albedo = mix(landColor * macro, wColor, seaBlend);

    vec3 color = mix(albedo, vec3(1.0), fresnel0);
    color = mix(color, vec3(0.0, 0.0, 0.95), fresnel1);



    color = color * (diffuse + ambient);
    // HDR tonemapping
    color = color / (color + vec3(1.0));
    // gamma correct
    color = pow(color, vec3(1.0/2.2));

    FragColor = vec4(vec3(color), 1.0);
}