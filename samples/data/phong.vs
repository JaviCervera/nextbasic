#version 130

uniform mat4 MVPMatrix;
uniform mat4 WorldMatrix;
in vec3 Position;
in vec3 Normal;
out vec3 WorldPos;
out vec3 WorldNormal;
void main() {
    gl_Position = MVPMatrix * vec4(Position, 1);
    WorldPos = (WorldMatrix * vec4(Position, 1)).xyz;
    WorldNormal = mat3(WorldMatrix) * Normal;
}
