#include <rt/lights/arealight.h>


namespace rt {

LightHit AreaLight::getLightHit(const Point& p) const {
    Solid::Sample sample =  this->source->sample();
    LightHit lh;
    lh.direction = (sample.point - p).normalize();
    lh.distance = (sample.point - p).length();
    lh.normal = sample.normal;
    return lh;
}

RGBColor AreaLight::getIntensity(const LightHit& irr) const {
    RGBColor emission = this->source->material->getEmission(Point(0,0,0), irr.normal, Vector(1,1,1).normalize());
    float c = dot(irr.normal, irr.direction);
    if(c < 0){
        return RGBColor::rep(0);
    }
    return (emission*this->source->getArea()*pow(c, 1))/pow(irr.distance, 2);
}

AreaLight::AreaLight(Solid* source)
{
    this->source = source;
}

}