#include "GameLevel.h"

#include <fstream>
#include <sstream>

void GameLevel::Load(const char *file, unsigned int levelWidth, unsigned int levelHeight)
{
    this->m_Bricks.clear();

    unsigned int tileCode;
    GameLevel level;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<unsigned int>> tileData;
    if (fstream)
    {
        while (std::getline(fstream, line))
        {
            std::istringstream sstream(line);
            std::vector<unsigned int> row;
            while (sstream >> tileCode)
                row.push_back(tileCode);
            tileData.push_back(row);
        }
        if (tileData.size() > 0)
            this->init(tileData, levelWidth, levelHeight);
    }
}

void GameLevel::Draw(SpriteRenderer &renderer)
{
    for (GameObject &tile : this->m_Bricks)
        if (!tile.Destroyed())
            tile.Draw(renderer);
}

bool GameLevel::IsCompleted()
{
    for (GameObject &tile : this->m_Bricks)
        if (!tile.IsSolid() && !tile.Destroyed())
            return false;
    return true;
}

void GameLevel::init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight)
{
    // calculate dimensions
    unsigned int height = tileData.size();
    unsigned int width  = tileData[0].size();
    float unit_width    = levelWidth / static_cast<float>(width);
    float unit_height   = levelHeight / height;

    // initialize level tiles based on tileData		
    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            GameObjectConfig brick_config{};

            // check block type from level data (2D level array)
            if (tileData[y][x] == 1) // solid
            {
                brick_config.Position = glm::vec2(unit_width * x, unit_height * y);
                brick_config.Size = glm::vec2(unit_width, unit_height);
                brick_config.Sprite = ResourceManager::GetTexture("block_solid");
                brick_config.Color = glm::vec3(0.8f, 0.8f, 0.7f);
                brick_config.IsSolid = true;

                this->m_Bricks.push_back(GameObject(brick_config));
            }
            else if (tileData[y][x] > 1)	
            {
                brick_config.Color = glm::vec3(1.0f); // original: white
                if (tileData[y][x] == 2)
                    brick_config.Color = glm::vec3(0.2f, 0.6f, 1.0f);
                else if (tileData[y][x] == 3)
                    brick_config.Color = glm::vec3(0.0f, 0.7f, 0.0f);
                else if (tileData[y][x] == 4)
                    brick_config.Color = glm::vec3(0.8f, 0.8f, 0.4f);
                else if (tileData[y][x] == 5)
                    brick_config.Color = glm::vec3(1.0f, 0.5f, 0.0f);

                brick_config.Position = glm::vec2(unit_width * x, unit_height * y);
                brick_config.Size = glm::vec2(unit_width, unit_height);
                brick_config.Sprite = ResourceManager::GetTexture("block");
                brick_config.IsSolid = false;

                this->m_Bricks.push_back(GameObject(brick_config));
            }
        }
    } 
}