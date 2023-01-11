#include "Face.h"

Face::Face(const std::vector<Vertex> &vertices) : m_vertices{vertices} {
    m_fullArea = calculate_area(m_vertices[0], m_vertices[1], m_vertices[2]);
}

Face::~Face() {}

std::ostream &operator<<(std::ostream &s, const Face &face)
{
    return s << "(" << face.m_vertices.at(0) << ", "
             << face.m_vertices.at(1) << ", " << face.m_vertices.at(2) << ") " << std::endl;
}

void Face::draw_triangle(TGAImage &img, TGAColor color) const
{
    std::array <int, 4> box = load_bounding_box();

    // Remplir le reectangle
    for (int x = box[0]; x <= box[2]; x++){
        for (int y = box[1]; y <= box[3]; y++){
            if (check_pixel_in_triangle(x, y)) img.set(x, y, color);
        }
    }
}

void Face::draw_line_triangle(TGAImage &img, TGAColor color) const
{
    auto v0 = m_vertices[0];
    auto v1 = m_vertices[1];
    auto v2 = m_vertices[2];

    v0.draw_line(v1, img, color);
    v0.draw_line(v2, img, color);
    v1.draw_line(v2, img, color);
    
}

std::array <int, 4> Face::load_bounding_box() const
{
    Vertex temp = Vertex(0,0,0);

    int max_x = INT_MIN;
    int max_y = INT_MIN;
    int min_x = INT_MAX;
    int min_y = INT_MAX;

    for (const Vertex &v : m_vertices)
    {
        if (v.getX() >= max_x){
            max_x = v.getX();
        }
        if (v.getY() >= max_y){
            max_y = v.getY();
        }
        if (v.getX() <= min_x){
            min_x = v.getX();
        }
        if (v.getY() <= min_y){
            min_y = v.getY();
        }
    }

    std::array <int, 4> array {min_x, min_y, max_x, max_y};
    return array;

}

bool Face::check_pixel_in_triangle(const int x, const int y) const
{
    int area1 = calculate_area(m_vertices[0], m_vertices[1], x, y);
    int area2 = calculate_area(m_vertices[1], m_vertices[2], x, y);
    int area3 = calculate_area(m_vertices[0], m_vertices[2], x, y);

    //std::cout << area1 << " / " << m_fullArea << " = " << static_cast<float>((float)area1 / (float)m_fullArea) << std::endl;
    return (m_fullArea == (area1 + area2 + area3));
}

int Face::calculate_area (const Vertex &v1, const Vertex &v2, const Vertex &v3) const {
    return calculate_area(v1, v2, v3.getX(), v3.getY());
}

int Face::calculate_area (const Vertex &v1, const Vertex &v2, int x, int y) const {
    return abs(v1.getX() * (v2.getY() - y)
    + v2.getX() * (y - v1.getY()) 
    + x * (v1.getY() - v2.getY())); 
}

