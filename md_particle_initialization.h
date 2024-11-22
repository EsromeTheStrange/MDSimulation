#include <stdio.h>
#include <stdlib.h>
#include "md_math.h"
#include "md_output.h"

struct Particle* get_initial_particles_fcc(int num_particles, int simulation_length, float cell_length){
    struct Particle* particles = malloc(sizeof(struct Particle) * num_particles);
    int i=0;
    for (int x=0; x<simulation_length; x++){
        for(int y=0; y<simulation_length; y++){
            for(int z=0; z<simulation_length; z++){
                particles[i].x = cell_length * x;
                particles[i].y = cell_length * y;
                particles[i].z = cell_length * z;

                particles[i+1].x = cell_length * (x+0.5f);
                particles[i+1].y = cell_length * (y+0.5f);
                particles[i+1].z = cell_length * z;

                particles[i+2].x = cell_length * (x+0.5f);
                particles[i+2].y = cell_length * y;
                particles[i+2].z = cell_length * (z+0.5f);

                particles[i+3].x = cell_length * x;
                particles[i+3].y = cell_length * (y+0.5f);
                particles[i+3].z = cell_length * (z+0.5f);

                i+=4;
            }
        }
    }
    return particles;
}

void print_particle_position_tests(float cell_length){
    printf("Face Centered Cubic Unit Cell\n");
    struct Particle* particles = get_initial_particles_fcc(4, 1, cell_length);
    for(int i=0; i<4; i++){
        struct Particle particle = particles[i];
        printf("Particle %i: %f %f %f\n", i, particle.x, particle.y, particle.z);
    }
    write_file("FCC_test", particles, 4);
    printf("\n\n\n");
}

void set_initial_velocities(struct Particle* particles, int num_particles){
    for (int i=0; i<num_particles; i++){
        particles[i].vel_x = 0;
    }
}