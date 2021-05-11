#include <iostream>
#include <valarray>
#include "valarray_updates.h"
#include <vector>
#include <ctime>
#include <string>
#include "constants.h"

using namespace std;

int main() {
    /* Here is an example of constructing our specific vectors to get (x,y,z) for each object in each timestep.
     * This is an example way to initialize the array, just using random double values in [0,1].
     * Also this is a great way to do multi-line comments.
    */
    srand(time(NULL)); // just seeding the RNG

    vector<vector<valarray<double> > > test_main{}; // the main array, this is how to initialize empty vector
    int N_array = 3; // test number for amount of timesteps
    int N_obj = 5; // test number for amount of objects
    int N_cart = 3; // amount of cartesian coordinate elements; i.e. x, y, and z
    for (int i = 0; i < N_array; i++) // looping all timesteps
    {
        vector<valarray<double> > temp_sub{}; // temporary vector that will be appended to main array
        for (int j = 0; j < N_obj; j++) // looping through all objects
        {
            valarray<double> temp_doub(N_cart); // making temporary valarray to add to temporary
            // this is how you initialize a valarray of a specific size, starting with all elements as 0

            for (int k = 0; k < (int) temp_doub.size(); k++) // looping through all indices available
            {
                temp_doub[k] = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 1000.0)); // just a
                // random number generator, random number for valarray at element k
            }
            valarray<double> temp_idk;
            temp_idk = temp_doub + pi; // can't do *= or other self-changing operator for valarrays for now
            // should be able to do operations between valarrays and scalars like with numpy's ndarray
            temp_sub.push_back(temp_idk); // appending valarray to end of sub vector
            delete &temp_doub; // deleting temporary valarray for memory conservation
        }
        test_main.push_back(temp_sub); // appending sub vector to main vector
        delete &temp_sub; // deleting temporary sub vector for memory conservation
    }
    // now to print our results
    cout << "We can get a specific element:" << endl;
    cout << test_main[0][0][0] << endl;
    cout << "And the whole main array if needed:" << endl;
    for (vector<valarray<double>> x : test_main) {
        printf("-------------------------------------------------------\n");
        for (valarray<double> y : x) {
            for (double z : y) {
                printf("%.6f ", z);
            }
            printf("\n");
        }
    }
    return 0;
}



/*
 * #########################################################################################
 */

/* Integrator function */

