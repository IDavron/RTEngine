#include <core/homogeneouscoord.h>
#include <core/vector.h>
#include <core/point.h>
#include <core/assert.h>
#include <core/scalar.h>

namespace rt {

HomogeneousCoord::HomogeneousCoord(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

HomogeneousCoord::HomogeneousCoord(const Point& p) {
    this->x = p.x;
    this->y = p.y;
    this->z = p.z;
    this->w = 1;
}

HomogeneousCoord::HomogeneousCoord(const Vector& vec) {
    this->x = vec.x;
    this->y = vec.y;
    this->z = vec.z;
    this->w = 0;
}

float& HomogeneousCoord::operator [] (int idx) {
    rt_assert(idx >= 0 && idx <= 3);
    if(idx == 0) return this->x;
    if(idx == 1) return this->y;
    if(idx == 2) return this->z;
    if(idx == 3) return this->w;
    return this->w;
}

float HomogeneousCoord::operator [] (int idx) const {
    rt_assert(idx >= 0 && idx <= 3);
    if(idx == 0) return this->x;
    if(idx == 1) return this->y;
    if(idx == 2) return this->z;
    if(idx == 3) return this->w;
    return 0.0f;
}

HomogeneousCoord HomogeneousCoord::operator + (const HomogeneousCoord& b) const {
    return HomogeneousCoord(this->x + b.x, this->y + b.y, this->z + b.z, this->w + b.w);
}

HomogeneousCoord HomogeneousCoord::operator - (const HomogeneousCoord& b) const {
        return HomogeneousCoord(this->x - b.x, this->y - b.y, this->z - b.z, this->w - b.w);
}

HomogeneousCoord HomogeneousCoord::operator * (const HomogeneousCoord& b) const {
    return HomogeneousCoord(this->x * b.x, this->y * b.y, this->z * b.z, this->w * b.w);
}

HomogeneousCoord HomogeneousCoord::operator / (const HomogeneousCoord& b) const {
    return HomogeneousCoord(this->x / b.x, this->y / b.y, this->z / b.z, this->w / b.w);
}

HomogeneousCoord operator * (float scalar, const HomogeneousCoord& b) {
    return HomogeneousCoord(b.x * scalar, b.y * scalar, b.z * scalar, b.w * scalar);
}

HomogeneousCoord operator * (const HomogeneousCoord& a, float scalar) {
    return scalar*a;
}

HomogeneousCoord operator / (const HomogeneousCoord& a, float scalar) {
    return HomogeneousCoord(a.x / scalar, a.y / scalar, a.z / scalar, a.w / scalar);
}

float dot(const HomogeneousCoord& a, const HomogeneousCoord& b) {
    return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
}

HomogeneousCoord HomogeneousCoord::operator - () const {
    return HomogeneousCoord(-this->x, -this->y, -this->z, -this->w);
}

bool HomogeneousCoord::operator == (const HomogeneousCoord& b) const {
    return this->x == b.x && this->y == b.y && this->z == b.z && this->w == b.w;
}

bool HomogeneousCoord::operator != (const HomogeneousCoord& b) const {
    return this->x != b.x || this->y != b.y || this->z != b.z || this->w != b.w;
}

HomogeneousCoord min(const HomogeneousCoord& a, const HomogeneousCoord& b) {
    return HomogeneousCoord(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z), min(a.w, b.w));
}

HomogeneousCoord max(const HomogeneousCoord& a, const HomogeneousCoord& b) {
    return HomogeneousCoord(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z), max(a.w, b.w));
}

}