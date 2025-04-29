#ifdef ANDROID
precision mediump float;
#endif

#ifdef WIN

#endif


in vec2 vUV;
in vec4 vColor;
out vec4 FragColor;

uniform sampler2D tex;

void main() {
    FragColor = texture(tex, vUV).rgba * vColor;
    if(FragColor.a < 0.001f)
        discard;
}