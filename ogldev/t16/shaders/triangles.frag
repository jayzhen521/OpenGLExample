#version 450 core

out vec4 FragColor;

uniform sampler2D gSampler;

in vec2 TexCoord0;

void main()
{
    FragColor = texture2D(gSampler, TexCoord0.xy);
}
