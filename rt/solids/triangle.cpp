#include <rt/solids/triangle.h>
#include <iostream>
namespace rt {

Triangle::Triangle(Point vertices[3], CoordMapper* texMapper, Material* material)
{
    this->vertices[0] = vertices[0];
    this->vertices[1] = vertices[1];
    this->vertices[2] = vertices[2];
    if(texMapper == nullptr){
        this->texMapper = new WorldMapper(Vector::rep(1));
    }else{
        this->texMapper = texMapper;
    }
    this->material = material;
}

Triangle::Triangle(const Point& v1, const Point& v2, const Point& v3, CoordMapper* texMapper, Material* material)
{
    this->vertices[0] = v1;
    this->vertices[1] = v2;
    this->vertices[2] = v3;
    if(texMapper == nullptr){
        this->texMapper = new WorldMapper(Vector::rep(1));
    }else{
        this->texMapper = texMapper;
    }
    this->material = material;
}

BBox Triangle::getBounds() const {
    BBox box = BBox(min(this->vertices[0], min(this->vertices[1], this->vertices[2])), max(this->vertices[0], max(this->vertices[1], this->vertices[2])));
    if(box.max.x - box.min.x == 0){
        box.max.x += 0.001f;
        box.min.x -= 0.001f;
    }
    if(box.max.y - box.min.y == 0){
        box.max.y += 0.001f;
        box.min.y -= 0.001f;
    }
    if(box.max.z - box.min.z == 0){
        box.max.z += 0.001f;
        box.min.z -= 0.001f;
    }
    return box;
}

Intersection Triangle::intersect(const Ray& ray, float tmin, float tmax) const {
    Point a = this->vertices[0];
    Point b = this->vertices[1];
    Point c = this->vertices[2];
    Point e = ray.o;
    Vector d = ray.d;

    float ea = a.x-b.x;
    float eb = a.y-b.y;
    float ec = a.z-b.z;
    float ed = a.x-c.x;
    float ee = a.y-c.y;
    float ef = a.z-c.z;
    float eg = d.x;
    float eh = d.y;
    float ei = d.z;

    float ej = a.x - e.x;
    float ek = a.y - e.y;
    float el = a.z - e.z;
    float M = ea*(ee*ei - eh*ef) + eb*(eg*ef - ed*ei) + ec*(ed*eh - ee*eg);
    float t = -1*(ef*(ea*ek - ej*eb) + ee*(ej*ec - ea*el) + ed*(eb*el - ek*ec))/M;

    if(t < tmin || t > tmax){
        return Intersection::failure();
    }
    float gamma = (ei*(ea*ek - ej*eb) + eh*(ej*ec - ea*el) + eg*(eb*el - ek*ec))/M;

    if(gamma < 0 || gamma > 1){
        return Intersection::failure();
    }
    float beta = (ej*(ee*ei - eh*ef) + ek*(eg*ef - ed*ei) + el*(ed*eh-ee*eg))/M;

    if(beta < 0 || beta > 1-gamma || t <= 0.001){
        return Intersection::failure();
    }
    return Intersection(t, ray, this, Vector(cross(b - a, c - a)).normalize(),  Point(1-gamma-beta,beta, gamma));
}

Solid::Sample Triangle::sample() const {
    Point a = this->vertices[0];
    Point b = this->vertices[1];
    Point c = this->vertices[2];
    Solid::Sample sample;
    float r1 = random();
    float r2 = random() * (1-r1);
    sample.point = lerpbar(a, b, c, r1, r2);
    sample.normal = Vector(cross(b - a, c - a)).normalize();
    return sample;
}

float Triangle::getArea() const {
    return abs(this->vertices[0].x*(this->vertices[1].y-this->vertices[2].y) + this->vertices[1].x*(this->vertices[2].y - this->vertices[1].y) + this->vertices[2].x*(this->vertices[0].y - this->vertices[1].y));
}

// Point Triangle::getCenter() const{
//     return Point((this->vertices[0].x + this->vertices[1].x + this->vertices[2].x)/3, (this->vertices[0].y + this->vertices[1].y + this->vertices[2].y)/3, (this->vertices[0].z + this->vertices[1].z + this->vertices[2].z)/3);
// }
}