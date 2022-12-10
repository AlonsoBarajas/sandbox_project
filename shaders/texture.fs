#version 330 core

in vec3 myColor;
in vec2 texCoor;

out vec4 FragColor;

uniform sampler2D ourTexture;

void main()
{
FragColor = texture(ourTexture, texCoor);
}