#ifndef __VERTEX_H__
#define __VERTEX_H__


#include <iostream>
#include <cmath>
#include <vector>
#include "tgaimage.h"


struct vecteur {
    double x;
    double y;
    double z;
};

class Vertex
{
private:
    double m_x;
    double m_y;
    double m_z;

    double m_ox;
    double m_oy;
    double m_oz;    

    friend std::ostream& operator <<(std::ostream &s, const Vertex& vertex);
    friend bool operator== (Vertex &s, Vertex &t);

public:
    
    Vertex(const double x, const double y, const double z);


    ~Vertex();

    int roundX() const;
    int roundY() const;
    int roundZ() const;

    double getX() const;
    double getY() const;
    double getZ() const;


    void rasterize_line(int x0, int x1, int y0, int y1, TGAImage &img, TGAColor color) const;


    void draw_line (const Vertex &end, TGAImage &img, TGAColor color) const;

    void resize(const int width, const int height);

};






#endif //__VERTEX_H__