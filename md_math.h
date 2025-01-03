#ifndef MD_MATH
#define MD_MATH
#include <math.h>

#define PARTICLES_PER_UNIT_CELL_FCC 4

#define AVOGADROS 6.0221367e+23
#define BOLTZMANN 1.380658e-23
#define PI 3.1415926535897932384

struct Vector3 {
    double x, y, z;
};

struct Particle {
    struct Vector3 position, velocity;
};

struct Vector3 calculate_total_velocity(struct Particle* particles, int num_particles){
    struct Vector3 total_velocity = {0, 0, 0};
    for (int i=0; i<num_particles; i++) {
        total_velocity.x += particles[i].velocity.x;
        total_velocity.y += particles[i].velocity.y;
        total_velocity.z += particles[i].velocity.z;
    }
    return total_velocity;
}

double calculate_dimensionless_temperature(struct Particle* particles, int num_particles){
    double total_squared_velocity = 0;
    for (int i=0; i<num_particles; i++){
        total_squared_velocity += particles[i].velocity.x * particles[i].velocity.x;
        total_squared_velocity += particles[i].velocity.y * particles[i].velocity.y;
        total_squared_velocity += particles[i].velocity.z * particles[i].velocity.z;
    }
    return total_squared_velocity / (3*(num_particles-1));
}

#endif