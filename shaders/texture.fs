#version 330 core

in vec3 myColor;
in vec2 texCoor;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float linearBlend;

void main()
{
FragColor = mix(texture(texture1, texCoor),
                texture(texture2, vec2(texCoor.x * -1, texCoor.y)), linearBlend);
}