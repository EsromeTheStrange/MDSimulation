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

void correct_temperature(struct Particle* particles, int num_particles, double target_temp){
    double temperature = calculate_dimensionless_temperature(particles, num_particles);
    double temp_scale = sqrt(target_temp / temperature);
    
    for(int i=0; i<num_particles; i++){
        particles[i].velocity.x *= temp_scale;
        particles[i].velocity.y *= temp_scale;
        particles[i].velocity.z *= temp_scale;
    }
}

struct Vector3 signed_distance(struct Vector3 vec1, struct Vector3 vec2, double simulation_length){
    struct Vector3 distance = {
        vec1.x - vec2.x,
        vec1.y - vec2.y,
        vec1.z - vec2.z
    };

    if(distance.x > simulation_length / 2)
        distance.x -= simulation_length;
    if(distance.x < -simulation_length / 2)
        distance.x += simulation_length;
    
    if(distance.y > simulation_length / 2)
        distance.y -= simulation_length;
    if(distance.y < -simulation_length / 2)
        distance.y += simulation_length;
    
    if(distance.z > simulation_length / 2)
        distance.z -= simulation_length;
    if(distance.z < -simulation_length / 2)
        distance.z += simulation_length;
    
    return distance;
}

void enforce_boundary_condition(struct Particle* particles, int num_particles, double simulation_length, int current_step){
    for(int i=0; i<num_particles; i++){
        particles[i].position.x = fmod(particles[i].position.x, simulation_length);
        if(particles[i].position.x < 0)
            particles[i].position.x += simulation_length;
        
        particles[i].position.y = fmod(particles[i].position.y, simulation_length);
        if(particles[i].position.y < 0)
            particles[i].position.y += simulation_length;

        particles[i].position.z = fmod(particles[i].position.z, simulation_length);
        if(particles[i].position.z < 0)
            particles[i].position.z += simulation_length;
    }
}

#endif