//
// Created by hecook on 4/29/21.
//


#ifndef REYNOLDS_GROUP_INTEGRATOR_INTEGRATOR_H
#define REYNOLDS_GROUP_INTEGRATOR_INTEGRATOR_H

#include "valarray_updates.h"

#include "integrator.h"
#include "valarray_updates.h"


using namespace std;

vector<vector<valarray<double>>> butcher_tableaus_rk(string method);

#endif //REYNOLDS_GROUP_INTEGRATOR_INTEGRATOR_H

