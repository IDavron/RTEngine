#include <rt/cameras/orthographic.h>

namespace rt {

OrthographicCamera::OrthographicCamera(const Point& center, const Vector& forward, const Vector& up, float scaleX, float scaleY)
{
    this->center = center;
    this->forward = forward.normalize();
    this->up = up.normalize();
    this->scaleX = scaleX;
    this->scaleY = scaleY;
}

Ray OrthographicCamera::getPrimaryRay(float x, float y) const {
    Ray r;
    Vector x_basis = cross(forward, up).normalize();
    Vector y_basis = cross(x_basis, forward).normalize();
    float x_multiplier = x * scaleX / 2;
    float y_multiplier = y * scaleY / 2;
    r.o = Point(this->center + x_multiplier*x_basis + y_multiplier*y_basis);
    r.d = forward;
    return r;
}

}
