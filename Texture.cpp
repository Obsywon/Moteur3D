#include "Texture.h"

Texture::Texture(const double x, const double y) : m_ox{x}, m_oy{y}
{
}

Texture::~Texture()
{
}

void Texture::resize(const int width, const int height)
{
    m_x = width * m_ox;
    m_y = height * m_oy;
}

int Texture::getRoundX() const
{
    return m_x;
}
int Texture::getRoundY() const
{
    return m_y;
}
double Texture::getX() const
{
    return m_ox;
}
double Texture::getY() const
{
    return m_oy;
}