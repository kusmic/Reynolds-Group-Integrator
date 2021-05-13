//
// Created by Audrey Dijeau on 4/29/21.
//

#ifndef REYNOLDS_GROUP_INTEGRATOR_INTEGRATORFUNCS_H
#define REYNOLDS_GROUP_INTEGRATOR_INTEGRATORFUNCS_H

#include <iostream>
#include <valarray>
//#include "valarray_updates.h"
#include <vector>
#include <ctime>
#include <cmath>
#include <string>
//#include "constants.h"
#include <numeric>

using namespace std;

vector<vector<valarray<double>>> com_shift(valarray<double> m, vector<valarray<double>> p, vector<valarray<double>> v);

vector<valarray<double>> accelerations(valarray<double> masses, vector<valarray<double>> positions);

vector<vector<valarray<double>>> ode(valarray<double> masses, vector<valarray<double>> positions,
                                     vector<valarray<double>> velocities, double time);

#endif //REYNOLDS_GROUP_INTEGRATOR_INTEGRATORFUNCS_H