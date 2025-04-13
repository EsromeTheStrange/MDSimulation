#ifndef MD_ARGON_DEFS
#define MD_ARGON_DEFS

#include "md_logger.h"
#include "md_math.h"

#define UNIT_LENGTH 3.4e-10
#define UNIT_LENGTH_ANGSTROMS UNIT_LENGTH * 1e10
#define UNIT_MASS (39.948 / AVOGADROS * 1e-3)
#define UNIT_ENERGY (120 * BOLTZMANN)
#define UNIT_TIME (UNIT_LENGTH * sqrt(UNIT_MASS / UNIT_ENERGY))

#define DENSITY (1380 * UNIT_LENGTH * UNIT_LENGTH * UNIT_LENGTH / UNIT_MASS)
#define TARGET_TEMP (86.64 / UNIT_ENERGY * BOLTZMANN)
#define TIME_STEP (2.0e-15 / UNIT_TIME)

#define CELL_LENGTH cbrt(PARTICLES_PER_UNIT_CELL_FCC / DENSITY)

void print_initial_variables()
{
    log_header("Base Units\n");
    printf("Unit Length: %.5e (m)\n", UNIT_LENGTH);
    printf("Unit Mass:   %.5e (kg)\n", UNIT_MASS);
    printf("Unit Energy: %.5e (J)\n", UNIT_ENERGY);
    printf("Unit Time:   %.5e (s)\n", UNIT_TIME);

    log_header("\nDimensionless Values\n");
    printf("Density:            %f\n", DENSITY);
    printf("Target Temperature: %f\n", TARGET_TEMP);
    printf("Time Step:          %f\n", TIME_STEP);

    printf("\nCell Length: %f\n", CELL_LENGTH);

    printf("\n\n\n");
}
#endif