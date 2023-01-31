#include "Face.h"

Face::Face(std::vector<Vertex> &vertices, std::vector<Texture> &textures) : m_vertices{vertices}, m_textures{textures}
{
    m_fullArea = calculate_area(m_vertices[0], m_vertices[1], m_vertices[2]);
}

Face::~Face() {}

std::ostream &operator<<(std::ostream &s, const Face &face)
{
    return s << "(" << face.m_vertices.at(0) << ", "
             << face.m_vertices.at(1) << ", " << face.m_vertices.at(2) << ") " << std::endl;
}

void Face::draw_triangle(TGAImage &img, double *z_buffer, TGAImage &texture)
{
    std::array<int, 4> box = load_bounding_box();
    std::array<double, 4> baryo = {0};
    vecteur light_source = {0, 0, -1};
    double intensity;
    int indice, x_texture, y_texture;
    TGAColor color;


    // Remplir le rectangle
    for (int x = box[0]; x <= box[2]; x++)
    {
        for (int y = box[1]; y <= box[3]; y++)
        {

            if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT ) continue;

            baryo = baryocentric_values(x, y);
            indice = int(x + y * WIDTH);

            if (baryo[0] > -0.0001 && baryo[1] > -0.0001 && baryo[2] > -0.0001)
            {

                if (z_buffer[indice] < baryo[3])
                {


                    // calcul z-index : pixel doit être rasterisé
                    z_buffer[indice] = baryo[3];

                    x_texture = baryo[0] * m_textures[0].getRoundX() +
                                    baryo[1] * m_textures[1].getRoundX() +
                                    baryo[2] * m_textures[2].getRoundX();
                    y_texture = baryo[0] * m_textures[0].getRoundY() +
                                    baryo[1] * m_textures[1].getRoundY() +
                                    baryo[2] * m_textures[2].getRoundY();
                    
                    color = texture.get(x_texture, y_texture);


                    // Intensité lumineuse
                    intensity = color_intensity(light_source);
                    if (intensity > 0) img.set(x, y, TGAColor(color.r * intensity, color.g * intensity, color.b * intensity, color.a * intensity));
                
                }
            }
        }
    }
}

double Face::color_intensity(const vecteur &light_source)
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

    double intensity = -((light_source.x * normal.x) + (light_source.y * normal.y) + (light_source.z * normal.z));
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

    double baryo_z = alpha * m_vertices[0].getZ() +
                     beta * m_vertices[1].getZ() +
                     gamma * m_vertices[2].getZ();
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
