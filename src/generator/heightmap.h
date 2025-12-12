#pragma once

namespace Generator
{
    class HeightMap
    {
    public:
        virtual float GetHeight(int x, int z) = 0;
        virtual ~HeightMap() = default;
    };
};
