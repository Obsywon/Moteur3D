#include "Face.h"

Face::Face (const std::vector<Vertex> &vertices) : _vertices{vertices}
{
}

Face::~Face(){}


std::ostream& operator <<(std::ostream& s, const Face& face){
    return s << "(" << face._vertices.at(0) << ", " 
        << face._vertices.at(1) << ", " << face._vertices.at(2) << ") " << std::endl;

}


void Face::draw_line_triangle(TGAImage& img, TGAColor color){
    auto v0 = _vertices[0];
    auto v1 = _vertices[1];
    auto v2 = _vertices[2];
    _vertices[0].draw_line(_vertices[1], img, color);
    _vertices[0].draw_line(_vertices[2], img, color);
    _vertices[2].draw_line(_vertices[1], img, color);
}
