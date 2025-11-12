/**
 * @file point3d.cpp
 * @brief Реализация методов структуры point3d
 * @author Perevozchikov M
 * @date 2025
 */

 #include "point3d.h"
 #include <iostream>
 #include <cmath>
 
 /**
  * @brief Конструктор структуры point3d
  * @param x Координата X
  * @param y Координата Y
  * @param z Координата Z
  */
 point3d::point3d(double x, double y, double z) : x(x), y(y), z(z) {}
 
 /**
  * @brief Выводит координаты точки на экран
  */
 void point3d::print() const {
    std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
 }
 
 /**
  * @brief Возвращает координату X
  * @return Координата X
  */
 double point3d::getBackX() const { return x; }
 
 /**
  * @brief Возвращает координату Y
  * @return Координата Y
  */
 double point3d::getBackY() const { return y; }
 
 /**
  * @brief Возвращает координату Z
  * @return Координата Z
  */
 double point3d::getBackZ() const { return z; }
 
 /**
  * @brief Вычисляет длину вектора
  * @return Длина вектора
  */
 double point3d::length() const {
     return std::sqrt(x*x + y*y + z*z);
 }
 
 /**
  * @brief Нормализует вектор (делает длину = 1)
  * @return Нормализованный вектор
  */
 point3d point3d::normalize() const {
     double len = length();
     if (len == 0) return point3d(0, 0, 0);
     return point3d(x/len, y/len, z/len);
 }
 
 /**
  * @brief Вращает точку вокруг оси на заданный угол
  * @param axis Ось вращения
  * @param angle Угол в радианах
  * @return Вращенная точка
  */
 point3d point3d::rotate(const point3d& axis, double angle) const {
     double len = axis.length();
     if (len == 0) return *this; // Если ось нулевая - возвращаем исходную точку
     
     point3d u = axis.normalize();
     double cos_a = std::cos(angle);
     double sin_a = std::sin(angle);
     
     // Формула Родрига
     point3d result = (*this) * cos_a + 
                     u.cross(*this) * sin_a + 
                     u * (u.dot(*this)) * (1 - cos_a);
     
     return result;
 }
 
 /**
  * @brief Векторное произведение
  * @param other Второй вектор
  * @return Векторное произведение
  */
 point3d point3d::cross(const point3d& other) const {
     return point3d(
         y * other.z - z * other.y,
         z * other.x - x * other.z,
         x * other.y - y * other.x
     );
 }
 
 /**
  * @brief Скалярное произведение
  * @param other Второй вектор
  * @return Скалярное произведение
  */
 double point3d::dot(const point3d& other) const {
     return x * other.x + y * other.y + z * other.z;
 }
 
 // Операторы
 point3d point3d::operator+(const point3d& other) const {
     return point3d(x + other.x, y + other.y, z + other.z);
 }
 
 point3d point3d::operator-(const point3d& other) const {
     return point3d(x - other.x, y - other.y, z - other.z);
 }
 
 point3d point3d::operator*(double scalar) const {
     return point3d(x * scalar, y * scalar, z * scalar);
 }
 
 point3d point3d::operator/(double scalar) const {
     return point3d(x / scalar, y / scalar, z / scalar);
 }