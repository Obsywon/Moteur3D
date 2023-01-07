#include "Face.h"

Face::Face (const std::vector<Vertex> &vertices) : m_vertices{vertices}
{
}

Face::~Face(){}


std::ostream& operator <<(std::ostream& s, const Face& face){
    return s << "(" << face.m_vertices.at(0) << ", " 
        << face.m_vertices.at(1) << ", " << face.m_vertices.at(2) << ") " << std::endl;

}


void Face::draw_line_triangle(TGAImage& img, TGAColor color) const{
    auto v0 = m_vertices[0];
    auto v1 = m_vertices[1];
    auto v2 = m_vertices[2];
    m_vertices[0].draw_line(m_vertices[1], img, color);
    m_vertices[0].draw_line(m_vertices[2], img, color);
    m_vertices[2].draw_line(m_vertices[1], img, color);
}

void Face::draw_triangle(TGAImage& img, TGAColor color){
    auto v0 = m_vertices[0];
    auto v1 = m_vertices[1];
    auto v2 = m_vertices[2];

    // Ordonne du plus petit au plus grand y les sommets
    if (v0.getY() > v1.getY()) std::swap(v0, v1);
    if (v0.getY() > v2.getY()) std::swap(v0, v2);
    if (v1.getY() > v2.getY()) std::swap(v1, v2);

    
    
    
}

