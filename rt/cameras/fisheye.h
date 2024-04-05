#ifndef CG1RAYTRACER_CAMERAS_FISHEYE_HEADER
#define CG1RAYTRACER_CAMERAS_FISHEYE_HEADER

#include <rt/cameras/camera.h>
#include <core/vector.h>
#include <core/point.h>
#include <cmath>

namespace rt {

class Fisheye : public Camera {
public:
    Fisheye(
        const Point& center,
        const Vector& forward,
        const Vector& up,
        float fov
        );

    virtual Ray getPrimaryRay(float x, float y) const;
    
private:
    Point center;
    Vector forward;
    Vector up;
    float fov;
};

}


#endif