//
// Created by hecook on 4/29/21.
//


#ifndef REYNOLDS_GROUP_INTEGRATOR_INTEGRATOR_H
#define REYNOLDS_GROUP_INTEGRATOR_INTEGRATOR_H

#include "valarray_updates.h"
#include <vector>
#include "integrator.h"
#include "valarray_updates.h"


using namespace std;

struct OrbitData {
    vector<vector<valarray<double>>> pos;
    vector<vector<valarray<double>>> vel;
    vector<double> times;
};

OrbitData integrator(valarray<double> masses, vector<valarray<double>> i_positions, vector<valarray<double>> i_velocities,
           double t_tot, double dt, string method, string frame);

vector<vector<valarray<double>>> butcher_tableaus_rk(string method);

#endif //REYNOLDS_GROUP_INTEGRATOR_INTEGRATOR_H

