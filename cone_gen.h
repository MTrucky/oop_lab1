/**
 * @file cone_gen.h
 * @brief Заголовочный файл класса ConeGen
 * @author Perevozchikov M
 * @date 2025
 */

#ifndef CONE_GEN_H
#define CONE_GEN_H

#include "point3d.h"
#include <string>

/**
 * @brief Класс для генерации случайных точек внутри конуса
 * 
 * Класс генерирует точки, равномерно распределенные внутри заданного конуса.
 * Конус задается радиусом основания, высотой, координатами центра основания и нормалью.
 * Нормаль - вектор направления от основания к вершине конуса.
 * 
 * Система координат:
 * - Ось X: вправо (→)
 * - Ось Y: вперед (↑) 
 * - Ось Z: вверх (⬆)
 */
class ConeGen {
private:
    double radius;  ///< Радиус основания конуса
    double height;  ///< Высота конуса
    point3d center; ///< Центр основания конуса
    point3d normal; ///< Нормаль конуса (направление от основания к вершине)

public:
    /**
     * @brief Конструктор класса ConeGen
     * @param r Радиус конуса
     * @param h Высота конуса
     * @param c Центр основания (по умолчанию (0,0,0))
     * @param n Нормаль конуса (по умолчанию (0,0,1) - вертикально вверх)
     */
    ConeGen(double r, double h, const point3d& c = point3d(), const point3d& n = point3d(0,0,1));

    /**
     * @brief Генерирует случайную точку внутри конуса с равномерным распределением
     * @param p Указатель на точку для заполнения координатами
     * 
     * Точка генерируется с равномерным распределением внутри объема конуса.
     * Если указатель nullptr, функция ничего не делает.
     */
    void rnd(point3d* p);

    /**
     * @brief Устанавливает параметры конуса
     * @param r Радиус конуса
     * @param h Высота конуса
     * @param c Центр основания (по умолчанию (0,0,0))
     * @param n Нормаль конуса (по умолчанию (0,0,1))
     */
    void setParams(double r, double h, const point3d& c = point3d(), const point3d& n = point3d(0,0,1));

    /**
     * @brief Возвращает параметры конуса в виде строки
     * @return Строка с параметрами конуса
     */
    std::string getParams() const;

    /**
     * @brief Сохраняет параметры конуса в файл
     * @param filename Имя файла для сохранения
     */
    void saveSet(const std::string& filename) const;

    /**
     * @brief Возвращает радиус конуса
     * @return Радиус конуса
     */
    double getRadius() const { return radius; }

    /**
     * @brief Возвращает высоту конуса
     * @return Высота конуса
     */
    double getHeight() const { return height; }

    /**
     * @brief Возвращает центр основания конуса
     * @return Центр основания конуса
     */
    point3d getCenter() const { return center; }

    /**
     * @brief Возвращает нормаль конуса
     * @return Нормаль конуса
     */
    point3d getNormal() const { return normal; }

    /**
     * @brief Возвращает вершину конуса
     * @return Вершина конуса
     */
    point3d getApex() const { return center + normal.normalize() * height; }

    /**
     * @brief Вращает конус вокруг оси на заданный угол
     * @param axis Ось вращения
     * @param angle Угол в радианах
     * 
     * Примеры:
     * - Вращение вокруг оси Y (0,1,0) на 90°: конус ляжет вдоль оси X
     * - Вращение вокруг оси X (1,0,0) на 90°: конус ляжет вдоль оси Y
     */
    void rotate(const point3d& axis, double angle);

private:
    /**
     * @brief Преобразует локальные координаты конуса в глобальные
     * @param local Локальные координаты (z вдоль нормали)
     * @return Глобальные координаты
     */
    point3d localToGlobal(const point3d& local) const;
};
#endif