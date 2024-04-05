#include <core/color.h>
#include <core/scalar.h>
#include <core/homogeneouscoord.h>

namespace rt {

RGBColor::RGBColor(const HomogeneousCoord& coord)
{
    this->r = coord.x;
    this->g = coord.y;
    this->b = coord.z;
}

RGBColor RGBColor::operator + (const RGBColor& c) const {
    RGBColor rgb_c;
    rgb_c.r = this->r + c.r;
    rgb_c.g = this->g + c.g;
    rgb_c.b = this->b + c.b;
    return rgb_c;
}

RGBColor RGBColor::operator - (const RGBColor& c) const {
    RGBColor rgb_c;
    rgb_c.r = this->r - c.r;
    rgb_c.g = this->g - c.g;
    rgb_c.b = this->b - c.b;
    return rgb_c;
}

RGBColor RGBColor::operator * (const RGBColor& c) const {
    RGBColor rgb_c;
    rgb_c.r = this->r * c.r;
    rgb_c.g = this->g * c.g;
    rgb_c.b = this->b * c.b;
    return rgb_c;
}

bool RGBColor::operator == (const RGBColor& c) const {
    return (this->r == c.r && this->g == c.g && this->b == c.b);
}

bool RGBColor::operator != (const RGBColor& b) const {
    return (this->r != b.r || this->g != b.g || this->b != b.b);
}

RGBColor RGBColor::clamp() const {
    RGBColor rgb_c;
    float m = max(this->r, max(this->g, this->b));
    rgb_c.r = this->r > 0 ? this->r/m : 0;
    rgb_c.g = this->r > 0 ? this->g/m : 0;
    rgb_c.b = this->r > 0 ? this->b/m : 0;
    return rgb_c;
}

RGBColor RGBColor::gamma(float gam) const {
    /* TODO */ NOT_IMPLEMENTED;
}

float RGBColor::luminance() const {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor operator * (float scalar, const RGBColor& c) {
    RGBColor rgb_c;
    rgb_c.r = c.r * scalar;
    rgb_c.g = c.g * scalar;
    rgb_c.b = c.b * scalar;
    return rgb_c;
}

RGBColor operator * (const RGBColor& c, float scalar) {
    return scalar*c;
}

RGBColor operator / (const RGBColor& c, float scalar) {
    RGBColor rgb_c;
    rgb_c.r = c.r / scalar;
    rgb_c.g = c.g / scalar;
    rgb_c.b = c.b / scalar;
    return rgb_c;
}

}
