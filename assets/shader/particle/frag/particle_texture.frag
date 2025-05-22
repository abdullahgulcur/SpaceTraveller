#ifdef ANDROID
precision mediump float;
#endif

#ifdef WIN

#endif

in vec2 TexCoord;
in vec4 Color;
out vec4 FragColor;

uniform sampler2D tex;

void main() {
    float alpha = texture(tex, TexCoord).r;
    if (alpha < 0.001)
        discard;
    FragColor = vec4(Color.rgb, Color.a * alpha);
}