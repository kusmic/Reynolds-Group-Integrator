//
// Created by samir on 4/8/2021.
//

#ifndef REYNOLDS_GROUP_INTEGRATOR_VALARRAY_UPDATES_H
#define REYNOLDS_GROUP_INTEGRATOR_VALARRAY_UPDATES_H
#include <valarray>

using namespace std;

/*
 * first the simple operators
 */

// I can't for the love of all dieties get doubles to multiply with long doubles with valarrays
// if you can find a solution, please implement
valarray<double> operator*(valarray<double> a, long double b);
valarray<double> operator+(valarray<double> a, long double b);
valarray<double> operator-(valarray<double> a, long double b);
valarray<double> operator/(valarray<double> a, long double b);

template<typename T1, typename T2>
valarray<T1> operator*(valarray<T1> a, T2 b);

template<typename T1, typename T2>
valarray<T1> operator+(valarray<T1> a, T2 b);

template<typename T1, typename T2>
valarray<T1> operator-(valarray<T1> a, T2 b);

template<typename T1, typename T2>
valarray<T1> operator/(valarray<T1> a, T2 b);


#endif //REYNOLDS_GROUP_INTEGRATOR_VALARRAY_UPDATES_H
