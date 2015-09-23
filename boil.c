/******************************************************************************
 *  boil.c
 *
 *  A simple no-input 3D heat diffusion solver.
 *
 *  Basic physical parameters of the simulation are specifed in define
 *  directives. This simple simulation doesn't do error checking, make sure
 *  your parameters are sane. E.g. we do float division on length/cell-size
 *  and cast it to an int to size the data structure.
 *
 *  A difference equation approach is taken to solve the diffusion equation
 *  in three dimentions. By using static outer-volume boundary conditions we
 *  can use just the central-difference (or Crank-Nicolson) method.
 *    - https://en.wikipedia.org/wiki/Crank%E2%80%93Nicolson_method
 *    - https://en.wikipedia.org/wiki/Heat_equation
 *
 *  It's not terribly complicated, really, but works well. In order to use
 *  non-static boundary conditions in the outer-volume a forward and backward
 *  Euler difference path must be added to the simulation core.
 *
 *  Usage: ./boil | tee boiled.logs
 *****************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Physical constants of the simulation
#define BAR_LENGTH 1.0 // meters, will be a cube
#define CELL_SIZE 0.2 // meters, resolution of heat spatial step
#define TIME_STEP 2.0 // seconds
#define SIMULATION_TIME 10.0 // seconds
#define BOLTZMAN 1.38064852e-23 // the Boltzman constant 'k' m^2 kg s^-2 K^-1
#define AL_DENSITY 2700000 // g / m^3
#define AL_SP_HEAT 0.897 // J/(g*K)

int main();
bool is_edge(int i, int j, int k, int length);
// Specify array sizes https://gcc.gnu.org/onlinedocs/gcc/Variable-Length.html
// A cool C99 solution.
void initial_conditions_uniform_box_boundary(int n_cells, double temperature[n_cells][n_cells][n_cells]);
void print_initial_values(int n_cells, double temperature[n_cells][n_cells][n_cells]);
void perform_simulation(int n_cells, double temperature[n_cells][n_cells][n_cells], int n_steps);

/* main
 *
 * Data structures for the simulation are constructed. We call out to helpers
 * to initialize them and perform the simulation. The simulation writes to
 * stdout.
 */
int main()
{
    /* Initialize variables based on simulation settings (approx) */
    int n_cells = (int) (BAR_LENGTH/CELL_SIZE); // Number of simulation cells per dimension
    int n_steps = (int) (SIMULATION_TIME/TIME_STEP); // Time steps
    double temperature[n_cells][n_cells][n_cells];

    initial_conditions_uniform_box_boundary(n_cells, temperature);
    print_initial_values(n_cells, temperature);
    perform_simulation(n_cells, temperature, n_steps);

    printf("\nDone. \n");
}


/* perform_simulation
 *
 * Given the initialized temperature data structure and the simulation length
 * loop through time/space and:
 *   - apply boundary conditions
 *   - calculate the temperature
 *   - print the state to stdout
 *
 *  After the simulation, all data is available in the temperature array.
 */
void perform_simulation(int n_cells, double temperature[n_cells][n_cells][n_cells], int n_steps)
{
    // Still getting a Aluminumish simultion working, we use 1 for now.
    //double linear_diffusivity = BOLTZMAN/(AL_SP_HEAT*AL_DENSITY);
    double linear_diffusivity = 1;
    double ugly_const = 2*linear_diffusivity*TIME_STEP*(1.0/(pow(CELL_SIZE, 2)));
    int i, j, k, t;
    /* Calculate final state of heat simulation after SIMULATION_TIME */
    for (t=1; t<n_steps; t++)
    {
        // TODO track this in the data structure
        printf("\nTime: %06.2fs Bar temperature:\n", t*TIME_STEP);
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
                            printf("%06.2fK ", temperature[i][j][k]);
                        continue;
                    }

                    temperature[i][j][k] = (1.0/(1.0 + 6*ugly_const))*(temperature[i][j][k] + ugly_const*(temperature[i+1][j][k] + temperature[i-1][j][k] + temperature[i][j+1][k] + temperature[i][j-1][k] + temperature[i][j][k+1] + temperature[i][j][k-1]));
                    if (k == n_cells/2)
                        printf("%06.2fK ", temperature[i][j][k]);
                }
            }
            printf("\n");
        }
    }
}


/* print_initial_values
 *
 * This was broken out of perform_simulation to keep it cleaner, here we just
 * print the initial conditions to stdout.
 */
void print_initial_values(int n_cells, double temperature[n_cells][n_cells][n_cells])
{
    int i, j;
    int k = n_cells / 2; // Rough int middle
    printf("\nPerforming simulation...\n");
    printf("\nTime: %06.2fs Bar temperature: \n", 0*TIME_STEP);
    for (i=0; i<n_cells; i++)
    {
        for (j=0; j<n_cells; j++)
        {
            printf("%06.2fK ", temperature[i][j][k]);
        }
        printf("\n");
    }
}


/* initial_conditions_uniform_box_boundary
 *
 * This function sets all internal points of the temperature matrix to 0.0 K
 * and the outer box boundary to 100.0 K
 */
void initial_conditions_uniform_box_boundary(int n_cells, double temperature[n_cells][n_cells][n_cells])
{
    int i, j, k;
    // initialize bar to even temp
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

    // initial application of boundary conditions
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


/* is_edge
 *
 * Determine if a 3D space index i,j,k lies on the outer boundary of our
 * simulated volume.
 */
bool is_edge(int i, int j, int k, int length)
{
    if (i == 0 || j == 0 || k == 0)
        return true;
    else if (i == length - 1 || j == length -1 || k ==length - 1)
        return true;
    else
        return false;
}
