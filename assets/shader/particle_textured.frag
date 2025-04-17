#version 320 es
precision mediump float;

in vec2 vUV;
in vec4 vColor;

uniform sampler2D particleTexture;

out vec4 FragColor;

void main() {

//    vec2 middle = vec2(0.5, 0.5);
//    float distance = distance(vUV, middle);
//    float temp = step(distance, 0.5);

    vec4 albedo = texture(particleTexture, vUV).rgba;

    if(albedo.a < 0.001f)
        discard;

    FragColor = vColor * albedo;

    //vec4 texColor = texture(uParticleTex, vUV);
    //FragColor = texColor * vColor;

    //if (FragColor.a < 0.01) discard;  // optional alpha threshold
}