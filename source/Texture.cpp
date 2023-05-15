#include <iostream>

#include "Texture.h"


Texture2D::Texture2D()
    : m_Width(0), m_Height(0), m_InternalFormat(GL_RGB), m_ImageFormat(GL_RGB), m_WrapS(GL_REPEAT), m_WrapT(GL_REPEAT), m_FilterMin(GL_LINEAR), m_FilterMax(GL_LINEAR)
{
    glGenTextures(1, &this->m_ID);
}

Texture2D::Texture2D(const Texture2DConfig& config)
    : m_Width(config.Width), m_Height(config.Height), m_InternalFormat(config.InternalFormat), m_ImageFormat(config.ImageFormat), m_WrapS(config.WrapS), m_WrapT(config.WrapT), m_FilterMin(config.FilterMin), m_FilterMax(config.FilterMax)
{
    glGenTextures(1, &this->m_ID);
}

void Texture2D::Generate(unsigned char* data)
{
    // create Texture
    glBindTexture(GL_TEXTURE_2D, this->m_ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->m_InternalFormat, m_Width, m_Height, 0, this->m_ImageFormat, GL_UNSIGNED_BYTE, data);

    // set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->m_WrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->m_WrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->m_FilterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->m_FilterMax);

    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Generate(unsigned int width, unsigned int height, unsigned char* data)
{
    this->m_Width = width;
    this->m_Height = height;

    // create Texture
    glBindTexture(GL_TEXTURE_2D, this->m_ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->m_InternalFormat, m_Width, m_Height, 0, this->m_ImageFormat, GL_UNSIGNED_BYTE, data);

    // set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->m_WrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->m_WrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->m_FilterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->m_FilterMax);

    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Update(unsigned char* data)
{
    // create Texture
    glBindTexture(GL_TEXTURE_2D, this->m_ID);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, this->m_ImageFormat, GL_UNSIGNED_BYTE, data);

    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->m_ID);
}