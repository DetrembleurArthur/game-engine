#version 330 core

uniform vec4 uColor;
uniform int uTexEnable;
uniform sampler2D texture1;

in vec2 TexCoord;

out vec4 FragColor;


void main()
{
    if(uTexEnable == 1)
    {
        FragColor = texture(texture1, TexCoord) * uColor;
    }
    else if(uTexEnable == 2)
    {
        FragColor = uColor * vec4(1, 1, 1, texture(texture1, TexCoord).r);
    }
    else
    {
        FragColor = uColor;
    }
} 
