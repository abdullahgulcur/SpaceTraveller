#ifdef ANDROID
precision mediump float;
#endif

#ifdef WIN

#endif

in vec2 TexCoord;
in vec4 Color;

out vec4 FragColor;

void main() {
    vec2 centered = TexCoord - 0.5;
    float distSq = dot(centered, centered); // x² + y²
    float alpha = step(distSq, 0.25); // (0.5 * 0.5)
    if(alpha < 0.01)
        discard;
    FragColor = Color;
}