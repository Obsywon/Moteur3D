#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "Vertex.h"
#include <cassert>


const int SIZE = 4;

class Matrix
{
private:
    int m_rows;
    int m_cols;
    std::vector<std::vector<double> > m_matrix;

    
public:
    explicit Matrix(const int h = SIZE, const int w = SIZE);
    Matrix(const vecteur& v);
    Matrix(const Vertex& v);
    ~Matrix();
    int getNbCols() const;
    int getNbRows() const;
    std::vector<double>& operator[](const int i);
    Matrix operator*(const Matrix& other);
    Matrix identify(const int dimension);
};



#endif //__MATRIX_H__