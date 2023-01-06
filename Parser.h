#ifndef __PARSER_H__
#define __PARSER_H__


#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>


class Parser
{
private:
    std::vector <std::string> _lines;
    const std::string& _path;
public:
    
    Parser(const std::string& path);
    ~Parser();
};






#endif //__PARSER_H__