#version 320 es
precision mediump float;

in vec2 vUV;

out vec4 FragColor;

uniform sampler2D noiseTexture;

float tempFunc(float distance, float radius, float strength){
    return clamp(((radius - distance) / radius), 0.0, 1.0) * strength;
}

void main() {

//    vec2 middle = vec2(0.5, 0.5);
//    float radius = 0.5;
//    float distance = distance(vUV, middle);
//    float temp = step(distance, radius);
//
////    if(temp < 0.0001)
////        discard;
//
//    float col0 = tempFunc(distance, radius, 0.1);
//    float col1 = tempFunc(distance, 0.01, 0.1);
//    float col2 = tempFunc(distance, 0.3, 0.1);
//
//
//    float col = clamp((col0+col1+col2) * 5.0, 0.0, 1.0);
//
//    float texValue = texture(noiseTexture, vUV * vec2(1.0, 6.0)).r * texture(noiseTexture, vUV * vec2(4.0, 1.0)).r * texture(noiseTexture, vUV * 8.0).r;//texture(noiseTexture, vUV * 3.0).r;
//    float noise = clamp(pow(texValue * 4.0, 1.7), 0.0, 1.0);
//
//    float co = tempFunc(distance, 0.25, 1.0);
//    float grad = mix(noise, col, co) * col;
//
//    //float blueFactor = 1.0 - (distance / radius);
//
//    float noise1 = texture(noiseTexture, vUV * 0.25).r;
//    vec4 coll = mix(vec4(0.8,0.9,1.0,1.0), vec4(1.0, 0.5, 0.4, 1.0), noise1);
//
//    float coo = tempFunc(distance, 0.1, 1.0);
//    vec4 ttt = mix(coll, vec4(1), coo);
//    FragColor = vec4(vec3(grad) , 1) * ttt;

    vec2 middle = vec2(0.5, 0.5);
    float radius = 0.5;
    float distance = distance(vUV, middle);
    float temp = step(distance, radius);

    float col0 = tempFunc(distance, radius, 1.0);
    FragColor = vec4(vec3(1.0) , col0);
}