from math import cos, pi, exp
from random import uniform


def f(x):  # Тестовая функция Растригина
    A = 10
    n = len(x)
    result = A * n + sum(x[i] ** 2 - A * cos(2 * pi * x[i]) for i in range(n))
    return result


def generate_agents():
    global number_of_agents
    return list((uniform(-5.12, 5.12), uniform(-5.12, 5.12)) for i in range(number_of_agents))


y = 5
# попробовать 1, 0.5
step_ind = list()
step_vol = list()
step_ind.append(float(input("Введите макс размер шага индивидуального перемещения: ")))
step_vol.append(float(input("Введите макс размер шага коллективно-волевого перемещения: ")))
number_of_agents = 10  # количество агентов популяции (20-40-50 должно быть)
t = 0  # текущий номер поколения
P = list()  # Начальная популяция
P.append(generate_agents())  # Случано сгенерированное текущее поколение
p_qbest = P[t][0]
f_t = list()
f_min = f(P[t][0])
f_t.append(f_min)
for i in range(1, number_of_agents):
    f_i_t = f(P[t][i])
    if f_i_t < f_min:
        f_min = f_i_t
        p_qbest = P[t][i]
    f_t.append(f_i_t)

iterations = 0
iter_max = 10000
# критерий останова может быть и другим
while iterations <= iter_max:
    t += 1
    step_ind.append(step_ind[0] * exp(-y * t / iter_max))
    step_vol.append(step_vol[0] * exp(-y * t / iter_max))
    # for 

# f(P[t][i]) for i in range(number_of_agents))
