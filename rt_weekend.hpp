#ifndef RT_WEEKEND_HPP
#define RT_WEEKEND_HPP

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

// Constants
namespace RT_Constants{

    const double infinity = std::numeric_limits<double>::infinity();
    const double pi = 3.1415926535897932385;

}

namespace RT_Util{

    inline double degrees_to_radians(double degrees){
        return degrees * RT_Constants::pi / 180.0;
    }

    inline double random_double(){

        // Returns a random real in [0, 1).
        return rand() / (RAND_MAX + 1.0);

    }

    inline double random_double(double min, double max){

        // Returns a random real in [min, max);
        return min + (max - min) * random_double();

    }

    inline double clamp(double x, double min, double max){
        
        if(x < min)
            return min;

        else if(x > max)
            return max;
        
        else
            return x; 
    }

}

#include "ray.hpp"
#include "vec3.hpp"

#endif