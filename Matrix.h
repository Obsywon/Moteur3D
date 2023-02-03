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
    friend std::ostream& operator<<(std::ostream& s, Matrix& m);

    
public:
    explicit Matrix(const int rows = SIZE, const int cols = SIZE);
    Matrix(const Vecteur v);
    Matrix(const Vertex& v);
    ~Matrix();
    int getNbCols() const;
    int getNbRows() const;
    std::vector<double>& operator[](const int i);
    Matrix operator*(const Matrix& other);
    Matrix identify(const int dimension);
    Matrix inverse();
    Matrix transpose();
    Vecteur matrixToVector();

};



#endif //__MATRIX_H__