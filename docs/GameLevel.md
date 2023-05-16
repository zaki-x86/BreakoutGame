# `GameLevel`

A level in Breakout consists entirely of bricks so we can represent a level by exactly that: a collection of bricks. Because a brick requires the same state as a game object, we're going to represent each brick of the level as a `GameObject`.

Levels are loaded from external files, these text files has a specific format that represents the level structure.

A level is stored in a matrix-like structure where each number represents a type of brick, each one separated by a space. Within the level code we can then assign what each number represents. We have chosen the following representation:

- A number of 0: no brick, an empty space within the level.
- A number of 1: a solid brick, a brick that cannot be destroyed.
- A number higher than 1: a destroyable brick; each subsequent number only differs in color.

## Example of a level file

Here is an example of a level file:

```text
1 1 1 1 1 1 
2 2 0 0 2 2
3 3 4 4 3 3
```

Here is how it is represented in the game:

![Level](./assets/levels-example.png)

## API

A game level object is a container for the bricks of the level. It is responsible for loading the level from a file and storing the bricks in a matrix-like structure.

```cpp
GameLevel()
```

Initializes the level object.

```cpp
Load(const char *file, unsigned int levelWidth, unsigned int levelHeight)
```

Reads the level configuration from a `file`. It sets the level width `levelWidth` which is usually the width of the game window and the level height `levelHeight` which is usually half the height of the game window.

```cpp
void Draw(SpriteRenderer &renderer)
```

Draws all the level's bricks.

```cpp
 bool IsCompleted()
```

Returns `true` if all the bricks in the level are destroyed, `false` otherwise.

```cpp
const GameObject* data() const
```

Returns a pointer to the level's data. This is a pointer to the first element in the level's matrix.
