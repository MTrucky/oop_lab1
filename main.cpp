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
 
 #include <mgl2/mgl.h>
 
 /**
  * @brief Функция визуализации точек и конуса
  * @param points Массив точек
  * @param count Количество точек
  * @param generator Генератор конуса
  */
 void visualizePoints(const point3d* points, int count, const ConeGen& generator) {
     // Создаем данные для точек
     mglData x(count), y(count), z(count);
     
     for (int i = 0; i < count; ++i) {
         x.a[i] = points[i].x;
         y.a[i] = points[i].y;
         z.a[i] = points[i].z;
     }
     
     // Параметры конуса
     double radius = generator.getRadius();
     double height = generator.getHeight();
     point3d center = generator.getCenter();
     
     // Создаем график
     mglGraph gr;
     gr.SetSize(1000, 800);
     
     // Устанавливаем диапазоны осей с учетом центра
     gr.SetRange('x', center.x - radius*1.5, center.x + radius*1.5);
     gr.SetRange('y', center.y - radius*1.5, center.y + radius*1.5);
     gr.SetRange('z', center.z, center.z + height*1.2);
     
     gr.Title("Точки в конусе", "", 5);
     gr.Label('x', "Ось X", 0);
     gr.Label('y', "Ось Y", 0);
     gr.Label('z', "Ось Z", 0);
     
     // Вращаем для лучшего обзора
     gr.Rotate(50, 60);
     
     // Рисуем оси
     gr.Box();
     gr.Axis();
     
     // Рисуем сетку
     gr.Grid("xyz", "h;");
     
     // Рисуем точки красным цветом
     gr.Plot(x, y, z, " r.");
     
     // Рисуем контур конуса для наглядности
     int cone_points = 50;
     mglData cx(cone_points), cy(cone_points), cz(cone_points);
     
     // Боковая поверхность конуса
     for (int i = 0; i < cone_points; ++i) {
         double angle = 2 * M_PI * i / (cone_points - 1);
         cx.a[i] = center.x + radius * cos(angle);
         cy.a[i] = center.y + radius * sin(angle);
         cz.a[i] = center.z;
     }
     gr.Plot(cx, cy, cz, "b-");
     
     // Верхняя точка конуса
     mglData top_x(1), top_y(1), top_z(1);
     top_x.a[0] = center.x;
     top_y.a[0] = center.y;
     top_z.a[0] = center.z + height;
     gr.Plot(top_x, top_y, top_z, "b.");
     
     // Линии от основания к вершине
     for (int i = 0; i < 8; ++i) {
         double angle = 2 * M_PI * i / 8;
         mglData line_x(2), line_y(2), line_z(2);
         line_x.a[0] = center.x + radius * cos(angle);
         line_y.a[0] = center.y + radius * sin(angle);
         line_z.a[0] = center.z;
         line_x.a[1] = center.x;
         line_y.a[1] = center.y;
         line_z.a[1] = center.z + height;
         gr.Plot(line_x, line_y, line_z, "b--");
     }
     
     // Сохраняем в файл
     gr.WritePNG("cone_visualization.png");
     
     std::cout << "Визуализация сохранена в cone_visualization.png" << std::endl;
     std::cout << "Всего точек: " << count << std::endl;
     std::cout << "Параметры конуса: " << generator.getParams() << std::endl;
 }
 
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
         std::cout << "5. Изменить параметры конуса\n";  
         std::cout << "6. Визуализация с MathGL\n";
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
             
             case 5: {
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
                 
                 // ПЕРЕГЕНЕРАЦИЯ ТОЧЕК С НОВЫМИ ПАРАМЕТРАМИ
                 std::cout << "Перегенерируем точки с новыми параметрами..." << std::endl;
                 for (int i = 0; i < pointCount; ++i) {
                     generator.rnd(&points[i]);
                 }
                 std::cout << "Все точки перегенерированы!" << std::endl;
                 break;
             }
 
             case 6: {
                 // Визуализация точек
                 visualizePoints(points, pointCount, generator);
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