#ifndef __PARSER_H__
#define __PARSER_H__

#include "Face.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <array>


class Parser
{
private:
    std::vector <std::string> _lines;
    const std::string& _path;
    
public:
    
    Parser(const std::string& path);
    ~Parser();

    void parseLine (const std::string &line, std::vector <std::string> &words);
    std::array <int,3> parsePartFace (std::string &word);
    const std::vector<Vertex> buildVertexes(const int width, const int height);
    const std::vector<Face> buildFaces (const std::vector <Vertex> &vertices);

};






#endif //__PARSER_H__