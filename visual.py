"""
@file visual.py
@brief Скрипт для 3D визуализации точек из файла points.txt
@author Perevozchikov M
@date 2025-09-28
"""

import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

def main():
    try:
        print("Чтение данных из points.txt...")
        data = np.loadtxt('points.txt')
        
        if data.size == 0:
            print("Файл points.txt пуст!")
            return
            
        # Обработка случая с одной точкой
        if data.ndim == 1:
            x, y, z = data[0], data[1], data[2]
            x, y, z = [x], [y], [z]
        else:
            x, y, z = data[:, 0], data[:, 1], data[:, 2]
        
        print(f"Загружено {len(x)} точек")
        
        print("Создание 3D визуализации...")
        
        # Создание фигуры и 3D оси
        fig = plt.figure(figsize=(10, 8))
        ax = fig.add_subplot(111, projection='3d')
        
        # Правильные подписи осей (соответствуют системе координат C++)
        ax.scatter(x, y, z, c=z, cmap='viridis', alpha=0.7, s=20)
        
        ax.set_xlabel('Y (→)')
        ax.set_ylabel('X (↑)')
        ax.set_zlabel('Z (⬆)')
        
        ax.set_title('Точки в конусе')
        
        # Сетка
        ax.grid(True, linestyle='--', alpha=0.3)
        
        # Начальный угол обзора
        ax.view_init(elev=25, azim=45)
        
        # Сохраняем пропорции
        ax.set_box_aspect([1, 1, 1])  
        
        print("Загрузка графика...")
        
        # Показать график
        plt.show()
        
        print("Визуализация завершена!")
        
    except FileNotFoundError:
        print("Ошибка: файл points.txt не найден!")
    except Exception as e:
        print(f"Ошибка: {e}")

if __name__ == "__main__":
    main()