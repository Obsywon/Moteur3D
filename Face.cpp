#include "Face.h"

Face::Face(std::vector<Vertex> &vertices, std::vector<Texture> &textures, std::vector<NormalVector> &normals)
    : m_vertices{vertices}, m_textures{textures}, m_normals{normals}
{
}

Face::~Face() {}

std::ostream &operator<<(std::ostream &s, const Face &face)
{
    return s << "(" << face.m_vertices.at(0) << ", "
             << face.m_vertices.at(1) << ", " << face.m_vertices.at(2) << ") " << std::endl;
}

Vertex &Face::getVertex(const int indice)
{
    return m_vertices[indice];
}

NormalVector &Face::getNormal(const int indice)
{
    return m_normals[indice];
}

    void Face::setVertex(Vertex v, const int indice){
        m_vertices[indice] = v;
    }

double Face::color_intensity(const Vecteur &light_source)
{

    Vecteur v01 = {
        m_vertices[1].getX() - m_vertices[0].getX(),
        m_vertices[1].getY() - m_vertices[0].getY(),
        m_vertices[1].getZ() - m_vertices[0].getZ()};

    Vecteur v02 = {
        m_vertices[2].getX() - m_vertices[0].getX(),
        m_vertices[2].getY() - m_vertices[0].getY(),
        m_vertices[2].getZ() - m_vertices[0].getZ()};
    Vecteur normal = {
        v01.y * v02.z - v01.z * v02.y,
        v01.z * v02.x - v01.x * v02.z,
        v01.x * v02.y - v01.y * v02.x,
    };

    double longueur = Vecteur::norm(normal);

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
    double fullArea = calculate_area(m_vertices[0], m_vertices[1], m_vertices[2]);
    double area1 = calculate_area(m_vertices[0], m_vertices[1], x, y);
    double area2 = calculate_area(m_vertices[1], m_vertices[2], x, y);
    double area3 = calculate_area(m_vertices[2], m_vertices[0], x, y);
    double alpha = (double)area2 / (double)fullArea;
    double beta = (double)area3 / (double)fullArea;
    double gamma = (double)area1 / (double)fullArea;

    double baryo_z = alpha * m_vertices[0].getZ() +
                     beta * m_vertices[1].getZ() +
                     gamma * m_vertices[2].getZ();
    values[0] = alpha;
    values[1] = beta;
    values[2] = gamma;
    values[3] = baryo_z;
    return values;
}

double Face::calculate_area(const Vertex &v1, const Vertex &v2, const Vertex &v3) const
{
    return calculate_area(v1, v2, v3.getX(), v3.getY());
}

double Face::calculate_area(const Vertex &v1, const Vertex &v2, double x, double y) const
{
    return (v1.getX() * (v2.getY() - y) + v2.getX() * (y - v1.getY()) + x * (v1.getY() - v2.getY())) / 2.;
}

void Face::transform(Matrix &viewport, Matrix &modelview, Matrix &projection)
{
    Vecteur vect;
    Matrix temp, normals;
    Matrix m = viewport * modelview * projection;

    for (Vertex &v : m_vertices)
    {
        if (v.hasBeenTransformed())
            continue;
        temp = Matrix(v);
        temp = m * temp;
        vect = temp.matrixToVector();
        v.setX(vect.x);
        v.setY(vect.y);
        v.setZ(vect.z);
        v.setTransformed(true);
    }

    Matrix mT = m.transpose();

    /* for (NormalVector& n : m_normals){
        normals = Matrix(4, 1);
        normals[0][0] = n.getX();
        normals[1][0] = n.getY();
        normals[2][0] = n.getZ();
        normals[3][0] = 0.;

        normals = mT.inverse() * normals;
        normals = normals.transpose();
        n.setX(normals[0][0]);
        n.setY(normals[1][0]);
        n.setZ(normals[2][0]);

        std::cout << n << std::endl;
    } */
}

TGAColor Face::getColor(TGAImage &texture, std::array<double, 4> baryo)
{
    int x = baryo[0] * m_textures[0].getRoundX() +
            baryo[1] * m_textures[1].getRoundX() +
            baryo[2] * m_textures[2].getRoundX();

    int y = baryo[0] * m_textures[0].getRoundY() +
            baryo[1] * m_textures[1].getRoundY() +
            baryo[2] * m_textures[2].getRoundY();

    // Récupération de la couleur du pixel sur la texture
    TGAColor color = texture.get(x, y);
    return color;
}