# `BallObject`

The `BallObject` class extends `GameObject` class. In addition to the general game object components, a ball has a `radius`, and an extra boolean value indicating whether the ball is `stuck` on the player paddle or it's allowed free movement. When the game starts, the ball is initially stuck on the player paddle until the player starts the game by pressing some arbitrary key.

## API

In addition to [`GameObject`](GameObject.md) class members, the `BallObject` class also has the following members:

```cpp
BallObject()
```

The constructor of BallObject initializes its own values, but also initializes the underlying GameObject.

```cpp
BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite)
```

The constructor of BallObject initializes its own values, and specify a texture for the ball.

```cpp
glm::vec2 Move(float dt, unsigned int window_width)
```

Moves the ballbased on its velocity, keeping it constrained within the window bounds (except bottom edge); returns new position.

```cpp
void Reset(glm::vec2 position, glm::vec2 velocity)
```

Resets the ball to original state with given position and velocity.

```cpp
const float Radius() const
float Radius()
```

Gets the ball radius.

```cpp
const bool Stuck() const
bool Stuck()
```

Gets the ball stuck state.
