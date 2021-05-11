//
// Created by samir on 4/8/2021.
//

#include <valarray>
#include "valarray_updates.h"

valarray<double> operator*(valarray<double> a, long double b) {
    int size = a.size();
    valarray<double> result(a);
    for (int i = 0; i < size; i++) {
        result[i] = a[i] * (double) b;
    }
    return result;
}

valarray<double> operator+(valarray<double> a, long double b) {
    int size = a.size();
    valarray<double> result(a);
    for (int i = 0; i < size; i++) {
        result[i] = a[i] + (double) b;
    }
    return result;
}

valarray<double> operator-(valarray<double> a, long double b) {
    int size = a.size();
    valarray<double> result(a);
    for (int i = 0; i < size; i++) {
        result[i] = a[i] - (double) b;
    }
    return result;
}

valarray<double> operator/(valarray<double> a, long double b) {
    int size = a.size();
    valarray<double> result(a);
    for (int i = 0; i < size; i++) {
        result[i] = a[i] / (double) b;
    }
    return result;
}

template<typename T1, typename T2>
valarray<T1> operator*(valarray<T1> a, T2 b) {
    int size = a.size();
    valarray<T1> result(a);
    for (int i = 0; i < size; i++) {
        result[i] = a[i] * (T1) b;
    }
    return result;
}

template<typename T1, typename T2>
valarray<T1> operator+(valarray<T1> a, T2 b) {
    int size = a.size();
    valarray<T1> result(a);
    for (int i = 0; i < size; i++) {
        result[i] = a[i] + (T1) b;
    }
    return result;
}

template<typename T1, typename T2>
valarray<T1> operator-(valarray<T1> a, T2 b) {
    int size = a.size();
    valarray<T1> result(a);
    for (int i = 0; i < size; i++) {
        result[i] = a[i] - (T1) b;
    }
    return result;
}

template<typename T1, typename T2>
valarray<T1> operator/(valarray<T1> a, T2 b) {
    int size = a.size();
    valarray<T1> result(a);
    for (int i = 0; i < size; i++) {
        result[i] = a[i] / (T1) b;
    }
    return result;
}