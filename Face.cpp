#include "Face.h"

Face::Face(std::vector<Vertex> &vertices) : m_vertices{vertices}
{
    m_fullArea = calculate_area(m_vertices[0], m_vertices[1], m_vertices[2]);
}

Face::~Face() {}

std::ostream &operator<<(std::ostream &s, const Face &face)
{
    return s << "(" << face.m_vertices.at(0) << ", "
             << face.m_vertices.at(1) << ", " << face.m_vertices.at(2) << ") " << std::endl;
}


void Face::draw_triangle(TGAImage &img, TGAColor color)
{
    std::array<int, 4> box = load_bounding_box();

    // Remplir le reectangle
    for (int x = box[0]; x <= box[2]; x++)
    {
        for (int y = box[1]; y <= box[3]; y++)
        {
            if (check_pixel_in_triangle(x, y))
            {
                img.set(x, y, color);
            }
        }
    }
}

TGAColor Face::intensity(){
    float vector0 = m_vertices[1].getX() - m_vertices[0].getX();
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

std::array<int, 4> Face::load_bounding_box() const
{
    Vertex temp = Vertex(0, 0, 0);

    int max_x = INT_MIN;
    int max_y = INT_MIN;
    int min_x = INT_MAX;
    int min_y = INT_MAX;

    for (const Vertex &v : m_vertices)
    {
        if (v.getX() >= max_x)
        {
            max_x = v.getX();
        }
        if (v.getY() >= max_y)
        {
            max_y = v.getY();
        }
        if (v.getX() <= min_x)
        {
            min_x = v.getX();
        }
        if (v.getY() <= min_y)
        {
            min_y = v.getY();
        }
    }

    std::array<int, 4> array{min_x, min_y, max_x, max_y};
    return array;
}

bool Face::check_pixel_in_triangle(const int x, const int y)
{
    int area1 = calculate_area(m_vertices[0], m_vertices[1], x, y);
    int area2 = calculate_area(m_vertices[1], m_vertices[2], x, y);
    int area3 = calculate_area(m_vertices[2], m_vertices[0], x, y);

    double alpha = (double)area2 / (double)m_fullArea;
    double beta = (double)area3 / (double)m_fullArea;
    double gamma = (double)area1 / (double)m_fullArea;

    m_vertices.at(1).setCoef(alpha);
    m_vertices.at(2).setCoef(beta);
    m_vertices.at(0).setCoef(gamma);
    
    return alpha > -0.01 && beta > -0.01 && gamma > -0.01;
}

int Face::calculate_area(const Vertex &v1, const Vertex &v2, const Vertex &v3) const
{
    return calculate_area(v1, v2, v3.getX(), v3.getY());
}

int Face::calculate_area(const Vertex &v1, const Vertex &v2, int x, int y) const
{
    return (v1.getX() * (v2.getY() - y) + v2.getX() * (y - v1.getY()) + x * (v1.getY() - v2.getY()));
}
