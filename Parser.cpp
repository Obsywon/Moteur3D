#include "Parser.h"



Parser::Parser(const std::string& path) : _path{path}
{
    // Lecture et enregistrement de chaque ligne du fichier dans le vector
    std::ifstream file(_path);
    if (file.is_open()){
        std::string current_line;

        while (std::getline(file, current_line)){
            _lines.push_back(current_line);
        }

        file.close();

    }else{
        throw std::invalid_argument("Impossible d'ouvrir le fichier.");
    }

}

Parser::~Parser(){}


const std::vector<Node> Parser::buildNodes(const int width, const int height){
    std::vector<Node> nodes;            // Contient les nodes finales
    std::vector<std::string> content;   // Contient les éléments de la ligne avant création d'un noeud
    std::string temp;


    float x, y, z; // valeurs d'une Node

    for (const std::string& line : _lines){
        if (line.size() <= 2) continue;
        content.clear();

        std::stringstream stream(line);

        // Séparation de chaque mot
        while (std::getline(stream, temp, ' '))
        {
            content.push_back(temp);
        }

        // Création des nodes
        if (content.at(0).compare("v") == 0 && content.size() == 4){
            x = std::stof(content.at(1));
            y = std::stof(content.at(2));
            z = std::stof(content.at(3));
            Node node = Node(x, y, z);
            node.resize(width, height);
            nodes.push_back(node);
        }
    }
    std::cout << nodes.at(0);
    return nodes;
}