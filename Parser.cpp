#include "Parser.h"

const int DEPTH {255};

Parser::Parser(const std::string &path, const int width, const int height, TGAImage &texture):
m_texture{texture}
{
    // Initialisation des structures:
    std::vector<std::string> words;

    // Lecture et enregistrement de chaque ligne du fichier dans le vector
    std::ifstream file(path);
    if (file.is_open())
    {
        std::string current_line;

        while (std::getline(file, current_line))
        {
            if (current_line.size() <= 2)
                continue;
            
            parseLine(current_line, words);
            buildVertexes(words, width, height);
            buildFaces(words);
        }

        file.close();
    }
    else
    {
        throw std::invalid_argument("Impossible d'ouvrir le fichier.");
    }
}

Parser::~Parser() {}

std::vector<Vertex> Parser::getVertexes()
{
    return m_vertices;
}
std::vector<Face> Parser::getFaces()
{
    return m_faces;
}

const TGAColor Parser::randomize_color()
{
    return TGAColor(m_distr(m_engine), m_distr(m_engine), m_distr(m_engine), 255);
}

void Parser::parseLine(const std::string &line, std::vector<std::string> &words)
{
    words.clear();
    std::string temp;

    std::stringstream stream(line);

    // Séparation de chaque mot
    while (std::getline(stream, temp, ' '))
    {
        words.push_back(temp);
    }
}

std::array<int, 3> Parser::parsePartFace(std::string &word)
{
    std::array<int, 3> array;
    std::stringstream stream(word);
    std::string temp;
    int index = 0;

    while (std::getline(stream, temp, '/'))
    {
        array[index] = std::stoi(temp);
        index++;
    }
    return array;
}

void Parser::buildVertexes(std::vector<std::string> &words, const int width, const int height)
{
    // Contient les vertices finales
    double x, y, z; 
    // Création des vertices
    if (words.size() < 4)
    {
        return;
    }
    if (words.at(0).compare("v") == 0)
    {
        x = std::stod(words.at(1));
        y = std::stod(words.at(2));
        z = std::stod(words.at(3));
        Vertex vertex = Vertex(x, y, z);
        vertex.resize(width, height);
        m_vertices.push_back(vertex);
    }
    if (words.at(0).compare("vt") == 0){
        x = std::stod(words.at(2));
        y = std::stod(words.at(3));
        Texture texture = Texture(x, y);
        texture.resize(m_texture.get_width(), m_texture.get_height());
        m_textures.push_back(texture);
    }
    if (words.at(0).compare("vn") == 0){
        x = std::stod(words.at(2));
        y = std::stod(words.at(3));
        z = std::stod(words.at(4));
        NormalVector normal = NormalVector(x, y, z);
        //vertex.resize(width, height);
        m_normals.push_back(normal);
    }
}

void Parser::project(const double distance_z)
{
    Vecteur vect;
    Matrix matrix, identity;
    identity = matrix.identify(4);

    for (Vertex &v : m_vertices){
        identity[3][2] = -1/distance_z;
        matrix = Matrix(4, 1);
        matrix[0][0] = v.getX();
        matrix[1][0] = v.getY();
        matrix[2][0] = v.getZ();
        matrix[3][0] = double(1);
        matrix = identity * matrix;
        vect = matrix.matrixToVector();
        v.setX(vect.x);
        v.setY(vect.y);
        v.setZ(vect.z);
    }
}

void Parser::transform(){
    for (Vertex &v : m_vertices){
        
    }

}

void Parser::generateModelview (Vecteur pov, Vecteur center, Vecteur haut){
    Vecteur diff_pov_center= {pov.x - center.x, pov.y - center.y, pov.z - center.z};

    Vecteur z = normalize(diff_pov_center);
    Vecteur x = normalize(produitCroix(haut, z));
    Vecteur y = normalize(produitCroix(z, x));

    Matrix Minv, t, modelview; 
    Minv = Matrix::identify(4);
    t = Matrix::identify(4);


    for (int i = 0; i < 3; i++){
        Minv[0][i] = x[i];
        Minv[1][i] = y[i];
        Minv[2][i] = z[i];
        t[0][3] = -center[i];
    }

    modelview = Minv * t;
    m_modelview = modelview;

}

void Parser::generateViewport (int x, int y, int w, int h){
    Matrix viewport = Matrix::identify(4);
    viewport[0][3] = x+w/2.;
    viewport[1][3] = y+h/2.;
    viewport[2][3] = DEPTH/2.;

    viewport[0][0] = w/2.;
    viewport[1][1] = h/2.;
    viewport[2][2] = DEPTH/2.;

    m_viewport = viewport;
}

void Parser::generateProjection (Vecteur pov, Vecteur center){
    Matrix proj = Matrix::identify(4);
    Vecteur diff_pov_center= {pov.x - center.x, pov.y - center.y, pov.z - center.z};
    double n = diff_pov_center.x * diff_pov_center.x + diff_pov_center.y * diff_pov_center.y + diff_pov_center.z * diff_pov_center.z;
    n = sqrt(n);

    proj[3][2] = -1. / n;
    m_projection = proj;
}




void Parser::buildFaces(std::vector<std::string> &words)
{
    std::vector<Vertex> local_vertices;
    std::vector<Texture> local_textures;
    std::vector<NormalVector> local_normals;

    std::array<int, 3> f1, f2, f3;

    // Création des faces
    if (words.at(0).compare("f") != 0 || words.size() != 4)
    {
        return;
    }

    f1 = parsePartFace(words.at(1));
    f2 = parsePartFace(words.at(2));
    f3 = parsePartFace(words.at(3));

    local_vertices.push_back(m_vertices.at(f1[0] - 1));
    local_vertices.push_back(m_vertices.at(f2[0] - 1));
    local_vertices.push_back(m_vertices.at(f3[0] - 1));

    
    local_textures.push_back(m_textures.at(f1[1] - 1));
    local_textures.push_back(m_textures.at(f2[1] - 1));
    local_textures.push_back(m_textures.at(f3[1] - 1));

    local_normals.push_back(m_normals.at(f1[2] - 1));
    local_normals.push_back(m_normals.at(f2[2] - 1));
    local_normals.push_back(m_normals.at(f3[2] - 1));

    Face face = Face(local_vertices, local_textures, local_normals);
    m_faces.push_back(face);
}