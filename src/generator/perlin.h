#include <iostream>
#include <cstdint>
#include <generator/heightmap.h>
#include <perlin/PerlinNoise.hpp>

namespace Generator
{
    class PerlinNoise : public HeightMap
    {
    public:
        PerlinNoise() = default;
        PerlinNoise(uint32_t width, uint32_t depth, double frequency, int octaves, uint32_t seed);
        ~PerlinNoise();

        float GetHeight(int x, int z) override;
        void GeneratePerlinNoise();

        double GetFrequency() const;
        void SetFrequency(double frequency);

        int GetOctaves() const;
        void SetOctaves(int octaves);

        uint32_t GetSeed() const;
        void SetSeed(uint32_t seed);

        uint32_t GetWidth() const;
        void SetWidth(uint32_t width);

        uint32_t GetDepth() const;
        void SetDepth(uint32_t depth);

        float GetOffset() const;
        void SetOffset(float offset);

        float GetHeight(uint32_t) const;

    private:
        double frequency;
        int octaves;
        uint32_t seed;
        uint32_t width;
        uint32_t depth;
        float offset;
        std::vector<float> heights;
    };
};
