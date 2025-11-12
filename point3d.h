/**
 * @file point3d.h
 * @brief Заголовочный файл структуры point3d
 * @author Perevozchikov M
 * @date 2025
 */

 #ifndef POINT3D_H
 #define POINT3D_H
 
 #include <cmath>
 
 /**
  * @brief Структура для хранения точки в 3D пространстве
  * 
  * Структура хранит координаты точки в трехмерном пространстве
  * и предоставляет методы для работы с ними.
  */
 struct point3d
 {  
     double x; ///< Координата X
     double y; ///< Координата Y  
     double z; ///< Координата Z
 
     /**
      * @brief Конструктор по умолчанию
      * @param x Координата X (по умолчанию 0.0)
      * @param y Координата Y (по умолчанию 0.0)
      * @param z Координата Z (по умолчанию 0.0)
      */
     point3d(double x=0.0, double y=0.0, double z=0.0);
 
     /**
      * @brief Выводит координаты точки на экран
      * 
      * Формат вывода: (x, y, z)
      */
     void print() const;
 
     /**
      * @brief Возвращает координату X
      * @return Координата X
      */
     double getBackX() const;
 
     /**
      * @brief Возвращает координату Y
      * @return Координата Y
      */
     double getBackY() const;
 
     /**
      * @brief Возвращает координату Z
      * @return Координата Z
      */
     double getBackZ() const;
 
     // Новые методы для векторных операций
     
     /**
      * @brief Вычисляет длину вектора
      * @return Длина вектора
      */
     double length() const;
     
     /**
      * @brief Нормализует вектор (делает длину = 1)
      * @return Нормализованный вектор
      */
     point3d normalize() const;
     
     /**
      * @brief Вращает точку вокруг оси на заданный угол
      * @param axis Ось вращения
      * @param angle Угол в радианах
      * @return Вращенная точка
      */
     point3d rotate(const point3d& axis, double angle) const;
     
     /**
      * @brief Векторное произведение
      * @param other Второй вектор
      * @return Векторное произведение
      */
     point3d cross(const point3d& other) const;
     
     /**
      * @brief Скалярное произведение
      * @param other Второй вектор
      * @return Скалярное произведение
      */
     double dot(const point3d& other) const;
     
     // Операторы
     point3d operator+(const point3d& other) const;
     point3d operator-(const point3d& other) const;
     point3d operator*(double scalar) const;
     point3d operator/(double scalar) const;
 };
 
 #endif