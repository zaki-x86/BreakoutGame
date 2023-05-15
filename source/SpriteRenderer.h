#ifndef _SPRITE_RENDERER_H_
#define _SPRITE_RENDERER_H_

#include "common.h"

#include "Shader.h"
#include "Texture.h"

class SpriteRenderer
{
public:
    SpriteRenderer(const Shader &shader);
    ~SpriteRenderer();

    void DrawSprite(const Texture2D &texture, glm::vec2 position,
                    glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f,
                    glm::vec3 color = glm::vec3(1.0f));

private:
    Shader m_Shader;
    unsigned int m_QuadVAO;

    void initRenderData();
};

#endif // !_SPRITE_RENDERER_H_
