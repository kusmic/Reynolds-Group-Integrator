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
#include "integratorfuncs.h"

using namespace std;

/* Integrator Function */

OrbitData integrator(valarray<double> masses, vector<valarray<double>> i_positions, vector<valarray<double>> i_velocities,
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
            "kdk", "rk4-classic", "rk4-fehlberg", "rk5-fehlberg"
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

    if(method.compare("kdk") == 0) {
        vector<valarray<double>> x = positions.back();
        vector<valarray<double>> v = velocities.back();

        vector<valarray<double>> acc_0 = accelerations(masses, x);
        for(int ti = 0; ti < times.size(); ti++) {
            //cout << ti << endl;
            vector<valarray<double>> v_half{};
            for (int i = 0; i < v.size(); i++) {
                valarray<double> v_t {0., 0., 0.};
                for(int vi = 0; vi < v[i].size(); vi++) {
                    v_t[vi] = v[i][vi] + acc_0[i][vi] * (dt / 2.0);
                }
                // cout << v_t[0] << ", " << v[i][0] << ", " << acc_0[i][0] << endl;

                v_half.push_back(valarray<double> {0., 0., 0.});
                for(int vi = 0; vi < v[i].size(); vi++) {
                    v_half[i][vi] = v_t[vi];
                }
            }
            vector<valarray<double>> pos{};
            for (int i = 0; i < x.size(); i++) {
                pos.push_back(x[i] + v_half[i] * dt);
            }
            vector<valarray<double>> acc_1 = accelerations(masses, pos);
            vector<valarray<double>> vel{};
            for (int i = 0; i < v.size(); i++) {
                vel.push_back(v_half[i] + acc_1[i] * (dt / 2.0));
            }

            if (frame.compare("com") == 0) {
                vector<vector<valarray<double>>> temp_com = com_shift(masses, pos, vel);
                pos = temp_com[0];
                vel = temp_com[1];
            }
            positions.push_back(x);
            velocities.push_back(v);
        }
    }

    else if(method.compare("rk4-classic") == 0 || method.compare("rk4-fehlberg") == 0 || method.compare("rk5-fehlberg") == 0) {
        for (int ti = 0; ti < times.size(); ti++) {
            vector<valarray<double>> x = positions.back();
            vector<valarray<double>> v = velocities.back();

            vector<vector<valarray<double>>> coeffs = butcher_tableaus_rk(method);
            vector<valarray<double>> a = {coeffs[0]};
            vector<valarray<double>> b{coeffs[1].begin(), coeffs[1].end()};

            int stages = coeffs[1].size();
            int n = masses.size();
            int n_dimensions = 3;

            valarray<double> tmp0{0., 0., 0.};
            vector<valarray<double>> tmp1;
            for (int i = 0; i < n; i++) {
                tmp1.push_back(tmp0);
                tmp1[i] = tmp0;
            }

            vector<vector<valarray<double>>> kx;
            vector<vector<valarray<double>>> kv;
            for (int i = 0; i < stages; i++) {

                kx.push_back(tmp1);
                kv.push_back(tmp1);
            }

            vector<valarray<double>> x0(x.begin(), x.end());
            vector<valarray<double>> v0(v.begin(), v.end());

            vector<vector<valarray<double>>> temp_ode = ode(masses, x0, v0, times[ti]);
            kx[0] = temp_ode[0];
            kv[0] = temp_ode[1];
            for (int ii = 1; ii < stages; ii++) {
                vector<valarray<double>> x_aux = tmp1;
                vector<valarray<double>> v_aux = tmp1;
                for (int jj = 0; jj < ii; jj++) {
                    for (int i = 0; i < x_aux.size(); i++) {
                        x_aux[i] += coeffs[0][ii - 1][jj] * kx[jj][i];
                        v_aux[i] += coeffs[0][ii - 1][jj] * kx[jj][i];
                    }
                    vector<valarray<double>> x0_new = x0;
                    vector<valarray<double>> v0_new = v0;
                    for (int i = 0; i < x0_new.size(); i++) {
                        x0_new[i] = x0[i] + x_aux[i] * dt;
                        v0_new[i] = v0[i] + v_aux[i] * dt;
                    }
                    temp_ode = ode(masses, x0_new, v0_new, times[ti]);
                }

                x_aux = tmp1;
                v_aux = tmp1;
                for (int ii = 0; ii < stages; ii++) {
                    for (int i = 0; i < x_aux.size(); i++) {
                        x_aux[i] = coeffs[1][ii][i] * kx[ii][i];
                        v_aux[i] = coeffs[1][ii][i] * kv[ii][i];
                    }
                }

                for (int i = 0; i < x.size(); i++) {
                    x[i] = x0[i] + x_aux[i] * dt;
                    v[i] = v0[i] + v_aux[i] * dt;
                }

                if (frame.compare("com") == 0) {
                    vector<vector<valarray<double>>> temp_com = com_shift(masses, x, v);
                    x = temp_com[0];
                    v = temp_com[1];
                }
            }
            positions.push_back(x);
            velocities.push_back(v);
        }
    }
    OrbitData returnValue;
    returnValue.pos = positions;
    returnValue.vel = velocities;
    returnValue.times = times;

    return returnValue;
}

/*
 * #########################################################################################
 */


//vector<vector<vector<double>>> integrator(vector<valarray<double>> m, vector<valarray<double>> i_positions,
//                                          vector<valarray<double>> i_velocities, vector<valarray<double>> t_tot,
//                                          vector<valarray<double>> dt, string frame) {
//
//    int nsteps = (int)(t_tot / dt);
//    float times;
//
//    times = [n_steps];
//
//    times = np.arange(0, t_tot, dt, dtype=np.float_)
//    positions = []
//    velocities = []
//// populate with intitial values
//    positions.append(i_positions)
//    velocities.append(i_velocities)
//}




/* Table of Butcher coefficients */
vector<vector<valarray<double>>> butcher_tableaus_rk(string method) {
/*
 * Function to retrieve Butcher coefficients for the designated method.
 */
    vector<vector<valarray<double>>> coeffs;
    vector<valarray<double>> a;
    vector<valarray<double>> b;

    if (method.compare("rk4-fehlberg") == 0) {
        // p = 4;
        valarray<double> a0 {1. / 4.,       0.,            0.,            0.,           0.};
        valarray<double> a1 {3. / 32.,      9. / 32.,       0.,            0.,           0.};
        valarray<double> a2 {1932. / 2197., -7200. / 2197., 7296. / 2197.,  0.,           0.};
        valarray<double> a3 {439. / 216.,   -8.,           3680. / 513.,   -845. / 4104., 0.};
        valarray<double> a4 {-8. / 27.,     2.,           -3544. / 2565., 1859. / 4104., -11. / 40.};

        a.push_back(a0);
        a.push_back(a1);
        a.push_back(a2);
        a.push_back(a3);
        a.push_back(a4);
        /*vector<valarray<double>> c{
                {1. / 4., 3. / 8., 12. / 13., 1., 0.5}
        };*/
        valarray<double> b0 {25. / 216., 0., 1408. / 2565., 2197. / 4104., -0.2, 0.};
        b.push_back(b0);
    } // rk4-fehlberg

    else if (method.compare("rk5-fehlberg") == 0) {
        //p = 5;
        valarray<double> a0 {1. / 4.,       0.,            0.,            0.,           0.};
        valarray<double> a1 {3. / 32.,      9. / 32.,       0.,            0.,           0.};
        valarray<double> a2 {1932. / 2197., -7200. / 2197., 7296. / 2197.,  0.,           0.};
        valarray<double> a3 {439. / 216.,   -8.,           3680. / 513.,   -845. / 4104., 0.};
        valarray<double> a4 {-8. / 27.,     2.,           -3544. / 2565., 1859. / 4104., -11. / 40.};

        a.push_back(a0);
        a.push_back(a1);
        a.push_back(a2);
        a.push_back(a3);
        a.push_back(a4);
        //vector<valarray<double>> c{
        //        {1. / 4., 3. / 8., 12. / 13., 1., 0.5}
        //};
        valarray<double> b0 {16. / 135., 0., 6656. / 12825., 28561. / 56430., -9. / 50., 2. / 55.};
        b.push_back(b0);
    } // rk5-fehlberg

    else if (method.compare("rk4-classic") == 0) {
        //p = 4;
        valarray<double> a0 {.5, 0.,  0.};
        valarray<double> a1 {0.,  .5, 0.};
        valarray<double> a2 {0.,  0.,  1.};

        a.push_back(a0);
        a.push_back(a1);
        a.push_back(a2);
        //vector<valarray<double>> c{
        //        {0., 1. / 2., 1. / 2., 1.}
        //};
        valarray<double> b0 {1. / 6., 1. / 3., 1. / 3., 1. / 6.};
        b.push_back(b0);
    } // rk4-classic

    else {
        printf("%s order not found\n", method.c_str());
        exit(EXIT_FAILURE); // exits the code
    }

    //valarray<double> tmp1{static_cast<double>(p)};

    //tmp0.push_back(tmp1);

    // add each coeff. vector to the appropriate place
    coeffs.push_back(a);
    coeffs.push_back(b);

    return coeffs;
}