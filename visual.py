"""
@file visual.py
@brief Скрипт для 3D визуализации точек из файла points.txt
@author Perevozchikov M
@date 2025-09-28

@details
Этот скрипт использует библиотеки matplotlib и numpy для создания
3D-визуализации точек, сгенерированных программой на C++.

Скрипт читает данные из файла points.txt, создает интерактивный
3D-график и отображает точки внутри конуса.

@note Для работы требуются установленные библиотеки:
- matplotlib
- numpy

@see cone_gen
@see point3d
"""

import matplotlib.pyplot as plt
import numpy as np

def main():
    """
    @brief Основная функция скрипта визуализации.
    
    @details
    Читает данные из файла points.txt, создает 3D-график
    и отображает точки в интерактивном окне. Функция включает
    обработку ошибок для случаев когда файл не найден или
    имеет неправильный формат.
    
    @throws FileNotFoundError если файл points.txt не существует
    @throws ValueError если данные в файле имеют неправильный формат
    
    @code
    # Пример использования:
    # python3 visual.py
    # Открывается окно с 3D визуализацией точек
    @endcode
    """
    try:
        # Чтение данных из файла
        print("Чтение данных из points.txt...")
        data = np.loadtxt('points.txt')
        x, y, z = data[:, 0], data[:, 1], data[:, 2]
        
        # Создание 3D-графика
        print("Создание 3D визуализации...")
        fig = plt.figure(figsize=(12, 9))
        ax = fig.add_subplot(111, projection='3d')
        
        # Отображение точек
        scatter = ax.scatter(x, y, z, c=z, cmap='viridis', marker='o', 
                           alpha=0.7, s=30, label='Случайные точки')
        
        # Настройка осей и меток
        ax.set_xlabel('Ось X', fontsize=12, labelpad=10)
        ax.set_ylabel('Ось Y', fontsize=12, labelpad=10)
        ax.set_zlabel('Ось Z', fontsize=12, labelpad=10)
        ax.set_title('3D визуализация точек внутри конуса', fontsize=14, pad=20)
        
        # Добавление цветовой шкалы
        cbar = fig.colorbar(scatter, ax=ax, shrink=0.6, aspect=20)
        cbar.set_label('Высота (Z)', rotation=270, labelpad=15)
        
        # Добавление легенды
        ax.legend(loc='upper right')
        
        # Настройка вида
        ax.view_init(elev=20, azim=45)
        
        # Отображение графика
        print("Отображение графика...")
        plt.tight_layout()
        plt.show()
        
        print("Визуализация завершена успешно!")
        
    except FileNotFoundError:
        print("Ошибка: файл points.txt не найден!")
        print("Убедитесь, что программа на C++ была запущена и сохранила данные.")
    except Exception as e:
        print(f"Ошибка при визуализации: {e}")

if __name__ == "__main__":
    """
    @brief Точка входа скрипта.
    
    @details
    Проверяет, что скрипт запущен напрямую, а не импортирован как модуль,
    и вызывает основную функцию.
    """
    main()