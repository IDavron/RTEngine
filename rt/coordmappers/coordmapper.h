#ifndef CG1RAYTRACER_COORDMAPPERS_COORDMAPPER_HEADER
#define CG1RAYTRACER_COORDMAPPERS_COORDMAPPER_HEADER

#include <core/point.h>
#include <core/vector.h>
#include <rt/intersection.h>
#include <core/matrix.h>

namespace rt {

class Intersection;

class CoordMapper {
public:
    virtual Point getCoords(const Intersection& hit) const = 0;
};

}

#endif