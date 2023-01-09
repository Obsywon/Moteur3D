#include "Parser.h"

Parser::Parser(const std::string &path, const int width, const int height)
{
    // Initialisation des structures:
    std::vector <std::string> words;


    // Lecture et enregistrement de chaque ligne du fichier dans le vector
    std::ifstream file(path);
    if (file.is_open())
    {
        std::string current_line;

        while (std::getline(file, current_line))
        {
            if (current_line.size() <= 2) continue;
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



std::vector <Vertex> Parser::getVertexes () const{
    return m_vertices;
}
std::vector <Face> Parser::getFaces () const{
    return m_faces;
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
    int index;
    index = 0;

    while (std::getline(stream, temp, '/'))
    {
        array[index] = std::stoi(temp);
        index++;
    }
    return array;
}

void Parser::buildVertexes(std::vector <std::string> &words, const int width, const int height)
{
    // Contient les vertices finales
    std::string temp;

    float x, y, z; // valeurs d'une Vertex
    

    // Création des vertices
    if (words.at(0).compare("v") != 0 || words.size() != 4){
        return;
    }
    x = std::stof(words.at(1));
    y = std::stof(words.at(2));
    z = std::stof(words.at(3));
    Vertex vertex = Vertex(x, y, z);
    vertex.resize(width, height);
    m_vertices.push_back(vertex);
    
    
}

void Parser::buildFaces(std::vector <std::string> &words)
{
    std::vector<Vertex> local_vertices;
    std::array<int, 3> f1, f2, f3;


    // Création des faces
    if (words.at(0).compare("f") != 0 || words.size() != 4){
        return;
    }
    
    f1 = parsePartFace(words.at(1));
    f2 = parsePartFace(words.at(2));
    f3 = parsePartFace(words.at(3));

    local_vertices.push_back(m_vertices.at(f1[0] - 1));
    local_vertices.push_back(m_vertices.at(f2[0] - 1));
    local_vertices.push_back(m_vertices.at(f3[0] - 1));


    Face face = Face(local_vertices);
    m_faces.push_back(face);
    
}