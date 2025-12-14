#version 460 core

out vec4 Color;

in float height;

void main()
{
    float heightNormalized = height/16.0f;
    vec3 color = vec3(1.0f, 1.0f, 1.0f) * heightNormalized + vec3(0.0f, 0.0f, 0.0f) * (1-heightNormalized);
    Color = vec4(color, 1.0f); 
}
