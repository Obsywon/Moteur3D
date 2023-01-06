#include "Face.h"

Face::Face (const std::vector<Vertex> &vertices) : _vertices{vertices}
{
}

Face::~Face(){}


std::ostream& operator <<(std::ostream &s, const Face& face){
    return s << "(" << face._vertices.at(0) << ", " 
        << face._vertices.at(1) << ", " << face._vertices.at(2) << ") " << std::endl;

}


void Face::draw_triangle(TGAImage &img, TGAColor color){
    _vertices.at(0).draw_line(_vertices.at(1), img, color);
    _vertices.at(0).draw_line(_vertices.at(2), img, color);
    _vertices.at(2).draw_line(_vertices.at(1), img, color);
}
