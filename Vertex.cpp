#include "Vertex.h"

Vertex::Vertex(const float x, const float y, const float z): _x{x}, _y{y}, _z{z}{

}

Vertex::~Vertex(){}


void Vertex::resize(const int width, const int height){
    int w = width / 2;
    int h = height / 2;
    _x = (_x * w) + w;
    _y = (_y * h) + h;
}

int Vertex::getX() const{
    return static_cast<int>(_x);
}

int Vertex::getY() const{
    return static_cast<int> (_y);
}

int Vertex::getZ() const{
    return static_cast<int> (_z);
}

void Vertex::draw_line (const Vertex &end, TGAImage &img, TGAColor color) const{

    int x0 = getX();
    int y0 = getY();

    int x1 = end.getX();
    int y1 = end.getY();

	bool steep = false; 
    if (std::abs(x0-x1)<std::abs(y0-y1)) { // if the line is steep, we transpose the image 
        std::swap(x0, y0); 
        std::swap(x1, y1); 
        steep = true; 
    } 
    if (x0>x1) { // make it left−to−right 
        std::swap(x0, x1); 
        std::swap(y0, y1); 
    } 
    for (int x=x0; x<=x1; x++) { 
        float t = (x-x0)/(float)(x1-x0); 
        int y = y0*(1.-t) + y1*t; 
        if (steep) { 
            img.set(y, x, color); // if transposed, de−transpose 
        } else { 
            img.set(x, y, color); 
        } 
    }  
}

std::ostream& operator <<(std::ostream &s, const Vertex& node){
    return s << "(" << node._x << ", " << node._y << ", " << node._z << ")";
}

bool operator== (Vertex &s, Vertex &t){
    if (s._x == t._x && s._y == t._y && s._z == t._z) return true;
    return true;
}