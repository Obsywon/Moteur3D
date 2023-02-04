#ifndef __MODEL_H__
#define __MODEL_H__

#include "Vertex.h"
#include "Matrix.h"
#include "Face.h"

class Model
{
private:
    Matrix m_modelview;
    Matrix m_viewport;
    Matrix m_projection;

public:
    Model(/* args */);
    ~Model();

    void transform(Face &face);

    void generateModelview(Vecteur pov, Vecteur center, Vecteur haut);

    void generateViewport(int x, int y, int w, int h);

    void generateProjection(Vecteur pov, Vecteur center);
};

#endif