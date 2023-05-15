#include "Game.h"
#include "config.h"

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

    m_Renderer = std::make_unique<SpriteRenderer>(ResourceManager::GetShader("sprite"));
    ResourceManager::LoadTexture("assets/textures/awesomeface.png", true, "face");
}

void Game::ProcessInput(float dt) {
    UNUSED(dt);
}

void Game::Update(float dt) {
    UNUSED(dt);
}

void Game::Render()
{
    m_Renderer->DrawSprite(ResourceManager::GetTexture("face"), 
        glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
} 
