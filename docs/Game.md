# `Game`

The `Game` class contains all relevant render and gameplay code. The idea of such a game class is that it (sort of) organizes your game code, while also decoupling all windowing code from the game. This way, you could use the same class in a completely different windowing library (like SDL or SFML for example) without much effort.

- The class constructor initializes the game with a given (width, height) to set the game resolution.
- Using the game class, you can load all game assets such as: shaders, textures, and gameplay state using `Init`.
- We can process input as stored within the Keys array by calling `ProcessInput`. This function is called every frame.
- Update all gameplay events (like player/ball movement) in the `Update` function. This function is also called every frame.
- Last, we can render the game by calling `Render`. Note that we split the movement logic from the render logic.

The game objective is to let the ball collide with all the bricks until each of the destroyable bricks are destroyed, but this all within the condition that the ball is not allowed to reach the bottom edge of the screen.

## Game Components

- `Game` class: contains all relevant render and gameplay code.
- [`GameObject`](GameObject.md) class: encapsulates all game object logic.
- [`GameLevel`](GameLevel.md) class: is a container for bricks and implements the logic for loading levels.
- [`BallObject`](BallObject.md) class: encapsulates all ball logic.

## Game States

The game has 3 states:

- `GAME_ACTIVE`: the game is currently active and the player can move the paddle to play the game.

- `GAME_MENU`: the game is in the main menu and the player can choose to start the game or exit the game.

- `GAME_WIN`: the game is won and the player can choose to replay the game or exit the game.

The current game state can be accessed and modified via `State()` function.

## Game Resolution

The game is initialized with a given (width, height) to set the game resolution. The game resolution is used to calculate the aspect ratio of the game window and the size of the game objects.

It is mandatory to specify the game resolution when constructing the game object. Also, the game resolution can be accessed and modified via `Width()` and `Height()` functions.

## Game Initialization

## Game Input

## Game Levels

This game features a total of 4 levels:

- Level 0: [Standard]()
- Level 1: [A few small gaps]()
- Level 2: [Space invader]()
- Level 3: [Bounce galore]()

All game levels assets are initialized via `init()` function.

The current active level can be accessed and modified via `CurrentLevel()` function.

## Game Paddle

The paddle is controlled by the player and is used to hit the ball back up towards the bricks. The paddle is the only game object that is not destroyed when hit by the ball. The paddle is controlled by the player using the `A` and `D` keys.

The paddle object can be accessed via `Player()` function.

## Game Ball

The ball is the game object that is used to hit the bricks. The ball is destroyed when it hits the bottom edge of the screen. The ball is controlled by the player using the `SPACE` key.

The ball object can be accessed via `Ball()` function.