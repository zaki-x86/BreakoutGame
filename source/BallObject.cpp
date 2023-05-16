#include "BallObject.h"

BallObject::BallObject()
    : GameObject(), m_Radius(12.5f), m_Stuck(true)
{
}

BallObject::BallObject(const BallObjectConfig& config)
    : GameObject(), m_Radius(config.Radius), m_Stuck(config.Stuck)
{
    Config().Position = config.Position;
    Config().Size = glm::vec2(m_Radius * 2, m_Radius * 2);
    Config().Velocity = config.Velocity;
    Config().Sprite = config.Sprite;
    Config().Color = glm::vec3(1.0f);
    Config().IsSolid = false;
    Config().Rotation = 0.0f;
}

glm::vec2 BallObject::Move(float dt, unsigned int window_width)
{
    // if not stuck to player board
    if (!this->m_Stuck)
    {
        // move the ball
        this->Position() += this->Velocity() * dt;
        // then check if outside window bounds and if so, reverse velocity and restore at correct position
        if (this->Position().x <= 0.0f)
        {
            this->Velocity().x = -this->Velocity().x;
            this->Position().x = 0.0f;
        }
        else if (this->Position().x + this->Size().x >= window_width)
        {
            this->Velocity().x = -this->Velocity().x;
            this->Position().x = window_width - this->Size().x;
        }
        if (this->Position().y <= 0.0f)
        {
            this->Velocity().y = -this->Velocity().y;
            this->Position().y = 0.0f;
        }
    }
    return this->Position();
}

void BallObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
    this->Position() = position;
    this->Velocity() = velocity;
    this->m_Stuck = true;
}