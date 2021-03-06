//
// Created by samir on 5/13/2021.
//

#include <iomanip>
#include <iostream>
#include <fstream>
#include <valarray>
#include "integrator.h"
#include <vector>
#include <ctime>
#include <string>
#include "constants.h"

;using namespace std; // I have no clue where the semi-colon in the beginning is suppose to belong....

int main() {
    /*
     * Hard-coding in the solar system parameters
     * The order of the indices for each planet should follow:
     * {Sun, Mercury, Venus, Earth, Mars, Jupiter, Saturn, Uranus, Neptune}
     */

    // first the mass rations w.r.t. the Sun
    double M_Sol_toSun = G_AU_day_normMsun * 1.0;
    double M_Mer_toSun = G_AU_day_normMsun * 3.302e23 / Msun;
    double M_Ven_toSun = G_AU_day_normMsun * 4.8685e24 / 408523.72;
    double M_Ear_toSun = G_AU_day_normMsun * 5.97219e24 / Msun;
    double M_Mar_toSun = G_AU_day_normMsun * 6.4171e23 / Msun;
    double M_Jup_toSun = G_AU_day_normMsun * 1.89818722e27 / Msun;
    double M_Sat_toSun = G_AU_day_normMsun * 5.6834e26 / Msun;
    double M_Ura_toSun = G_AU_day_normMsun * 8.6813e25 / Msun;
    double M_Nep_toSun = G_AU_day_normMsun * 1.02409e26 / Msun;
    double M_Plu_toSun = G_AU_day_normMsun * 1.307e22 / Msun;

    valarray<double> masses_all {M_Sol_toSun, M_Mer_toSun, M_Ven_toSun, M_Ear_toSun, M_Mar_toSun,
                                 M_Jup_toSun, M_Sat_toSun, M_Ura_toSun, M_Nep_toSun, M_Plu_toSun};

    // now doing positions and velocities for each object, 5-14-2021 at 00:00:00.0000 TDB

    valarray<double> x_Sol { -7.489689731123352e-3, 5.162107224601347e-3, 1.327885703674413e-4};
    valarray<double> v_Sol { -5.794676528175743e-6, -6.922128148181264e-6, 1.920916676735994e-7};

    valarray<double> x_Mer { -3.635454439473201e-1, 9.260451636577180e-2, 3.993938396799459e-2};
    valarray<double> v_Mer { -1.254539179951032e-2, -2.612441538922992e-2, -9.837843145708127e-4};

    valarray<double> x_Ven { 9.270102588777503e-2, 7.182913080816696e-1, 4.138071540348071e-3};
    valarray<double> v_Ven { -2.010393965517645e-2, 2.703997860114793e-3, 1.197167065432414e-3};

    valarray<double> x_Ear { -6.271227786950516e-1, -7.929760388072012e-1, 1.727451815209775e-4};
    valarray<double> v_Ear { 1.330976858377612e-2, -1.062466962084262e-2,  3.401068733653035e-8};

    valarray<double> x_Mar { -1.051698762478201, 1.278668935096419, 5.243532537981634e-2};
    valarray<double> v_Mar { -1.029969744515465e-2, -7.688607341109127e-3, 9.172674936482014e-5 };

    valarray<double> x_Jup { 3.757204642356236, -3.364874497628962, -7.009879964964759e-2 };
    valarray<double> v_Jup { 4.942067862047172e-3, 5.977525972512466e-3, -1.353446060559466e-4 };

    valarray<double> x_Sat { 6.043092457264607, -7.911857988316727, -1.030251709449136e-1 };
    valarray<double> v_Sat { 4.121139275154733e-3, 3.373725099865320e-3, -2.228408331292618e-4 };

    valarray<double> x_Ura { 1.500707592828585e1, 1.284212851611610e1, -1.467233448652270e-1 };
    valarray<double> v_Ura { -2.586151773268411e-3, 2.805085708088122e-3, 4.395599401307332e-5 };

    valarray<double> x_Nep { 2.952067411922501e+1, -4.814875740817373, -5.811806274667526e-1 };
    valarray<double> v_Nep { 4.849459207122563e-4, 3.116869763952191e-3, -7.566040325729129e-5 };

    valarray<double> x_Plu { 1.444046169148815e+1, -3.106882087151637e+1, -8.524956483369166e-1 };
    valarray<double> v_Plu { 2.915438611783105e-3, 6.497085231385701e-04, -9.015485579873926e-4 };

    vector<valarray<double>> x_all {x_Sol, x_Mer, x_Ven, x_Ear, x_Mar, x_Jup, x_Sat, x_Ura, x_Nep, x_Plu};
    vector<valarray<double>> v_all {v_Sol, v_Mer, v_Ven, v_Ear, v_Mar, v_Jup, v_Sat, v_Ura, v_Nep, v_Plu};

    double t_end = 1 * 365.25; // time in days
    double dt = 0.1; //days, this can be debated
    string method = "kdk";
    string frame = "com";

    time_t starttime = time(0);
    OrbitData SolSys_data = integrator(masses_all, x_all, v_all, t_end, dt, method, frame);

    double integrator_time = difftime(time(0), starttime);

    cout << integrator_time << endl;

    ofstream outfile;
    outfile.open("mercury_test.csv");

    outfile << "t,x,y,z,vx,xy,vz,buffer" << endl;

    // cout << SolSys_data.vel.size() << endl;
    int n_prec = 15;
    for(int i = 0; i < SolSys_data.times.size(); i++) {
        outfile << setprecision(n_prec) << SolSys_data.times[i] << ","; // i index is in time, times[i] should be time of pos and vel
        for(int xi = 0; xi < SolSys_data.pos[i][1].size(); xi++) {
            outfile << setprecision(n_prec) << SolSys_data.pos[i][1][xi] << ","; // x, y, z
        }
        for(int vi = 0; vi < SolSys_data.vel[i][1].size(); vi++) {
            outfile << setprecision(n_prec) << SolSys_data.vel[i][1][vi] << ",";
        }
        outfile << " " << endl;
    }

    outfile.close();

    return 0;
}
