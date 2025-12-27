#include <generator/perlin.h>

Generator::PerlinNoise::PerlinNoise(uint32_t width, uint32_t depth, double frequency, int octaves, uint32_t seed)
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
    heights.clear();

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

double Generator::PerlinNoise::GetFrequency() const
{
    return frequency;
}

void Generator::PerlinNoise::SetFrequency(double frequency)
{
    this->frequency = frequency;
}

int Generator::PerlinNoise::GetOctaves() const
{
    return octaves;
}

void Generator::PerlinNoise::SetOctaves(int octaves)
{
    this->octaves = octaves;
}

uint32_t Generator::PerlinNoise::GetSeed() const
{
    return seed;
}

void Generator::PerlinNoise::SetSeed(uint32_t seed)
{
    this->seed = seed;
}

uint32_t Generator::PerlinNoise::GetWidth() const
{
    return width;
}

void Generator::PerlinNoise::SetWidth(uint32_t width)
{
    this->width = width;
}

uint32_t Generator::PerlinNoise::GetDepth() const
{
    return depth;
}

void Generator::PerlinNoise::SetDepth(uint32_t depth)
{
    this->depth = depth;
}

float Generator::PerlinNoise::GetOffset() const
{
    return offset;
}

void Generator::PerlinNoise::SetOffset(float offset)
{
    this->offset = offset;
}
