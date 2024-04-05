#include <rt/solids/striangle.h>
#include <rt/intersection.h>

namespace rt {

SmoothTriangle::SmoothTriangle(Point vertices[3], Vector normals[3], CoordMapper* texMapper, Material* material)
{
    this->vertices[0] = vertices[0];
    this->vertices[1] = vertices[1];
    this->vertices[2] = vertices[2];

    this->normals[0] = normals[0];
    this->normals[1] = normals[1];
    this->normals[2] = normals[2];

    if(texMapper == nullptr){
        this->texMapper = new WorldMapper(Vector::rep(1));
    }else{
        this->texMapper = texMapper;
    }
    this->material = material;
}

SmoothTriangle::SmoothTriangle(const Point& v1, const Point& v2, const Point& v3, const Vector& n1, const Vector& n2, const Vector& n3, CoordMapper* texMapper, Material* material)
{
    this->vertices[0] = v1;
    this->vertices[1] = v2;
    this->vertices[2] = v3;

    this->normals[0] = n1;
    this->normals[1] = n2;
    this->normals[2] = n3;

    if(texMapper == nullptr){
        this->texMapper = new WorldMapper(Vector::rep(1));
    }else{
        this->texMapper = texMapper;
    }
    this->material = material;
}

Intersection SmoothTriangle::intersect(const Ray& ray, float tmin, float tmax) const {
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

    if(beta < 0 || beta > 1-gamma){
        return Intersection::failure();
    }

    Vector normal = lerpbar(this->normals[0], this->normals[1], this->normals[2], 1-gamma-beta,beta);
    return Intersection(t, ray, this, normal.normalize(),  Point(1-gamma-beta,beta, gamma));
}

}