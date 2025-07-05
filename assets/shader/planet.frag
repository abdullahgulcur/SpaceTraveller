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

// macro scale
// noise texture selection
// cloud (scale, power, overlay, color)

float fresnel(float power, float scale, float bias){
    vec3 viewDir = normalize(cameraPosition - FragPos);
    return bias + scale * pow(1.0 - max(dot(viewDir, normalize(Normal)), 0.0), power);
}

float fresnelAtmosphre(float power, float scale, float bias){
    vec3 viewDir = normalize(cameraPosition - FragPos);
    float viewAngle = 1.0 - dot(viewDir, normalize(Normal));
    return smoothstep(0.75, 0.95, viewAngle);
}

float getSeaBlend(float albedo, float seaAmount){
    return step(albedo, seaAmount);
}

float getContinentalShelfBlend(float albedo, float seaAmount, float continentalShelf){
    continentalShelf = mix(seaAmount, 0.0, continentalShelf);
    return smoothstep(continentalShelf, seaAmount, albedo);
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

vec3 getWeight(vec3 normal){
    vec3 weight = abs(normal);
    weight /= weight.x + weight.y + weight.z;
    return weight;
}

float getNoiseOctave(vec2 uv){
    float noise = texture(texArray, vec3(vec2(uv.x, uv.y) * surfaceTopologyScale, 1.0)).r;
    noise += texture(texArray, vec3(vec2(uv.x, uv.y) * surfaceTopologyScale * 0.2, 0.0)).r;
    noise += texture(texArray, vec3(vec2(uv.x, uv.y) * surfaceTopologyScale * 0.05, 1.0)).r;
    return noise * 0.33;
}

float getNoise(vec3 weight){

    float noiseXY = getNoiseOctave(vec2(FragPos.x, FragPos.y));
    float noiseXZ = getNoiseOctave(vec2(FragPos.x, FragPos.z));
    float noiseYZ = getNoiseOctave(vec2(FragPos.y, FragPos.z));

    float noise = weight.x * noiseYZ + weight.y * noiseXZ + weight.z * noiseXY;
    return noise;
}

float getLandColorBlendNoiseOctave(vec2 uv){
    float offset = 5.0; // make it parameter
    float albedo = texture(noiseTex1, vec2(uv.x, uv.y) * landColorBlendScale + vec2(offset)).r;
    albedo *= texture(noiseTex1, vec2(uv.x, uv.y) * landColorBlendScale * 0.2 + vec2(offset) * 16.0).r;
    albedo *= texture(noiseTex1, vec2(uv.x, uv.y) * landColorBlendScale * 0.05 + vec2(offset) * 256.0).r;
    return albedo;
}

float getLandColorBlend(vec3 weight){
    float noise = getLandColorBlendNoiseOctave(vec2(FragPos.y, FragPos.z)) * weight.x;
    noise += getLandColorBlendNoiseOctave(vec2(FragPos.x, FragPos.z)) * weight.y;
    noise += getLandColorBlendNoiseOctave(vec2(FragPos.x, FragPos.y)) * weight.z;
    return clamp(pow(noise * landColorOverlay, landColorPower), 0.0, 1.0);
}

float getMacro(vec3 weight){

    float macroXY = getMacro(vec2(FragPos.x, FragPos.y));
    float macroXZ = getMacro(vec2(FragPos.x, FragPos.z));
    float macroYZ = getMacro(vec2(FragPos.y, FragPos.z));

    float macro = weight.x * macroYZ + weight.y * macroXZ + weight.z * macroXY;
    return macro;
}

void main()
{
    vec3 normal = normalize(Normal);
    vec3 weight = getWeight(normal);
    float height = getNoise(weight);
    float macro = getMacro(weight);

    float continentalShelfBlend = getContinentalShelfBlend(height, amountSea, waterContinentalShelf);
    vec3 wColor = mix(waterColor, continentalShelfColor, continentalShelfBlend);

    float blendNoise = getLandColorBlend(weight);
    vec3 landColor = mix(landColor0, landColor1, blendNoise);

    float seaBlend = getSeaBlend(height, amountSea);
    vec3 albedo = mix(landColor * macro, wColor, seaBlend);

    float fresnel0 = fresnel(3.0, 0.25, 0.0);
    float fresnel1 = fresnelAtmosphre(15.0, 2.0, 0.75);
    vec3 color = mix(albedo, vec3(1.0), fresnel0);
    color = mix(color, vec3(0.0, 0.0, 0.95), fresnel1);


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