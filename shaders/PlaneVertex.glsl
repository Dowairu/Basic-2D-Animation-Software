#version 410 core

layout(location = 0)in vec3 inPos;
layout(location = 1)in vec3 inNormal;

out vec3 worldPos;
out vec3 normal;
//uniform mat4 MVP;
layout( std140) uniform TransformUBO
{
  mat4 MVP;
  mat4 normalMatrix;
  mat4 M;
}transforms;

void main()
{
    worldPos = vec3(transforms.M * vec4(inPos, 1.0));
    normal=normalize(mat3(transforms.normalMatrix)*inNormal);
    gl_Position = transforms.MVP*vec4(inPos,1.0);
    //gl_Position = MVP * vec4(inPos,1.0);
}