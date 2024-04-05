#include <rt/textures/imagetex.h>

namespace rt {

ImageTexture::ImageTexture()
{
    /* TODO */
}

ImageTexture::ImageTexture(const std::string& filename, BorderHandlingType bh, InterpolationType i)
{
    this->image.readPNG(filename);
    this->border_handling = bh;
    this->interpolation_handling = i;
}

ImageTexture::ImageTexture(const Image& image, BorderHandlingType bh, InterpolationType i)
{
    this->image = image;
    this->border_handling = bh;
    this->interpolation_handling = i;
}

RGBColor ImageTexture::getColor(const Point& coord) {
    float x = coord.x;
    float y = coord.y;

    if(this->border_handling == ImageTexture::CLAMP)
    {
        if(x < 0) x = 0;
        if(x > 1) x = 1;
        if(y < 0) y = 0;
        if(y > 1) y = 1;
    }
    else if(this->border_handling == ImageTexture::MIRROR)
    {
        x = abs(x);
        y = abs(y);
        int l_u = int(x);
        int l_v = int(y);
        x = x - l_u;
        y = y - l_v;
        if(l_u % 2 == 1) x = 1 - x;
        if(l_v % 2 == 1) y = 1 - y;
    }
    else if(this->border_handling == ImageTexture::REPEAT)
    {
        if(x<0){
            x = abs(x);
            x = 1 - x + int(x);
        }else{
            x = x - int(x);
        }

        if(y<0){
            y = abs(y);
            y = 1 - y + int(y);
        }else{
            y = y - int(y);
        }
    }

    if(this->interpolation_handling == ImageTexture::NEAREST)
    {
        x = round(x*(image.width()-1));
        y = round(y*(image.height()-1));
        // unsigned int u = x * (this->image.width());
        // unsigned int v = y * (this->image.height());
        // x = u < (image.width() - 1) ? u : (image.width() - 1);
        // y = v < (image.height() - 1) ? v : (image.height() - 1);
    }
    else if(this->interpolation_handling == ImageTexture::BILINEAR)
    {
        x = x * (image.width() - 1);
        y = y * (image.height() - 1);

        int fx = int(x);
        int fy = int(y);

        if(x - fx == 0 && x != 0){
            fx -= 1;
        }
        if(y - fy == 0 && y != 0){
            fy -= 1;
        }

        float diff_x = x - fx;
        float diff_y = y - fy;

        RGBColor c = (1-diff_x)*(1-diff_y)*image(fx,fy) + (1-diff_x)*(diff_y)*image(fx,fy+1) + (diff_x)*(1-diff_y)*image(fx+1,fy) + (diff_x)*(diff_y)*image(fx+1,fy+1);

        return c;
    }
    return this->image(x, y);
}

RGBColor ImageTexture::getColorDX(const Point& coord) {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor ImageTexture::getColorDY(const Point& coord) {
    /* TODO */ NOT_IMPLEMENTED;
}

}