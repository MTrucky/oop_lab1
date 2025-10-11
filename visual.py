"""
@file visual.py
@brief Скрипт для 3D визуализации точек из файла points.txt
@author Perevozchikov M
@date 2025-09-28

@details
Упрощенная версия визуализации точек в конусе.
"""

import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

def main():
    """
    @brief Основная функция скрипта визуализации.
    """
    try:
        # Чтение данных из файла
        print("Чтение данных из points.txt...")
        data = np.loadtxt('points.txt')
        x, y, z = data[:, 0], data[:, 1], data[:, 2]
        
        # Создание 3D-графика
        print("Создание 3D визуализации...")
        
        fig = plt.figure(figsize=(10, 8))
        ax = fig.add_subplot(111, projection='3d')
        
        # Простое отображение точек
        scatter = ax.scatter(x, y, z, c=z, cmap='viridis', 
                           alpha=0.7, s=20, marker='o')
        
        # СТАНДАРТНЫЕ НАСТРОЙКИ MATPLOTLIB ДЛЯ ИНТУИТИВНОГО УПРАВЛЕНИЯ
        
        # Стандартные подписи осей
        ax.set_xlabel('X', fontsize=12, fontweight='bold')
        ax.set_ylabel('Y', fontsize=12, fontweight='bold')
        ax.set_zlabel('Z', fontsize=12, fontweight='bold')
        
        # Простой заголовок
        ax.set_title('Точки в конусе', fontsize=14, pad=20)
        
        # Цветовая шкала
        cbar = fig.colorbar(scatter, ax=ax, shrink=0.6)
        cbar.set_label('Высота Z', fontsize=10)
        
        # Простая сетка
        ax.grid(True, linestyle='--', alpha=0.3)
        
        # Полупрозрачные плоскости для лучшего восприятия глубины
        ax.xaxis.pane.set_alpha(0.1)
        ax.yaxis.pane.set_alpha(0.1)
        ax.zaxis.pane.set_alpha(0.1)
        
        # Начальный вид
        ax.view_init(elev=25, azim=45)
        
        # Автоматическое масштабирование для всех точек
        ax.set_box_aspect([1, 1, 1])  # Сохраняем пропорции
        
        print("Загрузка графика...")
        print("Управление:")
        print("- ЛКМ + движение: вращение")
        print("- ПКМ + движение: масштабирование") 
        print("- Колесо мыши: приближение/отдаление")
        print("- R: сброс вида")
        
        plt.show()
        
        print("Визуализация завершена успешно!")
        
    except FileNotFoundError:
        print("Ошибка: файл points.txt не найден!")
        print("Убедитесь, что программа на C++ была запущена и сохранила данные.")
    except Exception as e:
        print(f"Ошибка при визуализации: {e}")

if __name__ == "__main__":
    main()