#include <rt/materials/fuzzyconductor.h>

namespace rt {

FuzzyConductorMaterial::FuzzyConductorMaterial(float eta, float kappa, float fuzzyangle)
{
    this->eta = eta;
    this->kappa = kappa;
    this->fuzzyangle = fuzzyangle;
}

RGBColor FuzzyConductorMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    CG_UNUSED(texPoint);
    CG_UNUSED(normal);
    CG_UNUSED(outDir);
    CG_UNUSED(inDir);   
    
    return RGBColor::rep(0); 
}

RGBColor FuzzyConductorMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    CG_UNUSED(texPoint);
    CG_UNUSED(normal);
    CG_UNUSED(outDir);

    return RGBColor::rep(0);
}

Material::SampleReflectance FuzzyConductorMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    CG_UNUSED(texPoint);
    CG_UNUSED(normal);
    CG_UNUSED(outDir);

    float c = dot(normal, outDir)/(normal.length()*outDir.length());
    float sum = pow(this->eta,2) + pow(this->kappa,2);
    float c_sqr = pow(c,2);

    float r_par = (sum*c_sqr - 2*this->eta*c + 1)/(sum*c_sqr + 2*this->eta*c + 1);
    float r_per = (sum - 2*this->eta*c + c_sqr)/(sum + 2*this->eta*c + c_sqr);
    float F = (r_par + r_per)/2;

    Vector r = -outDir + 2*dot(outDir,normal)*normal;
    Disc disc(Point::rep(0) + r, -r, tan(this->fuzzyangle), nullptr, nullptr);
    Disc::Sample s = disc.sample();

    SampleReflectance sr;
    sr.direction = (s.point - Point::rep(0)).normalize();
    sr.reflectance = RGBColor::rep(F);
    return sr;
}

Material::Sampling FuzzyConductorMaterial::useSampling() const {
    return SAMPLING_ALL;
}

}
