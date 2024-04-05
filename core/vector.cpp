#include <core/scalar.h>
#include <core/vector.h>
#include <core/point.h>
#include <core/homogeneouscoord.h>
#include <core/assert.h>
#include <algorithm>
#include <cmath>

namespace rt {

Vector::Vector(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector::Vector(const HomogeneousCoord& coord)
{
    this->x = coord.x;
    this->y = coord.y;
    this->z = coord.z;
}

Vector Vector::operator + (const Vector& b) const {
    Vector v;
    v.x = this->x + b.x;
    v.y = this->y + b.y;
    v.z = this->z + b.z;
    return v;
}

Vector Vector::operator - (const Vector& b) const {
    Vector v;
    v.x = this->x - b.x;
    v.y = this->y - b.y;
    v.z = this->z - b.z;
    return v;
}

Vector Vector::operator - () const {
    Vector v;
    v.x = -this->x;
    v.y = -this->y;
    v.z = -this->z;
    return v;
}

Vector Vector::normalize() const {
    Vector v;
    float l = length();
    v.x = this->x / l;
    v.y = this->y / l;
    v.z = this->z / l;
    return v;
}

Vector operator * (float scalar, const Vector& b) {
    Vector v;
    v.x = b.x * scalar;
    v.y = b.y * scalar;
    v.z = b.z * scalar;
    return v;
}

Vector operator * (const Vector& a, float scalar) {
    Vector v;
    v.x = a.x * scalar;
    v.y = a.y * scalar;
    v.z = a.z * scalar;
    return v;
}

Vector operator / (const Vector& a, float scalar) {
    Vector v;
    v.x = a.x / scalar;
    v.y = a.y / scalar;
    v.z = a.z / scalar;
    return v;
}

Vector cross(const Vector& a, const Vector& b) {
    Vector v;
    v.x = (a.y*b.z) - (a.z*b.y);
    v.y = (a.z*b.x) - (a.x*b.z);
    v.z = (a.x*b.y) - (a.y*b.x);
    return v;
}

float dot(const Vector& a, const Vector& b) {
    return (a.x*b.x) + (a.y*b.y) + (a.z*b.z);
}

float Vector::lensqr() const {
    return (this->x*this->x) + (this->y*this->y) + (this->z*this->z);
}

float Vector::length() const {
    return sqrt(lensqr());
}

bool Vector::operator == (const Vector& b) const {
    return (this->x == b.x && this->y == b.y && this->z == b.z);
}

bool Vector::operator != (const Vector& b) const {
    return (this->x != b.x || this->y != b.y || this->z != b.z);
}

Vector min(const Vector& a, const Vector& b) {
    Vector v;
    v.x = std::min(a.x, b.x);
    v.y = std::min(a.y, b.y);
    v.z = std::min(a.z, b.z);
    return v;
}

Vector max(const Vector& a, const Vector& b) {
    Vector v;
    v.x = std::max(a.x, b.x);
    v.y = std::max(a.y, b.y);
    v.z = std::max(a.z, b.z);
    return v;
}

Point operator + (const Point& a, const Vector& b) {
    Point p;
    p.x = a.x + b.x;
    p.y = a.y + b.y;
    p.z = a.z + b.z;
    return p;
}

Point operator + (const Vector& a, const Point& b) {
    return b+a;
}

Point operator - (const Point& a, const Vector& b) {
    return a+(-b);
}

Point operator * (const HomogeneousCoord& scale, const Point& p) {
    /* TODO */ NOT_IMPLEMENTED;
}
}
