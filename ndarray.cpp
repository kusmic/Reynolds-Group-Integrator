//
// Created by samir on 4/6/2021.
//

#include "ndarray.h"
#include <iostream>

template<typename T>
ndarray<T> operator+(ndarray<T> a, ndarray<T> b)
{
    try
    {
        if (a.size() != b.size())
        {
            throw ;
        }
        int max = a.size();
        for (int i = 0; i < max; i++)
        {
            std::cout << "yay" << std::endl;
        }
    }
    catch (const char* msg)
    {
        std::cout << msg << a.size() << ", " << b.size() << std::endl;
    }
}