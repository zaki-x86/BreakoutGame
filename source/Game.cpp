#include "Game.h"
#include "config.h"

Game::Game(unsigned int width, unsigned int height)
    : m_State(GAME_ACTIVE), m_Keys(), m_Width(width), m_Height(height)
{
}

Game::~Game() {}

void Game::Init() {}

void Game::ProcessInput(float dt) {
    UNUSED(dt);
}

void Game::Update(float dt) {
    UNUSED(dt);
}

void Game::Render() {}
