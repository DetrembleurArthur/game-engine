#version 330 core

uniform vec4 uColor;
uniform sampler2D texture1;

in vec2 TexCoord;

out vec4 FragColor;


void main()
{
    FragColor = uColor * vec4(1, 1, 1, texture(texture1, TexCoord).r);
} 
