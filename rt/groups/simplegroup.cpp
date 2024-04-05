#include <rt/groups/simplegroup.h>

namespace rt {

BBox SimpleGroup::getBounds() const {
    BBox box = BBox::empty();
    for(auto const& p : this->primitives){
        box.extend(p->getBounds());
    }
    return box;
}

Intersection SimpleGroup::intersect(const Ray& ray, float tmin, float tmax) const {
    bool intersection_occured = false;
    Intersection min;
    for(auto const& p : this->primitives){
        Intersection i = p->intersect(ray, tmin, tmax);
        if(i) {
            intersection_occured = true;
            min = i;
            tmax = i.distance;
        }
    }
    if(!intersection_occured){
        return Intersection::failure();
    }
    return min;
}

void SimpleGroup::rebuildIndex() {
    //do nothing
}

void SimpleGroup::add(Primitive* p) {
    this->primitives.push_back(p);
}

void SimpleGroup::setMaterial(Material* m) {
    for(auto primitive : this->primitives){
        primitive->setMaterial(m);
    }
}

void SimpleGroup::setCoordMapper(CoordMapper* cm) {
    /* TODO */ NOT_IMPLEMENTED;
}

// Point SimpleGroup::getCenter() const{
//     return Point();
// }
}
