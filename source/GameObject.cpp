#include "GameObject.h"

GameObject::GameObject()
    : m_Config({glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), Texture2D(), glm::vec3(1.0f), glm::vec2(0.0f), 0.0f, false, false})
{
}

GameObject::GameObject(const GameObjectConfig &config)
    : m_Config(config)
{
}

void GameObject::Update(float dt) {
    UNUSED(dt);
}

void GameObject::Draw(SpriteRenderer &renderer)
{
    renderer.DrawSprite(this->m_Config.Sprite, this->m_Config.Position, this->m_Config.Size, this->m_Config.Rotation, this->m_Config.Color);
}