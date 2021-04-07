//
// Created by samir on 4/6/2021.
//

#ifndef REYNOLDS_GROUP_INTEGRATOR_NDARRAY_H
#define REYNOLDS_GROUP_INTEGRATOR_NDARRAY_H

#include <vector>
#include <cmath>

using namespace std;

template<typename T>
class ndarray : public std::vector<T>{};

template<typename T>
ndarray<float> operator+(ndarray<float> a, ndarray<float> b);

template<typename T>
ndarray<T> operator-(ndarray<T> a, ndarray<T> b);

template<typename T>
ndarray<T> operator*(ndarray<T> a, ndarray<T> b);

template<typename T>
ndarray<T> operator/(ndarray<T> a, ndarray<T> b);

template<typename T>
ndarray<T> pow(ndarray<T> a, T b);

template<typename T>
ndarray<T> pow(ndarray<T> a, ndarray<T> b);

#endif //REYNOLDS_GROUP_INTEGRATOR_NDARRAY_H
