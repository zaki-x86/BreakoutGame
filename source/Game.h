#ifndef _GAME_H_
#define _GAME_H_

#include "common.h"

#include "ResourceManager.h"
#include "Shader.h"
#include "SpriteRenderer.h"

// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
}; 

class Game
{
public:        
    // constructor/destructor
    // TODO: add a constructor that takes in a config file
    // TODO: configure the constructor as a singleton
    Game(unsigned int width, unsigned int height);
    ~Game();

    // initialize game state (load all shaders/textures/levels)
    void Init();

    // game loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();

    // setters/accessors
    inline constexpr const unsigned int& Width() const {
        return this->m_Width;
    }

    inline constexpr unsigned int& Width() {
        return this->m_Width;
    }

    inline constexpr const unsigned int& Height() const {
        return this->m_Height;
    }

    inline constexpr unsigned int& Height() {
        return this->m_Height;
    }

    inline constexpr const GameState& State() const {
        return this->m_State;
    }

    inline constexpr GameState& State() {
        return this->m_State;
    }

    inline constexpr const bool& Keys(const unsigned int& key) const {
        return this->m_Keys[key];
    }

    inline constexpr bool& Keys(const unsigned int& key) {
        return this->m_Keys[key];
    }
    

private:
    // game state
    GameState m_State;	
    bool m_Keys[1024];
    unsigned int m_Width, m_Height;

    // renderer
    std::unique_ptr<SpriteRenderer> m_Renderer;
};

#endif // !_GAME_H_