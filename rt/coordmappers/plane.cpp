#include <rt/coordmappers/plane.h>

namespace rt {

PlaneCoordMapper::PlaneCoordMapper(const Vector& e1, const Vector& e2) {
    this->e1 = e1;
    this->e2 = e2;
}

Point PlaneCoordMapper::getCoords(const Intersection& hit) const {
    // Vector n = cross(this->e2, this->e1).normalize();
    // Vector v = hit.local() - Point::rep(0);
    // float dist = dot(v, n);
    // Point proj = hit.local() - dist*n;
    // Vector hv = proj - Point::rep(0);
    // float x = dot(this->e1.normalize(), hv);
    // float y = dot(this->e2.normalize(), hv);
    // return Point(x/this->e1.length(),y/this->e2.length(),0);

    Vector n = cross(this->e1, this->e2);

    Matrix m = Matrix::system(this->e1, this->e2, n);
    m = m.invert();

    HomogeneousCoord p = HomogeneousCoord(hit.local());

    p = m*p;
    return Point(p);
}

}
