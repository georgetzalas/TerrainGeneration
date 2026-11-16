#version 460 core

out vec4 Color;

uniform int chunkID;

void main()
{
    Color = vec4(vec3(chunkID/16.0f), 1.0f);
}
