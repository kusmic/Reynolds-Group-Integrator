#include <iostream>
#include <valarray>
#include <cmath>
#include "constants.h"
#include "valarray_updates.h"

using namespace std;

int main()
{
    valarray<long double> test1 {1.0, 2.0, 3.0};

    valarray<long double> test = test1 / pi;
    for(double x : test)
    {
        printf("%.8f ", x);
    }
    printf("\n");
    test = pi / test1;
    for(double x : test)
    {
        printf("%.8f ", x);
    }
    return 0;
}
