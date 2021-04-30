//
// Created by hecook on 4/29/21.
//

#include "integrator.h"
#include "constants.h"
#include "valarray_updates.h"
#include <iostream>
#include <valarray>
#include <cmath>
#include <vector>
#include <ctime>
#include <string>

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

    if (method == "rk4-fehlberg") {
        p = 4;
        vector<valarray<double>> a{
                {1 / 4,       0,            0,            0,           0},
                {3 / 32,      9 / 32,       0,            0,           0},
                {1932 / 2197, -7200 / 2197, 7296 / 2197,  0,           0},
                {439 / 216,   -8,           3680 / 513,   -845 / 4104, 0},
                {-8 / 27,     2.,           -3544 / 2565, 1859 / 4104, -11 / 40}
        };
        vector<valarray<double>> c{
                {1 / 4, 3 / 8, 12 / 13, 1., 0.5}
        };
        vector<valarray<double>> b{
                {25 / 216, 0, 1408 / 2565, 2197 / 4104, -0.2, 0}
        };
    } // rk4-fehlberg

    else if (method == "rk5-fehlberg") {
        p = 5;
        vector<valarray<double>> a{
                {1 / 4,       0,            0,            0,           0},
                {3 / 32,      9 / 32,       0,            0,           0},
                {1932 / 2197, -7200 / 2197, 7296 / 2197,  0,           0},
                {439 / 216,   -8,           3680 / 513,   -845 / 4104, 0},
                {-8 / 27,     2.,           -3544 / 2565, 1859 / 4104, -11 / 40}
        };
        vector<valarray<double>> c{
                {1 / 4, 3 / 8, 12 / 13, 1., 0.5}
        };
        vector<valarray<double>> b{
                {16 / 135, 0, 6656 / 12825, 28561 / 56430, -9 / 50, 2 / 55}
        };
    } // rk5-fehlberg

    else if (method == "rk4-classic") {
        p = 4;
        vector<valarray<double>> a{
                {.5, 0,  0},
                {0,  .5, 0},
                {0,  0,  1},
        };
        vector<valarray<double>> c{
                {0, 1 / 2, 1 / 2, 1}
        };
        vector<valarray<double>> b{
                {1 / 6, 1 / 3, 1 / 3, 1 / 6}
        };
    } // rk4-classic

    else {
        printf("%s order not found\n", method.c_str());
        exit(EXIT_FAILURE); // exits the code
    }

    valarray<double> tmp1{p};

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