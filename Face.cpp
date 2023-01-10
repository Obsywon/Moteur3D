#include "Face.h"

Face::Face(const std::vector<Vertex> &vertices) : m_vertices{vertices} {
    
}

Face::~Face() {}

std::ostream &operator<<(std::ostream &s, const Face &face)
{
    return s << "(" << face.m_vertices.at(0) << ", "
             << face.m_vertices.at(1) << ", " << face.m_vertices.at(2) << ") " << std::endl;
}

void Face::draw_line_triangle(TGAImage &img, TGAColor color) const
{
    /*
    auto v0 = m_vertices[0];
    auto v1 = m_vertices[1];
    auto v2 = m_vertices[2];
    
    m_vertices[0].draw_line(m_vertices[1], img, color);
    m_vertices[0].draw_line(m_vertices[2], img, color);
    m_vertices[2].draw_line(m_vertices[1], img, color);
    */
    

    std::array <int, 4> box = load_bounding_box();
    const TGAColor red = TGAColor(255, 255, 255, 100);


    //m_vertices[0].rasterize_line(box[0], box[2], box[1], box[3], img, red);
    
    m_vertices[0].rasterize_line(box[0], box[0], box[1], box[3], img, red);
    m_vertices[0].rasterize_line(box[0], box[2], box[1], box[1], img, red);
    m_vertices[0].rasterize_line(box[2], box[2], box[1], box[3], img, red);
    m_vertices[0].rasterize_line(box[0], box[2], box[3], box[3], img, red);

    // TODO : ne fonctionne pas 
    /*
    for (int x = box[0]; x++; x <= box[1]){
        for (int y = box[1]; y++; y <= box[3]){
            //std::cout << box[0] << std::endl;
            std::cout << "x: " << box[0] <<" "<< box[1] << " | y: " << y << std::endl;
            img.set(x, y, red);
        }
    }
    */


}

void Face::draw_triangle(TGAImage &img, TGAColor color)
{
    const TGAColor red = TGAColor(255, 0, 0, 255);
    const TGAColor green = TGAColor(0, 255, 0, 255);
    const TGAColor blue = TGAColor(0, 0, 255, 255);

    auto v0 = m_vertices[0];
    auto v1 = m_vertices[1];
    auto v2 = m_vertices[2];

    // Ordonne du plus petit au plus grand y les sommets
    if (v0.getY() > v1.getY())
        std::swap(v0, v1);
    if (v0.getY() > v2.getY())
        std::swap(v0, v2);
    if (v1.getY() > v2.getY())
        std::swap(v1, v2);
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
}
