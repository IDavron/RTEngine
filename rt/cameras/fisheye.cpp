#include <rt/cameras/fisheye.h>

namespace rt {

Fisheye::Fisheye(const Point& center, const Vector& forward, const Vector& up, float fov)
{
    this->center = center;
    this->forward = forward.normalize();
    this->up = up.normalize();
    this->fov = fov;
}

Ray Fisheye::getPrimaryRay(float sscx, float sscy) const {
    Ray r;
    Vector x_basis = cross(forward,up).normalize();
    Vector y_basis = cross(x_basis,forward).normalize();
    float rad = sqrt(sscx*sscx + sscy*sscy);
    float phi = atan2(sscy,sscx);
    float theta = rad*fov/2;
    float cx = sin(theta)*cos(phi);
    float cy = sin(theta)*sin(phi);
    float cz = cos(theta);
    r.o = center;
    r.d = (cx*x_basis + cy*y_basis + cz*forward).normalize();
    return r;
}

}
