#include <rt/coordmappers/cylindrical.h>

namespace rt {

CylindricalCoordMapper::CylindricalCoordMapper(const Point& origin, const Vector& longitudinalAxis, const Vector& polarAxis)
{
    this->origin = origin;
    this->longitudinalAxis = longitudinalAxis;
    this->polarAxis = polarAxis;
}

Point CylindricalCoordMapper::getCoords(const Intersection& hit) const {
    float radius = this->polarAxis.length();
    Vector e1 = cross(this->longitudinalAxis, this->polarAxis);
    Vector e2 = cross(this->longitudinalAxis, -e1).normalize() * radius;

    Vector hv = hit.local() - this->origin;
    float proj_vector = (dot(hv, this->longitudinalAxis)/this->longitudinalAxis.length());

    float dist = dot(hv, this->longitudinalAxis.normalize());
    Point proj_point = hit.local() - (dist*this->longitudinalAxis.normalize());

    Vector pv = proj_point - this->origin;

    float angle = acos(dot(pv, e2)/(pv.length()*e2.length()));

    float direction = dot(cross(pv, e2), this->longitudinalAxis);
    if(direction < 0){
        angle = 2*M_PI - angle;
    }
    float x = angle/M_PI;
    float y = proj_vector/this->longitudinalAxis.length();

    return Point(x, y, 0);
}

}