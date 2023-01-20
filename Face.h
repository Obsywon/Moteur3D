#ifndef __FACE_H__
#define __FACE_H__


#include <iostream>
#include <vector>
#include <climits>
#include <array>
#include <random>
#include "Vertex.h"
#include "Texture.h"

constexpr int HEIGHT {1000};
constexpr int WIDTH {1000};

struct vecteur {
    double x;
    double y;
    double z;
};


class Face
{
private:
    std::vector<Vertex> m_vertices;
    std::vector<Texture> m_textures;
    int m_fullArea;

    friend std::ostream& operator <<(std::ostream &s, const Face& face);
    std::array <int, 4> load_bounding_box() const;


public:
    Face(std::vector<Vertex> &vertices, std::vector<Texture> &textures);
    ~Face();

    /**
     * Dessine les segments du triangle
    */
    void draw_line_triangle(TGAImage &img, TGAColor color) const;

    /**
     * Dessine un triangle rempli
    */
    void draw_triangle(TGAImage &img, double* z_buffer, TGAImage &texture);


    int calculate_area (const Vertex &v1, const Vertex &v2, const Vertex &v3) const;


    int calculate_area (const Vertex &v1, const Vertex &v2, int x, int y) const;

    double color_intensity(const vecteur& light);

    void adapt_color (const int x, const int y, TGAImage &img, TGAColor &color, double intensity);

    std::array<double, 4> baryocentric_values (const int x, const int y) const;
};

#endif //__FACE_H__