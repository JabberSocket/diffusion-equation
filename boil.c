/* A simple no-input 3D heat solver */
/* TODO: Convert 3D array passing to format as specified here: http://stackoverflow.com/a/24623778 */

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

/* Physical constants of the simulation */
#define BAR_LENGTH 1.0 /* meters, will be a cube*/
#define CELL_SIZE 0.1 /* meters, resolution of heat spatial step */
#define TIME_STEP 0.1 /* seconds */
#define SIMULATION_TIME 10.0 /* seconds */
#define BOLTZMAN 1.38064852e-23 /* the Boltzman constant k */
#define AL_DENSITY 2700000 /* g / m^3 */
#define AL_SP_HEAT 0.897 /* J/(g*K) */

int main();
void initialize_temperatures(int n_cells, double temperature[n_cells][n_cells][n_cells]);
void print_initial_values(int n_cells, double temperature[n_cells][n_cells][n_cells]);
void perform_simulation(int n_cells, double temperature[n_cells][n_cells][n_cells], int n_steps);
bool is_edge(int i, int j, int k, int length);

int main()
{
    /* Initialize variables based on simulation settings (approx) */
    int n_cells = (int) (BAR_LENGTH/CELL_SIZE); // Number of simulation cells per dimension
    int n_steps = (int) (SIMULATION_TIME/TIME_STEP); // Time steps
    double temperature[n_cells][n_cells][n_cells];

    initialize_temperatures(n_cells, temperature);
    print_initial_values(n_cells, temperature);
    perform_simulation(n_cells, temperature, n_steps);

    printf("\nDone. \n");
}

void perform_simulation(int n_cells, double temperature[n_cells][n_cells][n_cells], int n_steps)
{
//    double linear_diffusivity = BOLTZMAN/(AL_SP_HEAT*AL_DENSITY);
    double linear_diffusivity = 1;
    double ugly_const = 2*linear_diffusivity*TIME_STEP*(1.0/(pow(CELL_SIZE, 2)));
    int i, j, k, t;
    /* Calculate final state of heat simulation after SIMULATION_TIME */
    for (t=1; t<n_steps; t++)
    {
        printf("\nTime: %4.2fs Bar temperature: ", t*TIME_STEP);
        for (i=0; i<n_cells; i++)
        {
            for (j=0; j<n_cells; j++)
            {
                for (k=0; k<n_cells; k++)
                {
                    /* boundary conditions*/
                    if (is_edge(i, j, k, n_cells))
                    {
                        if (k == n_cells/2)
                            printf("%4.2fK ", temperature[i][j][k]);
                        continue;
                    }

                    temperature[i][j][k] = (1.0/(1.0 + 6*ugly_const))*(temperature[i][j][k] + ugly_const*(temperature[i+1][j][k] + temperature[i-1][j][k] + temperature[i][j+1][k] + temperature[i][j-1][k] + temperature[i][j][k+1] + temperature[i][j][k-1]));
                    if (k == n_cells/2)
                        printf("%4.2fK ", temperature[i][j][k]);
                }
            }
            printf("\n");
        }
    }
}

void print_initial_values(int n_cells, double temperature[n_cells][n_cells][n_cells])
{
    int i, j;
    int k = n_cells / 2; // Rough int middle
    printf("\nPerforming simulation...\n");
    printf("\nTime: %4.2fs Bar temperature: \n", 0*TIME_STEP);
    for (i=0; i<n_cells; i++)
    {
        for (j=0; j<n_cells; j++)
        {
            printf("%4.2fK ", temperature[i][j][k]);
        }
        printf("\n");
    }
}

void initialize_temperatures(int n_cells, double temperature[n_cells][n_cells][n_cells])
{
    int i, j, k;
    /* Initial conditions; initialize bar to even temp */
    for (i=0; i<n_cells; i++)
    {
        for (j=0; j<n_cells; j++)
        {
            for (k=0; k<n_cells; k++)
            {
                temperature[i][j][k] = 0.0;
            }
        }
    }

    /* Boundary conditions */
    for (i=0; i<n_cells; i++)
    {
        for (j=0; j<n_cells; j++)
        {
            for (k=0; k<n_cells; k++)
            {
                if (is_edge(i, j, k, n_cells))
                    temperature[i][j][k] = 100.0;
            }
        }
    }
}

bool is_edge(int i, int j, int k, int length)
{
    if (i == 0 || j == 0 || k == 0)
        return true;
    else if (i == length - 1 || j == length -1 || k ==length - 1)
        return true;
    else
        return false;
}
