#ifdef ANDROID
precision mediump float;
#endif

#ifdef WIN

#endif

in vec2 vUV;
out vec4 FragColor;

uniform sampler2D tex;

float linstep(float edge0, float edge1, float x) {
    return clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
}

float distanceBasedStrength(float distance, float radius, float strength){
    return clamp(((radius - distance) / radius), 0.0, 1.0) * strength;
}

void main() {
    vec2 middle = vec2(0.5, 0.5);
    float radius = 0.5;
    float distance = distance(vUV, middle);

    float lightAmount = distanceBasedStrength(distance, radius, 0.05);
    lightAmount += distanceBasedStrength(distance, 0.4, 0.05);
    lightAmount += distanceBasedStrength(distance, 0.3, 0.1);
    lightAmount += distanceBasedStrength(distance, 0.2, 0.3);
    lightAmount += distanceBasedStrength(distance, 0.1, 0.5);
    //lightAmount = clamp(lightAmount * 5.0, 0.0, 1.0);

    float tttt = linstep(0.5, 1.0, distance / radius);
    float temp = 1.0 - tttt;//linstep(1.2, 0.0, distance / radius);

    float noise = texture(tex, vUV * vec2(1.0, 6.0)).r * texture(tex, vUV * vec2(4.0, 1.0)).r * texture(tex, vUV * 8.0).r;
    noise = clamp(pow(noise * 4.0, 1.7), 0.0, 1.0);

    float co = distanceBasedStrength(distance, 0.5, 1.0);
    float grad = mix(noise, 1.0, temp) * temp;

    float colorNoise = texture(tex, vUV * 4.0).r;
    vec3 galaxyColor = mix(vec3(1.0,0.8,0.6), vec3(0.8, 0.8, 1.0), colorNoise);

    galaxyColor = vec3(1.0, 0.5, 0.1);
    float hotCoreAmount = distanceBasedStrength(distance, 0.1, 1.0);

    hotCoreAmount = 1.0 - linstep(0.3, 1.0, distance / radius);


    vec3 finalColor = mix(galaxyColor, vec3(1.0), hotCoreAmount);

    FragColor = vec4(finalColor, grad);
    //    FragColor = vec4(vec3(texture(tex, vUV).r), 1.0);
}