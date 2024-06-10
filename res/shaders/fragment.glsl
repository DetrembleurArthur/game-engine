#version 330 core

uniform vec4 uColor;
uniform bool uTexEnable;
uniform sampler2D texture1;

in vec2 TexCoord;

out vec4 FragColor;


void main()
{
    if(uTexEnable)
    {
        FragColor = texture(texture1, TexCoord) * uColor;
    }
    else
    {
        FragColor = uColor;
    }
} 
