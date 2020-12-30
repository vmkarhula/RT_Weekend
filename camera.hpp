#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "rt_weekend.hpp"

class Camera{

public:

    Camera(){

        double aspect_ratio = 16.0 / 9.0;
        double viewport_height = 2.0;
        double viewport_width = aspect_ratio * viewport_height;
        double focal_length = 1.0;

        origin = point3(0, 0, 0);
        horizontal = vec3(viewport_width, 0.0, 0.0);
        vertical = vec3(0.0, viewport_height, 0.0);
        lower_left_corner = origin - horizontal / 2 - vertical/2 - vec3(0,0, focal_length);   
    }

    Ray get_ray(double u, double v) const{

        return Ray(origin, lower_left_corner + u*horizontal +v*vertical - origin);        
    }

private:

    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;

};


#endif