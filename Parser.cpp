#include "Parser.h"




Parser::Parser(const std::string& path) : _path{path}
{

    std::ifstream file(_path);
    if (file.is_open()){
        

    }else{
        throw std::invalid_argument("Impossible d'ouvrir le fichier.");
    }

}

Parser::~Parser(){}
