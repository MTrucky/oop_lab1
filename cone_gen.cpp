/**
 * @file cone_gen.cpp
 * @brief Реализация методов класса ConeGen
 */

#include "cone_gen.h"
#include <fstream>
#include <cmath>
#include <sstream>
#include <random>
#include <ctime>

ConeGen::ConeGen(double r, double h, const point3d& c) 
    : radius(r), height(h), center(c) {}

void ConeGen::rnd(point3d* p) {
    if (p == nullptr) return;

    static std::mt19937 gen(time(0));
    
    // Генерация высоты
    std::uniform_real_distribution<> distZ(0, height);
    double z = distZ(gen);
    
    // Максимальный радиус на высоте z
    double maxRadius = radius * (1 - z / height);

    // Генерация угла
    std::uniform_real_distribution<> distAngle(0, 2 * M_PI);
    double angle = distAngle(gen);

    // Генерация радиуса
    std::uniform_real_distribution<> distRadius(0, maxRadius);
    double r_val = distRadius(gen);

    // Преобразование в декартовы координаты
    p->x = center.x + r_val * cos(angle);
    p->y = center.y + r_val * sin(angle);
    p->z = center.z + z;
}

void ConeGen::setParams(double r, double h, const point3d& c) {
    radius = r;
    height = h;
    center = c;
}

std::string ConeGen::getParams() const {
    std::ostringstream oss;
    oss << "Конус: радиус=" << radius << ", высота=" << height 
        << ", центр=(" << center.x << ", " << center.y << ", " << center.z << ")";
    return oss.str();
}

void ConeGen::saveSet(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << radius << " " << height << " " 
             << center.x << " " << center.y << " " << center.z;
        file.close();
    }
}