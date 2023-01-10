#include "Vertex.h"

Vertex::Vertex(const float x, const float y, const float z): m_x{x}, m_y{y}, m_z{z}{

}

Vertex::~Vertex(){}


void Vertex::resize(const int width, const int height){
    int w = width / 2;
    int h = height / 2;
    
    m_x = (m_x * w) + w;
    m_y = (m_y * h) + h;
}

int Vertex::getX() const{
    return static_cast<int>(m_x);
}

int Vertex::getY() const{
    return static_cast<int> (m_y);
}

int Vertex::getZ() const{
    return static_cast<int> (m_z);
}

void Vertex::rasterize_line(int x0, int x1, int y0, int y1, TGAImage &img, TGAColor color) const {
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
        int y = y0 + (y1 - y0) * t; 

        if (steep) { 
            img.set(y, x, color); // if transposed, de−transpose 
        } else { 
            img.set(x, y, color); 
        } 
    }  
}

void Vertex::draw_line (const Vertex &end, TGAImage &img, TGAColor color) const{

    int x0 = getX();
    int y0 = getY();

    int x1 = end.getX();
    int y1 = end.getY();

	rasterize_line(x0, x1, y0, y1, img, color);
}

std::ostream& operator <<(std::ostream &s, const Vertex& node){
    return s << "(" << node.m_x << ", " << node.m_y << ", " << node.m_z << ")";
}

bool operator== (Vertex &s, Vertex &t){
    if (s.m_x == t.m_x && s.m_y == t.m_y && s.m_z == t.m_z) return true;
    return true;
}