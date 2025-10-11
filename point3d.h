/**
 * @file point3d.h
 * @brief Заголовочный файл структуры point3d
 */

#ifndef POINT3D_H
#define POINT3D_H

/**
 * @brief Структура для хранения точки в 3D пространстве
 */
struct point3d
{  
    double x; ///< Координата X
    double y; ///< Координата Y  
    double z; ///< Координата Z

    /**
     * @brief Конструктор по умолчанию
     * @param x Координата X
     * @param y Координата Y
     * @param z Координата Z
     */
    point3d(double x=0.0, double y=0.0, double z=0.0);

    /**
     * @brief Выводит координаты на экран
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
};

#endif