import matplotlib.pyplot as plt
import pandas as pd

def plot_point():
    point = pd.read_csv("../../cmake-build-debug/src/Point.txt", sep=' ', names=['X', 'Y'])
    line = pd.read_csv("../../cmake-build-debug/src/Line.txt", sep=' ', names=['X', 'Y'])

    plt.scatter(point['X'], point['Y'], label='Точки')
    plt.plot(line['X'], line['Y'], label='Прямая')

    plt.title('График точек и прямой')
    plt.xlabel('Ось X')
    plt.ylabel('Ось Y')
    plt.legend()

    plt.show()

plot_point()
