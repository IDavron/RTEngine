#include <rt/cameras/environment.h>

namespace rt {

Environment::Environment(const Point& center, const Vector& forward, const Vector& up, float fovx, float fovy)
{
    this->center = center;
    this->forward = forward.normalize();
    this->up = up.normalize();
    this->fovx = fovx;
    this->fovy = fovy;
}

Ray Environment::getPrimaryRay(float sscx, float sscy) const {
    Ray r;
    Vector x_basis = cross(forward,up).normalize();
    Vector y_basis = cross(x_basis,forward).normalize();
    float phi = sscx*this->fovx/2;
    float theta = sscy*fovy/2;
    float cx = cos(theta)*cos(phi);
    float cy = cos(theta)*sin(phi);
    float cz = sin(theta);
    r.o = center;
    r.d = (cx*x_basis + cy*y_basis + cz*forward).normalize();
    return r;
}

}
