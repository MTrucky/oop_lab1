/**
 * @file cone_gen.h
 * @brief Заголовочный файл класса ConeGen
 */

#ifndef CONE_GEN_H
#define CONE_GEN_H

#include "point3d.h"
#include <string>

/**
 * @brief Класс для генерации точек внутри конуса
 */
class ConeGen {
private:
    double radius;  ///< Радиус основания конуса
    double height;  ///< Высота конуса
    point3d center; ///< Центр основания конуса

public:
    /**
     * @brief Конструктор
     * @param r Радиус конуса
     * @param h Высота конуса
     * @param c Центр основания
     */
    ConeGen(double r, double h, const point3d& c = point3d());

    /**
     * @brief Генерирует случайную точку внутри конуса
     * @param p Указатель на точку для заполнения
     */
    void rnd(point3d* p);

    /**
     * @brief Устанавливает параметры конуса
     * @param r Радиус конуса
     * @param h Высота конуса
     * @param c Центр основания
     */
    void setParams(double r, double h, const point3d& c = point3d());

    /**
     * @brief Возвращает параметры конуса в виде строки
     * @return Строка с параметрами
     */
    std::string getParams() const;

    /**
     * @brief Сохраняет параметры в файл
     * @param filename Имя файла
     */
    void saveSet(const std::string& filename) const;
};

#endif