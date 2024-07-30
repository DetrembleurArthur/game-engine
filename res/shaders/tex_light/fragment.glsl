#version 330 core

uniform vec4 uColor;
uniform sampler2D texture1;

in vec2 TexCoord;
in vec2 FragPos;

out vec4 FragColor;


void main()
{
    // Calculate distance from the center of the screen
    float distance = length(FragPos - vec2(0, 0));
    
    // Calculate attenuation based on distance
    float attenuation = 1.0 - clamp(distance / 0.75, 0.0, 1.0);


    FragColor = texture(texture1, TexCoord) * uColor * attenuation;
} 
