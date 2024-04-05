#include <rt/solids/solid.h>

namespace rt {

Solid::Solid(CoordMapper* texMapper, Material* material)
{
    if(texMapper == nullptr){
        this->texMapper = new WorldMapper(Vector::rep(1));
    }else{
        this->texMapper = texMapper;
    }
    this->material = material;
}

}
