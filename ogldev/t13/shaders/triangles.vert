
#version 400 core
#extension GL_ARB_separate_shader_objects : enable

layout( location = 0 ) in vec3 Position;

uniform mat4 gWorld;

layout(location = 0) out vec4 outColor;

void main()
{
    gl_Position = gWorld * vec4(Position, 1.0);
    outColor = vec4(clamp(Position, 0.0, 1.0), 1.0);
}
