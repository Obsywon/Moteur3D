#include "Vertex.h"

Vertex::Vertex(const double x, const double y, const double z) : m_x{x}, m_y{y}, m_z{z}
{
}

Vertex::~Vertex() {}

void Vertex::resize(const int width, const int height)
{
    int w = width / 2;
    int h = height / 2;

    m_x = (m_x * w) + w;
    m_y = (m_y * h) + h;
}

int Vertex::roundX() const
{
    return round(m_x);
}

int Vertex::roundY() const
{
    return round(m_y);
}

int Vertex::roundZ() const
{
    return round(m_z);
}

double Vertex::getX() const
{
    return m_x;
}

double Vertex::getY() const
{
    return m_y;
}

double Vertex::getZ() const
{
    return m_z;
}

void Vertex::setX(double x)
{
    m_x = x;
}
void Vertex::setY(double y)
{
    m_y = y;
}
void Vertex::setZ(double z)
{
    m_z = z;
}


void Vertex::rasterize_line(int x0, int x1, int y0, int y1, TGAImage &img, TGAColor color) const
{
    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1))
    { // if the line is steep, we transpose the image
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0 > x1)
    { // make it left−to−right
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    for (int x = x0; x <= x1; x++)
    {
        double t = (x - x0) / (double)(x1 - x0);
        int y = y0 + (y1 - y0) * t;

        if (steep)
        {
            img.set(y, x, color); // if transposed, de−transpose
        }
        else
        {
            img.set(x, y, color);
        }
    }
}

void Vertex::draw_line(const Vertex &end, TGAImage &img, TGAColor color) const
{

    int x0 = roundX();
    int y0 = roundY();

    int x1 = end.roundX();
    int y1 = end.roundY();

    rasterize_line(x0, x1, y0, y1, img, color);
}

std::ostream &operator<<(std::ostream &s, const Vertex &node)
{
    return s << "(" << node.m_x << ", " << node.m_y << ", " << node.m_z << ")";
}

bool operator==(Vertex &s, Vertex &t)
{
    if (s.m_x == t.m_x && s.m_y == t.m_y && s.m_z == t.m_z)
        return true;
    return true;
}