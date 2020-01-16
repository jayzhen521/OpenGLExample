
#version 400 core
#extension GL_ARB_separate_shader_objects : enable

layout( location = 0 ) in vec3 Position;

uniform float gScale;

void main()
{
    gl_Position = vec4(gScale * Position.x, gScale * Position.y, Position.z, 1.0);
}
