#include <rt/lights/spotlight.h>
#include <iostream>
namespace rt {

SpotLight::SpotLight(const Point& position, const Vector& direction, float angle, float exp, const RGBColor& intensity)
{
    this->position = position;
    this->direction = direction;
    this->angle = angle;
    this->exp = exp;
    this->intensity = intensity;
}

RGBColor SpotLight::getIntensity(const LightHit& irr) const {
    float c = dot(-irr.direction, this->direction)/(irr.direction.length()*this->direction.length());
    float angle = acos(c);
    if(angle <= this->angle){
        return this->intensity * pow(c, this->exp) / pow(irr.distance,2);
    }
    return RGBColor(0,0,0);
}
}
