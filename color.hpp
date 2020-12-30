#ifndef COLOR_HPP
#define COLOR_HPP

#include "vec3.hpp"

#include <iostream>
/*
void write_color(std::ostream& out, color pixel_color){

    // Write the translated [0, 255] value of each color component

    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';

}

*/

void write_color(std::ostream& out, color pixel_color, int samples_per_pixel){

    double r = pixel_color.x();
    double g = pixel_color.y();
    double b = pixel_color.z();

    // Divide the color by the number of samples
    double scale = 1.0 / samples_per_pixel;

    r = std::sqrt(scale * r);
    g = std::sqrt(scale * g);
    b = std::sqrt(scale * b); 

    // Write the translated [0, 255] value of each color component
    out << static_cast<int>(256 * RT_Util::clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * RT_Util::clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * RT_Util::clamp(b, 0.0, 0.999)) << '\n';
}


#endif