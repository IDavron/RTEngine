#include "interpolate.h"

namespace rt {

template <typename T>
T lerp(const T& px0, const T& px1, float xPoint) {
    T result = px0 + xPoint * (px1 - px0);
    return result;
}

template <typename T>
T lerpbar(const T& a, const T& b, const T& c, float aWeight, float bWeight) {
    T result = aWeight*a + bWeight*b + (1-aWeight-bWeight)*c;
    return result;
}

template <typename T>
T lerp2d(const T& px0y0, const T& px1y0, const T& px0y1, const T& px1y1, float xWeight, float yWeight) {
    T Y0 = (1-xWeight)*px0y0 + xWeight*px1y0;
    T Y1 = (1-xWeight)*px0y1 + xWeight*px1y1;
    T result = (1-yWeight)*Y0 + yWeight*Y1;
    return result;
}

template <typename T>
T lerp3d(const T& px0y0z0, const T& px1y0z0, const T& px0y1z0, const T& px1y1z0,
    const T& px0y0z1, const T& px1y0z1, const T& px0y1z1, const T& px1y1z1,
    float xPoint, float yPoint, float zPoint)
{
    T Y0 = (1-xPoint)*px0y0z0 + xPoint*px1y0z0;
    T Y1 = (1-xPoint)*px0y1z0 + xPoint*px1y1z0;
    T Z0 = (1-yPoint)*Y0 + yPoint*Y1;

    T Y3 = (1-xPoint)*px0y0z1 + xPoint*px1y0z1;
    T Y4 = (1-xPoint)*px0y1z1 + xPoint*px1y1z1;
    T Z1 = (1-yPoint)*Y3 + yPoint*Y4;

    T result = (1-zPoint)*Z0 + zPoint*Z1;
    return result;
}

}