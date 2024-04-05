#include <rt/integrators/raytrace.h>

namespace rt {

RGBColor RayTracingIntegrator::getRadiance(const Ray& ray) const {
    Intersection i = this->world->scene->intersect(ray);
    RGBColor color = RGBColor::rep(0);
    if(i){
        i.distance -= 0.000001;
        Point texPoint = i.local();
        if(i.solid->texMapper != nullptr){
            texPoint = i.solid->texMapper->getCoords(i); 
        }
        for(Light* light : this->world->light){
            Point hitPoint = i.hitPoint();
            LightHit lh = light->getLightHit(hitPoint);
            float angle = acos(dot(i.normal(), lh.direction)/(i.normal().length()*lh.direction.length()));
            if(angle > (pi/2) || angle < -(pi/2)){
                continue;
            }
            Ray sr = Ray(hitPoint, lh.direction);
            Intersection si = this->world->scene->intersect(sr);
            if(!si || lh.distance <= si.distance){
                RGBColor intensity = light->getIntensity(lh);
                RGBColor reflectance = i.solid->material->getReflectance(texPoint, i.normal(), -ray.d, lh.direction);
                color = color + intensity*reflectance;
            }
        }
        color = color + i.solid->material->getEmission(texPoint, i.normal(), -i.ray.d);
    }
    return color;
}
}