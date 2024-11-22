#ifndef MD_MATH
#define MD_MATH
#include <math.h>

#define PARTICLES_PER_UNIT_CELL_FCC 4

#define AVOGADROS 6.0221367e+23
#define BOLTZMANN 1.380658e-23

struct Particle {
    float x, y, z;
    float vel_x, vel_y, vel_z;
};

#endif