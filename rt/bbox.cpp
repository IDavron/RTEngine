#include <rt/bbox.h>

namespace rt {

BBox BBox::empty() {
    return BBox(Point(FLT_MAX, FLT_MAX, FLT_MAX), Point(-FLT_MAX, -FLT_MAX, -FLT_MAX));
}

BBox BBox::full() {
    return BBox(Point(-FLT_MAX, -FLT_MAX, -FLT_MAX), Point(FLT_MAX, FLT_MAX, FLT_MAX));
}


void BBox::extend(const Point& point) {
    this->min.x = point.x < this->min.x ? point.x : this->min.x;
    this->min.y = point.y < this->min.y ? point.y : this->min.y;
    this->min.z = point.z < this->min.z ? point.z : this->min.z;

    this->max.x = point.x > this->max.x ? point.x : this->max.x;
    this->max.y = point.y > this->max.y ? point.y : this->max.y;
    this->max.z = point.z > this->max.z ? point.z : this->max.z;
}

void BBox::extend(const BBox& bbox) {
    this->min = rt::min(this->min, bbox.min);
    this->max = rt::max(this->max, bbox.max);
}

std::pair<float, float> BBox::intersect(const Ray& ray) const {
    Point min = this->min;
    Point max = this->max;
    Vector inv = Vector(1/ray.d.x, 1/ray.d.y, 1/ray.d.z);
    int s0 = inv.x < 0 ? 1 : 0;
    int s1 = inv.y < 0 ? 1 : 0;
    int s2 = inv.z < 0 ? 1 : 0;

    float tfmin, tfmax, tymin, tymax, tzmin, tzmax;

    tfmin = s0 == 1 ? (max.x - ray.o.x)*inv.x : (min.x - ray.o.x)*inv.x;
    tfmax = s0 == 0 ? (max.x - ray.o.x)*inv.x : (min.x - ray.o.x)*inv.x;
    tymin = s1 == 1 ? (max.y - ray.o.y)*inv.y : (min.y - ray.o.y)*inv.y;
    tymax = s1 == 0 ? (max.y - ray.o.y)*inv.y : (min.y - ray.o.y)*inv.y;

    if((tfmin > tymax) || (tymin > tfmax)){
        return std::pair<float, float>(tfmin, 0);
    }
    if(tymin > tfmin) tfmin = tymin;
    if(tymax < tfmax) tfmax = tymax;

    tzmin = s2 == 1 ? (max.z - ray.o.z)*inv.z : (min.z - ray.o.z)*inv.z;
    tzmax = s2 == 0 ? (max.z - ray.o.z)*inv.z : (min.z - ray.o.z)*inv.z;

    if((tfmin > tzmax) || (tzmin > tfmax)){
        return std::pair<float, float>(tfmin, 0);
    }

    if(tymin > tfmin) tfmin = tzmin;
    if(tymax < tfmax) tfmax = tzmax;

    return std::pair<float, float>(tfmin, tfmax);
}


bool BBox::isUnbound() const {
    return this->min.x == -FLT_MAX || this->min.y == -FLT_MAX || this->min.z == -FLT_MAX || this->max.x == FLT_MAX || this->max.y == FLT_MAX || this->max.z == FLT_MAX;
}

Point BBox::getCenter() const{
    return Point((this->max.x + this->min.x)/2, (this->max.y + this->min.y)/2, (this->max.z + this->min.z)/2);
}

}