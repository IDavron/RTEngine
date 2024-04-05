#include <rt/materials/dielectric.h>
#include <iostream>
namespace rt {

DielectricMaterial::DielectricMaterial(float eta)
{
    this->eta = eta;
}

RGBColor DielectricMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    CG_UNUSED(texPoint);
    CG_UNUSED(normal);
    CG_UNUSED(outDir);
    CG_UNUSED(inDir);
    return RGBColor::rep(0);
}

RGBColor DielectricMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    CG_UNUSED(texPoint);
    CG_UNUSED(normal);
    CG_UNUSED(outDir);
    return RGBColor::rep(0);
}

Material::SampleReflectance DielectricMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    CG_UNUSED(texPoint);
    CG_UNUSED(normal);
    CG_UNUSED(outDir);

    float e = 1/this->eta;
    Vector n = normal;
    float c = dot(outDir, n);
    if(c < 0){
        n = -normal;
        e = this->eta;
    }
    float cosThetaI = dot(outDir, n);
    float sin2ThetaI = std::max(0.f, 1.f - cosThetaI * cosThetaI);
    float sin2ThetaT = e * e * sin2ThetaI;
    if (sin2ThetaT >= 1) return SampleReflectance(Vector(1,0,0), RGBColor::rep(0));
    float cosThetaT = sqrt(1 - sin2ThetaT);

    float f_par = (cosThetaI - e*cosThetaT)/(cosThetaI + e*cosThetaT);
    float f_per = (e*cosThetaI - cosThetaT)/(e*cosThetaI + cosThetaT);
    float F = (pow(f_par,2) + pow(f_per,2))/2;

    Vector T;
    if(random() < 0.5){
        T = -outDir + 2*dot(outDir,n)*n;
    }else{
        T = e*(-outDir) + (e * cosThetaI - cosThetaT)*n;
        F = 1-F;
    }
    return SampleReflectance(T.normalize(), RGBColor::rep(F*2));
}

Material::Sampling DielectricMaterial::useSampling() const {
    return SAMPLING_ALL;
}

}