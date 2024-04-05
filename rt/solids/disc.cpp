#include <rt/solids/disc.h>

namespace rt {

Disc::Disc(const Point& center, const Vector& normal, float radius, CoordMapper* texMapper, Material* material)
{
   this->center = center;
   this->normal = normal.normalize();
   this->radius = radius;
    if(texMapper == nullptr){
        this->texMapper = new WorldMapper(Vector::rep(1));
    }else{
        this->texMapper = texMapper;
    }
   this->material = material;
}

BBox Disc::getBounds() const {
    return BBox(this->center - radius, this->center + radius);
}

Intersection Disc::intersect(const Ray& ray, float tmin, float tmax) const {
    float numerator = this->normal.x*(this->center.x-ray.o.x) + this->normal.y*(this->center.y-ray.o.y) + this->normal.z*(this->center.z - ray.o.z);
    float denominator = ray.d.x*this->normal.x + ray.d.y*this->normal.y + ray.d.z*this->normal.z;
    if(denominator == 0){
        return Intersection::failure();
    }
    float t = numerator/denominator;
    if(t < tmin || t > tmax) return Intersection::failure();
    Point hitPoint = ray.o + t*ray.d;
    if((hitPoint-this->center).length() > this->radius){
        return Intersection::failure();
    }
    return Intersection(t, ray, this, this->normal, ray.o + t*ray.d);
}

Solid::Sample Disc::sample() const {
    Sample s;
    Vector iv = Vector(this->normal.x + random(), this->normal.y + random(), this->normal.z + random());
    Vector v1 = cross(this->normal, iv).normalize();
    Vector v2 = cross(this->normal, v1).normalize();
    float r1 = (random()*this->radius)*2 - this->radius;
    float r2 = random()*sqrt(pow(this->radius,2) - pow(r1,2));
    if(random() > 0.5){
        r2 = -r2;
    }
    Point p = this->center + r1*v1 + r2*v2;
    s.normal = this->normal;
    s.point = p;
    return s;
}

float Disc::getArea() const {
    return pi*this->radius*this->radius;
}
}
