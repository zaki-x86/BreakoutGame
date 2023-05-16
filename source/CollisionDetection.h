#ifndef _COLLISION_DETECTION_H_
#define _COLLISION_DETECTION_H_

#include "common.h"

#include <tuple>

struct GameObject;
struct BallObject;

enum class Direction
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};

using Collision = std::tuple<bool, Direction, glm::vec2>;

Direction VectorDirection(glm::vec2 target)
{
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),	// up
        glm::vec2(1.0f, 0.0f),	// right
        glm::vec2(0.0f, -1.0f),	// down
        glm::vec2(-1.0f, 0.0f)	// left
    };
    float max = 0.0f;
    unsigned int best_match = -1;
    for (unsigned int i = 0; i < 4; i++)
    {
        float dot_product = glm::dot(glm::normalize(target), compass[i]);
        if (dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return (Direction)best_match;
}  

bool CheckCollision(const GameObject& a, const GameObject& b)
{
    // collision x-axis?
    bool collisionX = a.Position().x + a.Size().x >= b.Position().x &&
        b.Position().x + b.Size().x >= a.Position().x;
    // collision y-axis?
    bool collisionY = a.Position().y + a.Size().y >= b.Position().y &&
        b.Position().y + b.Size().y >= a.Position().y;
    
    // collision only if on both axes
    return collisionX && collisionY;
}

Collision CheckCollision(const BallObject& a, const GameObject& b)
{
    // get center point circle first 
    glm::vec2 center(a.Position() + a.Radius());
    // calculate AABB info (center, half-extents)
    glm::vec2 aabbHalfExtents(b.Size().x / 2.0f, b.Size().y / 2.0f);
    glm::vec2 aabbCenter(b.Position().x + aabbHalfExtents.x, b.Position().y + aabbHalfExtents.y);
    // get difference vector between both centers
    glm::vec2 difference = center - aabbCenter;
    glm::vec2 clamped = glm::clamp(difference, -aabbHalfExtents, aabbHalfExtents);
    // add clamped value to AABB_center and we get the value of box closest to circle
    glm::vec2 closest = aabbCenter + clamped;
    // retrieve vector between center circle and closest point AABB and check if length <= radius
    difference = closest - center;
    
    if (glm::length(difference) <= a.Radius())
        return std::make_tuple(true, VectorDirection(difference), difference);
    else
        return std::make_tuple(false, Direction::UP, glm::vec2(0.0f, 0.0f));
}


#endif // !_COLLISION_DETECTION_H_