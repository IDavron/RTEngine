#include <rt/solids/aabox.h>

namespace rt {

AABox::AABox(const Point& corner1, const Point& corner2, CoordMapper* texMapper, Material* material)
{
    this->corner1 = corner1;
    this->corner2 = corner2;
    if(texMapper == nullptr){
        this->texMapper = new WorldMapper(Vector::rep(1));
    }else{
        this->texMapper = texMapper;
    }
    this->material = material;
}

BBox AABox::getBounds() const {
    return BBox(Point(min(this->corner1.x, this->corner2.x), min(this->corner1.y, this->corner2.y), min(this->corner1.z, this->corner2.z)), Point(max(this->corner1.x, this->corner2.x), max(this->corner1.y, this->corner2.y), max(this->corner1.z, this->corner2.z)));
}

Solid::Sample AABox::sample() const {
    NOT_IMPLEMENTED;
}

float AABox::getArea() const {
    return 2*(abs((this->corner1.x - this->corner2.x)*abs(this->corner1.y - this->corner2.y))) + 2*(abs((this->corner1.x - this->corner2.x)*abs(this->corner1.z - this->corner2.z))) + 2*(abs((this->corner1.y - this->corner2.y)*abs(this->corner1.z - this->corner2.z)));
}

Intersection AABox::intersect(const Ray& ray, float tmin, float tmax) const {
    Intersection i;
    bool intersection_occured = false;
    Point p1 = Point(min(this->corner1.x, this->corner2.x), min(this->corner1.y, this->corner2.y), min(this->corner1.z, this->corner2.z));
    Point p2 = Point(max(this->corner1.x, this->corner2.x), max(this->corner1.y, this->corner2.y), max(this->corner1.z, this->corner2.z));
    
    //side 1
    float numerator = (p1.z - ray.o.z);
    float denominator = ray.d.z;
    if(denominator != 0){
        float t = numerator/denominator;
        Point hitPoint = ray.o + t*ray.d;
        if((t >= tmin && t <= tmax) && (hitPoint.x >= p1.x && hitPoint.x <= p2.x) && (hitPoint.y >= p1.y && hitPoint.y <= p2.y)){
            i = Intersection(t, ray, this, Vector(0,0,-1), hitPoint);
            tmax = t;
        }
    }

    //side 2
    numerator = (p2.z - ray.o.z);
    denominator = ray.d.z;
    if(denominator != 0){
        float t = numerator/denominator;
        Point hitPoint = ray.o + t*ray.d;
        if((t >= tmin && t <= tmax) && (hitPoint.x >= p1.x && hitPoint.x <= p2.x) && (hitPoint.y >= p1.y && hitPoint.y <= p2.y)){
            intersection_occured = true;
            i = Intersection(t, ray, this, Vector(0,0,1), hitPoint);
            tmax = t;
        }
    }

    //side 3
    numerator = (p2.x - ray.o.x);
    denominator = ray.d.x;
    if(denominator != 0){
        float t = numerator/denominator;
        Point hitPoint = ray.o + t*ray.d;
        if((t >= tmin && t <= tmax) && (hitPoint.y >= p1.y && hitPoint.y <= p2.y) && (hitPoint.z >= p1.z && hitPoint.z <= p2.z)){
            intersection_occured = true;
            i = Intersection(t, ray, this, Vector(1,0,0), hitPoint);
            tmax = t;
        }
    }

    //side 4
    numerator = (p1.x - ray.o.x);
    denominator = ray.d.x;
    if(denominator != 0){
        float t = numerator/denominator;
        Point hitPoint = ray.o + t*ray.d;
        if((t >= tmin && t <= tmax) && (hitPoint.y >= p1.y && hitPoint.y <= p2.y) && (hitPoint.z >= p1.z && hitPoint.z <= p2.z)){
            intersection_occured = true;
            i = Intersection(t, ray, this, Vector(-1,0,0), hitPoint);
            tmax = t;
        }
    }

    //side 5
    numerator = (p1.y - ray.o.y);
    denominator = ray.d.y;
    if(denominator != 0){
        float t = numerator/denominator;
        Point hitPoint = ray.o + t*ray.d;
        if((t >= tmin && t <= tmax) && (hitPoint.x >= p1.x && hitPoint.x <= p2.x) && (hitPoint.z >= p1.z && hitPoint.z <= p2.z)){
            intersection_occured = true;
            i = Intersection(t, ray, this, Vector(0,-1,0), hitPoint);
            tmax = t;
        }
    }

    //side 6
    numerator = (p2.y - ray.o.y);
    denominator = ray.d.y;
    if(denominator != 0){
        float t = numerator/denominator;
        Point hitPoint = ray.o + t*ray.d;
        if((t >= tmin && t <= tmax) && (hitPoint.x >= p1.x && hitPoint.x <= p2.x) && (hitPoint.z >= p1.z && hitPoint.z <= p2.z)){
            intersection_occured = true;
            i = Intersection(t, ray, this, Vector(0,1,0), hitPoint);
            tmax = t;
        }
    }

    //return min distance
    if(!intersection_occured){
        return Intersection::failure();
    }
    return i;
}

// Point AABox::getCenter() const{
//     Point p1 = min(this->corner1, this->corner2);
//     Point p2 = max(this->corner1, this->corner2);

//     return Point((p2.x - p1.x)/2, (p2.y - p1.y)/2, (p2.z - p1.z)/2);
// } 

}
