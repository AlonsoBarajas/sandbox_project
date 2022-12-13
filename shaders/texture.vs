#version 330 core

layout (location = 0) in vec3 aPos;  
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexture;

out vec3 myColor;
out vec2 texCoor;

uniform vec2 pos;

void main()
{
gl_Position = vec4(aPos.x + pos.x, aPos.y + pos.y, aPos.z, 1.0f);

myColor = aColor;

texCoor = aTexture;

}