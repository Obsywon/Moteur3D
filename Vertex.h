#ifndef __VERTEX_H__
#define __VERTEX_H__


#include <iostream>
#include "tgaimage.h"



class Vertex
{
private:
    float _x;
    float _y;
    float _z;

    friend std::ostream& operator <<(std::ostream &s, const Vertex& vertex);
    friend bool operator== (Vertex &s, Vertex &t);

public:
    
    Vertex(const float x, const float y, const float z);
    ~Vertex();

    int getX() const;
    int getY() const;
    int getZ() const;

    void draw_line (const Vertex &end, TGAImage &img, TGAColor color) const;


    void resize(const int width, const int height);
};






#endif //__VERTEX_H__