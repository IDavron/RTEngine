#include <rt/integrators/recraytrace.h>

namespace rt {

RGBColor RecursiveRayTracingIntegrator::getRadiance(const Ray& ray) const {
    return getRadianceRec(ray, 0);
}

RGBColor RecursiveRayTracingIntegrator::getRadianceRec(const Ray& ray, uint depth) const{
    if(depth > 128){
        return RGBColor(0,0,0);
    }
    Intersection i = this->world->scene->intersect(ray);
    RGBColor color = RGBColor::rep(0);
    RGBColor lights_color = RGBColor::rep(0);

    if(i){
        i.distance -= 0.0005;
        Point texPoint = i.local();
        Point hitPoint = i.hitPoint();
        if(i.solid->texMapper != nullptr){
            texPoint = i.solid->texMapper->getCoords(i); 
        }

        if(i.solid->material->useSampling() == Material::SAMPLING_NOT_NEEDED){
            for(Light* light : this->world->light){
                LightHit lh = light->getLightHit(hitPoint);
                float angle = acos(dot(i.normal(), lh.direction)/(i.normal().length()*lh.direction.length()));
                if(angle > (pi/2) || angle < -(pi/2)){
                    continue;
                }
                Ray sr = Ray(hitPoint, lh.direction);
                Intersection si = this->world->scene->intersect(sr);
                if(!si || lh.distance <= si.distance+0.000001){
                    RGBColor intensity = light->getIntensity(lh);
                    RGBColor reflectance = i.solid->material->getReflectance(texPoint, i.normal(), -ray.d, lh.direction);
                    lights_color = lights_color + intensity*reflectance;
                }
            }
            color = color + lights_color;
        }
        if(i.solid->material->useSampling() == Material::SAMPLING_ALL){
            Material::SampleReflectance sr = i.solid->material->getSampleReflectance(texPoint, i.normal(), -ray.d);
            Ray r = Ray(hitPoint, sr.direction);
            RGBColor sc = getRadianceRec(r, depth + 1);
            color = color + sc*sr.reflectance;
        }

        color = color + i.solid->material->getEmission(texPoint, i.normal(), -i.ray.d);
    }
    return color;
}

}