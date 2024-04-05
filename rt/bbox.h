#ifndef CG1RAYTRACER_BBOX_HEADER
#define CG1RAYTRACER_BBOX_HEADER

#include <utility>
#include <core/point.h>
#include <core/vector.h>
#include <vector>
#include <rt/intersection.h>

namespace rt {

class Ray;
class Primitive;

class BBox {
public:
    Point min, max;

    BBox() {}
    BBox(const Point& min, const Point& max)
    {
        this->min = min;
        this->max = max;
    }

    static BBox empty();
    static BBox full();

    void extend(const Point& point);
    void extend(const BBox& bbox);

    Vector diagonal() const {
        /* TODO */ NOT_IMPLEMENTED;
    }

    float area() const {
        return 2*((max.x-min.x)*(max.y-min.y) + (max.x - min.x)*(max.z-min.z) + (max.y-min.y)*(max.z-min.z));
    }

    std::pair<float, float> intersect(const Ray& ray) const;

    bool isUnbound() const;

    bool overlaps(const BBox& bbox);
    Point getCenter() const;
};

}

#endif