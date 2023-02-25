#ifndef __FACE_H__
#define __FACE_H__


#include <iostream>
#include <climits>
#include <array>
#include <random>
#include "Texture.h"
#include "Matrix.h"
#include "tgaimage.h"








class Face
{
private:
    std::vector<Vertex> m_vertices;
    std::vector<Texture> m_textures;
    std::vector<NormalVector> m_normals;

    friend std::ostream& operator <<(std::ostream &s, const Face& face);



public:
    /**
     * @brief Constructeur de Face
     * Contient des triplets de vertex, textures et normales
     * 
     * @param vertices 
     * @param textures 
     * @param normals 
     */
    Face(std::vector<Vertex> &vertices, std::vector<Texture> &textures, std::vector<NormalVector> &normals);
    ~Face();

    Vertex& getVertex(const int indice);
    NormalVector& getNormal(const int indice);

    void setVertex(Vertex v, const int indice);

    /**
     * @brief Dessine les lignes du triangle sur l'image 
     * 
     * @param img Image cible
     * @param color Couleur à appliquer sur les lignes
     */
    void draw_line_triangle(TGAImage &img, TGAColor color) const;

    /**
     * @brief Projection en profondeur
     * 
     * @param distance_z 
     */
    void project(const double distance_z);
    std::array <int, 4> load_bounding_box() const;

    /**
     * @brief Calcule l'aire d'un triangle grâce à trois points
     * 
     * @param v1 
     * @param v2 
     * @param v3 
     * @return double 
     */
    double calculate_area (const Vertex &v1, const Vertex &v2, const Vertex &v3) const;

    /**
     * @brief Calcule l'aire d'un triangle grâce à 2 points et deux valeurs flottantes
     * 
     * @param v1 
     * @param v2 
     * @param x 
     * @param y 
     * @return double 
     */
    double calculate_area (const Vertex &v1, const Vertex &v2, double x, double y) const;

    /**
     * @brief Calcule l'intensité de la lumière via un vecteur 3D (source de lumière)
     * 
     * @param light_source 
     * @return double 
     */
    double color_intensity(const Vecteur& light_source);


    std::array<double, 4> baryocentric_values (const int x, const int y) const;


    TGAColor getColor (TGAImage &texture, std::array<double, 4> baryo);


    /**
     * @brief Applique une transformation matricielle sur tous les points
     * 
     * @param viewport 
     * @param modelview 
     * @param projection 
     */
    void transform(Matrix &viewport, Matrix &modelview, Matrix &projection);

};


#endif //__FACE_H__