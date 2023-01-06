#ifndef __PARSER_H__
#define __PARSER_H__

#include "Node.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <sstream>


class Parser
{
private:
    std::vector <std::string> _lines;
    const std::string& _path;
    
public:
    
    Parser(const std::string& path);
    ~Parser();

    const std::vector<Node> buildNodes(const int width, const int height);

};






#endif //__PARSER_H__