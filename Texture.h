#ifndef __TEXTURE_H__
#define __TEXTURE_H__


#include "Vertex.h"


class Texture
{
private:
    const double m_ox;
    const double m_oy;

    int m_x;
    int m_y;


public:
    Texture(const double x, const double y);
    ~Texture();

    void resize(const int width, const int height);

    int getRoundX() const;
    int getRoundY() const;
    double getX() const;
    double getY() const;


};



#endif //__TEXTURE_H__
