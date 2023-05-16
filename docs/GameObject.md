# `GameObject`

A `GameObject` object acts as the base representation of an object inside the game. Such a game object holds state data like its position, size, and velocity. It holds a color, a rotation component, whether it is solid and/or destroyed, and it also stores a Texture2D variable as its sprite.

Each object in the game is represented as a `GameObject` or a derivative of this class.

## API

### `struct GameObjectConfig`

The `GameObjectConfig` struct is used to configure a `GameObject` object. It contains the following fields:

```c
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
```

### `GameObject` class

#### Constructors

* The default constructor `GameObject()` initializes the `GameObject` object with default values for its configuration.
* `GameObject(GameObjectConfig config)` initializes the `GameObject` object with the given configuration.

#### Public Member Functions

##### Render

* `virtual void Update(float dt)` is a virtual function that can be overridden by a derived class. This function is called every frame to update the game object's state.
* `virtual void Draw(SpriteRenderer &renderer)` is a virtual function that can be overridden by a derived class. This function is called every frame to render the game object.

##### Accessors

The `GameObject` class provides the following accessor functions to modify its state:

```cpp
const glm::vec2 &Position() const;
glm::vec2 &Position();

const glm::vec2 &Size() const;
glm::vec2 &Size();

const glm::vec2 &Velocity() const;
glm::vec2 &Velocity();

const glm::vec3 &Color() const;
glm::vec3 &Color();

const Texture2D &Sprite() const;
Texture2D &Sprite();

const float &Rotation() const;
float &Rotation();

const bool &IsSolid() const;
bool &IsSolid();

const bool &Destroyed() const;
bool &Destroyed();

const GameObjectConfig &Config() const;
GameObjectConfig &Config();
```
