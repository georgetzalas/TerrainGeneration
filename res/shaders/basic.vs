#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aTexCoords;

uniform mat4 projection;
uniform mat4 view;

out float height;

void main()
{
    gl_Position = projection * view * vec4(aPos, 1.0f);
    height      = aPos.y;
}
