#include <core/point.h>
#include <core/homogeneouscoord.h>
#include <core/scalar.h>
#include <core/assert.h>
#include <core/vector.h>

namespace rt {

Point::Point(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Point::Point(const HomogeneousCoord& coord)
{
    rt_assert(coord.w != 0);
    this->x = coord.x / coord.w;
    this->y = coord.y / coord.w;
    this->z = coord.z / coord.w;
}

Vector Point::operator - (const Point& b) const {
   Vector v;
   v.x = this->x-b.x;
   v.y = this->y-b.y;
   v.z = this->z-b.z;
   return v;
}

Point Point::operator - (float x) const {
    Point p ;
    p.x = this->x - x;
    p.y = this->y - x;
    p.z = this->z - x;
    return p;
}

Point Point::operator + (float x) const {
    Point p ;
    p.x = this->x + x;
    p.y = this->y + x;
    p.z = this->z + x;
    return p;
}

bool Point::operator == (const Point& b) const {
    return (this->x == b.x && this->y == b.y && this->z == b.z);
}

bool Point::operator != (const Point& b) const {
    return (this->x != b.x || this->y != b.y || this->z != b.z);
}

Point operator * (float scalar, const Point& b) {
    Point p;
    p.x = b.x * scalar;
    p.y = b.y * scalar;
    p.z = b.z * scalar;
    return p;
}

Point operator * (const Point& a, float scalar) {
    Point p;
    p.x = a.x * scalar;
    p.y = a.y * scalar;
    p.z = a.z * scalar;
    return p;
}

Point min(const Point& a, const Point& b) {
    Point p;
    p.x = std::min(a.x,b.x);
    p.y = std::min(a.y,b.y);
    p.z = std::min(a.z,b.z);
    return p;
}

Point max(const Point& a, const Point& b) {
    Point p;
    p.x = std::max(a.x,b.x);
    p.y = std::max(a.y,b.y);
    p.z = std::max(a.z,b.z);
    return p;
}

}
