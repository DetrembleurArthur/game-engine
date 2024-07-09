#include "ge/graphics/image.hpp"
#include <stb_image.h>


ge::Image::Image(const std::string &filename, bool load) : filename(filename)
{
    image.pixels = nullptr;
    if(load)
    {
        this->load();
    }
}

ge::Image::~Image()
{
    unload();
}

void ge::Image::load(int target_channels)
{
    unload();
    image.pixels = stbi_load(filename.c_str(), &image.width, &image.height, &channels, target_channels ? target_channels : 4);
    if (!image.pixels)
    {
        ge::log("failed to load image at '" + filename + "'", LogLevels::ERROR);
        image.width = image.height = 0;
    }
    else
    {
        ge::log("image at '" + filename + "' loaded successfuly", LogLevels::INFO);
    }
}

void ge::Image::unload()
{
    if(image.pixels)
    {
        stbi_image_free(image.pixels);
        image.pixels = nullptr;
        ge::log("image at '" + filename + "' freed successfuly", LogLevels::INFO);
    }
}

GLFWimage &ge::Image::get()
{
    return image;
}

int ge::Image::get_channels() const
{
    return channels;
}
