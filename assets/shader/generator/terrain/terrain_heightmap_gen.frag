#ifdef ANDROID
precision mediump float;
#endif

#ifdef WIN

#endif

in vec2 vUV;
out float FragColor;

uniform float isBase;
uniform sampler2D tex;

void main() {

    // Center of the quad in UV space
    vec2 center = vec2(0.5, 0.5);

    // Distance from center (0.0 → center, ~0.707 → corner of quad)
    float dist = distance(vUV, center);

    // Circle radius reaching quad's border
    float radius = 0.5;

    // Compute gradient (1 at center → 0 at radius)
    float weight = 1.0 - smoothstep(0.0, radius, dist);

    weight = mix(weight, 1.0, isBase);

    float height = texture(tex, vUV).r;

    FragColor = height * weight;
}