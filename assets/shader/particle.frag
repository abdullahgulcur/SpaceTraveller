#version 320 es
precision mediump float;

in vec2 vUV;
in vec4 vColor;

out vec4 FragColor;

void main() {

    vec2 middle = vec2(0.5, 0.5);
    float distance = distance(vUV, middle);
    float temp = step(distance, 0.5);

    if(temp < 0.01)
        discard;

    FragColor = vColor * temp;

    //vec4 texColor = texture(uParticleTex, vUV);
    //FragColor = texColor * vColor;

    //if (FragColor.a < 0.01) discard;  // optional alpha threshold
}