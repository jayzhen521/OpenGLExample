#version 450 core

out vec4 FragColor;

layout(location = 0) in vec4 inColor;

void main()
{
    FragColor = inColor;
}
