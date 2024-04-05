#include <rt/lights/pointlight.h>

#include <core/vector.h>

namespace rt {

PointLight::PointLight(const Point& position, const RGBColor& intensity)
{
    this->position = position;
    this->intensity = intensity;
}

LightHit PointLight::getLightHit(const Point& p) const {
    LightHit lh;
    lh.direction = (this->position - p).normalize();
    lh.distance = (this->position - p).length();
    lh.normal = -lh.direction;
    return lh;
}

RGBColor PointLight::getIntensity(const LightHit& irr) const {
    return this->intensity/pow(irr.distance, 2);
}

}
