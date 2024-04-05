#ifndef CG1RAYTRACER_CAMERAS_DOFPERSPECTIVE_HEADER
#define CG1RAYTRACER_CAMERAS_DOFPERSPECTIVE_HEADER

#include <rt/cameras/camera.h>
#include <rt/ray.h>
#include <core/random.h>
namespace rt {

class Point;
class Vector;

class DOFPerspectiveCamera : public Camera {
public:
    DOFPerspectiveCamera(
        const Point& center,
        const Vector& forward,
        const Vector& up,
        float verticalOpeningAngle,
        float horizonalOpeningAngle,
        float focalDistance,
        float apertureRadius
    );

    virtual Ray getPrimaryRay(float x, float y) const;

private:
    Point center;
    Vector forward;
    Vector up;
    float verticalOpeningAngle;
    float horizontalOpeningAngle;
    float focalDistance;
    float apertureRadius;
};

}

#endif