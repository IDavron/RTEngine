#include <rt/cameras/perspective.h>

namespace rt {

PerspectiveCamera::PerspectiveCamera(const Point& center, const Vector& forward, const Vector& up, float verticalOpeningAngle, float horizontalOpeningAngle)
{
    this->center = center;
    this->forward = forward.normalize();
    this->up = up.normalize();
    this->verticalOpeningAngle = verticalOpeningAngle;
    this->horizontalOpeningAngle = horizontalOpeningAngle;
}

Ray PerspectiveCamera::getPrimaryRay(float x, float y) const {
    Ray r;
    Vector x_basis = cross(forward,up).normalize();
    Vector y_basis = cross(x_basis, forward).normalize();
    float horizontalAngle = x*this->horizontalOpeningAngle/2;
    float verticalAngle = y*this->verticalOpeningAngle/2;
    Vector v = (forward + tan(verticalAngle)*y_basis + tan(horizontalAngle)*x_basis).normalize();
    r.o = this->center;
    r.d = v;
    return r;
}

}
