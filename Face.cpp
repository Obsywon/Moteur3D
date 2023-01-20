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

void Face::draw_triangle(TGAImage &img, TGAColor color, double *z_buffer)
{
    std::array<int, 4> box = load_bounding_box();
    std::array<double, 4> baryocentric = {0};
    vecteur light = {0, 0, -1};
    double intensity;
    int indice;

    // Remplir le reectangle
    for (int x = box[0]; x <= box[2]; x++)
    {
        for (int y = box[1]; y <= box[3]; y++)
        {
            baryocentric = baryocentric_values(x, y);
            indice = int(x + y * WIDTH);

            if (baryocentric[0] > -0.01 && baryocentric[1] > -0.01 && baryocentric[2] > -0.01)
            {

                if (z_buffer[indice] < baryocentric[3])
                {
                    z_buffer[indice] = baryocentric[3];
                    intensity = color_intensity(light);
                    img.set(x, y, TGAColor(255 * intensity, 255 * intensity, 255 * intensity, 255 * intensity));
                    
                }
            }
        }
    }
}

double Face::color_intensity(const vecteur &light)
{

    vecteur v01 = {
        m_vertices[1].getX() - m_vertices[0].getX(),
        m_vertices[1].getY() - m_vertices[0].getY(),
        m_vertices[1].getZ() - m_vertices[0].getZ()};

    vecteur v02 = {
        m_vertices[2].getX() - m_vertices[0].getX(),
        m_vertices[2].getY() - m_vertices[0].getY(),
        m_vertices[2].getZ() - m_vertices[0].getZ()};
    vecteur normal = {
        v01.y * v02.z - v01.z * v02.y,
        v01.z * v02.x - v01.x * v02.z,
        v01.x * v02.y - v01.y * v02.x,
    };

    double longueur = std::sqrt((normal.x * normal.x) +
                                (normal.y * normal.y) + (normal.z * normal.z));

    normal.x /= longueur;
    normal.y /= longueur;
    normal.z /= longueur;

    double intensity = -((light.x * normal.x) + (light.y * normal.y) + (light.z * normal.z));
    return intensity;
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
        if (v.roundX() >= max_x)
        {
            max_x = v.roundX();
        }
        if (v.roundY() >= max_y)
        {
            max_y = v.roundY();
        }
        if (v.roundX() <= min_x)
        {
            min_x = v.roundX();
        }
        if (v.roundY() <= min_y)
        {
            min_y = v.roundY();
        }
    }

    std::array<int, 4> array{min_x, min_y, max_x, max_y};
    return array;
}

std::array<double, 4> Face::baryocentric_values(const int x, const int y) const
{
    std::array<double, 4> values = {0};

    int area1 = calculate_area(m_vertices[0], m_vertices[1], x, y);
    int area2 = calculate_area(m_vertices[1], m_vertices[2], x, y);
    int area3 = calculate_area(m_vertices[2], m_vertices[0], x, y);

    double alpha = (double)area2 / (double)m_fullArea;
    double beta = (double)area3 / (double)m_fullArea;
    double gamma = (double)area1 / (double)m_fullArea;

    double baryo_z = alpha * m_vertices[1].getZ() +
                     beta * m_vertices[2].getZ() +
                     gamma * m_vertices[0].getZ();
    values[0] = alpha;
    values[1] = beta;
    values[2] = gamma;
    values[3] = baryo_z;

    return values;
}

int Face::calculate_area(const Vertex &v1, const Vertex &v2, const Vertex &v3) const
{
    return calculate_area(v1, v2, v3.roundX(), v3.roundY());
}

int Face::calculate_area(const Vertex &v1, const Vertex &v2, int x, int y) const
{
    return (v1.roundX() * (v2.roundY() - y) + v2.roundX() * (y - v1.roundY()) + x * (v1.roundY() - v2.roundY()));
}
