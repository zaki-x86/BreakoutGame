# `SpriteRenderer`

Sprite is a 2D image used together with some data to position it in a larger world (e.g. position, rotation, and size). Basically, sprites are the render-able image/texture objects we use in a 2D game.

## 2D Projection Matrix

We don't need any perspective applied to the coordinates, since the game is entirely in 2D, so an orthographic projection matrix would suit the rendering quite well. Because an orthographic projection matrix directly transforms all coordinates to normalized device coordinates, we can choose to specify the world coordinates as screen coordinates by defining the projection matrix as follows:

```cpp
glm::mat4 projection = glm::ortho(0.0f, SCR_WIDTH, SCR_HEIGHT, 0.0f, -1.0f, 1.0f); 
```

## Rendering sprites

We create a textured quad that we can transform with a model matrix, after which we project it using the previously defined orthographic projection matrix.

> Since Breakout is a single-scene game, there is no need for a view/camera matrix. Using the projection matrix we can directly transform the world-space coordinates to normalized device coordinates.