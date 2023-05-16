# `ResourceManager` Class

A static singleton ResourceManager class that hosts several functions to load Textures and Shaders. Each loaded texture and/or shader is also stored for future reference by string handles. All functions and resources are static, and no public constructor is defined.

## Class API

### Public Members

```cpp
static std::map<std::string, Shader> Shaders
```

A map that stores the loaded shaders with their corresponding string names as keys.

```cpp
static std::map<std::string, Texture2D> Textures
```

A map that stores the loaded textures with their corresponding string names as keys.

---

### Public Static Functions

```cpp
static Shader LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name)
```

Loads (and generates) a shader program from file by loading the vertex, fragment (and geometry) shader's source code. If `gShaderFile` is not nullptr, it also loads a geometry shader. The shader is then stored in the Shaders map with the specified name as the key. Returns the loaded shader.

```cpp
static Shader GetShader(std::string name)
```

Retrieves a stored shader from the Shaders map based on the given name. Returns the shader associated with the specified name.

```cpp
static Texture2D LoadTexture(const char *file, bool alpha, std::string name)
```

Loads (and generates) a texture from file. If alpha is true, the texture is assumed to have an alpha channel. The texture is stored in the Textures map with the specified name as the key. Returns the loaded texture.

```cpp
static Texture2D GetTexture(std::string name)
```

Retrieves a stored texture from the Textures map based on the given name. Returns the texture associated with the specified name.

```cpp
static void Clear()
```

Properly de-allocates all loaded resources. Deletes all shaders and textures that were loaded by calling the appropriate cleanup functions.

---

### Private Members

```cpp
ResourceManager()
```

Private constructor. No actual ResourceManager objects should be created. All members and functions are publicly available as static members.

---

### Private Static Functions

```cpp
static Shader loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile)
```

Loads and generates a shader from file. Reads the vertex shader code from vShaderFile, the fragment shader code from fShaderFile, and optionally the geometry shader code from gShaderFile. Returns the generated shader.

```cpp
static Texture2D loadTextureFromFile(const char *file, bool alpha)
```

Loads a single texture from file. If alpha is true, the texture is assumed to have an alpha channel. Returns the loaded texture.

---

## Comments and Notes

- The ResourceManager class provides a centralized place to load and manage resources such as shaders and textures.
- The class uses static member variables and functions to ensure there is only one instance of the resource manager and to provide easy access to loaded resources.
- Shaders and textures are stored in `std::map` containers, allowing efficient lookup based on string names.
- The `Clear()` function is responsible for properly deallocating all loaded resources. It iterates over the maps and deletes the shader and texture objects.
- The `loadShaderFromFile()` function reads shader source code from file using ifstream and stringstream.
- The `loadTextureFromFile()` function uses the `stb_image` library to load the image data from file.