#ifdef ANDROID
precision mediump float;
precision mediump sampler2D;
#endif

#ifdef WIN

#endif

in vec2 TexCoord;
in vec4 Color;
out vec4 FragColor;

uniform sampler2D tex;

void main() {
    vec4 col = texture(tex, TexCoord).rgba;
    if (col.a < 0.01)
        discard;
    FragColor = col;
}