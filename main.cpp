/**
 * @file main.cpp
 * @brief Основная программа для демонстрации работы генератора точек
 * @mainpage Генератор случайных точек в конусе
 */

#include <iostream>
#include <vector>
#include <fstream>
#include "point3d.h"
#include "cone_gen.h"

/**
 * @brief Основная функция программы
 * @return Код завершения
 */
int main() {
    // Создаем генератор для конуса с радиусом 1 и высотой 2
    ConeGen generator(1.0, 2.0);
    
    // Динамический массив точек (используем указатели)
    point3d* points = nullptr;
    int pointCount = 0;

    std::cout << "Параметры области: " << generator.getParams() << std::endl;
    
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
    for (int i = 0; i < pointCount; ++i) {
        generator.rnd(&points[i]);
    }

    // Основной цикл меню
    int choice;
    do {
        std::cout << "\nМеню:\n";
        std::cout << "1. Вывести точку\n";
        std::cout << "2. Добавить точку\n";
        std::cout << "3. Сохранить в файл\n";
        std::cout << "4. Показать параметры области\n";
        std::cout << "0. Выход\n";
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
                // Добавление новой точки
                point3d* newPoints = new point3d[pointCount + 1];
                
                // Копируем старые точки
                for (int i = 0; i < pointCount; ++i) {
                    newPoints[i] = points[i];
                }
                
                // Ввод координат новой точки
                double x, y, z;
                std::cout << "Введите координаты новой точки (x y z): ";
                std::cin >> x >> y >> z;
                newPoints[pointCount] = point3d(x, y, z);
                
                // Освобождаем старый массив и переключаем указатель
                delete[] points;
                points = newPoints;
                pointCount++;
                
                std::cout << "Точка добавлена. Всего точек: " << pointCount << std::endl;
                break;
            }
            
            case 3: {
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
            
            case 4: {
                // Показ параметров области
                std::cout << generator.getParams() << std::endl;
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