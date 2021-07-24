#include "rt_weekend.hpp"

#include "color.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"

#include "camera.hpp"

#include "material.hpp"

#include <iostream>




/*
double hit_sphere(const point3& center, double radius, const Ray& r){

    vec3 oc = r.origin() - center;

    double a = r.direction().length_squared();
    double half_b = dot(oc, r.direction());
    double c = oc.length_squared() - radius * radius;
    
    double discriminant = half_b * half_b - a*c;

    if(discriminant < 0){
        return -1.0;        
    }
    else {

        return (-half_b - std::sqrt(discriminant)) / a;
    }
}
*/

color ray_color(const Ray& r, const Hittable& world, int depth){

    hit_record rec;
    
    // See if ray bounce limit is reached
    if(depth <= 0)
        return color(0, 0, 0);

    if(world.hit(r, 0.001, RT_Constants::infinity, rec)){

        Ray scattered;
        color attenuation;

        if(rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth -1);
        
        return color(0, 0, 0);
    }

    
    vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5*(unit_direction.y() + 1.0);
    
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0); 

}

int main(int argc, char * argv[]){

    // Image

    constexpr double aspect_ratio = 16.0 / 9.0;
   
    constexpr int image_width = 400;
    constexpr int image_height = static_cast<int>(image_width / aspect_ratio);

    constexpr int  samples_per_pixel = 100;
    constexpr int max_depth = 50;

    // World
    Hittable_List world;
    
    auto material_ground = std::make_shared<Lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<Lambertian>(color(0.7, 0.3, 0.3));
    auto material_left   = std::make_shared<Metal>(color(0.8, 0.8, 0.8));
    auto material_right  = std::make_shared<Metal>(color(0.8, 0.6, 0.2));

    world.add(std::make_shared<Sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<Sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
    world.add(std::make_shared<Sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(std::make_shared<Sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));
    
    // Camera
    Camera cam;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for(int j = image_height - 1; j >= 0; --j){

        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        
        for(int i = 0; i < image_width; i++){

            color pixel_color(0, 0, 0);

            for(int s = 0; s < samples_per_pixel; ++s){
                
                double u = (i + RT_Util::random_double()) / (image_width - 1);
                double v = (j + RT_Util::random_double()) / (image_height - 1);

                Ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }

            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "\nDone \n";
    
}