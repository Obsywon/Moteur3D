#include "Model.h"

const int DEPTH {255};


Model::Model(/* args */)
{
}

Model::~Model()
{
}

void Model::transform(Face &face){
    face.transform(m_viewport, m_modelview, m_projection);
}

void Model::generateModelview (Vecteur pov, Vecteur center, Vecteur haut){
    Vecteur diff_pov_center= {pov.x - center.x, pov.y - center.y, pov.z - center.z};

    Vecteur x, y, z;

    z = Vecteur::normalize(diff_pov_center);
    x = Vecteur::produitCroix(haut, z);
    x = Vecteur::normalize(x);
    y = Vecteur::produitCroix(z, x);
    y = Vecteur::normalize(y);

    Matrix Minv, t, modelview; 
    Minv = t.identify(4);
    t = t.identify(4);

    Minv[0][0] = x.x;
    Minv[0][1] = x.y;
    Minv[0][2] = x.z;

    Minv[1][0] = y.x;
    Minv[1][1] = y.y;
    Minv[1][2] = y.z;

    Minv[2][0] = z.x;
    Minv[2][1] = z.y;
    Minv[2][2] = z.z;

    t[0][3] = -(center.x + center.y + center.z);


    modelview = Minv * t;
    m_modelview = modelview;

}

void Model::generateViewport (int x, int y, int w, int h){
    Matrix viewport = viewport.identify(4);
    viewport[0][3] = x+w/2.;
    viewport[1][3] = y+h/2.;
    viewport[2][3] = DEPTH/2.;

    viewport[0][0] = w/2.;
    viewport[1][1] = h/2.;
    viewport[2][2] = DEPTH/2.;

    m_viewport = viewport;
}

void Model::generateProjection (Vecteur pov, Vecteur center){
    Matrix proj = proj.identify(4);
    Vecteur diff_pov_center= {pov.x - center.x, pov.y - center.y, pov.z - center.z};
    double n = diff_pov_center.x * diff_pov_center.x + diff_pov_center.y * diff_pov_center.y + diff_pov_center.z * diff_pov_center.z;
    n = sqrt(n);

    proj[3][2] = -1. / n;
    m_projection = proj;
}


