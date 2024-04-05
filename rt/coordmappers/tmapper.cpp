#include <rt/coordmappers/tmapper.h>

namespace rt {

TriangleMapper::TriangleMapper(Point ntv[3])
{
    this->ntv[0] = ntv[0];
    this->ntv[1] = ntv[1];
    this->ntv[2] = ntv[2];
}

TriangleMapper::TriangleMapper(const Point& tv0, const Point& tv1, const Point& tv2)
{
    this->ntv[0] = tv0;
    this->ntv[1] = tv1;
    this->ntv[2] = tv2;
}

Point TriangleMapper::getCoords(const Intersection& hit) const {
    Point hp = hit.local();
    Point p1 = hp.x * this->ntv[0];
    Point p2 = hp.y * this->ntv[1];
    Point p3 = hp.z * this->ntv[2];
    Point p = Point(p1.x + p2.x + p3.x, p1.y + p2.y + p3.y, p1.z + p2.z + p3.z);
    return p;
}

}