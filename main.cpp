/**
 * @file main.cpp
 * @brief Основная программа для демонстрации работы генератора точек в конусе
 * @mainpage Генератор случайных точек в конусе
 * 
 * @details
 * Программа демонстрирует работу генератора случайных точек внутри конуса.
 * Пользователь может генерировать точки, просматривать их, добавлять новые,
 * сохранять в файл и визуализировать с помощью MathGL.
 * 
 * @author Perevozchikov M
 * @date 2025
 */

#include <iostream>
#include <vector>
#include <fstream>
#include "point3d.h"
#include "cone_gen.h"

#include <mgl2/mgl.h>

/**
 * @brief Функция визуализации точек и конуса
 * @param points Массив точек для визуализации
 * @param count Количество точек в массиве
 * @param generator Генератор конуса для отображения границ
 */
void visualizePoints(const point3d* points, int count, const ConeGen& generator) {
    mglData x(count), y(count), z(count);
    
    for (int i = 0; i < count; ++i) {
        x.a[i] = points[i].x;
        y.a[i] = points[i].y;
        z.a[i] = points[i].z;
    }
    
    double radius = generator.getRadius();
    double height = generator.getHeight();
    point3d center = generator.getCenter();
    point3d apex = generator.getApex();
    point3d normal = generator.getNormal();
    
    mglGraph gr;
    gr.SetSize(1000, 800);
    
    // Устанавливаем диапазоны для лучшего отображения
    double range = std::max(radius, height) * 1.5;
    gr.SetRange('x', center.x - range, center.x + range);
    gr.SetRange('y', center.y - range, center.y + range);
    gr.SetRange('z', center.z - range, center.z + range);
    
    gr.Title("Точки в конусе", "", 5);
    gr.Rotate(60, 40); // Лучший угол обзора
    gr.Box();
    gr.Axis();
    
    // 1. Отображаем точки (красные)
    gr.Plot(x, y, z, " r.");
    
    // 2. Отображаем контур конуса (синий)
    
    // Основание конуса - круг
    int circlePoints = 50;
    mglData baseX(circlePoints), baseY(circlePoints), baseZ(circlePoints);
    
    // Создаем базовые векторы для построения основания
    point3d z_axis = normal.normalize();
    point3d arbitrary(1, 0, 0);
    if (std::abs(z_axis.dot(arbitrary)) > 0.9) {
        arbitrary = point3d(0, 1, 0);
    }
    point3d x_axis = z_axis.cross(arbitrary).normalize();
    point3d y_axis = z_axis.cross(x_axis).normalize();
    
    for (int i = 0; i < circlePoints; ++i) {
        double angle = 2 * M_PI * i / (circlePoints - 1);
        point3d local(radius * cos(angle), radius * sin(angle), 0);
        point3d global = center + x_axis * local.x + y_axis * local.y + z_axis * local.z;
        
        baseX.a[i] = global.x;
        baseY.a[i] = global.y;
        baseZ.a[i] = global.z;
    }
    
    // Рисуем основание
    gr.Plot(baseX, baseY, baseZ, "b-");
    
    // Боковые ребра конуса
    mglData edgeX(2), edgeY(2), edgeZ(2);
    
    // 4 боковых ребра (0°, 90°, 180°, 270°)
    for (int i = 0; i < 4; ++i) {
        double angle = i * M_PI / 2;
        point3d basePoint_local(radius * cos(angle), radius * sin(angle), 0);
        point3d basePoint_global = center + x_axis * basePoint_local.x + y_axis * basePoint_local.y + z_axis * basePoint_local.z;
        
        edgeX.a[0] = basePoint_global.x;
        edgeY.a[0] = basePoint_global.y;
        edgeZ.a[0] = basePoint_global.z;
        
        edgeX.a[1] = apex.x;
        edgeY.a[1] = apex.y;
        edgeZ.a[1] = apex.z;
        
        gr.Plot(edgeX, edgeY, edgeZ, "b--");
    }
    
    // Вершина конуса
    mglData apexX(1), apexY(1), apexZ(1);
    apexX.a[0] = apex.x;
    apexY.a[0] = apex.y;
    apexZ.a[0] = apex.z;
    gr.Plot(apexX, apexY, apexZ, "b*");
    
    // Центр основания
    mglData centerX(1), centerY(1), centerZ(1);
    centerX.a[0] = center.x;
    centerY.a[0] = center.y;
    centerZ.a[0] = center.z;
    gr.Plot(centerX, centerY, centerZ, "go");
    
    // Оси координат для ориентира (только линии, без подписей в 3D)
    mglData originX(2), originY(2), originZ(2);
    
    // Ось X - красная
    originX.a[0] = center.x; originY.a[0] = center.y; originZ.a[0] = center.z;
    originX.a[1] = center.x + range * 0.8; originY.a[1] = center.y; originZ.a[1] = center.z;
    gr.Plot(originX, originY, originZ, "r-");
    
    // Ось Y - зеленая
    originX.a[0] = center.x; originY.a[0] = center.y; originZ.a[0] = center.z;
    originX.a[1] = center.x; originY.a[1] = center.y + range * 0.8; originZ.a[1] = center.z;
    gr.Plot(originX, originY, originZ, "g-");
    
    // Ось Z - синяя
    originX.a[0] = center.x; originY.a[0] = center.y; originZ.a[0] = center.z;
    originX.a[1] = center.x; originY.a[1] = center.y; originZ.a[1] = center.z + range * 0.8;
    gr.Plot(originX, originY, originZ, "b-");
    
    gr.WritePNG("cone_visualization.png");
    std::cout << "=== ПАРАМЕТРЫ КОНУСА ===" << std::endl;
    std::cout << "Центр: (" << center.x << ", " << center.y << ", " << center.z << ")" << std::endl;
    std::cout << "Нормаль: (" << normal.x << ", " << normal.y << ", " << normal.z << ")" << std::endl;
    std::cout << "Вершина: (" << apex.x << ", " << apex.y << ", " << apex.z << ")" << std::endl;
    std::cout << "Оси: X(красная) Y(зеленая) Z(синяя)" << std::endl;
    std::cout << "Визуализация сохранена в cone_visualization.png" << std::endl;
    std::cout << "Всего точек: " << count << std::endl;
}

/**
 * @brief Основная функция программы
 * @return Код завершения программы
 * 
 * @details
 * Программа предоставляет интерактивное меню для работы с точками:
 * - Генерация случайных точек внутри конуса
 * - Просмотр отдельных точек
 * - Добавление точек вручную
 * - Сохранение точек в файл
 * - Изменение параметров конуса
 * - Визуализация точек
 */
int main() {
    // Создаем генератор для конуса с радиусом 1 и высотой 2
    ConeGen generator(1.0, 2.0);
    
    // Динамический массив точек (используем указатели)
    point3d* points = nullptr;
    int pointCount = 0;

    std::cout << "=== ГЕНЕРАТОР СЛУЧАЙНЫХ ТОЧЕК В КОНУСЕ ===" << std::endl;
    std::cout << "Исходные параметры: " << generator.getParams() << std::endl;
    std::cout << "Оси координат: X(→) Y(↑) Z(⬆)" << std::endl;
    
    // Запрос количества точек
    std::cout << "Введите количество точек: ";
    std::cin >> pointCount;

    if (pointCount <= 0) {
        std::cout << "Неверное количество точек!" << std::endl;
        return 1;
    }

    // Выделяем память под массив точек
    points = new point3d[pointCount];

    // Заполняем массив случайными точками
    std::cout << "Генерация " << pointCount << " точек..." << std::endl;
    for (int i = 0; i < pointCount; ++i) {
        generator.rnd(&points[i]);
    }

    // Основной цикл меню
    int choice;
    do {
        std::cout << "\n=== МЕНЮ ===" << std::endl;
        std::cout << "1. Вывести точку" << std::endl;
        std::cout << "2. Сохранить в файл" << std::endl;
        std::cout << "3. Показать параметры области" << std::endl;
        std::cout << "4. Изменить параметры конуса" << std::endl;  
        std::cout << "5. Визуализация с MathGL" << std::endl;
        std::cout << "6. Вращать конус" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "Выбор: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                // Вывод точки по индексу
                int index;
                std::cout << "Введите индекс точки (0-" << pointCount-1 << "): ";
                std::cin >> index;
                
                if (index >= 0 && index < pointCount) {
                    std::cout << "Точка " << index << ": ";
                    points[index].print();
                } else {
                    std::cout << "Неверный индекс!" << std::endl;
                }
                break;
            }
            
            case 2: {
                // Сохранение в файл
                std::ofstream file("points.txt");
                if (file.is_open()) {
                    for (int i = 0; i < pointCount; ++i) {
                        file << points[i].x << " " << points[i].y << " " << points[i].z << "\n";
                    }
                    file.close();
                    
                    // Сохраняем настройки
                    generator.saveSet("settings.dat");
                    
                    std::cout << "Данные сохранены в points.txt и settings.dat" << std::endl;
                } else {
                    std::cout << "Ошибка открытия файла!" << std::endl;
                }
                break;
            }
            
            case 3: {
                // Показ параметров 
                std::cout << generator.getParams() << std::endl;
                break;
            }
            
            case 4: {
                // ИЗМЕНЕНИЕ ПАРАМЕТРОВ КОНУСА
                double new_radius, new_height, new_x, new_y, new_z;
                
                std::cout << "Текущие параметры: " << generator.getParams() << std::endl;
                
                std::cout << "Введите новый радиус конуса: ";
                std::cin >> new_radius;
                
                std::cout << "Введите новую высоту конуса: ";
                std::cin >> new_height;
                
                std::cout << "Введите новые координаты центра основания (x y z): ";
                std::cin >> new_x >> new_y >> new_z;
                
                // Устанавливаем новые параметры
                generator.setParams(new_radius, new_height, point3d(new_x, new_y, new_z));
                
                std::cout << "Параметры конуса успешно изменены!" << std::endl;
                std::cout << "Новые параметры: " << generator.getParams() << std::endl;
                
                // ПЕРЕГЕНЕРАЦИЯ ТОЧЕК
                std::cout << "Перегенерируем точки с новыми параметрами..." << std::endl;
                for (int i = 0; i < pointCount; ++i) {
                    generator.rnd(&points[i]);
                }
                std::cout << "Все точки перегенерированы!" << std::endl;
                break;
            }

            case 5: {
                // Визуализация точек
                visualizePoints(points, pointCount, generator);
                break;
            }

            case 6: {
                // ВРАЩЕНИЕ КОНУСА
                double axis_x, axis_y, axis_z, angle_degrees;
                
                std::cout << "=== ВРАЩЕНИЕ КОНУСА ===" << std::endl;
                std::cout << "Текущая нормаль: (" << generator.getNormal().x << ", " 
                          << generator.getNormal().y << ", " << generator.getNormal().z << ")" << std::endl;
                std::cout << "Примеры осей:" << std::endl;
                std::cout << "  Ось X: 1 0 0" << std::endl;
                std::cout << "  Ось Y: 0 1 0" << std::endl;
                std::cout << "Введите ось вращения (x y z): ";
                std::cin >> axis_x >> axis_y >> axis_z;
                
                std::cout << "Введите угол вращения (в градусах): ";
                std::cin >> angle_degrees;
                
                double angle_radians = angle_degrees * M_PI / 180.0;
                point3d axis(axis_x, axis_y, axis_z);
                
                // Отладочная информация
                std::cout << "ДО вращения - нормаль: (" << generator.getNormal().x << ", " 
                          << generator.getNormal().y << ", " << generator.getNormal().z << ")" << std::endl;
                
                // Вращаем конус
                generator.rotate(axis, angle_radians);
                
                std::cout << "ПОСЛЕ вращения - нормаль: (" << generator.getNormal().x << ", " 
                          << generator.getNormal().y << ", " << generator.getNormal().z << ")" << std::endl;
                
                // ПЕРЕГЕНЕРИРУЕМ ТОЧКИ С НОВОЙ ОРИЕНТАЦИЕЙ
                std::cout << "Перегенерируем точки с новой ориентацией..." << std::endl;
                for (int i = 0; i < pointCount; ++i) {
                    generator.rnd(&points[i]);
                }
                std::cout << "Все точки перегенерированы!" << std::endl;
                break;
            }
             
            case 0: {
                std::cout << "Выход из программы." << std::endl;
                break;
            }
             
            default: {
                std::cout << "Неверный выбор!" << std::endl;
                break;
            }
        }
    } while (choice != 0);

    // Освобождаем память
    if (points != nullptr) {
        delete[] points;
    }

    return 0;
}