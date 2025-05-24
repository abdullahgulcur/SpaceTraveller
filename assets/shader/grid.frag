#ifdef ANDROID
precision mediump float;
#endif

#ifdef WIN

#endif

out vec4 FragColor;

void main() {

    FragColor = vec4(vec3(0.5), 1.0);
}