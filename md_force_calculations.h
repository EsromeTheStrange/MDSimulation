#ifndef MD_FORCE_CALCULATIONS
#define MD_FORCE_CALCULATIONS

#include <stdlib.h>
#include <stdio.h>
#include "md_math.h"

#define MAX_FORCE_SQUARED_DISTANCE 9

void update_forces(struct Vector3* forces, struct Particle* particles, int num_particles, double simulation_length){
    for(int i=0; i<num_particles-1; i++){
        for(int j=i+1; j<num_particles; j++){
            struct Vector3 distance = signed_distance(particles[i].position, particles[j].position, simulation_length);
            float square_distance = distance.x*distance.x + distance.y*distance.y + distance.z*distance.z;
            if(square_distance >= MAX_FORCE_SQUARED_DISTANCE)
                continue;

            double phi = 4.0 * (12.0 * pow(square_distance, -7) - 6.0 * pow(square_distance, -4));
            struct Vector3 new_force = {
                distance.x * phi,
                distance.y * phi,
                distance.z * phi
            };

            forces[i].x += new_force.x;
            forces[i].y += new_force.y;
            forces[i].z += new_force.z;
            
            forces[j].x -= new_force.x;
            forces[j].y -= new_force.y;
            forces[j].z -= new_force.z;
        }
    }
}

struct Vector3* calculate_forces(struct Particle* particles, int num_particles, double simulation_length){
    struct Vector3* forces = calloc(num_particles, sizeof(struct Vector3));
    update_forces(forces, particles, num_particles, simulation_length);
    return forces;
}

void update_velocities(struct Particle* particles, struct Vector3* forces, int num_particles, double delta_time){
    for(int i=0; i<num_particles; i++){
        particles[i].velocity.x += forces[i].x * delta_time;
        particles[i].velocity.y += forces[i].y * delta_time;
        particles[i].velocity.z += forces[i].z * delta_time;
    }
}

void move_particles(struct Particle* particles, int num_particles, double delta_time){
    for(int i=0; i<num_particles; i++){
        particles[i].position.x += particles[i].velocity.x * delta_time;
        particles[i].position.y += particles[i].velocity.y * delta_time;
        particles[i].position.z += particles[i].velocity.z * delta_time;
    }
}

void test_forces(struct Particle* particles, int num_particles, double simulation_length){
    struct Vector3* forces = calculate_forces(particles, num_particles, simulation_length);
    printf("Testing forces on Particles:\n");
    for(int i=0; i<num_particles; i++){
        printf("    {% .2e, % .2e, % .2e}", particles[i].position.x, particles[i].position.y, particles[i].position.z);
        printf("    Force = (% .4e, % .4e, % .4e)\n", forces[i].x, forces[i].y, forces[i].z);
    }
    free(forces);
}

void force_test_1(){
    struct Particle particles[] = {
        {{1,1,1}},
        {{2,2,2}}
    };
    test_forces(particles, 2, 3);
}

void force_test_2(){
    struct Particle particles[] = {
        {{1,1,1}},
        {{2,3,1}}
    };
    test_forces(particles, 2, 4);
}

void force_test_3(){
    struct Particle particles[] = {
        {{1,1,1}},
        {{2,3,1}},
        {{4,1,1}},
        {{5,5,1}}
    };
    test_forces(particles, 4, 6);
}

void print_force_tests(){
    force_test_1();
    force_test_2();
    force_test_3();
    printf("\n\n");
}

#endif