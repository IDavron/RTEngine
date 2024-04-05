#include <rt/primmod/instance.h>

namespace rt {

Instance::Instance(Primitive* content)
{
    this->cont = content;
    this->translateMatrix = Matrix::identity();
    this->rotateMatrix = Matrix::identity();
    this->scaleMatrix = Matrix::identity();
    this->finalTransformationMatrix = Matrix::identity();
}

Primitive* Instance::content() {
   return this->cont;
}

void Instance::reset() {
    this->translateMatrix = Matrix::identity();
    this->rotateMatrix = Matrix::identity();
    this->scaleMatrix = Matrix::identity();
    this->finalTransformationMatrix = Matrix::identity();
}

void Instance::translate(const Vector& t) {
    HomogeneousCoord r1 = HomogeneousCoord(1, 0, 0, t.x);
    HomogeneousCoord r2 = HomogeneousCoord(0, 1, 0, t.y);
    HomogeneousCoord r3 = HomogeneousCoord(0, 0, 1, t.z);
    HomogeneousCoord r4 = HomogeneousCoord(0, 0, 0, 1);
    Matrix m = Matrix(r1, r2, r3, r4);
    this->translateMatrix = m;

    this->finalTransformationMatrix = product(m, this->finalTransformationMatrix);
}

void Instance::rotate(const Vector& nnaxis, float angle) {
    Vector r = nnaxis;
    Vector s;
    float x = abs(r.x);
    float y = abs(r.y);
    float z = abs(r.z);

    if(x >= y && x >= z){
        s = Vector(0, -r.z, r.y);
    }else if(y >= x && y >= z){
        s = Vector(-r.z, 0, r.x);
    }else{
        s = Vector(-r.y, r.x, 0);
    }

    s = s.normalize();

    Vector t = cross(r, s);

    HomogeneousCoord r1 = HomogeneousCoord(r.x, s.x, t.x, 0);
    HomogeneousCoord r2 = HomogeneousCoord(r.y, s.y, t.y, 0);
    HomogeneousCoord r3 = HomogeneousCoord(r.z, s.z, t.z, 0);
    HomogeneousCoord r4 = HomogeneousCoord(0, 0, 0, 1);

    Matrix M = Matrix(r1, r2, r3, r4);

    HomogeneousCoord rr1 = HomogeneousCoord(1, 0, 0, 0);
    HomogeneousCoord rr2 = HomogeneousCoord(0, cos(angle), -sin(angle), 0);
    HomogeneousCoord rr3 = HomogeneousCoord(0, sin(angle), cos(angle), 0);
    HomogeneousCoord rr4 = HomogeneousCoord(0, 0, 0, 1);

    Matrix RM = Matrix(rr1, rr2, rr3, rr4);

    Matrix R = M.transpose();
    Matrix FRM = product(RM, R);
    FRM = product(M, FRM);

    this->rotateMatrix = FRM;
    this->finalTransformationMatrix = product(FRM, this->finalTransformationMatrix);
}

void Instance::scale(float f) {
    HomogeneousCoord r1 = HomogeneousCoord(f, 0, 0, 0);
    HomogeneousCoord r2 = HomogeneousCoord(0, f, 0, 0);
    HomogeneousCoord r3 = HomogeneousCoord(0, 0, f, 0);
    HomogeneousCoord r4 = HomogeneousCoord(0, 0, 0, 1);
    Matrix m = Matrix(r1, r2, r3, r4);
    this->scaleMatrix = m;

    this->finalTransformationMatrix = product(m, this->finalTransformationMatrix);
}

void Instance::scale(const Vector& s) {
    HomogeneousCoord r1 = HomogeneousCoord(s.x, 0, 0, 0);
    HomogeneousCoord r2 = HomogeneousCoord(0, s.y, 0, 0);
    HomogeneousCoord r3 = HomogeneousCoord(0, 0, s.z, 0);
    HomogeneousCoord r4 = HomogeneousCoord(0, 0, 0, 1);
    Matrix m = Matrix(r1, r2, r3, r4);
    this->scaleMatrix = m;

    this->finalTransformationMatrix = product(m, this->finalTransformationMatrix);
}

void Instance::setMaterial(Material* m) {
    /* TODO */ NOT_IMPLEMENTED;
}

void Instance::setCoordMapper(CoordMapper* cm) {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection Instance::intersect(const Ray& ray, float tmin, float tmax) const {
    Matrix invTransform = this->finalTransformationMatrix.invert();
    Ray r;
    r.o = invTransform * ray.o;
    r.d = invTransform * ray.d;
    Intersection i = this->cont->intersect(r, tmin / ray.d.length(), tmax  / ray.d.length());
    if(!i){
        return Intersection::failure();
    }

    Intersection fi;
    fi.distance = i.distance;
    fi.ray = r;
    fi.solid = i.solid;
    fi.n = (invTransform.transpose() * i.normal()).normalize();
    fi.l = invTransform.transpose() * i.l;
    return fi;
}

BBox Instance::getBounds() const {
    BBox bbox = this->cont->getBounds();
    bbox.min = this->finalTransformationMatrix*bbox.min;
    bbox.max = this->finalTransformationMatrix*bbox.max;
    return bbox;
}

}