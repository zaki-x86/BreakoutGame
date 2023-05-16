#include "Game.h"
#include "config.h"

// Player data
// TODO: move this to a player class if needed
// Initial size of the player paddle
static const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
// Initial velocity of the player paddle
static const float PLAYER_VELOCITY(500.0f);

Game::Game(unsigned int width, unsigned int height)
    : m_State(GAME_ACTIVE), m_Keys(), m_Width(width), m_Height(height)
    , m_Renderer(nullptr)
{
}

Game::~Game() {}

void Game::Init() {
    ResourceManager::LoadShader("assets/shaders/sprite.vs", "assets/shaders/sprite.fs", "", "sprite");

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width()), 
        static_cast<float>(this->Height()), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

    m_Renderer = std::make_shared<SpriteRenderer>(ResourceManager::GetShader("sprite"));
    
    // load textures
    ResourceManager::LoadTexture("assets/textures/background.jpg", false, "background");
    ResourceManager::LoadTexture("assets/textures/awesomeface.png", true, "face");
    ResourceManager::LoadTexture("assets/textures/block.png", false, "block");
    ResourceManager::LoadTexture("assets/textures/block_solid.png", false, "block_solid");
    ResourceManager::LoadTexture("assets/textures/paddle.png", true, "paddle");

    // load levels
    GameLevel one;
    one.Load("assets/levels/one.lvl", this->Width(), this->Height() / 2);
    GameLevel two;
    two.Load("assets/levels/two.lvl", this->Width(), this->Height() / 2);
    GameLevel three;
    three.Load("assets/levels/three.lvl", this->Width(), this->Height() / 2);
    GameLevel four;
    four.Load("assets/levels/four.lvl", this->Width(), this->Height() / 2);

    this->m_Levels.push_back(one);
    this->m_Levels.push_back(two);
    this->m_Levels.push_back(three);
    this->m_Levels.push_back(four);
    this->m_CurrentLevel = 0;

    // player setup
    GameObjectConfig playerConfig;
    playerConfig.Position = glm::vec2(this->Width() / 2.0f - PLAYER_SIZE.x / 2.0f, 
        this->Height() - PLAYER_SIZE.y);
    playerConfig.Size = PLAYER_SIZE;
    playerConfig.Velocity = glm::vec2(PLAYER_VELOCITY, 0.0f);
    playerConfig.Color = glm::vec3(1.0f);
    playerConfig.Sprite = ResourceManager::GetTexture("paddle");
    this->m_Player = std::make_shared<GameObject>(playerConfig);
}

void Game::ProcessInput(float dt) {
    if (this->m_State == GAME_ACTIVE)
    {
        float velocity = PLAYER_VELOCITY * dt;
        // move playerboard
        if (this->m_Keys[GLFW_KEY_A])
        {
            if (m_Player->Position().x >= 0.0f)
                m_Player->Position().x -= velocity;
        }
        if (this->m_Keys[GLFW_KEY_D])
        {
            if (m_Player->Position().x <= this->m_Width - m_Player->Size().x)
                m_Player->Position().x += velocity;
        }
    }
}

void Game::Update(float dt) {
    UNUSED(dt);
}

void Game::Render()
{
    if(this->m_State == GAME_ACTIVE)
    {
        // draw background
        m_Renderer->DrawSprite(ResourceManager::GetTexture("background"), 
            glm::vec2(0.0f, 0.0f), glm::vec2(this->Width(), this->Height()), 0.0f
        );
        // draw level
        this->m_Levels[this->m_CurrentLevel].Draw(*m_Renderer);
    }

    m_Player->Draw(*m_Renderer);  
} 
