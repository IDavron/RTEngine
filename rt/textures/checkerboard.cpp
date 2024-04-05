#include <rt/textures/checkerboard.h>

namespace rt {

CheckerboardTexture::CheckerboardTexture(const RGBColor& white, const RGBColor& black)
{
    this->white = white;
    this->black = black;
}

RGBColor CheckerboardTexture::getColor(const Point& coord) {
    int c = floor(coord.x/0.5) + floor(coord.y/0.5) + floor(coord.z/0.5);
    int parity = abs(c) % 2;
    if(parity == 1){
        return this->black;
    }
    return this->white;
}

RGBColor CheckerboardTexture::getColorDX(const Point& coord) {
    CG_UNUSED(coord);
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor CheckerboardTexture::getColorDY(const Point& coord) {
    CG_UNUSED(coord);
    /* TODO */ NOT_IMPLEMENTED;
}

}