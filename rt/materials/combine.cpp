#include <rt/materials/combine.h>

namespace rt {

CombineMaterial::CombineMaterial()
{
    /* TODO */
}

void CombineMaterial::add(Material* m, float w) {
    this->materials.push_back(std::pair<Material*, float>(m,w));
}

RGBColor CombineMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    RGBColor c = RGBColor::rep(0);
    for(auto material : this->materials){
        c = c + (material.first->getReflectance(texPoint, normal, outDir, inDir)*material.second);
    }
    return c;
}

RGBColor CombineMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    RGBColor c = RGBColor::rep(0);
    for(auto material : this->materials){
        c = c + (material.first->getEmission(texPoint, normal, outDir)*material.second);
    }
    return c;
}

Material::SampleReflectance CombineMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */ NOT_IMPLEMENTED;
}

Material::Sampling CombineMaterial::useSampling() const {
    return SAMPLING_NOT_NEEDED;
}

}