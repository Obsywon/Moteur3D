#include "Matrix.h"


Matrix::Matrix(const int rows, const int cols): 
m_rows{rows}, m_cols{cols}, m_matrix{std::vector<std::vector<double>> (rows, std::vector<double>(cols, 0))}
{

}

Matrix::Matrix(const Vecteur v) : m_rows(4), m_cols(1), m_matrix{std::vector<std::vector<double>> (m_rows, std::vector<double>(m_cols, 0.))}
{
    m_matrix[0][0] = double(v.x);
    m_matrix[1][0] = double(v.y);
    m_matrix[2][0] = double(v.z);
    m_matrix[3][0] = 1.;
}

Matrix::Matrix(const Vertex& v) : m_rows(4), m_cols(1), m_matrix{std::vector<std::vector<double>> (4, std::vector<double>(1, 0.))}
{
    m_matrix[0][0] = v.getX();
    m_matrix[1][0] = v.getY();
    m_matrix[2][0] = v.getZ();
    m_matrix[3][0] = 1.;
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

Vecteur Matrix::matrixToVector(){
    Vecteur v;
    double z = m_matrix[3][0];
    v.x = m_matrix[0][0] / z;
    v.y = m_matrix[1][0] / z;
    v.z = m_matrix[2][0] / z;
    return v;
}

Matrix Matrix::operator*(const Matrix& other) {
    assert(m_cols == other.getNbRows());
    
    int cols = other.getNbCols();

    Matrix temp(m_rows, cols);
    for (int i=0; i<m_rows; i++) {
        for (int j=0; j < cols; j++) {
            temp.m_matrix[i][j] = 0.;

            for (int k=0; k<m_cols; k++) {
                temp.m_matrix[i][j] += m_matrix[i][k] * other.m_matrix[k][j];
            }
        }
    }
    return temp;
}

std::ostream& operator<<(std::ostream& s, Matrix& m) {
    for (int i=0; i<m.getNbRows(); i++)  {
        for (int j=0; j<m.getNbCols(); j++) {
            s << m[i][j];
            if (j<m.getNbCols()-1) s << "\t";
        }
        s << "\n";
    }
    return s;
}

Matrix Matrix::inverse() {
    //assert(rows==cols);
    // augmenting the square matrix with the identity matrix of the same dimensions a => [ai]
    Matrix result(m_rows, m_cols*2);
    for(int i=0; i<m_rows; i++)
        for(int j=0; j<m_cols; j++)
            result[i][j] = m_matrix[i][j];

    for(int i=0; i<m_rows; i++)
        result[i][i+m_cols] = 1;

    // first pass
    for (int i=0; i<m_rows-1; i++) {
        // normalize the first row
        for(int j=result.m_cols-1; j>=0; j--)
            result[i][j] /= result[i][i];
        for (int k=i+1; k<m_rows; k++) {
            float coeff = result[k][i];
            for (int j=0; j<result.m_cols; j++) {
                result[k][j] -= result[i][j]*coeff;
            }
        }
    }
    // normalize the last row
    for(int j=result.m_cols-1; j>=m_rows-1; j--)
        result[m_rows-1][j] /= result[m_rows-1][m_rows-1];
    // second pass
    for (int i=m_rows-1; i>0; i--) {
        for (int k=i-1; k>=0; k--) {
            float coeff = result[k][i];
            for (int j=0; j<result.m_cols; j++) {
                result[k][j] -= result[i][j]*coeff;
            }
        }
    }
    // cut the identity matrix back
    Matrix truncate(m_rows, m_cols);
    for(int i=0; i<m_rows; i++)
        for(int j=0; j<m_cols; j++)
            truncate[i][j] = result[i][j+m_cols];
    return truncate;
}



Matrix Matrix::transpose() {
    Matrix result(m_cols, m_rows);
    for(int i=0; i<m_rows; i++)
        for(int j=0; j<m_cols; j++)
            result[j][i] = m_matrix[i][j];
    return result;
}



