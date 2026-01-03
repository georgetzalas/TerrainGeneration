#include <tile/tile_manager.h>

TileManager::TileManager()
{
    for(int i=0; i<TILE_NUMBER; i++)
    {
        tiles.regions[i] = {0};
        tiles.textures[i] = nullptr;
    }
    tiles.TileNumber = 0;
}

float TileManager::RegionPercetange(Region region, float height) const
{
    if(height < region.LowHeight || height > region.HighHeight)
    {
        return 0.0f;
    }

    if(height < region.OptimalHeight)
    {
        float a = (float)height - (float)region.LowHeight;
        float b = (float)region.OptimalHeight - (float)region.LowHeight;

        return a/b;
    }

    if(height >= region.OptimalHeight)
    {
        float a = (float)region.HighHeight - (float)height;
        float b = (float)region.HighHeight - (float)region.OptimalHeight;

        return a/b;
    }
}

void TileManager::CalculateRegions()
{
    float LastHeight = -1.0f;

    for(int i=0; i<TILE_NUMBER; i++)
    {
        if(tiles.textures[i])
        {
            tiles.regions[i].LowHeight = LastHeight+1;
        
            LastHeight += 255.0f/(float)tiles.TileNumber;
        
            tiles.regions[i].OptimalHeight = LastHeight;
            tiles.regions[i].HighHeight    = (LastHeight - tiles.regions[i].LowHeight) + LastHeight;
        }
    }
}

Gfx::OpenGL::Texture* TileManager::TextureGeneration(uint32_t width, uint32_t depth, World::Terrain* terrain)
{
    int channels = 3;
    int TextureBytes = width * depth * channels;
    unsigned char* TextureData = (unsigned char*)malloc(TextureBytes);
    unsigned char* temp = TextureData;
    
    CalculateRegions();
    
    for(uint32_t z=0; z<depth; z++)
    {
        for(uint32_t x=0; x<width; x++)
        {
            float fRed   = 0.0f;
            float fGreen = 0.0f;
            float fBlue  = 0.0f;

            float height = terrain->GetHeightInterpolated(x, z) * 255.0f;

            for(uint32_t i=0; i<TILE_NUMBER; i++)
            {
                if(tiles.textures[i])
                {
                    glm::vec3 color = tiles.textures[i]->GetColor(x, z);
                    float blend = RegionPercetange(tiles.regions[i], height);

                    fRed   += color.r * blend;
                    fGreen += color.g * blend;
                    fBlue  += color.b * blend;
                }
            }
            
            temp[0] = (unsigned char)fRed;
            temp[1] = (unsigned char)fGreen;
            temp[2] = (unsigned char)fBlue;
        
            temp += 3;
        }
    }

    stbi_write_jpg("res/textures/blend.jpg", width, depth, channels, TextureData, width * channels);

    Gfx::OpenGL::Texture* texture = new Gfx::OpenGL::Texture();
    texture->LoadData(width, depth, TextureData);

    return texture;
}

void TileManager::LoadTile(Gfx::OpenGL::Texture* texture, Slot slot)
{
    if(tiles.textures[(int)slot])
    {
        std::cout << "The slot is occupied, unload first" << std::endl;
        return;
    }

    tiles.textures[(int)slot] = texture;
    tiles.TileNumber++;
}

void TileManager::UnloadTile(Slot slot)
{
    if(tiles.textures[(int)slot] == nullptr)
        return;
    
    tiles.regions[(int)slot] = {0};
    tiles.textures[(int)slot] = nullptr;
    tiles.TileNumber--;
}

void TileManager::UnloadTiles()
{
    for(int i=0; i<TILE_NUMBER; i++)
    {
        tiles.regions[i] = {0};
        tiles.textures[i] = nullptr;
    }
    tiles.TileNumber = 0;
}