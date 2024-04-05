#include <rt/materials/lambertian.h>

namespace rt {

LambertianMaterial::LambertianMaterial(Texture* emission, Texture* diffuse)
{
    this->emission = emission;
    this->diffuse = diffuse;
}

RGBColor LambertianMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    CG_UNUSED(texPoint);
    CG_UNUSED(normal);
    CG_UNUSED(outDir);
    CG_UNUSED(inDir);
    float c = dot(normal, inDir)/(normal.length()*inDir.length());
    return (1/M_PI)*c*this->diffuse->getColor(texPoint);
}

RGBColor LambertianMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    CG_UNUSED(normal);
    CG_UNUSED(outDir);
    return this->emission->getColor(texPoint);
}

Material::SampleReflectance LambertianMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    CG_UNUSED(texPoint);
    CG_UNUSED(normal);
    CG_UNUSED(outDir);
	UNREACHABLE;
}

Material::Sampling LambertianMaterial::useSampling() const {
	return SAMPLING_NOT_NEEDED;
}

}