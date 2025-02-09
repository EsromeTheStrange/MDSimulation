#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "md_logger.h"
#include "md_math.h"
#include "md_output.h"

struct Particle* get_initial_particles_fcc(int num_particles, int simulation_length, double cell_length){
    struct Particle* particles = malloc(sizeof(struct Particle) * num_particles);
    int i=0;
    for (int x=0; x<simulation_length; x++){
        for(int y=0; y<simulation_length; y++){
            for(int z=0; z<simulation_length; z++){
                particles[i].position.x = cell_length * x;
                particles[i].position.y = cell_length * y;
                particles[i].position.z = cell_length * z;

                particles[i+1].position.x = cell_length * (x+0.5f);
                particles[i+1].position.y = cell_length * (y+0.5f);
                particles[i+1].position.z = cell_length * z;

                particles[i+2].position.x = cell_length * (x+0.5f);
                particles[i+2].position.y = cell_length * y;
                particles[i+2].position.z = cell_length * (z+0.5f);

                particles[i+3].position.x = cell_length * x;
                particles[i+3].position.y = cell_length * (y+0.5f);
                particles[i+3].position.z = cell_length * (z+0.5f);

                i+=4;
            }
        }
    }
    return particles;
}

void print_particle_position_tests(double cell_length){
    printf("Face Centered Cubic Unit Cell\n");
    struct Particle* particles = get_initial_particles_fcc(4, 1, cell_length);
    for(int i=0; i<4; i++){
        struct Particle particle = particles[i];
        printf("Particle %i: %f %f %f\n", i, particle.position.x, particle.position.y, particle.position.z);
    }
    write_file("FCC_test", particles, 4);
    printf("\n\n\n");
}

double generate_random_velocity(double u0, double u1){
    return sqrt(-2 * log(u0)) * cos(2 * PI * u1);
}

void set_initial_velocities(struct Particle* particles, int num_particles){
    //Randomize the velocity.
    for (int i=0; i<num_particles; i++){
        double x0 = (double)rand()/RAND_MAX, x1 = (double)rand()/RAND_MAX;
        particles[i].velocity.x = generate_random_velocity(x0, x1);

        double y0 = (double)rand()/RAND_MAX, y1 = (double)rand()/RAND_MAX;
        particles[i].velocity.y = generate_random_velocity(y0, y1);

        double z0 = (double)rand()/RAND_MAX, z1 = (double)rand()/RAND_MAX;
        particles[i].velocity.z = generate_random_velocity(z0, z1);
    }

    //Set the total velocity to zero (the system as a whole is stationary).
    struct Vector3 total_velocity = calculate_total_velocity(particles, num_particles);
    double x_correction = total_velocity.x / num_particles;
    double y_correction = total_velocity.y / num_particles;
    double z_correction = total_velocity.z / num_particles;
    
    log_header("Calculating Initial Velocity...\n");
    printf("Initial Total Velocity:           (%.4e, %.4e, %.4e)\n", total_velocity.x, total_velocity.y, total_velocity.z);

    for (int i=0; i<num_particles; i++){
        particles[i].velocity.x -= x_correction;
        particles[i].velocity.y -= y_correction;
        particles[i].velocity.z -= z_correction;
    }

    total_velocity = calculate_total_velocity(particles, num_particles);
    printf("Total Velocity Corrected to Zero: (% .4e, % .4e, % .4e)\n", total_velocity.x, total_velocity.y, total_velocity.z);

    //Scale the velocity to match the desired temperature.
    double temperature = calculate_dimensionless_temperature(particles, num_particles);
    printf("\nInitial Temperature:   %.6f\n", temperature);
    correct_temperature(particles, num_particles, TARGET_TEMP);
    temperature = calculate_dimensionless_temperature(particles, num_particles);
    printf("Target Temperature:    %.6f\n", TARGET_TEMP);
    printf("Corrected Temperature: %.6f\n", temperature);
}