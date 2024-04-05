#include <core/scalar.h>
#include <core/image.h>
#include <rt/renderer.h>
#include <rt/ray.h>
#include <iostream>
#include <omp.h>

namespace rt {

Renderer::Renderer(Camera* cam, Integrator* integrator)
    : cam(cam), integrator(integrator), samples(1024)
{}

void Renderer::setSamples(uint samples){
    this->samples = samples;
}

void Renderer::render(Image& img) {
    std::cout<<"Number of samples per ray: " << this->samples << std::endl;
    rt::uint width = img.width();
    rt::uint height = img.height();
#pragma omp parallel for
    for(rt::uint y = 0; y<height; y++){
        std::cout<< "Processing: " << float(y)/height*100 << "%" <<std::endl;
        for(rt::uint x = 0; x<width; x++){
            RGBColor pixel_color = RGBColor::rep(0);
            if(this->samples <= 1){
                float sscx = ((x+0.5f)/width)*2-1;
                float sscy = ((y+0.5f)/height)*2-1;
                Ray primary_ray = this->cam->getPrimaryRay(sscx,sscy);
                pixel_color = this->integrator->getRadiance(primary_ray);
            }
            else
            {
                for (uint i = 0; i < this->samples; i++){
                float sscx = ((x+random())/width)*2-1;
                float sscy = ((y+random())/height)*2-1;
                Ray primary_ray = this->cam->getPrimaryRay(sscx,sscy);
                pixel_color = pixel_color + (this->integrator->getRadiance(primary_ray) / this->samples);
                }
            }
            img(x,img.height()-1-y) = pixel_color;
        }
    }
}

}

rt::RGBColor a1computeColor(rt::uint x, rt::uint y, rt::uint width, rt::uint height);

namespace rt {

void Renderer::test_render1(Image& img) {
    rt::uint width = img.width();
    rt::uint height = img.height();
    for(rt::uint y = 0; y<height; y++){
        for(rt::uint x = 0; x<width; x++){
            img(x,y) = a1computeColor(x,y,width,height);
        }
    }
}
}

rt::RGBColor a2computeColor(const rt::Ray& r);

namespace rt {

void Renderer::test_render2(Image& img) {
    rt::uint width = img.width();
    rt::uint height = img.height();
    for(rt::uint y = 0; y<height; y++){
        for(rt::uint x = 0; x<width; x++){
            float sscx = ((x+0.5f)/width)*2-1;
            float sscy = ((y+0.5f)/height)*2-1;
            img(x,img.height()-y-1) = a2computeColor(this->cam->getPrimaryRay(sscx,sscy));
        }
    }
}

}
