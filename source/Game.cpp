#include "Game.h"
#include "config.h"

#include "CollisionDetection.h"

// Player data
// ------------
// TODO: move this to a player class if needed
// Initial size of the player paddle
static const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
// Initial velocity of the player paddle
static const float PLAYER_VELOCITY(500.0f);

// Ball data
// ---------
// Initial velocity of the Ball
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// Radius of the ball object
const float BALL_RADIUS = 12.5f;

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
    GameObjectConfig playerConfig{};
    playerConfig.Position = glm::vec2(this->Width() / 2.0f - PLAYER_SIZE.x / 2.0f, 
        this->Height() - PLAYER_SIZE.y);
    playerConfig.Size = PLAYER_SIZE;
    playerConfig.Velocity = glm::vec2(PLAYER_VELOCITY, 0.0f);
    playerConfig.Color = glm::vec3(1.0f);
    playerConfig.Sprite = ResourceManager::GetTexture("paddle");
    this->m_Player = std::make_shared<GameObject>(playerConfig);

    // ball setup
    BallObjectConfig ballConfig{};
    ballConfig.Radius = BALL_RADIUS;
    ballConfig.Stuck = true;
    ballConfig.Position = this->m_Player->Position() + glm::vec2(this->m_Player->Size().x / 2.0f - BALL_RADIUS, 
        -BALL_RADIUS * 2.0f);
    ballConfig.Size = glm::vec2(BALL_RADIUS * 2.0f);
    ballConfig.Velocity = INITIAL_BALL_VELOCITY;
    ballConfig.Color = glm::vec3(1.0f);
    ballConfig.Sprite = ResourceManager::GetTexture("face");
    this->m_Ball = std::make_shared<BallObject>(ballConfig);
}

void Game::ProcessInput(float dt) {
    if (this->m_State == GAME_ACTIVE)
    {
        float velocity = PLAYER_VELOCITY * dt;
        // move playerboard
        if (this->m_Keys[GLFW_KEY_A])
        {
            if (m_Player->Position().x >= 0.0f) {
                m_Player->Position().x -= velocity;
                if (m_Ball->Stuck())
                    m_Ball->Position().x -= velocity;
            }
        }
        if (this->m_Keys[GLFW_KEY_D])
        {
            if (m_Player->Position().x <= this->m_Width - m_Player->Size().x) {
                m_Player->Position().x += velocity;
                if (m_Ball->Stuck())
                    m_Ball->Position().x += velocity;
            }
        }
        if (this->m_Keys[GLFW_KEY_SPACE])
            m_Ball->Stuck() = false;
    }
}

void Game::ProcessCollisions() {
    for (GameObject &box : this->m_Levels[this->m_CurrentLevel].Bricks())
    {
        if (!box.Destroyed())
        {
            Collision collision = CheckCollision(*m_Ball, box);
            if (std::get<0>(collision)) // if collision is true
            {
                // destroy block if not solid
                if (!box.IsSolid())
                    box.Destroyed() = true;
                // collision resolution
                Direction dir = std::get<1>(collision);
                glm::vec2 diff_vector = std::get<2>(collision);
                if (dir == Direction::LEFT || dir == Direction::RIGHT) // horizontal collision
                {
                    m_Ball->Velocity().x = -m_Ball->Velocity().x; // reverse horizontal velocity
                    // relocate
                    float penetration = m_Ball->Radius() - std::abs(diff_vector.x);
                    if (dir == Direction::LEFT)
                        m_Ball->Position().x += penetration; // move ball to right
                    else
                        m_Ball->Position().x -= penetration; // move ball to left;
                }
                else // vertical collision
                {
                    m_Ball->Velocity().y = -m_Ball->Velocity().y; // reverse vertical velocity
                    // relocate
                    float penetration = m_Ball->Radius() - std::abs(diff_vector.y);
                    if (dir == Direction::UP)
                        m_Ball->Position().y -= penetration; // move ball back up
                    else
                        m_Ball->Position().y += penetration; // move ball back down
                }
            }
        }
    }

    Collision result = CheckCollision(*m_Ball, *m_Player);
    if (!m_Ball->Stuck() && std::get<0>(result))
    {
        // check where it hit the board, and change velocity based on where it hit the board
        float centerBoard = m_Player->Position().x + m_Player->Size().x / 2.0f;
        float distance = (m_Ball->Position().x + m_Ball->Radius()) - centerBoard;
        float percentage = distance / (m_Player->Size().x / 2.0f);
        // then move accordingly
        float strength = 2.0f;
        glm::vec2 oldVelocity = m_Ball->Velocity();
        m_Ball->Velocity().x = INITIAL_BALL_VELOCITY.x * percentage * strength; 
        m_Ball->Velocity().y = -1.0f * abs(m_Ball->Velocity().y); 
        m_Ball->Velocity() = glm::normalize(m_Ball->Velocity()) * glm::length(oldVelocity);
    } 
}

void Game::Update(float dt) {
    m_Ball->Move(dt, this->m_Width);
    this->ProcessCollisions();
    if (m_Ball->Position().y >= this->Height()) // did ball reach bottom edge?
    {
        this->ResetLevel();
        this->ResetPlayer();
    }
}

void Game::Render()
{
    if(this->m_State == GAME_ACTIVE)
    {
        // draw background
        m_Renderer->DrawSprite(
            ResourceManager::GetTexture("background"), 
            glm::vec2(0.0f, 0.0f), 
            glm::vec2(this->Width(), 
            this->Height()), 
            0.0f);
        
        this->m_Levels[this->m_CurrentLevel].Draw(*m_Renderer);
        m_Ball->Draw(*m_Renderer);
        m_Player->Draw(*m_Renderer);  
    }

}

void Game::ResetLevel()
{
    if (this->m_CurrentLevel == 0)
        this->m_Levels[0].Load("assets/levels/one.lvl", this->Width(), this->Height() / 2);
    else if (this->m_CurrentLevel == 1)
        this->m_Levels[1].Load("assets/levels/two.lvl", this->Width(), this->Height() / 2);
    else if (this->m_CurrentLevel == 2)
        this->m_Levels[2].Load("assets/levels/three.lvl", this->Width(), this->Height() / 2);
    else if (this->m_CurrentLevel == 3)
        this->m_Levels[3].Load("assets/levels/four.lvl", this->Width(), this->Height() / 2);
}

void Game::ResetPlayer()
{
    // reset player/ball stats
    m_Player->Size() = PLAYER_SIZE;
    m_Player->Position() = glm::vec2(this->Width() / 2.0f - PLAYER_SIZE.x / 2.0f, 
        this->Height() - PLAYER_SIZE.y);
    m_Ball->Reset(m_Player->Position() + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, 
        -(BALL_RADIUS * 2.0f)), INITIAL_BALL_VELOCITY);
}
