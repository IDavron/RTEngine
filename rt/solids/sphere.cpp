#include <rt/solids/sphere.h>
#include<iostream>
namespace rt {

Sphere::Sphere(const Point& center, float radius, CoordMapper* texMapper, Material* material)
{
    this->center = center;
    this->radius = radius;
    if(texMapper == nullptr){
        this->texMapper = new WorldMapper(Vector::rep(1));
    }else{
        this->texMapper = texMapper;
    }
    this->material = material;
}

BBox Sphere::getBounds() const {
    return BBox(Point(this->center - this->radius), Point(this->center + radius));
}

Intersection Sphere::intersect(const Ray& ray, float tmin, float tmax) const {
    Vector origin_center = ray.o - this->center;
    float sqrt_equation = sqr(dot(ray.d, origin_center)) - ray.d.lensqr() * ((origin_center).lensqr() - sqr(this->radius));
    if(sqrt_equation < 0){
        return Intersection::failure();
    }
    float numerator1 = -dot(ray.d, origin_center) + sqrt(sqrt_equation);
    float numerator2 = -dot(ray.d, origin_center) - sqrt(sqrt_equation);
    float denominator = ray.d.lensqr();
    float t1 = numerator1/denominator;
    float t2 = numerator2/denominator;
    float t = t1 < t2 ? t1 : t2;
    if(t1 < 0.00001 && t2 < 0.00001){
        return Intersection::failure();
    }
    if(t2 < 0.00001){
        t = t1;
    }
    if(t1 < 0.00001){
        t = t2;
    }
    if(t < tmin || t > tmax){
        return Intersection::failure();
    }
    Point hitPoint = ray.o + t*ray.d;
    return Intersection(t, ray, this, (hitPoint - this->center).normalize(), hitPoint);
}

Solid::Sample Sphere::sample() const {
	NOT_IMPLEMENTED;
}

float Sphere::getArea() const {
    return 4*pi*this->radius*this->radius;
}

// Point Sphere::getCenter() const{
//     return this->center;
// }

}
