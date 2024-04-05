#include <rt/textures/perlin.h>
#include <iostream>
namespace rt {

// returns a value in range -1 to 1
static inline float noise(int x, int y, int z) {
    int n = x + y * 57 + z * 997;
    n = (n << 13) ^ n;
    return (1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
}

PerlinTexture::PerlinTexture(const RGBColor& white, const RGBColor& black)
{
    this->white = white;
    this->black = black;
} 
float regNoise(float noise){
    // return abs(noise);
    return (noise + 1) / 2;
}
rt::RGBColor PerlinTexture::getColor(const Point& coord) {

    RGBColor color = RGBColor::rep(0);
    for(auto octave : this->octaves){
        Point co = Point(coord.x, coord.y, coord.z) * octave.frequency;
        Point c;
        c.x = co.x < 0 ? int(co.x) - 1 : int(co.x);
        c.y = co.y < 0 ? int(co.y) - 1 : int(co.y);
        c.z = co.z < 0 ? int(co.z) - 1 : int(co.z);
        RGBColor diff = this->white - this->black;

        float n111 = regNoise(noise(c.x, c.y, c.z));
        float n211 = regNoise(noise(c.x+1, c.y, c.z));
        float n121 = regNoise(noise(c.x, c.y+1, c.z));
        float n221 = regNoise(noise(c.x+1, c.y+1, c.z));
        float n112 = regNoise(noise(c.x, c.y, c.z+1));
        float n212 = regNoise(noise(c.x+1, c.y, c.z+1));
        float n122 = regNoise(noise(c.x, c.y+1, c.z+1));
        float n222 = regNoise(noise(c.x+1, c.y+1, c.z+1));

        RGBColor C111 = this->black + (1-n111)*diff;
        RGBColor C211 = this->black + (1-n211)*diff;
        RGBColor C121 = this->black + (1-n121)*diff;
        RGBColor C221 = this->black + (1-n221)*diff;
        RGBColor C112 = this->black + (1-n112)*diff;
        RGBColor C212 = this->black + (1-n212)*diff;
        RGBColor C122 = this->black + (1-n122)*diff;
        RGBColor C222 = this->black + (1-n222)*diff;

        RGBColor C11 = C211 + (1 - (co.x - c.x))*(C111 - C211);
        RGBColor C21 = C221 + (1 - (co.x - c.x))*(C121 - C221);
        RGBColor C12 = C212 + (1 - (co.x - c.x))*(C112 - C212);
        RGBColor C22 = C222 + (1 - (co.x - c.x))*(C122 - C222);

        RGBColor C1 = C21 + (1 - (co.y - c.y))*(C11 - C21);
        RGBColor C2 = C22 + (1 - (co.y - c.y))*(C12 - C22);

        RGBColor C = C2 + (1 - (co.z - c.z))*(C1 - C2);

        color = color + (octave.amplitude * C);
    }
    return color;
}

rt::RGBColor PerlinTexture::getColorDX(const Point& coord) {
    CG_UNUSED(coord);

    /* TODO */ NOT_IMPLEMENTED;
}

rt::RGBColor PerlinTexture::getColorDY(const Point& coord) {
    CG_UNUSED(coord);

    /* TODO */ NOT_IMPLEMENTED;
}

void PerlinTexture::addOctave(float amplitude, float frequency) {
    this->octaves.push_back(Octave(amplitude, frequency));
}

}