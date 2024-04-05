#include <rt/solids/quad.h>

namespace rt {

Quad::Quad(const Point& origin, const Vector& span1, const Vector& span2, CoordMapper* texMapper, Material* material)
{
    this->v1 = origin;
    this->span1 = span1;
    this->span2 = span2;
    if(texMapper == nullptr){
        this->texMapper = new WorldMapper(Vector::rep(1));
    }else{
        this->texMapper = texMapper;
    }
    this->material = material;
}

BBox Quad::getBounds() const {
    return BBox(min(this->v1, min(this->v1+this->span1, min(this->v1+this->span2, this->v1+this->span1+this->span2))), max(this->v1, max(this->v1+this->span1, max(this->v1+this->span2, this->v1+this->span1+this->span2))));
}

Intersection Quad::intersect(const Ray& ray, float tmin, float tmax) const {

    //half 1
    Point a = this->v1;
    Point b = this->v1+this->span1;
    Point c = this->v1+this->span2;
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
    float beta = (ej*(ee*ei - eh*ef) + ek*(eg*ef - ed*ei) + el*(ed*eh-ee*eg))/M;

    if(gamma >= 0 && gamma <= 1 && beta >= 0 && beta <= 1-gamma){
        return Intersection(t, ray, this, Vector(cross(b - a, c - a)).normalize(), Point(beta, gamma, 0));
    }

    //half 2
    b = this->v1+this->span1;
    a = this->v1+this->span1+this->span2;
    c = this->v1+this->span2;
    e = ray.o;
    d = ray.d;

    ea = a.x-b.x;
    eb = a.y-b.y;
    ec = a.z-b.z;
    ed = a.x-c.x;
    ee = a.y-c.y;
    ef = a.z-c.z;
    eg = d.x;
    eh = d.y;
    ei = d.z;

    ej = a.x - e.x;
    ek = a.y - e.y;
    el = a.z - e.z;
    M = ea*(ee*ei - eh*ef) + eb*(eg*ef - ed*ei) + ec*(ed*eh - ee*eg);
    t = -1*(ef*(ea*ek - ej*eb) + ee*(ej*ec - ea*el) + ed*(eb*el - ek*ec))/M;

    if(t < tmin || t > tmax){
        return Intersection::failure();
    }
    gamma = (ei*(ea*ek - ej*eb) + eh*(ej*ec - ea*el) + eg*(eb*el - ek*ec))/M;
    beta = (ej*(ee*ei - eh*ef) + ek*(eg*ef - ed*ei) + el*(ed*eh-ee*eg))/M;
    if(gamma >= 0 && gamma <= 1 && beta >= 0 && beta <= 1-gamma){
        return Intersection(t, ray, this, Vector(cross(a - b, c - b)).normalize(), Point((1-gamma), (1-beta), 0));
    }
    return Intersection::failure();
}

Solid::Sample Quad::sample() const {
    Point a = this->v1;
    Point b = this->v1 + this->span1;
    Point c = this->v1 + this->span2;
    Solid::Sample sample;
    float r1 = random();
    float r2 = random();
    sample.point = this->v1 + this->span1*r1 + this->span2*r2;
    sample.normal = Vector(cross(a - b, c - b)).normalize();
    return sample;
}

float Quad::getArea() const {
    return this->span1.length()*this->span2.length();
}

// Point Quad::getCenter() const{
//     return Point(this->v1.x + this->span1.x / 2 + this->span2.x / 2, this->v1.y + this->span1.y / 2 + this->span2.y / 2, this->v1.z + this->span1.z / 2 + this->span2.z / 2);
// }

}
