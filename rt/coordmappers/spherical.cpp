#include <rt/coordmappers/spherical.h>

namespace rt {

SphericalCoordMapper::SphericalCoordMapper(const Point& origin, const Vector& zenith, const Vector& azimuthRef)
{
    this->origin = origin;
    this->zenith = zenith;
    this->azimuthRef = azimuthRef;
}

Point SphericalCoordMapper::getCoords(const Intersection& hit) const {
    Vector y = this->zenith;
    Vector e1 = cross(y, this->azimuthRef);
    Vector x = cross(y, -e1).normalize() * this->azimuthRef.length();

    Vector hv = hit.local() - this->origin;

    float dist_x = dot(hv, y.normalize());
    Point proj_x = hit.local() - (dist_x * y.normalize());
    Vector v_x = proj_x - this->origin;
    float angle_x = acos(dot(v_x, x)/(v_x.length() * x.length()));

    float direction = dot(cross(v_x, x), y);
    if(direction < 0){
        angle_x = 2*M_PI - angle_x;
    }

    float angle_y = acos(dot(hv, y)/(hv.length()*y.length()));

    return Point(angle_x/M_PI, angle_y*y.length(), 0);
}
}