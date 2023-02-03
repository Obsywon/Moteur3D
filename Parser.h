#ifndef __PARSER_H__
#define __PARSER_H__


#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>

#include "Face.h"
#include "Texture.h"




class Parser
{
private:
    std::vector <Vertex> m_vertices;
    std::vector <Texture> m_textures;
    std::vector <NormalVector> m_normals;
    std::vector<Face> m_faces;
    TGAImage& m_texture;

    Matrix m_viewport;
    Matrix m_modelview;
    Matrix m_projection;

    std::uniform_int_distribution<int> m_distr; 
    std::default_random_engine m_engine;


    void parseLine (const std::string &line, std::vector <std::string> &words);
    std::array <int,3> parsePartFace (std::string &word);
    void buildVertexes(std::vector <std::string> &words, const int width, const int height);
    void buildFaces (std::vector <std::string> &words);
    
public:
    
    Parser(const std::string& path, const int width, const int height, TGAImage& textured);
    ~Parser();
    std::vector <Vertex> getVertexes ();
    std::vector <Face> getFaces ();

    const TGAColor randomize_color();
    void project(const double distance_z);
    void generateModelview (Vecteur pov, Vecteur center, Vecteur haut);
    void generateViewport (int x, int y, int w, int h);
    void generateProjection (Vecteur pov, Vecteur center);


};






#endif //__PARSER_H__