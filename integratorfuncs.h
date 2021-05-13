//
// Created by Audrey Dijeau on 4/29/21.
//

#ifndef REYNOLDS_GROUP_INTEGRATOR_INTEGRATORFUNCS_H
#define REYNOLDS_GROUP_INTEGRATOR_INTEGRATORFUNCS_H

#include <iostream>
#include <valarray>
#include "valarray_updates.h"
#include <vector>
#include <ctime>
#include <cmath>
#include <string>
#include "constants.h"

using namespace std;

vector<valarray<double>> accelerations(vector<valarray<double>> masses, vector<valarray<double>> positions);

vector<vector<valarray<double>>> ode(vector<valarray<double>> masses, vector<valarray<double>> positions,
        vector<valarray<double>> velocities, vector<valarray<double>> time);

#endif //REYNOLDS_GROUP_INTEGRATOR_INTEGRATORFUNCS_H