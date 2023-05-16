#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "config.h"
#include "common.h"

#include "SpriteRenderer.h"
#include "Texture.h"

struct GameObjectConfig {
  glm::vec2 Position;
  glm::vec2 Size;
  Texture2D Sprite;
  glm::vec3 Color;
  glm::vec2 Velocity;
  float Rotation = 0.0f;
  bool IsSolid;
  bool Destroyed = false;
};

// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
class GameObject {
public:
    // constructor(s)
    GameObject();

    GameObject(const GameObjectConfig &config);

    // draw sprite
    virtual void Update(float dt);
    virtual void Draw(SpriteRenderer &renderer);

    // getters/setters
    inline constexpr const glm::vec2 &Position() const {
        return this->m_Config.Position;
    }

    inline constexpr glm::vec2 &Position() {
        return this->m_Config.Position;
    }

    inline constexpr const glm::vec2 &Size() const {
        return this->m_Config.Size;
    }

    inline constexpr glm::vec2 &Size() {
        return this->m_Config.Size;
    }

    inline constexpr const Texture2D &Sprite() const {
        return this->m_Config.Sprite;
    }

    inline constexpr Texture2D &Sprite() {
        return this->m_Config.Sprite;
    }

    inline constexpr const glm::vec3 &Color() const {
        return this->m_Config.Color;
    }

    inline constexpr glm::vec3 &Color() {
        return this->m_Config.Color;
    }

    inline constexpr const glm::vec2 &Velocity() const {
        return this->m_Config.Velocity;
    }

    inline constexpr glm::vec2 &Velocity() {
        return this->m_Config.Velocity;
    }

    inline constexpr const float &Rotation() const {
        return this->m_Config.Rotation;
    }

    inline constexpr float &Rotation() {
        return this->m_Config.Rotation;
    }

    inline constexpr const bool &IsSolid() const {
        return this->m_Config.IsSolid;
    }

    inline constexpr bool &IsSolid() {
        return this->m_Config.IsSolid;
    }

    inline constexpr const bool &Destroyed() const {
        return this->m_Config.Destroyed;
    }

    inline constexpr bool &Destroyed() {
        return this->m_Config.Destroyed;
    }

    inline constexpr const GameObjectConfig &Config() const {
        return this->m_Config;
    }

    inline constexpr GameObjectConfig &Config() {
        return this->m_Config;
    }


private:
    GameObjectConfig m_Config;
};

#endif