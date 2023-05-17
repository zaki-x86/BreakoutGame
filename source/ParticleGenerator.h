#ifndef _PARTICLE_GENERATOR_H
#define _PARTICLE_GENERATOR_H
#include <vector>

#include "common.h"

#include "Shader.h"
#include "Texture.h"
#include "GameObject.h"


class Particle {
public:
    Particle() : m_Position(0.0f), m_Velocity(0.0f), m_Color(1.0f), m_Life(0.0f) { }
    Particle(glm::vec2 pos, glm::vec2 vel, glm::vec4 color, float life)
        : m_Position(pos), m_Velocity(vel), m_Color(color), m_Life(life) { }
    
    inline constexpr const glm::vec2& Position() const { return m_Position; }
    inline glm::vec2& Position() { return m_Position; }

    inline constexpr const glm::vec2& Velocity() const { return m_Velocity; }
    inline glm::vec2& Velocity() { return m_Velocity; }

    inline constexpr const glm::vec4& Color() const { return m_Color; }
    inline glm::vec4& Color() { return m_Color; }

    inline constexpr const float& Life() const { return m_Life; }
    inline float& Life() { return m_Life; }
    
private:
    glm::vec2 m_Position, m_Velocity;
    glm::vec4 m_Color;
    float m_Life;
};


// ParticleGenerator acts as a container for rendering a large number of 
// particles by repeatedly spawning and updating particles and killing 
// them after a given amount of time.
class ParticleGenerator
{
public:
    ParticleGenerator(Shader shader, Texture2D texture, unsigned int amount);

    void Update(float dt, GameObject &object, unsigned int newParticles, glm::vec2 offset = glm::vec2(0.0f, 0.0f));

    void Draw();

private:
    Shader m_Shader;
    Texture2D m_Texture;
    
    std::vector<Particle> m_Particles;
    unsigned int m_Amount;

    unsigned int m_VAO;

    unsigned int lastUsedParticle;

private:
    // initializes buffer and vertex attributes
    void init();
    // returns the first Particle index that's currently unused e.g. Life <= 0.0f or 0 if no particle is currently inactive
    unsigned int firstUnusedParticle();
    // respawns particle
    void respawnParticle(Particle &particle, GameObject &object, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
};

#endif