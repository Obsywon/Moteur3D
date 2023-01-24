#include "Matrix.h"


Matrix::Matrix(const int h, const int w): 
m_rows{h}, m_cols{w}, m_matrix{std::vector<std::vector<double>> (w, std::vector<double>(h, 0))}
{

}

Matrix::~Matrix()
{
}

std::vector<double>& Matrix::operator[](const int i) {
    assert(i>=0 && i<m_rows);
    return m_matrix[i];
}

int Matrix::getNbCols() const {
    return m_cols;
}

int Matrix::getNbRows() const {
    return m_rows;
}
Matrix Matrix::identify(const int dimension){
    Matrix temp (dimension, dimension);

    for (int i = 0; i < dimension; i++){
        for (int j = 0; j < dimension; j++){
            if (i == j){
                temp[i][j] = 1.f;
            }else{
                temp[i][j] = 0.f;
            }

        }
    }
    return temp;
}

Matrix Matrix::operator*(const Matrix& other) {
    assert(m_cols == other.getNbRows());
    
    int cols = other.getNbRows();

    Matrix temp(m_rows, cols);
    for (int i=0; i<m_rows; i++) {
        for (int j=0; j < cols; j++) {
            temp.m_matrix[i][j] = 0.f;

            for (int k=0; k<m_cols; k++) {
                temp.m_matrix[i][j] += m_matrix[i][k] * other.m_matrix[k][j];
            }
        }
    }
    return temp;
}