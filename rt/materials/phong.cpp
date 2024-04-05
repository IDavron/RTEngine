#include <rt/materials/phong.h>

namespace rt {

PhongMaterial::PhongMaterial(Texture* specular, float exponent)
{
    this->specular = specular;
    this->exponent = exponent;
}

RGBColor PhongMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    CG_UNUSED(texPoint);
    CG_UNUSED(outDir);

    Vector d = -inDir;
    float dot_product = dot(d, normal);
    Vector r = d - (2*dot_product*normal);
    float c_2 = dot(r, outDir)/(r.length()*outDir.length());
    if(c_2 < 0){
        return RGBColor::rep(0);
    }
    float norm_factor = (this->exponent + 2)/(2*M_PI);
    float c = dot(normal, inDir)/(normal.length()*inDir.length());
    return norm_factor * pow(c_2, this->exponent) * c * this->specular->getColor(texPoint);
}

RGBColor PhongMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    CG_UNUSED(texPoint);
    CG_UNUSED(normal);
    CG_UNUSED(outDir);

    return RGBColor::rep(0);
}

Material::SampleReflectance PhongMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    CG_UNUSED(texPoint);
    CG_UNUSED(normal);
    CG_UNUSED(outDir);

	UNREACHABLE;
}

Material::Sampling PhongMaterial::useSampling() const {
	return SAMPLING_NOT_NEEDED;
}

}