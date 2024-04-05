#include <rt/cameras/dofperspective.h>

namespace rt {

DOFPerspectiveCamera::DOFPerspectiveCamera(const Point& center, const Vector& forward, const Vector& up, float verticalOpeningAngle, float horizontalOpeningAngle, float focalDistance, float apertureRadius)
{
    this->center = center;
    this->forward = forward.normalize();
    this->up = up.normalize();
    this->verticalOpeningAngle = verticalOpeningAngle;
    this->horizontalOpeningAngle = horizontalOpeningAngle;
    this->focalDistance = focalDistance;
    this->apertureRadius = apertureRadius;
}

Ray DOFPerspectiveCamera::getPrimaryRay(float x, float y) const {
    Ray r;
    Vector x_basis = cross(forward,up).normalize();
    Vector y_basis = cross(x_basis, forward).normalize();
    float horizontalAngle = x*this->horizontalOpeningAngle/2;
    float verticalAngle = y*this->verticalOpeningAngle/2;
    Vector v = (forward + tan(verticalAngle)*y_basis + tan(horizontalAngle)*x_basis).normalize();
    Point C = this->center + this->focalDistance*v;
    float r1 = (random()*this->apertureRadius)*2 - this->apertureRadius;
    float r2 = random()*sqrt(pow(this->apertureRadius,2) - pow(r1,2));
    if(random() > 0.5){
        r2 = -r2;
    }
    r.o = this->center + r1*x_basis + r2*y_basis;
    r.d = (C-r.o).normalize();
    return r;
}

}