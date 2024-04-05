#include <rt/materials/conductor.h>
#include <core/scalar.h>

namespace rt {

ConductorMaterial::ConductorMaterial(float eta, float kappa)
{
    this->eta = eta;
    this->kappa = kappa;
}

RGBColor ConductorMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    CG_UNUSED(texPoint);
    CG_UNUSED(normal);
    CG_UNUSED(outDir);
    CG_UNUSED(inDir);
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor ConductorMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    CG_UNUSED(texPoint);
    CG_UNUSED(normal);
    CG_UNUSED(outDir);

    return RGBColor::rep(0);
}

Material::SampleReflectance ConductorMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    CG_UNUSED(texPoint);
    CG_UNUSED(normal);
    CG_UNUSED(outDir);

    float c = dot(normal,outDir)/(normal.length()*outDir.length());
    float sum = pow(this->eta,2) + pow(this->kappa,2);
    float c_sqr = pow(c,2);

    float r_par = (sum*c_sqr - 2*this->eta*c + 1)/(sum*c_sqr + 2*this->eta*c + 1);
    float r_per = (sum - 2*this->eta*c + c_sqr)/(sum + 2*this->eta*c + c_sqr);
    float F = (r_par + r_per)/2;

    Vector d = -outDir;
    float dot_product = dot(d, normal);
    Vector r = d - (2*dot_product*normal);

    SampleReflectance sr;
    sr.direction = r.normalize();
    sr.reflectance = RGBColor::rep(F);
    return sr;
}

Material::Sampling ConductorMaterial::useSampling() const {
	return SAMPLING_ALL;
}

}