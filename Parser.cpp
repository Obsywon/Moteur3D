#include "Parser.h"

Parser::Parser(const std::string &path) : _path{path}
{
    // Lecture et enregistrement de chaque ligne du fichier dans le vector
    std::ifstream file(_path);
    if (file.is_open())
    {
        std::string current_line;

        while (std::getline(file, current_line))
        {
            _lines.push_back(current_line);
        }

        file.close();
    }
    else
    {
        throw std::invalid_argument("Impossible d'ouvrir le fichier.");
    }
}

Parser::~Parser() {}

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

std::array <int,3> Parser::parsePartFace (std::string &word){
    std::array<int, 3> array;
    std::stringstream stream(word);
    std::string temp;
    int index;
    index = 0;

    while (std::getline(stream, temp, '/')){
        array[index] = std::stoi(temp);
        index++;
    }
    return array;
}

const std::vector<Vertex> Parser::buildVertexes(const int width, const int height)
{
    std::vector<Vertex> vertices;     // Contient les vertices finales
    std::vector<std::string> words; // Contient les éléments de la ligne avant création d'un noeud
    std::string temp;

    float x, y, z; // valeurs d'une Vertex

    for (const std::string &line : _lines)
    {
        if (line.size() <= 2)
            continue;
        parseLine(line, words);

        // Création des vertices
        if (words.at(0).compare("v") == 0 && words.size() == 4)
        {
            x = std::stof(words.at(1));
            y = std::stof(words.at(2));
            z = std::stof(words.at(3));
            Vertex vertex = Vertex(x, y, z);
            vertex.resize(width, height);
            vertices.push_back(vertex);
        }
    }
    return vertices;
}


const std::vector<Face> Parser::buildFaces (const std::vector <Vertex> &vertices){
    std::vector <Face> faces;
    std::vector <Vertex> local_vertices;
    std::vector <std::string> words;
    std::array<int, 3> f1, f2, f3;


    for (const std::string &line : _lines)
    {
        if (line.size() <= 2)
            continue;
        parseLine(line, words);

        // Création des faces
        if (words.at(0).compare("f") == 0 && words.size() == 4)
        {
            f1 = parsePartFace(words.at(1));
            f2 =  parsePartFace(words.at(2));
            f3 = parsePartFace(words.at(3));

            local_vertices.clear();
            local_vertices.push_back(vertices.at(f1[0] - 1));
            local_vertices.push_back(vertices.at(f2[0] - 1));
            local_vertices.push_back(vertices.at(f3[0] - 1));

            Face face = Face(local_vertices);
            faces.push_back(face);
        }
    }
    std::cout << faces.at(0);
    return faces;


}