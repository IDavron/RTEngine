#include <rt/materials/dummy.h>
#include <core/assert.h>

namespace rt {

DummyMaterial::DummyMaterial() {

}

RGBColor DummyMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    CG_UNUSED(texPoint);
    CG_UNUSED(outDir);
    float c = dot(normal, inDir)/(normal.length()*inDir.length());
    return c*RGBColor::rep(1);
}

RGBColor DummyMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return RGBColor::rep(0);
}

Material::SampleReflectance DummyMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    CG_UNUSED(texPoint);
    CG_UNUSED(normal);
    CG_UNUSED(outDir);
    /* TODO */ NOT_IMPLEMENTED;
}


}