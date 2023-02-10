#ifndef __FACE_H__
#define __FACE_H__


#include <iostream>
#include <climits>
#include <array>
#include <random>
#include "Texture.h"
#include "Matrix.h"

constexpr int HEIGHT {1000};
constexpr int WIDTH {1000};




class Face
{
private:
    std::vector<Vertex> m_vertices;
    std::vector<Texture> m_textures;
    std::vector<NormalVector> m_normals;

    friend std::ostream& operator <<(std::ostream &s, const Face& face);
    std::array <int, 4> load_bounding_box() const;


public:
    Face(std::vector<Vertex> &vertices, std::vector<Texture> &textures, std::vector<NormalVector> &normals);
    ~Face();

    /**
     * Dessine les segments du triangle
    */
    void draw_line_triangle(TGAImage &img, TGAColor color) const;

    void project(const double distance_z);


    /**
     * Dessine un triangle rempli
    */
    void draw_triangle(TGAImage &img, double* z_buffer, TGAImage &texture);


    double calculate_area (const Vertex &v1, const Vertex &v2, const Vertex &v3) const;


    double calculate_area (const Vertex &v1, const Vertex &v2, double x, double y) const;

    double color_intensity(const Vecteur& light_source);

    void adapt_color (const int x, const int y, TGAImage &img, TGAColor &color, double intensity);

    std::array<double, 4> baryocentric_values (const int x, const int y) const;

    void transform(Matrix &viewport, Matrix &modelview, Matrix &projection);
};

#endif //__FACE_H__