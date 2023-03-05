from math import cos, pi, exp
from random import uniform


def f(x):  # Тестовая функция Растригина
    A = 10
    n = len(x)
    result = A * n + sum(x[i] ** 2 - A * cos(2 * pi * x[i]) for i in range(n))
    return result


def generate_agents():
    global number_of_agents
    return list([uniform(-5.12, 5.12), uniform(-5.12, 5.12)] for i in range(number_of_agents))


y = 5
# попробовать 1, 0.5
step_ind = list()
step_vol = list()
step_ind.append(float(input("Введите макс размер шага индивидуального перемещения: ")))
step_vol.append(float(input("Введите макс размер шага коллективно-волевого перемещения: ")))
number_of_agents = 10  # количество агентов популяции (20-40-50 должно быть)
max_weight = 50
w = list()
w.append(list(max_weight / 2 for i in range(number_of_agents)))

t = 0  # текущий номер поколения
P = list()  # Начальная популяция
P.append(generate_agents())  # Случано сгенерированное текущее поколение
p_qbest = P[t][0]
for i in P[t]:
    if f(p_qbest) > f(i):
        p_qbest = i

F = list()
f_t = list()
f_min = f(P[t][0])
f_t.append(f_min)
for i in range(1, number_of_agents):
    f_i_t = f(P[t][i])
    if f_i_t < f_min:
        f_min = f_i_t
        p_qbest = P[t][i]
    f_t.append(f_i_t)

F.append(f_t)
iter_max = 1000  # больше 500 не нужно
# критерий останова может быть и другим
# t не только как поколение, но и кол-во иттераций
while t <= iter_max:
    t += 1
    step_ind.append(step_ind[0] * exp(-y * t / iter_max))
    step_vol.append(step_vol[0] * exp(-y * t / iter_max))

    P.append(P[t - 1])
    w.append(w[t - 1])
    F.append(list(0 for i in range(number_of_agents)))

    # для каждого агента выполнить
    for i in range(number_of_agents):
        # спросить про r1 и r2, сколько в них значений
        r1 = list(uniform(0, 1) for j in range(len(P[t][0])))
        r2 = list(uniform(0, 1) for j in range(len(P[t][0])))
        for j in range(len(P[t][0])):
            P[t][i][j] = P[t][i][j] + step_ind[t] * r1[j]
        # ???????? как это, прибавляем в каждому значению из списка значений агента?
        # P[t][i] = list(map(lambda x: x + step_ind[t] * r1, P[t][i]))
        # P[t][i] += step_ind[t] * r1
        F[t][i] = f(P[t][i])  # значение f для Pit

        if F[t][i] >= F[t - 1][i]:
            P[t][i] = P[t - 1][i]
        # кормление
        w[t][i] = w[t - 1][i] + (F[t][i] - F[t - 1][i]) / (max(F[t]))

    # вычисляем I
    I_t = list()
    for i in range(number_of_agents):
        sm1 = 0  # числитель
        sm2 = 0  # знаменатель
        for j in range(len(P[t][0])):
            sm1 += (P[t][i][j] - P[t - 1][i][j]) * (F[t][i] - F[t - 1][i])
            sm2 += (F[t][i] - F[t - 1][i])
        I_t.append(sm1 / sm2)

    # для каждого агента выполнить
    for i in range(number_of_agents):
        for j in range(len(P[t][0])):
            P[t][i][j] += I_t[j]
        # P[t][i] += I_t

    # Вычисляем B
    B_t = list()
    for i in range(number_of_agents):
        sm1 = 0  # числитель
        sm2 = 0  # знаменатель
        for j in range(len(P[t][0])):
            sm1 += P[t][i][j] * w[t][i]
            sm2 += P[t][i][j]
        B_t.append(sm1 / sm2)

    # для каждого агента выполнять
    for i in range(number_of_agents):
        if sum(w[t]) > sum(w[t - 1]):
            for j in range(len(P[t][0])):
                P[t][i][j] -= step_vol[t] * r2[j] * (P[t][i][j] - B_t[j]) / abs((P[t][i][j] - B_t[j]))
            # P[t][i] -= step_vol[t] * r2 * (P[t][i] - B) / abs((P[t][i] - B))
        else:
            for j in range(len(P[t][0])):
                P[t][i][j] += step_vol[t] * r2[j] * (P[t][i][j] - B_t[j]) / abs((P[t][i][j] - B_t[j]))
            # P[t][i] += step_vol[t] * r2 * (P[t][i] - B) / abs((P[t][i] - B))
    print(*P[t])
    # выбрать агента  ptgbest, такого, что
    p_qbest_t = P[t][0]
    for i in P[t]:
        if f(p_qbest) > f(i):
            p_qbest = i

print(p_qbest)
# for i in P:
#     print(*i)
# f(P[t][i]) for i in range(number_of_agents))
