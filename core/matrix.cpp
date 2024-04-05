#include <core/matrix.h>
#include <core/assert.h>

#include <core/vector.h>
#include <core/point.h>

namespace rt {

Matrix::Matrix(const HomogeneousCoord& r1, const HomogeneousCoord& r2, const HomogeneousCoord& r3, const HomogeneousCoord& r4) {
    this->r1 = r1;
    this->r2 = r2;
    this->r3 = r3;
    this->r4 = r4;
}

HomogeneousCoord& Matrix::operator[](int idx) {
    if(idx == 0)return this->r1;
    if(idx == 1)return this->r2;
    if(idx == 2)return this->r3;
    if(idx == 3)return this->r4;
    return this->r4;
}

HomogeneousCoord Matrix::operator[](int idx) const {
    if(idx == 0)return this->r1;
    if(idx == 1)return this->r2;
    if(idx == 2)return this->r3;
    if(idx == 3)return this->r4;

    return HomogeneousCoord(0,0,0,0);
}

Matrix Matrix::operator+(const Matrix& b) const {
    return Matrix(this->r1 + b.r1, this->r2 + b.r2, this->r3 + b.r3, this->r4 + b.r4);
}

Matrix Matrix::operator-(const Matrix& b) const {
    return Matrix(this->r1 - b.r1, this->r2 - b.r2, this->r3 - b.r3, this->r4 - b.r4);
}

Matrix Matrix::transpose() const {
    HomogeneousCoord c1(this->r1.x, this->r2.x, this->r3.x, this->r4.x);
    HomogeneousCoord c2(this->r1.y, this->r2.y, this->r3.y, this->r4.y);
    HomogeneousCoord c3(this->r1.z, this->r2.z, this->r3.z, this->r4.z);
    HomogeneousCoord c4(this->r1.w, this->r2.w, this->r3.w, this->r4.w);

    return Matrix(c1,c2,c3,c4);
}

Matrix Matrix::invert() const {
    Matrix result;
    const Matrix& m = *this;

    // Taken and modified from http://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
    result[0][0] =  m[1][1] * m[2][2] * m[3][3] - m[1][1] * m[2][3] * m[3][2] - m[2][1] * m[1][2] * m[3][3] + m[2][1] * m[1][3] * m[3][2] + m[3][1] * m[1][2] * m[2][3] - m[3][1] * m[1][3] * m[2][2];
    result[1][0] = -m[1][0] * m[2][2] * m[3][3] + m[1][0] * m[2][3] * m[3][2] + m[2][0] * m[1][2] * m[3][3] - m[2][0] * m[1][3] * m[3][2] - m[3][0] * m[1][2] * m[2][3] + m[3][0] * m[1][3] * m[2][2];
    result[2][0] =  m[1][0] * m[2][1] * m[3][3] - m[1][0] * m[2][3] * m[3][1] - m[2][0] * m[1][1] * m[3][3] + m[2][0] * m[1][3] * m[3][1] + m[3][0] * m[1][1] * m[2][3] - m[3][0] * m[1][3] * m[2][1];
    result[3][0] = -m[1][0] * m[2][1] * m[3][2] + m[1][0] * m[2][2] * m[3][1] + m[2][0] * m[1][1] * m[3][2] - m[2][0] * m[1][2] * m[3][1] - m[3][0] * m[1][1] * m[2][2] + m[3][0] * m[1][2] * m[2][1];

    float det = m[0][0] * result[0][0] + m[0][1] * result[1][0] + m[0][2] * result[2][0] + m[0][3] * result[3][0];
    if (det == 0)
        return Matrix::zero();

    result[0][1] = -m[0][1] * m[2][2] * m[3][3] + m[0][1] * m[2][3] * m[3][2] + m[2][1] * m[0][2] * m[3][3] - m[2][1] * m[0][3] * m[3][2] - m[3][1] * m[0][2] * m[2][3] + m[3][1] * m[0][3] * m[2][2];
    result[1][1] =  m[0][0] * m[2][2] * m[3][3] - m[0][0] * m[2][3] * m[3][2] - m[2][0] * m[0][2] * m[3][3] + m[2][0] * m[0][3] * m[3][2] + m[3][0] * m[0][2] * m[2][3] - m[3][0] * m[0][3] * m[2][2];
    result[2][1] = -m[0][0] * m[2][1] * m[3][3] + m[0][0] * m[2][3] * m[3][1] + m[2][0] * m[0][1] * m[3][3] - m[2][0] * m[0][3] * m[3][1] - m[3][0] * m[0][1] * m[2][3] + m[3][0] * m[0][3] * m[2][1];
    result[3][1] =  m[0][0] * m[2][1] * m[3][2] - m[0][0] * m[2][2] * m[3][1] - m[2][0] * m[0][1] * m[3][2] + m[2][0] * m[0][2] * m[3][1] + m[3][0] * m[0][1] * m[2][2] - m[3][0] * m[0][2] * m[2][1];
    result[0][2] =  m[0][1] * m[1][2] * m[3][3] - m[0][1] * m[1][3] * m[3][2] - m[1][1] * m[0][2] * m[3][3] + m[1][1] * m[0][3] * m[3][2] + m[3][1] * m[0][2] * m[1][3] - m[3][1] * m[0][3] * m[1][2];
    result[1][2] = -m[0][0] * m[1][2] * m[3][3] + m[0][0] * m[1][3] * m[3][2] + m[1][0] * m[0][2] * m[3][3] - m[1][0] * m[0][3] * m[3][2] - m[3][0] * m[0][2] * m[1][3] + m[3][0] * m[0][3] * m[1][2];
    result[2][2] =  m[0][0] * m[1][1] * m[3][3] - m[0][0] * m[1][3] * m[3][1] - m[1][0] * m[0][1] * m[3][3] + m[1][0] * m[0][3] * m[3][1] + m[3][0] * m[0][1] * m[1][3] - m[3][0] * m[0][3] * m[1][1];
    result[3][2] = -m[0][0] * m[1][1] * m[3][2] + m[0][0] * m[1][2] * m[3][1] + m[1][0] * m[0][1] * m[3][2] - m[1][0] * m[0][2] * m[3][1] - m[3][0] * m[0][1] * m[1][2] + m[3][0] * m[0][2] * m[1][1];
    result[0][3] = -m[0][1] * m[1][2] * m[2][3] + m[0][1] * m[1][3] * m[2][2] + m[1][1] * m[0][2] * m[2][3] - m[1][1] * m[0][3] * m[2][2] - m[2][1] * m[0][2] * m[1][3] + m[2][1] * m[0][3] * m[1][2];
    result[1][3] =  m[0][0] * m[1][2] * m[2][3] - m[0][0] * m[1][3] * m[2][2] - m[1][0] * m[0][2] * m[2][3] + m[1][0] * m[0][3] * m[2][2] + m[2][0] * m[0][2] * m[1][3] - m[2][0] * m[0][3] * m[1][2];
    result[2][3] = -m[0][0] * m[1][1] * m[2][3] + m[0][0] * m[1][3] * m[2][1] + m[1][0] * m[0][1] * m[2][3] - m[1][0] * m[0][3] * m[2][1] - m[2][0] * m[0][1] * m[1][3] + m[2][0] * m[0][3] * m[1][1];
    result[3][3] =  m[0][0] * m[1][1] * m[2][2] - m[0][0] * m[1][2] * m[2][1] - m[1][0] * m[0][1] * m[2][2] + m[1][0] * m[0][2] * m[2][1] + m[2][0] * m[0][1] * m[1][2] - m[2][0] * m[0][2] * m[1][1];

    result = result*(1.0f/det);
    return result;
}

bool Matrix::operator==(const Matrix& b) const {
    return this->r1 == b.r1 && this->r2 == b.r2 && this->r3 == b.r3 && this->r4 == b.r4;
}

bool Matrix::operator!=(const Matrix& b) const {
    return this->r1 != b.r1 || this->r2 != b.r2 || this->r3 != b.r3 || this->r4 != b.r4;
}

Matrix product(const Matrix& a, const Matrix& b) {
    Matrix bT = b.transpose();

    HomogeneousCoord r1(dot(a.r1, bT.r1), dot(a.r1, bT.r2), dot(a.r1, bT.r3), dot(a.r1, bT.r4));
    HomogeneousCoord r2(dot(a.r2, bT.r1), dot(a.r2, bT.r2), dot(a.r2, bT.r3), dot(a.r2, bT.r4));
    HomogeneousCoord r3(dot(a.r3, bT.r1), dot(a.r3, bT.r2), dot(a.r3, bT.r3), dot(a.r3, bT.r4));
    HomogeneousCoord r4(dot(a.r4, bT.r1), dot(a.r4, bT.r2), dot(a.r4, bT.r3), dot(a.r4, bT.r4));

    return Matrix(r1,r2,r3,r4);
}

Matrix operator*(const Matrix& a, float scalar) {
    return Matrix(a.r1 * scalar, a.r2 * scalar, a.r3 * scalar, a.r4 * scalar);
}

Matrix operator*(float scalar, const Matrix& a) {
    return a * scalar;
}

HomogeneousCoord Matrix::operator*(const HomogeneousCoord& b) const {
    return HomogeneousCoord(dot(this->r1, b), dot(this->r2, b), dot(this->r3, b), dot(this->r4, b));
}

Vector Matrix::operator*(const Vector& b) const {
    HomogeneousCoord hc(b);
    return Vector(HomogeneousCoord(dot(this->r1, hc), dot(this->r2, hc), dot(this->r3, hc), dot(this->r4, hc)));
}

Point Matrix::operator*(const Point& b) const {
    HomogeneousCoord hc(b);
    return Point(HomogeneousCoord(dot(this->r1, hc), dot(this->r2, hc), dot(this->r3, hc), dot(this->r4, hc)));
}

float Matrix::det() const {
    Matrix result;
    const Matrix& m = *this;
    result[0][0] =  m[1][1] * m[2][2] * m[3][3] - m[1][1] * m[2][3] * m[3][2] - m[2][1] * m[1][2] * m[3][3] + m[2][1] * m[1][3] * m[3][2] + m[3][1] * m[1][2] * m[2][3] - m[3][1] * m[1][3] * m[2][2];
    result[1][0] = -m[1][0] * m[2][2] * m[3][3] + m[1][0] * m[2][3] * m[3][2] + m[2][0] * m[1][2] * m[3][3] - m[2][0] * m[1][3] * m[3][2] - m[3][0] * m[1][2] * m[2][3] + m[3][0] * m[1][3] * m[2][2];
    result[2][0] =  m[1][0] * m[2][1] * m[3][3] - m[1][0] * m[2][3] * m[3][1] - m[2][0] * m[1][1] * m[3][3] + m[2][0] * m[1][3] * m[3][1] + m[3][0] * m[1][1] * m[2][3] - m[3][0] * m[1][3] * m[2][1];
    result[3][0] = -m[1][0] * m[2][1] * m[3][2] + m[1][0] * m[2][2] * m[3][1] + m[2][0] * m[1][1] * m[3][2] - m[2][0] * m[1][2] * m[3][1] - m[3][0] * m[1][1] * m[2][2] + m[3][0] * m[1][2] * m[2][1];

    float det = m[0][0] * result[0][0] + m[0][1] * result[1][0] + m[0][2] * result[2][0] + m[0][3] * result[3][0];
    return det;
}

Matrix Matrix::zero() {
    HomogeneousCoord r1(0,0,0,0);
    return Matrix(r1, r1, r1, r1);
}

Matrix Matrix::identity() {
    return Matrix(HomogeneousCoord(1,0,0,0), HomogeneousCoord(0,1,0,0), HomogeneousCoord(0,0,1,0), HomogeneousCoord(0,0,0,1));
}

Matrix Matrix::system(const Vector& e1, const Vector& e2, const Vector& e3) {
    return Matrix(HomogeneousCoord(e1), HomogeneousCoord(e2), HomogeneousCoord(e3), HomogeneousCoord(0,0,0,1)).transpose();
}

}