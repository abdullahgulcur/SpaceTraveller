#ifdef ANDROID
precision mediump float;
#endif

#ifdef WIN

#endif

in vec2 vUV;
out vec4 FragColor;

uniform sampler2D tex;
uniform ivec2 screenSize;

void main() {

    //FragColor = vec4(texture(tex, vUV).rgb, 1.0);

    float FXAA_REDUCE_MIN = (1.0/ 128.0);
    float FXAA_REDUCE_MUL = (1.0 / 8.0);
    float FXAA_SPAN_MAX =  8.0;
    vec2 inverseVP = vec2(1.0 / float(screenSize.x), 1.0 / float(screenSize.y));
    vec3 rgbNW = textureOffset(tex, vUV, ivec2(-1, -1)).xyz;
    vec3 rgbNE = textureOffset(tex, vUV, ivec2(1, -1)).xyz;
    vec3 rgbSW = textureOffset(tex, vUV, ivec2(-1, 1)).xyz;
    vec3 rgbSE = textureOffset(tex, vUV, ivec2(1, 1)).xyz;
    vec3 rgbM  = texture(tex, vUV).xyz;
    vec3 luma  = vec3(0.299, 0.587, 0.114);
    float lumaNW = dot(rgbNW, luma);
    float lumaNE = dot(rgbNE, luma);
    float lumaSW = dot(rgbSW, luma);
    float lumaSE = dot(rgbSE, luma);
    float lumaM  = dot(rgbM,  luma);
    float lumaMin = min(lumaM, min(min(lumaNW, lumaNE), min(lumaSW, lumaSE)));
    float lumaMax = max(lumaM, max(max(lumaNW, lumaNE), max(lumaSW, lumaSE)));

    vec2 dir;
    dir.x = -((lumaNW + lumaNE) - (lumaSW + lumaSE));
    dir.y =  ((lumaNW + lumaSW) - (lumaNE + lumaSE));
    float dirReduce = max((lumaNW + lumaNE + lumaSW + lumaSE) *
        (0.25 * FXAA_REDUCE_MUL), FXAA_REDUCE_MIN);
    float rcpDirMin = 1.0 / (min(abs(dir.x), abs(dir.y)) + dirReduce);
    dir = min(vec2(FXAA_SPAN_MAX, FXAA_SPAN_MAX), max(vec2(-FXAA_SPAN_MAX, -FXAA_SPAN_MAX), dir * rcpDirMin)) * inverseVP;

    vec3 rgbA = (1.0/2.0) * (texture(tex,vUV + dir * (1.0/3.0 - 0.5)).xyz + texture(tex,vUV + dir * (2.0/3.0 - 0.5)).xyz);
    vec3 rgbB = rgbA * (1.0/2.0) + (1.0/4.0) * (texture(tex,vUV + dir * (0.0/3.0 - 0.5)).xyz + texture(tex,vUV + dir * (3.0/3.0 - 0.5)).xyz);

    float lumaB = dot(rgbB, luma);

    if ((lumaB < lumaMin) || (lumaB > lumaMax)){
        FragColor = vec4(rgbA, 1.0);
    }else{
        FragColor = vec4(rgbB, 1.0);
    }
}