#ifndef BALLOBJECT_H
#define BALLOBJECT_H

#include "common.h"

#include "GameObject.h"
#include "Texture.h"

struct BallObjectConfig : public GameObjectConfig {
    float Radius;
    bool  Stuck;
};

// BallObject holds the state of the Ball object inheriting
// relevant state data from GameObject. Contains some extra
// functionality specific to Breakout's ball object that
// were too specific for within GameObject alone.
class BallObject : public GameObject
{
public:
    BallObject();

    BallObject(const BallObjectConfig& config);

    glm::vec2 Move(float dt, unsigned int window_width);

    void Reset(glm::vec2 position, glm::vec2 velocity);

    inline constexpr const float& Radius() const {
        return this->m_Radius;
    }

    inline constexpr float& Radius() {
        return this->m_Radius;
    }

    inline constexpr const bool& Stuck() const {
        return this->m_Stuck;
    }

    inline constexpr bool& Stuck() {
        return this->m_Stuck;
    }

private:
    float m_Radius;
    bool  m_Stuck;
};

#endif