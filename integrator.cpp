//
// Created by hecook on 4/29/21.
//

#include <vector>
#include <ctime>
#include <string>
#include <iostream>
#include <valarray>
#include <cmath>
#include "integrator.h"


/* Integrator Function */

void //vector<vector<valarray<double>>>
integrator(valarray<double> masses, vector<valarray<double>> i_positions, vector<valarray<double>> i_velocities,
           double t_tot, double dt, string method, string frame) {
    /*
    a function which integrates the motion of n-bodies
    inputs: masses  = an array containing the masses of the objects
                    form = np.array([mu_1,mu_2,...,mu_n-1,mu_n])
            i_positions = an array containing the initial x and y positions of all the objects
                        form = np.array([p_0_1_x, p_0_1_y], [p_0_2_x, p_0_2_y], ... ,
                                        [p_0_n-1_x, p_0_n-1_y], [p_0_n_x, p_0_n_y])
            i_velocities = an array containing the initial x and y velocities of all the objects
                        form = np.array([v_0_1_x, v_0_1_y], [v_0_2_x, v_0_2_y], ... ,
                                        [v_0_n-1_x, v_0_n-1_y], [v_0_n_x, v_0_n_y])
            t_tot = number of timesteps to integrate over (float)
            dt = timesteps (float)
            algorithm = selection of integration algorithm (string)
                        may be 'euler', 'leapfrog', 'kdk', 'rk'
                        default = 'euler'
            frame = selection of static frame or frame moving with the center of mass (string)
                    may be 'static' or 'com'
                    default = 'static'
    outputs: positions = an array containing the positions of each object
                        form = An array containing arrays for each time step which contain the
                                x and y positions for each mass, ie
            [[[p_0_1_x p_0_1_y] [p_0_2_x p_0_2_y] ... [p_0_n_x p_0_n_y]]
            [[p_1_1_x p_1_1_y] [p_1_2_x p_1_2_y] ... [p_1_n_x p_1_n_y]]
            [[p_2_1_x p_2_1_y] [p_2_2_x p_1_2_y] ... [p_2_n_x p_2_n_y]]
            ...
            [[p_n-1_1_x p_n-1_1_y] [p_n-1_2_x p_n-1_2_y] ... [p_n-1_n_x p_n-1_n_y]]
            [[p_n_1_x p_n_1_y] [p_n_2_x p_n_2_y] ... [p_n_n_x p_n_n_y]]]
            velocities = an array containing the x and y velocities of each object
                        form = An array containing arrays for each time step which contain the
                                x and y velocities for each mass, ie
            [[[v_0_1_x v_0_1_y] [v_0_2_x v_0_2_y]... [v_0_n_x v_0_n_y]]
            [[v_1_1_x v_1_1_y] [v_1_2_x v_1_2_y] ... [v_1_n_x v_1_n_y]]
            [[v_2_1_x v_2_1_y] [v_2_2_x v_1_2_y] ... [v_2_n_x v_2_n_y]]
            ...
            [[v_n-1_1_x v_n-1_1_y] [v_n-1_2_x v_n-1_2_y] ... [v_n-1_n_x v_n-1_n_y]]
            [[v_n_1_x v_n_1_y] [v_n_2_x v_n_2_y] ... [v_n_n_x v_n_n_y]]]
            times = an array containing the timesteps taken during the integration
                    form = 1d array
     */
    double n_steps_double = t_tot/dt;
    int n_steps = (int)n_steps_double;
    vector<double> times {};
    double t_i = 0.0;
    times.push_back(t_i);
    for(int i = 0; i < n_steps; i++) {
        t_i += dt;
        times.push_back(t_i);
    }

    vector<vector<valarray<double>>> positions {};
    vector<vector<valarray<double>>> velocities {};

    positions.push_back(i_positions);
    velocities.push_back(i_velocities);

    try {
        vector<string> method_list {
            "rk4-classic", "rk4-fehlberg", "rk5-fehlberg"
            };
        bool isOK = false;
        for(string meth : method_list) {
            if(method.compare(meth) == 0) {
                isOK = true;
            }
        }
        if( isOK == false) {
            throw (method);
        }
    }
    catch (string method) {
        cout << "Method not found and/or not supported: " << method << endl;
        exit (EXIT_FAILURE);
    }

    for(int i = 0; i < times.size(); i++) {
        vector<valarray<double>> x = positions.back();
        vector<valarray<double>> v = velocities.back();

        vector<vector<valarray<double>>> coeffs = butcher_tableaus_rk(method;
        int stages = coeffs[1].size();
        int n = masses.size();
        int ndim = 3;


    }

}

/*
 * #########################################################################################
 */

/* Table of Butcher coefficients */
vector<vector<valarray<double>>> butcher_tableaus_rk(string method) {
/*
 * Function to retrieve Butcher coefficients for the designated method.
 */
    int p;
    vector<vector<valarray<double>>> coeffs(4);
    vector<valarray<double>> a;
    vector<valarray<double>> b;
    vector<valarray<double>> c;
    vector<valarray<double>> tmp0;

    if (method.compare("rk4-fehlberg") == 0) {
        p = 4;
        vector<valarray<double>> a{
                {1. / 4.,       0.,            0.,            0.,           0.},
                {3. / 32.,      9. / 32.,       0.,            0.,           0.},
                {1932. / 2197., -7200. / 2197., 7296. / 2197.,  0.,           0.},
                {439. / 216.,   -8.,           3680. / 513.,   -845. / 4104., 0.},
                {-8. / 27.,     2.,           -3544. / 2565., 1859. / 4104., -11. / 40.}
        };
        vector<valarray<double>> c{
                {1. / 4., 3. / 8., 12. / 13., 1., 0.5}
        };
        vector<valarray<double>> b{
                {25. / 216., 0., 1408. / 2565., 2197. / 4104., -0.2, 0.}
        };
    } // rk4-fehlberg

    else if (method.compare("rk5-fehlberg") == 0) {
        p = 5;
        vector<valarray<double>> a{
                {1. / 4.,       0.,            0.,            0.,           0.},
                {3. / 32.,      9. / 32.,       0.,            0.,           0.},
                {1932. / 2197., -7200. / 2197., 7296. / 2197.,  0.,           0.},
                {439. / 216.,   -8.,           3680. / 513.,   -845. / 4104., 0.},
                {-8. / 27.,     2.,           -3544. / 2565., 1859. / 4104., -11. / 40.}
        };
        vector<valarray<double>> c{
                {1. / 4., 3. / 8., 12. / 13., 1., 0.5}
        };
        vector<valarray<double>> b{
                {16. / 135., 0., 6656. / 12825., 28561. / 56430., -9. / 50., 2. / 55.}
        };
    } // rk5-fehlberg

    else if (method.compare("rk4-classic") == 0) {
        p = 4;
        vector<valarray<double>> a{
                {.5, 0.,  0.},
                {0.,  .5, 0.},
                {0.,  0.,  1.},
        };
        vector<valarray<double>> c{
                {0., 1. / 2., 1. / 2., 1.}
        };
        vector<valarray<double>> b{
                {1. / 6., 1. / 3., 1. / 3., 1. / 6.}
        };
    } // rk4-classic

    else {
        printf("%s order not found\n", method.c_str());
        exit(EXIT_FAILURE); // exits the code
    }

    valarray<double> tmp1{static_cast<double>(p)};

    tmp0.push_back(tmp1);

    // add each coeff. vector to the appropriate place
    coeffs[0] = a;
    coeffs[1] = b;
    coeffs[2] = c;
    coeffs[3] = tmp0;

    delete &a;
    delete &b;
    delete &c;
    delete &p;

    return coeffs;
}