#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "hittable.hpp"

class Sphere: public Hittable{

public:

    Sphere(){}
    Sphere(point3 cen, double r, std::shared_ptr<Material> m): center(cen), radius(r), mat_ptr(m){}

    virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;

public: 
    
    point3 center;
    double radius;
    std::shared_ptr<Material> mat_ptr;

};

bool Sphere::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const{

    vec3 oc = r.origin() - center; 
    
    double a = r.direction().length_squared();
    double half_b = dot(oc, r.direction());
    double c = oc.length_squared() - radius * radius; 

    double discriminant = half_b * half_b - a*c;

    if(discriminant < 0.0)
        return false;

    
    double sqrtd = std::sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range. 

    double root = (-half_b -sqrtd) / a;

    if(root < t_min || t_max < root){

        root = (-half_b + sqrtd) / a;
        if(root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}


#endif