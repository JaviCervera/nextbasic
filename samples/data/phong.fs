#version 130

uniform vec3 EyePos = vec3(2, 2, 2);
uniform vec3 SurfaceDiffuse = vec3(0.9, 0.5, 1);
uniform vec3 SurfaceSpecular = vec3(0.3,0.3,0.3);
uniform float SurfaceSmooth = 256;
uniform vec3 LightPos[2] = vec3[2](vec3(10, 10, 12), vec3(-4, 5, 7));
uniform vec3 LightIntensity[2] = vec3[2](vec3(2, 2, 2), vec3(1.6f, 1.6f, 0.6f));
in vec3 WorldPos;
in vec3 WorldNormal;
out vec4 Color;
vec3 Shade(vec3 p, vec3 n) {
    vec3 eyeVec = normalize(EyePos - p);
    vec3 lightVec = normalize(LightPos[0] - p);
    vec3 halfVec = 0.5 * (eyeVec + lightVec);
    float cosTh = clamp(dot(n, halfVec), 0, 1);
    float cosTi = clamp(dot(n, lightVec), 0, 1);
    vec3 Lo = (SurfaceDiffuse + SurfaceSpecular * pow(cosTh, SurfaceSmooth)) * LightIntensity[0] * cosTi;
    lightVec = normalize(LightPos[1] - p);
    halfVec = 0.5 * (eyeVec + lightVec);
    cosTh = clamp(dot(n, halfVec), 0, 1);
    cosTi = clamp(dot(n, lightVec), 0, 1);
    Lo += (SurfaceDiffuse + SurfaceSpecular * pow(cosTh, SurfaceSmooth)) * LightIntensity[1] * cosTi;
    return Lo;
}
void main() {
    vec3 nw = normalize(WorldNormal);
    Color.rgb = Shade(WorldPos, nw);
    Color.a = 1;
};
