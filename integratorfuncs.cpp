//
// Created by Audrey Dijeau on 4/29/21.
//

#include "integrator.h"

using namespace std;
//###############################################################################

vector<vector<valarray<double>>> com_shift(
        valarray<double> m, vector<valarray<double>> p,
        vector<valarray<double>> v){
        //"Apply a shift to positions and velocities to recenter Center of Mass on the origin"
        double msum = m.sum();
        //std::valarray<double> p_COM = m[0] * p[0] + m[1] * p[1] / msum;
        //std::valarray<double> v_COM = m[0] * v[0] + m[1] * v[1] / msum;
        std::valarray<double> p_COM = {0.0,0.0,0.0};
        std::valarray<double> v_COM = {0.0,0.0,0.0};
    for (int i = 0 ; i < m.size(); i++) {
                p_COM += m[i] * p[i];
                v_COM += m[i] * v[i];
            }

    for(int i = 0; i < p.size(); i++) {
        p[i] = p[i] - p_COM / msum;
        v[i] = v[i] - v_COM / msum;
    }
    std::vector<vector<valarray<double>>> returnitem {p, v};
    return returnitem;
}

//###############################################################################

vector<valarray<double>> accelerations(valarray<double> masses, vector<valarray<double>> positions){
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
    std::valarray<double> zerooos {0.0,0.0,0.0};
    std::vector<valarray<double>> accels (positions.size(), zerooos);
    for (int i = 0 ; i < positions.size(); i++){
        for (int j = 0; j < positions.size(); j++){
            if(i != j){
                std::valarray<double> r {0.0, 0.0, 0.0};
                r = positions[i] - positions[j];
                double r_normal = hypot(r[0], r[1], r[2]);
                accels[i] += -masses[j] * r / pow(r_normal, 3);  // a = mu * r /(|r | **3), r is a vector
            }
        }
    }
    return accels;
};
//###############################################################################
vector<vector<valarray<double>>> ode(valarray<double> masses, vector<valarray<double>> positions,
           vector<valarray<double>> velocities, double time)
           {
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
    std::vector<valarray<double>> dxdt = velocities;
    std::vector<valarray<double>> dvdt = accelerations(masses, positions);
    std::vector<vector<valarray<double>>> returnitem {dxdt, dvdt};
    return returnitem;
}