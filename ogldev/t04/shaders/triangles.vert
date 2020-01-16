
#version 400 core
#extension GL_ARB_separate_shader_objects : enable

layout( location = 0 ) in vec3 Position;

void main()
{
    gl_Position = vec4(0.5 * Position.x, 0.5 * Position.y, Position.z, 1.0);
}
