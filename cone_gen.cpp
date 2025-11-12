/**
 * @file cone_gen.cpp
 * @brief Реализация методов класса ConeGen
 * @author Ваше Имя
 * @date 2025
 */

 #include "cone_gen.h"
 #include <fstream>
 #include <cmath>
 #include <sstream>
 #include <random>
 #include <ctime>
 #include <algorithm>
 
 /**
  * @brief Конструктор класса ConeGen
  * @param r Радиус основания конуса
  * @param h Высота конуса
  * @param c Центр основания конуса
  * @param n Нормаль конуса
  */
 ConeGen::ConeGen(double r, double h, const point3d& c, const point3d& n) 
     : radius(r), height(h), center(c), normal(n.normalize()) {}
 
 /**
  * @brief Генерирует случайную точку внутри конуса с равномерным распределением
  * @param p Указатель на точку для заполнения координатами
  * 
  * @details
  * Алгоритм генерации (метод обратного преобразования):
  * 1. Генерируем случайную высоту с учетом объемного распределения
  * 2. На этой высоте генерируем точку в круге
  * 3. Преобразуем в глобальную систему координат с учетом нормали
  */
 void ConeGen::rnd(point3d* p) {
     if (p == nullptr) return;
 
     static std::mt19937 gen(time(0));
     
     // УЛУЧШЕННОЕ РАСПРЕДЕЛЕНИЕ: учитываем объемный элемент
     // Плотность вероятности по z: p(z) ~ (1 - z/h)^2
     std::uniform_real_distribution<> distU(0, 1);
     double u = distU(gen);
     
     // Преобразование для равномерного распределения по объему
     double z = height * (1 - std::cbrt(u)); // Обратное преобразование
     
     // Максимальный радиус на высоте z
     double maxRadius = radius * (1 - z / height);
 
     // Генерация точки в круге (равномерно по площади)
     std::uniform_real_distribution<> distAngle(0, 2 * M_PI);
     double angle = distAngle(gen);
     
     // РАВНОМЕРНОЕ РАСПРЕДЕЛЕНИЕ В КРУГЕ
     std::uniform_real_distribution<> distR(0, 1);
     double r_val = maxRadius * std::sqrt(distR(gen)); // sqrt для равномерности в круге
 
     // Локальные координаты (z вдоль нормали)
     point3d local(
         r_val * std::cos(angle),
         r_val * std::sin(angle), 
         z
     );
 
     // Преобразование в глобальные координаты
     *p = localToGlobal(local);
 }
 
 /**
  * @brief Устанавливает новые параметры конуса
  * @param r Новый радиус конуса
  * @param h Новая высота конуса
  * @param c Новый центр основания конуса
  * @param n Новая нормаль конуса
  */
 void ConeGen::setParams(double r, double h, const point3d& c, const point3d& n) {
     radius = r;
     height = h;
     center = c;
     normal = n.normalize();
 }
 
 /**
  * @brief Возвращает строковое представление параметров конуса
  * @return Строка с параметрами конуса
  */
 std::string ConeGen::getParams() const {
     std::ostringstream oss;
     oss << "Конус: радиус=" << radius << ", высота=" << height 
         << ", центр=(" << center.x << ", " << center.y << ", " << center.z << ")"
         << ", нормаль=(" << normal.x << ", " << normal.y << ", " << normal.z << ")";
     return oss.str();
 }
 
 /**
  * @brief Сохраняет параметры конуса в файл
  * @param filename Имя файла для сохранения
  */
 void ConeGen::saveSet(const std::string& filename) const {
     std::ofstream file(filename);
     if (file.is_open()) {
         file << radius << " " << height << " " 
              << center.x << " " << center.y << " " << center.z << " "
              << normal.x << " " << normal.y << " " << normal.z;
         file.close();
     }
 }
 
 /**
  * @brief Вращает конус вокруг оси на заданный угол
  * @param axis Ось вращения
  * @param angle Угол в радианах
  */
 void ConeGen::rotate(const point3d& axis, double angle) {
     // Вращаем нормаль
     normal = normal.rotate(axis, angle);
     
     // Вращаем центр основания относительно начала координат
     // Это важно для правильного позиционирования конуса
     center = center.rotate(axis, angle);
 }
 
 /**
  * @brief Преобразует локальные координаты конуса в глобальные
  * @param local Локальные координаты (z вдоль нормали)
  * @return Глобальные координаты
  */
 point3d ConeGen::localToGlobal(const point3d& local) const {
     // Базовые векторы для локальной системы координат
     point3d z_axis = normal.normalize();
     
     // Выбираем произвольный вектор, не параллельный нормали
     point3d arbitrary(1, 0, 0);
     if (std::abs(z_axis.dot(arbitrary)) > 0.9) {
         arbitrary = point3d(0, 1, 0);
     }
     
     point3d x_axis = z_axis.cross(arbitrary).normalize();
     point3d y_axis = z_axis.cross(x_axis).normalize();
     
     // Преобразование координат
     return center + 
            x_axis * local.x + 
            y_axis * local.y + 
            z_axis * local.z;
 }