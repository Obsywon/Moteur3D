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
    std::vector <Vertex> m_vertices;
    std::vector<Face> m_faces;


    void parseLine (const std::string &line, std::vector <std::string> &words);
    std::array <int,3> parsePartFace (std::string &word);
    void buildVertexes(std::vector <std::string> &words, const int width, const int height);
    void buildFaces (std::vector <std::string> &words);
    
public:
    
    Parser(const std::string& path, const int width, const int height);
    ~Parser();
    std::vector <Vertex> getVertexes () const;
    std::vector <Face> getFaces () const;

};






#endif //__PARSER_H__