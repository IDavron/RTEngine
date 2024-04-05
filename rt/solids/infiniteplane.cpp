#include <rt/solids/infiniteplane.h>

namespace rt {

InfinitePlane::InfinitePlane(const Point& origin, const Vector& normal, CoordMapper* texMapper, Material* material)
{
    this->origin = origin;
    this->normal = normal;
    if(texMapper == nullptr){
        this->texMapper = new WorldMapper(Vector::rep(1));
    }else{
        this->texMapper = texMapper;
    }
    this->material = material;
}

BBox InfinitePlane::getBounds() const {
    return BBox(Point(-FLT_MAX, -FLT_MAX, -FLT_MAX), Point(FLT_MAX, FLT_MAX, FLT_MAX));
}

Intersection InfinitePlane::intersect(const Ray& ray, float tmin, float tmax) const {
    float numerator = this->normal.x*(this->origin.x-ray.o.x) + this->normal.y*(this->origin.y-ray.o.y) + this->normal.z*(this->origin.z - ray.o.z);
    float denominator = ray.d.x*this->normal.x + ray.d.y*this->normal.y + ray.d.z*this->normal.z;
    if(denominator == 0){
        return Intersection::failure();
    }
    float t = numerator/denominator;
    if(t < tmin || t > tmax) return Intersection::failure();
    Point hit_point = ray.o + t*ray.d;
    return Intersection(t, ray, this, this->normal, hit_point);
}

Solid::Sample InfinitePlane::sample() const {
    /* TODO */ NOT_IMPLEMENTED;
}

float InfinitePlane::getArea() const {
    return FLT_MAX;
}

// Point InfinitePlane::getCenter() const{
//     return this->origin;
// }

}
