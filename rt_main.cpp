#include "rt_weekend.hpp"

#include "color.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"

#include "camera.hpp"

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

        point3 target = rec.p + random_in_hemisphere(rec.normal);
        return 0.5 * ray_color(Ray(rec.p, target - rec.p), world, depth - 1);
    }
    
    vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5*(unit_direction.y() + 1.0);
    
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0); 

}

int main(int argc, char * argv[]){

    // Image

    const double aspect_ratio = 16.0 / 9.0;
   
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    const int samples_per_pixel = 100;
    const int max_depth = 50;

    // World
    Hittable_List world;
    world.add(std::make_shared<Sphere>(point3(0,0,-1), 0.5));
    world.add(std::make_shared<Sphere>(point3(0,-100.5, -1), 100));


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