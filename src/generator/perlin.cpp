#include <generator/perlin.h>

Generator::PerlinNoise::PerlinNoise(int width, int depth, double frequency, int octaves, uint32_t seed)
{
    this->width     = width;
    this->depth     = depth;
    this->seed      = seed;
    this->frequency = frequency;
    this->octaves   = octaves;
    this->seed      = seed; 
}

Generator::PerlinNoise::~PerlinNoise()
{

}

void Generator::PerlinNoise::GeneratePerlinNoise()
{
    const siv::PerlinNoise perlin{ seed };
    const double fx = (frequency / (double)width);
    const double fz = (frequency / (double)depth);

    for(int z = 0; z < depth; ++z)
    {
        for(int x = 0; x < width; ++x)
        {
            float height = perlin.octave2D_01((x * fx), (z * fz), octaves);
            heights.push_back(height);
        }
    }

}

float Generator::PerlinNoise::GetHeight(int x, int z) 
{
    if(x < 0 || x >= width)
    {
        std::cerr << "PerlinNoise GetHeight x out of bounds" << std::endl;
        return 0.0f;
    }

    if(z < 0 || z >= depth)
    {
        std::cerr << "PerlinNoise GetHeight z out of bounds" << std::endl;
        return 0.0f;
    }

    return heights[z + width * x];
}
