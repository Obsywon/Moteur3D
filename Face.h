#ifndef __FACE_H__
#define __FACE_H__


#include <iostream>
#include <vector>
#include <climits>
#include <array>
#include <random>
#include "Vertex.h"



class Face
{
private:
    const std::vector<Vertex> m_vertices;
    int m_fullArea;

    friend std::ostream& operator <<(std::ostream &s, const Face& face);
    std::array <int, 4> load_bounding_box() const;


public:
    Face(const std::vector<Vertex> &vertices);
    ~Face();

    /**
     * Dessine les segments du triangle
    */
    void draw_line_triangle(TGAImage &img, TGAColor color) const;

    /**
     * Dessine un triangle rempli
    */
    void draw_triangle(TGAImage &img, TGAColor color) const;


    /**
     * Vérifie si le pixel se situe dans le triangle
    */
    bool check_pixel_in_triangle(const int x, const int y) const;


    int calculate_area (const Vertex &v1, const Vertex &v2, const Vertex &v3) const;


    int calculate_area (const Vertex &v1, const Vertex &v2, int x, int y) const;

    
};

#endif //__FACE_H__