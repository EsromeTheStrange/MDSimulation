#include <stdio.h>
#include <stdlib.h>

#include "md_logger.h"
#include "md_argon_defs.h"
#include "md_particle_initialization.h"
#include "md_force_calculations.h"
#include "md_radial_distribution.h"

#define NUM_CELLS_PER_AXIS 4
#define NUM_STEPS 2000
#define NUM_PARTICLES (int)(PARTICLES_PER_UNIT_CELL_FCC * NUM_CELLS_PER_AXIS * NUM_CELLS_PER_AXIS * NUM_CELLS_PER_AXIS)
#define RADIAL_DISTRIBUTION_FREQUENCY 50

int main()
{
    // Test Cases
    // print_particle_position_tests(CELL_LENGTH);
    // print_force_tests();

    // Actual Program
    log_important("Starting Simulation...\n\n");

    // Initialize Everything
    print_initial_variables();
    struct Particle *particles;

    particles = get_initial_particles_fcc(NUM_PARTICLES, NUM_CELLS_PER_AXIS, CELL_LENGTH);
    set_initial_velocities(particles, NUM_PARTICLES);

    struct Vector3 *forces = calculate_forces(particles, NUM_PARTICLES, NUM_CELLS_PER_AXIS * CELL_LENGTH);
    FILE *output_file = start_file("result");

    initialize_radial_distribution_calculations();

    // Main Loop
    log_header("\n\nStarting Simulation Loop...\n");
    for (int i = 0; i < NUM_STEPS; i++)
    {
        printf("\rSimulation Step %i/%i", i + 1, NUM_STEPS);
        fflush(stdout);

        update_velocities(particles, forces, NUM_PARTICLES, TIME_STEP / 2.0);
        move_particles(particles, NUM_PARTICLES, TIME_STEP);
        enforce_boundary_condition(particles, NUM_PARTICLES, NUM_CELLS_PER_AXIS * CELL_LENGTH, i);
        update_forces(forces, particles, NUM_PARTICLES, NUM_CELLS_PER_AXIS * CELL_LENGTH);
        update_velocities(particles, forces, NUM_PARTICLES, TIME_STEP / 2.0);

        correct_temperature(particles, NUM_PARTICLES, TARGET_TEMP);
        if (i % RADIAL_DISTRIBUTION_FREQUENCY == 0)
            calculate_radial_distribution(particles, NUM_PARTICLES, NUM_CELLS_PER_AXIS * CELL_LENGTH);

        append_to_file(output_file, particles, NUM_PARTICLES, i + 1, NUM_STEPS);
    }

    // Output
    printf("\n\n");
    finish_file(output_file);
    finish_radial_distribution_calculations();

    free(forces);
    free(particles);

    log_success("\nSimulation Finished.\n");
    return 0;
}