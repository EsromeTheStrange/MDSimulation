#ifndef MD_RADIAL_DISTRIBUTION
#define MD_RADIAL_DISTRIBUTION

#include "md_output.h"
#include "md_argon_defs.h"

#define RADIAL_DISTRIBUTION_RADIUS 0.05

FILE *radial_distribution_output;

void initialize_radial_distribution_calculations()
{
    radial_distribution_output = start_file("radial_distribution");
}

void calculate_radial_distribution(struct Particle *particles, int num_particles, double simulation_length)
{
    int num_spheres = (int)(simulation_length / RADIAL_DISTRIBUTION_RADIUS);
    int *particle_distribution = calloc(num_spheres, sizeof(int));

    for (int i = 0; i < num_particles; i++)
    {
        for (int j = i + 1; j < num_particles; j++)
        {
            struct Vector3 distance = signed_distance(particles[i].position, particles[j].position, simulation_length);
            float square_distance = distance.x * distance.x + distance.y * distance.y + distance.z * distance.z;

            int sphere_index = sqrt(square_distance) / RADIAL_DISTRIBUTION_RADIUS;
            if (sphere_index < num_spheres)
                particle_distribution[sphere_index]++;
        }
    }

    double total_density = 0;
    for (int i = 0; i < num_spheres; i++)
    {
        double radius = (i + 1) * RADIAL_DISTRIBUTION_RADIUS;
        total_density += particle_distribution[i] / (4 * PI * radius * radius * RADIAL_DISTRIBUTION_RADIUS);
    }
    total_density /= num_spheres;
    float radial_distribution = total_density / DENSITY;

    fprintf(radial_distribution_output, "%.5e %.5e\n", total_density, radial_distribution);
    free(particle_distribution);
}

void finish_radial_distribution_calculations()
{
    finish_file(radial_distribution_output);
}

#endif