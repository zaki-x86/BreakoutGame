#ifndef _GAME_LEVEL_H_
#define _GAME_LEVEL_H_

#include "common.h"
#include "config.h"

#include "GameObject.h"
#include "ResourceManager.h"

#include <vector>

class GameLevel
{
public:    
    GameLevel() : m_Bricks() { }

    void Load(const char *file, unsigned int levelWidth, unsigned int levelHeight);

    void Draw(SpriteRenderer &renderer);

    bool IsCompleted();

    const GameObject* data() const { return m_Bricks.data(); }

    GameObject* data() { return m_Bricks.data(); }

private:
    void init(std::vector<std::vector<unsigned int>> tileData, 
                unsigned int levelWidth, unsigned int levelHeight);

private:
    std::vector<GameObject> m_Bricks;
};

#endif // !_GAME_LEVEL_H_