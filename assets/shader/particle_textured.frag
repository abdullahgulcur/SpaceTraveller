#version 320 es
precision mediump float;

in vec2 vUV;
in vec4 vColor;
out vec4 FragColor;

uniform sampler2D particleTexture;

void main() {
    FragColor = texture(particleTexture, vUV).rgba * vColor;
    if(FragColor.a < 0.001f)
        discard;
}