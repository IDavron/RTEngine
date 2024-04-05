#include <rt/textures/constant.h>

namespace rt {

ConstantTexture::ConstantTexture()
{
    /* TODO */
}

ConstantTexture::ConstantTexture(const RGBColor& color)
{
    this->color = color;
}

RGBColor ConstantTexture::getColor(const Point& coord) {
    return this->color;
}

RGBColor ConstantTexture::getColorDX(const Point& coord) {
    return RGBColor(0,0,0);
}

RGBColor ConstantTexture::getColorDY(const Point& coord) {
    return RGBColor(0,0,0);
}

}