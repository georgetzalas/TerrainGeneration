#pragma once

#include <gfx/opengl/types/texture.h>
#include <world/terrain.h>
#include <stb/stb_image_write.h>

#define TILE_NUMBER 4

enum class Slot{ZERO = 0, ONE, TWO, THREE};

struct Region
{
    int LowHeight;
    int OptimalHeight;
    int HighHeight;
};

struct Tiles
{
    Region regions[TILE_NUMBER];
    Gfx::OpenGL::Texture* textures[TILE_NUMBER];
    int TileNumber;
};

namespace World {
    class Terrain;   
}

class TileManager
{
public:
    TileManager();
    Gfx::OpenGL::Texture* TextureGeneration(uint32_t width, uint32_t depth, World::Terrain* terrain);

    void LoadTile(Gfx::OpenGL::Texture* texture, Slot slot);
    void UnloadTile(Slot slot);
    void UnloadTiles();
private:

    void CalculateRegions();
    float RegionPercetange(Region, float) const;

private:
    Tiles tiles;
};

/*
First Tile
    LowHeight = 0      | (LastHeight = 0)
    OptimalHeight = 50 | (LastHeight = 200/4 = 50)
    HighHight = 100    | (LastHeight = 50)

Second Tile
    LowHeight = 50      | (LastHeight = 50)
    OptimalHeight = 100 | (LastHeight = 100)
    HighHight = 150     | (LastHeight = 100)
 .
 .
 .
*/