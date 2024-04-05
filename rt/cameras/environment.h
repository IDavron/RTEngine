#ifndef CG1RAYTRACER_CAMERAS_ENVIRONMENT_HEADER
#define CG1RAYTRACER_CAMERAS_ENVIRONMENT_HEADER

#include <rt/cameras/camera.h>
#include <core/vector.h>
#include <core/point.h>
#include <cmath>

namespace rt {

class Environment : public Camera {
public:
    Environment(
        const Point& center,
        const Vector& forward,
        const Vector& up,
        float fovx,
        float fovy
        );

    virtual Ray getPrimaryRay(float x, float y) const;
    
private:
    Point center;
    Vector forward;
    Vector up;
    float fovx;
    float fovy;
};

}


#endif