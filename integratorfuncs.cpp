//
// Created by Audrey Dijeau on 4/29/21.
//
#include <iostream>
#include <valarray>
#include "valarray_updates.h"
#include <vector>
#include <ctime>
#include <cmath>
#include <string>
#include "constants.h"

double com_shift(
        vector<valarray<double>> m, vector<valarray<double>> p, vector<valarray<double>> v, double dt) {
        //"Apply a shift to positions and velocities to recenter Center of Mass on the origin"
        std::double msum = m.sum();
        std::vector<valarray<double>> p_COM = m[0] * p[0] + m[1] * p[1] / msum;
        std::vector<valarray<double>> v_COM = m[0] * v[0] + m[1] * v[1] / msum;
        p_COM = sum(m[:, np.newaxis] *p, axis = 0) / msum;
        v_COM = sum(m[:, np.newaxis] *v, axis = 0) / msum;
        p = p - p_COM;
        v = v - v_COM;
}
//###############################################################################
double accelerations(vector<valarray<double>> masses, vector<valarray<double>> positions) {
    /*
    a function to compute the accelerations of the masses
            inputs: masses  = an array containing the masses of the objects
            form = np.array([mu_1,mu_2,...,mu_n-1,mu_n])
    positions = an array containing the x and y positions of all the objects at
            the n-th timestep
    form = np.array([p_n_1_x, p_n_1_y], [p_n_2_x, p_n_2_y], ... ,
    [p_n_n-1_x, p_n_n-1_y], [p_n_n_x, p_n_n_y])
    outputs: accels = an array containing the accelerations for each particle at
            the n-th timestep, of the same shape as the positions array
    */
    std::vector<valarray<double>> accels = np.zeros(positions.shape, dtype = np.longdouble)
    for (int i = 0 , i < positions.size(), i++){
        for (int j = 0, j < positions.size(), j++){
            if(i != j){
                std::double r = positions(i) - positions(j);
                accels(i) ++ -masses(j)*r/ np.linalg.norm(r)**3  // a = mu * r /(|r | **3), r is a vector
            }
        }
    }
    return accels
}
###############################################################################
def ode(masses, positions, velocities, time):
/*
a function to get the solutions of the ode of positions and velocity
inputs: masses = an array containing the masses of the objects
        form = np.array([mu_1,mu_2,...,mu_n-1,mu_n])
positions = an array containing the x and y positions of all the objects at
        a timestep n
form = np.array([p_n_1_x, p_n_1_y], [p_n_2_x, p_n_2_y], ... ,
[p_n_n-1_x, p_n_n-1_y], [p_n_n_x, p_n_n_y])
velocities = an array containing the x and y velocities of all the objects at
        a timestep n
form = np.array([v_n_1_x, v_n_1_y], [v_n_2_x, v_n_2_y], ... ,
[v_n_n-1_x, v_n_n-1_y], [v_n_n_x, v_n_n_y])
time = the timestep which the ode is being solved at (float)
outputs: dxdt = the velocities input array
        dvdt = an array containing the accelerations for each particle at the n-th timestep,
        of the same shape as the positions array
*/
// get solutions to ode of position and velocity
dxdt = velocities
dvdt = accelerations(masses,positions)

return dxdt, dvdt