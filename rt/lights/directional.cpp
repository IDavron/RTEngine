#include <rt/lights/directional.h>
#include <core/scalar.h>
#include <core/vector.h>

namespace rt {

DirectionalLight::DirectionalLight(const Vector& direction, const RGBColor& color)
{
    this->direction = direction;
    this->intensity = color;
}

LightHit DirectionalLight::getLightHit(const Point& p) const {
    LightHit lh;
    lh.direction = -this->direction;
    lh.distance = FLT_MAX;
    lh.normal = lh.direction.normalize();
    return lh;
}

RGBColor DirectionalLight::getIntensity(const LightHit& irr) const {
    return this->intensity;
}

}
