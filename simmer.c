/* A simple no-input 1D heat solver */

#include <stdio.h>
#include <math.h>

/* Physical constants of the simulation */
#define BAR_LENGTH 1.0 /* meters */
#define CELL_SIZE 0.01 /* meters, resolution of heat spatial step */
#define TIME_STEP 0.1 /* seconds */
#define SIMULATION_TIME 2.0 /* seconds */
#define BOLTZMAN 1.38064852e-23 /* the Boltzman constant k */
#define AL_DENSITY 2700000 /* g / m^3 */
#define AL_SP_HEAT 0.897 /* J/(g*K) */

int main();
void initialize_temperatures(double * temperature, int n_cells);

int main()
{
    /* Initialize variables based on simulation settings (approx) */
    int n_cells = (int) (BAR_LENGTH/CELL_SIZE); // Number of simulation cells
    int n_steps = (int) (SIMULATION_TIME/TIME_STEP); // Time steps
    double temperature[n_cells];
//    double linear_diffusivity = BOLTZMAN/(AL_SP_HEAT*AL_DENSITY);
    double linear_diffusivity = 1;
    double ugly_const = 2*linear_diffusivity*TIME_STEP*(1.0/(pow(CELL_SIZE, 2)));
    int i, t;

    printf("\nPerforming simulation...\n");
    initialize_temperatures(temperature, n_cells);

    /* Print initial values */
    printf("\nTime: %4.2fs Bar temperature: ", 0*TIME_STEP);
    for (i=0; i<n_cells; i++)
    {
        printf("%4.2fK ", temperature[i]);
    }

    /* Calculate final state of heat simulation after SIMULATION_TIME */
    for (t=1; t<n_steps; t++)
    {
        printf("\nTime: %4.2fs Bar temperature: ", t*TIME_STEP);
        for (i=0; i<n_cells; i++)
        {
            /* boundary conditions*/
            if (i == 0 || i == n_cells - 1)
            {
                printf("%4.2fK ", temperature[i]);
                continue;
            }

            temperature[i] = (1.0/(1.0 + 2*ugly_const))*(temperature[i] + ugly_const*(temperature[i+1] + temperature[i-1]));
            printf("%4.2fK ", temperature[i]);
        }
    }

    printf("\nDone. \n");
}

void initialize_temperatures(double * temperature, int n_cells)
{
    int i;
    /* Initial conditions; initialize bar to even temp */
    for (i=0; i<n_cells; i++)
    {
        temperature[i] = 50.0;
    }

    /* Boundary conditions */
    temperature[0] = 0.0;
    temperature[n_cells - 1] = 100.0;
}
