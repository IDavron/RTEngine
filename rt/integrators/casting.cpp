#include <rt/integrators/casting.h>

namespace rt {

RGBColor RayCastingIntegrator::getRadiance(const Ray& ray) const {
    Intersection i = this->world->scene->intersect(ray);
    if(i){
        float coef = -dot(ray.d, i.normal());
        return RGBColor(coef,coef,coef);
    }
    return RGBColor(0,0,0);
}

}
