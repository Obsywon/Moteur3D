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

    int getX();
    int getY();
    int getZ();

    void draw_line (Vertex &end, TGAImage &img, TGAColor color);


    void resize(const int width, const int height);
};






#endif //__VERTEX_H__