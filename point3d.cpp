/**
 * @file point3d.cpp
 * @brief Реализация методов структуры point3d
 */

#include "point3d.h"
#include <iostream>

point3d::point3d(double x, double y, double z) : x(x), y(y), z(z) {}

void point3d::print() const {
    std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}

double point3d::getBackX() const { return x; }
double point3d::getBackY() const { return y; }
double point3d::getBackZ() const { return z; }