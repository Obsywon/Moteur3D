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

    /**
     * @brief Parçage d'une ligne provenant d'un .obj en les découpant en sous mots
     * 
     * @param line Ligne traitée
     * @param words Mots sorties
     */
    void parseLine (const std::string &line, std::vector <std::string> &words);

    /**
     * @brief Traitement et récupération des entier d'une face
     * 
     * @param word Mot traité
     * @return std::array <int,3> 
     */
    std::array <int,3> parsePartFace (std::string &word);

    /**
     * @brief Construction de chaque type d'éléments contenus dans le fichier .obj
     * 
     * @param words Mots à traiter - vers valeurs flottantes
     */
    void buildVertexes(std::vector <std::string> &words);

    /**
     * @brief Assemblage des vertexes dans une face
     * 
     * @param words mots à traiter
     */
    void buildFaces (std::vector <std::string> &words);
    
public:
    
    Parser(const std::string& path, TGAImage& textured);
    ~Parser();
    std::vector <Vertex> getVertexes ();
    std::vector <Face> getFaces ();

    const TGAColor randomize_color();
    void project(const double distance_z);
};






#endif //__PARSER_H__