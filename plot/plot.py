import matplotlib.pyplot as plt
import pandas as pd

data_newton_and_gauss = pd.read_csv("Newton_And_Gauss.txt", sep=" ",header=None)
data_neldera_and_mida = pd.read_csv("Neldera_And_Mida.txt", sep=" ",header=None)
data_hybrid = pd.read_csv("Hybrid.txt", sep=" ",header=None)

plt.subplot(3, 1, 1)
plt.plot(data_newton_and_gauss[0], data_newton_and_gauss[1],color="pink")
plt.title('Метод Ньютона-Гаусса')
plt.xlabel('Количество итераций')
plt.ylabel('Точность')

plt.subplot(3, 1, 2)
plt.plot(data_neldera_and_mida[0], data_neldera_and_mida[1],color="pink")
plt.title('Метод Нелдера-Мида')
plt.xlabel('Количество итераций')
plt.ylabel('Точность')

plt.subplot(3, 1, 3)
plt.plot(data_hybrid[0], data_hybrid[1],color="pink")
plt.title('Гибридный метод')
plt.xlabel('Количество итераций')
plt.ylabel('Точность')

plt.tight_layout()
plt.show()
