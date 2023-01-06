#ifndef __FACE_H__
#define __FACE_H__


#include <iostream>
#include <vector>
#include "Vertex.h"


class Face
{
private:
    const std::vector<Vertex> _vertices;

    friend std::ostream& operator <<(std::ostream &s, const Face& face);


public:
    Face(const std::vector<Vertex> &vertices);
    ~Face();


    void draw_triangle(TGAImage &img, TGAColor color);
    
};

#endif //__FACE_H__