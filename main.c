#include <stdio.h>
#include <stdlib.h>
#include "md_argon_defs.h"
#include "md_particle_initialization.h"

#define SIMULATION_LENGTH 1
#define NUM_PARTICLES (int)(PARTICLES_PER_UNIT_CELL_FCC * SIMULATION_LENGTH * SIMULATION_LENGTH * SIMULATION_LENGTH)

void output_file(int num_particles, double* cd, double simulation_width);

int main(){
    //Test Cases
    print_initial_variables();
    print_particle_position_tests(CELL_LENGTH);

    //Actual Program
    struct Particle* particles;

    particles = get_initial_particles_fcc(NUM_PARTICLES, SIMULATION_LENGTH, CELL_LENGTH);
    set_initial_velocities(particles, NUM_PARTICLES);

    free(particles);
    return 0;
}