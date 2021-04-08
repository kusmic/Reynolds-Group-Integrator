//
// Created by samir on 4/8/2021.
//

#ifndef REYNOLDS_GROUP_INTEGRATOR_VALARRAY_UPDATES_H
#define REYNOLDS_GROUP_INTEGRATOR_VALARRAY_UPDATES_H
#include <valarray>

using namespace std;

// first the simple operators
template<class T1, typename T2>
valarray<T1> operator*(valarray<T1> a, T2 b);
template<class T1, typename T2>
valarray<T1> operator+(valarray<T1> a, T2 b);
template<class T1, typename T2>
valarray<T1> operator-(valarray<T1> a, T2 b);
template<class T1, typename T2>
valarray<T1> operator/(valarray<T1> a, T2 b);


#endif //REYNOLDS_GROUP_INTEGRATOR_VALARRAY_UPDATES_H
