#include <iostream>
#include <cstdint>
#include <generator/heightmap.h>
#include <perlin/PerlinNoise.hpp>

namespace Generator
{
    class PerlinNoise : public HeightMap
    {
    public:
        PerlinNoise(int width, int depth, double frequency, int octaves, uint32_t seed);
        ~PerlinNoise();
        float GetHeight(int x, int z) override;
        void GeneratePerlinNoise();

    private:
        double frequency;
        int octaves;
        uint32_t seed;
        int width;
        int depth;
        std::vector<float> heights;
    };
};
