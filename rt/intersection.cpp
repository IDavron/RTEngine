#include <rt/intersection.h>

namespace rt {

Intersection::Intersection(float distance, const Ray& ray, const Solid* solid, const Vector& normal, const Point& local)
{
    this->distance = distance;
    this->ray = ray;
    this->solid = solid;
    this->n = normal;
    this->l = local;
}

Intersection::operator bool() const {
    if(this->distance != FLT_MAX) return true;
    return false;
}

Intersection Intersection::failure() {
    Intersection i;
    i.distance = FLT_MAX;
    return i;
}

Point Intersection::hitPoint() const {
    return Point(this->ray.o + this->distance*this->ray.d);
}

Vector Intersection::normal() const {
    return n;
}

Point Intersection::local() const {
    return l;
}

}
