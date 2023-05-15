#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <GL/glew.h>

struct Texture2DConfig {
    unsigned int Width;
    unsigned int Height;
    unsigned int InternalFormat;
    unsigned int ImageFormat;
    unsigned int WrapS;
    unsigned int WrapT;
    unsigned int FilterMin;
    unsigned int FilterMax;
};

// Texture2D is able to store and configure a texture in OpenGL.
// It also hosts utility functions for easy management.
class Texture2D
{
public:
    // constructor (sets default texture modes)
    Texture2D();
    Texture2D(const Texture2DConfig& config);

    // generates texture from image data
    void Generate(unsigned char* data);
    void Generate(unsigned int width, unsigned int height, unsigned char* data);

    // updates texture image data
    // this must be called when any config changes are made
    void Update(unsigned char* data);

    // binds the texture as the current active GL_TEXTURE_2D texture object
    void Bind() const;

    // texture configuration
    inline constexpr const unsigned int& Width() const { return this->m_Width; }

    inline constexpr unsigned int& Width() { return this->m_Width; }

    inline constexpr const unsigned int& Height() const { return this->m_Height; }

    inline constexpr unsigned int& Height() { return this->m_Height; }

    inline constexpr const unsigned int& InternalFormat() const { return this->m_InternalFormat; }

    inline constexpr unsigned int& InternalFormat() { return this->m_InternalFormat; }

    inline constexpr const unsigned int& ImageFormat() const { return this->m_ImageFormat; }

    inline constexpr unsigned int& ImageFormat() { return this->m_ImageFormat; }

    inline constexpr const unsigned int& WrapS() const { return this->m_WrapS; }
    
    inline constexpr unsigned int& WrapS() { return this->m_WrapS; }

    inline constexpr const unsigned int& WrapT() const { return this->m_WrapT; }

    inline constexpr unsigned int& WrapT() { return this->m_WrapT; }

    inline constexpr const unsigned int& FilterMin() const { return this->m_FilterMin; }

    inline constexpr unsigned int& FilterMin() { return this->m_FilterMin; }

    inline constexpr const unsigned int& FilterMax() const { return this->m_FilterMax; }

    inline constexpr unsigned int& FilterMax() { return this->m_FilterMax; }

    inline constexpr const unsigned int& ID() const { return this->m_ID; }    

private:
    // holds the m_ID of the texture object, used for all texture operations to reference to this particular texture
    unsigned int m_ID;

    // texture image dimensions
    // width and height of loaded image in pixels
    unsigned int m_Width, m_Height; 

    // texture Format
    // format of texture object
    unsigned int m_InternalFormat;
    
    // format of loaded image
    unsigned int m_ImageFormat;

    // texture configuration
    unsigned int m_WrapS; // wrapping mode on S axis
    unsigned int m_WrapT; // wrapping mode on T axis
    unsigned int m_FilterMin; // filtering mode if texture pixels < screen pixels
    unsigned int m_FilterMax; // filtering mode if texture pixels > screen pixels
};

#endif // !_TEXTURE_H_