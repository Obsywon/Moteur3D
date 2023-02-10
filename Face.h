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
    Face(std::vector<Vertex> &vertices, std::vector<Texture> &textures, std::vector<NormalVector> &normals);
    ~Face();

    Vertex& getVertex(const int indice);
    NormalVector& getNormal(const int indice);

    void setVertex(Vertex v, const int indice);

    /**
     * Dessine les segments du triangle
    */
    void draw_line_triangle(TGAImage &img, TGAColor color) const;

    void project(const double distance_z);
    std::array <int, 4> load_bounding_box() const;


    /**
     * Dessine un triangle rempli
    */

    double calculate_area (const Vertex &v1, const Vertex &v2, const Vertex &v3) const;


    double calculate_area (const Vertex &v1, const Vertex &v2, double x, double y) const;

    double color_intensity(const Vecteur& light_source);

    void adapt_color (const int x, const int y, TGAImage &img, TGAColor &color, double intensity);

    std::array<double, 4> baryocentric_values (const int x, const int y) const;


    TGAColor getColor (TGAImage &texture, std::array<double, 4> baryo);


    /**
     * Réalise la transformation de l'objet 
    */
    void transform(Matrix &viewport, Matrix &modelview, Matrix &projection);

};


#endif //__FACE_H__