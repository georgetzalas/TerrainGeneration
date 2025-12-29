#version 460 core

out vec4 Color;

in float height;
in vec2 TexCoords;
uniform float normalizationFactor;
uniform sampler2D tex;

void main()
{
    /*float heightNormalized = height/normalizationFactor;

    vec3 color = vec3(0.0f, 0.0f, 0.0f);

    //Water
    if(heightNormalized >= 0.0f && heightNormalized < 0.4f)
    {
        color = vec3(0.0f, 0.0f, 1.0f);
    }

    //Sand
    if(heightNormalized >= 0.4f && heightNormalized < 0.5f)
    {
        color = vec3(0.890f, 0.752f, 0.384f);
    }

    //Grass
    if(heightNormalized >= 0.5f && heightNormalized < 0.7f)
    {
        color = vec3(0.0f, 1.0f, 0.0f);
    }

    //Rock
    if(heightNormalized >= 0.7f && heightNormalized < 0.85f)
    {
        color = vec3(0.521f, 0.490f, 0.415f);
    }

    //Snow
    if(heightNormalized >= 0.85f && heightNormalized <= 1.0f)
    {
        color = vec3(1.0f, 1.0f, 1.0f);
    }*/

    Color = texture(tex, TexCoords);
}
