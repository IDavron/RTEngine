#include <rt/integrators/castingdist.h>

namespace rt {

RayCastingDistIntegrator::RayCastingDistIntegrator(World* world, const RGBColor& nearColor, float nearDist, const RGBColor& farColor, float farDist)
    : Integrator(world)
{
    this->nearColor = nearColor;
    this->farColor = farColor;
    this->nearDist = nearDist;
    this->farDist = farDist;
}

RGBColor RayCastingDistIntegrator::getRadiance(const Ray& ray) const {
    Intersection i = this->world->scene->intersect(ray);
    if(i){
        float coef = (i.distance - this->nearDist) / (this->farDist - this->nearDist);
        coef = coef > 1 ? 1 : coef;
        coef = coef < 0 ? 0 : coef;
        float cosine = -dot(ray.d, i.normal())/(i.ray.d.length() * i.normal().length());
        RGBColor color = (1-coef)*this->nearColor + coef*this->farColor;
        return cosine*color;

    }
    return RGBColor(0,0,0);
}

}
