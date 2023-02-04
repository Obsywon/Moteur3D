#ifndef __VERTEX_H__
#define __VERTEX_H__


#include <iostream>
#include <cmath>
#include <vector>
#include "tgaimage.h"

struct Vecteur {
    double x;
    double y;
    double z;
    Vecteur static normalize(Vecteur & vecteur){
    double n = sqrt(vecteur.x * vecteur.x + vecteur.y * vecteur.y + vecteur.z * vecteur.z);
    Vecteur v;
    v.x = vecteur.x;
    v.y = vecteur.y;
    v.z = vecteur.z;

    v.x *= (1/n);
    v.y *= (1/n);
    v.z *= (1/n);

    return v;
};
Vecteur static produitCroix (Vecteur& v1, Vecteur & v2){
    Vecteur v;
    v.x = v1.y*v2.z - v1.z*v2.y;
    v.y = v1.z*v2.x - v1.x*v2.z;
    v.z = v1.x*v2.y - v1.y*v2.x;
    return v;
}

};

class Vertex
{
protected:
    double m_x;
    double m_y;
    double m_z;
    bool m_hasBeenTransformed;

    friend std::ostream& operator <<(std::ostream &s, const Vertex& vertex);
    friend bool operator== (Vertex &s, Vertex &t);



public:
    
    explicit Vertex(const double x, const double y, const double z);
    Vertex (Vecteur & v);

    Vecteur toVecteur () const;

    ~Vertex();

    int roundX() const;
    int roundY() const;
    int roundZ() const;

    double getX() const;
    double getY() const;
    double getZ() const;

    void setX(double x);
    void setY(double y);
    void setZ(double z);

    void setTransformed(bool transformed);
    bool hasBeenTransformed();


    void rasterize_line(int x0, int x1, int y0, int y1, TGAImage &img, TGAColor color) const;


    void draw_line (const Vertex &end, TGAImage &img, TGAColor color) const;

    void resize(const int width, const int height);

};

class NormalVector : Vertex
{
private:
    /* data */
public:
    NormalVector(const double x, const double y, const double z);
    ~NormalVector();
};







#endif //__VERTEX_H__