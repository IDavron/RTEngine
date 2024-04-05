#include <rt/coordmappers/world.h>

namespace rt {

Point WorldMapper::getCoords(const Intersection& hit) const {
    return Point(hit.local().x * this->scale.x, hit.local().y * this->scale.y, hit.local().z * this->scale.z);
}

WorldMapper::WorldMapper()
{
    this->scale = Vector(1,1,1);
}

WorldMapper::WorldMapper(const Vector& scale)
{
    this->scale = scale;
}

}