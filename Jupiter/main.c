#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "math.h"

#define PI 3.1415926535897931159979635
#define e 2.7182818284904523536028747

typedef struct {
    float *best_solution;
    float best_y;
    double time_spent;
} Result;

float random_uniform2(float min, float max) {
    return min + (max - min) / RAND_MAX * rand();
}

float *add_arrays(const float arr[], const float plus[], int n_args_count) {
    float *result = (float *) malloc(n_args_count * sizeof(float));
    for (int i = 0; i < n_args_count; i++) {
        result[i] = arr[i] + plus[i];
    }
    return result;
}

float *sub_arrays(const float arr[], const float minus[], int n_args_count) {
    float *result = (float *) malloc(n_args_count * sizeof(float));
    for (int i = 0; i < n_args_count; i++) {
        result[i] = arr[i] - minus[i];
    }
    return result;
}

float *mul_arrays(const float arr[], const float mul[], int n_args_count) {
    float *result = (float *) malloc(n_args_count * sizeof(float));
    for (int i = 0; i < n_args_count; i++) {
        result[i] = arr[i] * mul[i];
    }
    return result;
}

float *div_arrays(const float arr[], const float div[], int n_args_count) {
    float *result = (float *) malloc(n_args_count * sizeof(float));
    for (int i = 0; i < n_args_count; i++) {
        result[i] = arr[i] / div[i];
    }
    return result;
}

float *add_array_number(const float arr[], float number, int n_args_count) {
    float *result = (float *) malloc(n_args_count * sizeof(float));
    for (int i = 0; i < n_args_count; i++) {
        result[i] = arr[i] + number;
    }
    return result;
}

float *sub_array_number(const float arr[], float number, int n_args_count) {
    float *result = (float *) malloc(n_args_count * sizeof(float));
    for (int i = 0; i < n_args_count; i++) {
        result[i] = arr[i] - number;
    }
    return result;
}

float *mul_array_number(const float arr[], float number, int n_args_count) {
    float *result = (float *) malloc(n_args_count * sizeof(float));
    for (int i = 0; i < n_args_count; i++) {
        result[i] = arr[i] * number;
    }
    return result;
}

float *div_array_number(const float arr[], float number, int n_args_count) {
    float *result = (float *) malloc(n_args_count * sizeof(float));
    for (int i = 0; i < n_args_count; i++) {
        result[i] = arr[i] / number;
    }
    return result;
}

void copy_1d(float *arr1, const float arr2[], int n) {
//    float *result = (float *) malloc(n * sizeof(float));
    for (int i = 0; i < n; i++) {
        arr1[i] = arr2[i];
    }
}

void copy_2d(float **arr1, const float *arr2[], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            arr1[i][j] = arr2[i][j];
        }
    }
}

float max(const float arr[], int n) {
    float result = arr[0];
    for (int i = 1; i < n; i++) {
        if (result < arr[i]) {
            result = arr[i];
        }
    }
    return result;
}

float f1(const float *x, int n_args_count) { // Тестовая функция Растригина
    float A = 10;
    float result = 0;
    for (int i = 0; i < n_args_count; i++) {
        result += x[i] * x[i] - A * cos(2 * x[i] * PI);
    }
    result += A * n_args_count;

    return result;
}

void generate_agents1(float **arr, int number_of_agents, int n_args_count) {
    for (int i = 0; i < number_of_agents; i++) {
        for (int j = 0; j < n_args_count; j++) {
            arr[i][j] = random_uniform2(-5.12f, 5.12f);
        }
    }
}

float f2(const float *x, int n_args_count) { // Тестовая функция Экли

    float result = -20 * exp(-0.2 * sqrt(0.5 * (x[0] * x[0] + x[1] * x[1]))) \
 - exp(0.5 * (cos(2 * PI * x[0]) + cos(2 * PI * x[1]))) + e + 20;

    return result;
}

void generate_agents2(float **arr, int number_of_agents, int n_args_count) {
    for (int i = 0; i < number_of_agents; i++) {
        for (int j = 0; j < n_args_count; j++) {
            arr[i][j] = random_uniform2(-5.f, 5.f);
        }
    }
}

float f3(const float *x, int n_args_count) { // Тестовая функция Сферы

    float result = 0;
    for (int i = 0; i < n_args_count; i++) {
        result += x[i] * x[i];
    }
    return result;
}

void generate_agents3(float **arr, int number_of_agents, int n_args_count) {
    for (int i = 0; i < number_of_agents; i++) {
        for (int j = 0; j < n_args_count; j++) {
            arr[i][j] = random_uniform2(-2.f, 2.f);
        }
    }
}

float f4(const float *x, int n_args_count) { // Тестовая функция Розенбока

    float result = 0;
    for (int i = 0; i < n_args_count - 1; i++) {
        result += 100 * (x[i + 1] - x[i] * x[i]) * (x[i + 1] - x[i] * x[i]) + (x[i] - 1) * (x[i] - 1);
    }
    return result;
}

void generate_agents4(float **arr, int number_of_agents, int n_args_count) {
    for (int i = 0; i < number_of_agents; i++) {
        for (int j = 0; j < n_args_count; j++) {
            arr[i][j] = random_uniform2(-11.f, 11.f);
        }
    }
}

float f5(const float *x, int n_args_count) { // Тестовая функция Била

    float result = (1.5 - x[0] + x[0] * x[1]) * (1.5 - x[0] + x[0] * x[1]) + \
             (2.25 - x[0] + x[0] * x[1] * x[1]) * (2.25 - x[0] + x[0] * x[1] * x[1]) + \
             (2.625 - x[0] + x[0] * x[1] * x[1] * x[1]) * (2.625 - x[0] + x[0] * x[1] * x[1] * x[1]);
    return result;
}

void generate_agents5(float **arr, int number_of_agents, int n_args_count) {
    for (int i = 0; i < number_of_agents; i++) {
        for (int j = 0; j < n_args_count; j++) {
            arr[i][j] = random_uniform2(-4.5f, 4.5f);
        }
    }
}

float f6(const float *x, int n_args_count) { // Тестовая функция Гольдшейна-прайса

    float result = (1 + (x[0] + x[1] + 1) * (x[0] + x[1] + 1) *
                        (19 - 14 * x[0] + 3 * x[0] * x[0] - 14 * x[1] + 6 * x[0] * x[1] + 3 * x[1] * x[1])) * \
             (30 + (2 * x[0] - 3 * x[1]) * (2 * x[0] - 3 * x[1]) *
                   (18 - 32 * x[0] + 12 * x[0] * x[0] + 48 * x[1] - 36 * x[0] * x[1] + 27 * x[1] * x[1]));
    return result;
}

void generate_agents6(float **arr, int number_of_agents, int n_args_count) {
    for (int i = 0; i < number_of_agents; i++) {
        for (int j = 0; j < n_args_count; j++) {
            arr[i][j] = random_uniform2(-2.f, 2.f);
        }
    }
}

float f7(const float *x, int n_args_count) { // Тестовая функция Бута

    float result = (x[0] * 2 * x[1] - 7) * (x[0] * 2 * x[1] - 7) + (2 * x[0] + x[1] - 5) * (2 * x[0] + x[1] - 5);
    return result;
}

void generate_agents7(float **arr, int number_of_agents, int n_args_count) {
    for (int i = 0; i < number_of_agents; i++) {
        for (int j = 0; j < n_args_count; j++) {
            arr[i][j] = random_uniform2(-10.f, 10.f);
        }
    }
}

void output_array2d(float **arr, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%f ", arr[i][j]);
        }
        printf("\n");
    }
}

void output_array1d(float *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%f ", arr[i]);
    }
    printf("\n");
}

float sum_2d(const float **arr, int n, int j) {
    float result = 0;
    for (int i = 0; i < n; i++) {
        result += arr[i][j];
    }
    return result;
}

float sum_1d(const float *arr, int n) {
    float result = 0;
    for (int i = 0; i < n; i++) {
        result += arr[i];
    }
    return result;
}

void test() {
    int n = 500;
    int m = 3;
    float **arr1 = (float **) malloc(n * sizeof(float *));
    float **arr2 = (float **) malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++) {
        arr1[i] = (float *) malloc(m * sizeof(float));
        arr2[i] = (float *) malloc(m * sizeof(float));
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            arr1[i][j] = 1;
            arr2[i][j] = 2;
        }
    }
    for (int i = 0; i < 500; i++) {
        arr1[i] = add_arrays(arr1[i], arr2[i], m);
    }
    output_array2d(arr1, n, m);
}

Result main_function(float (*f)(float *, int), void (*generate_agents)(float **, int, int), int n_args_count,
                     int iter_max, int number_of_agents, float max_weight) {

    clock_t begin = clock();
    srand(time(NULL));
    int y = 5;
    float *step_ind = (float *) malloc(iter_max * sizeof(float));
    float *step_vol = (float *) malloc(iter_max * sizeof(float));
    float **p_gbest_list = (float **) malloc(iter_max * sizeof(float *));
    for (int i = 0; i < iter_max; i++) {
        p_gbest_list[i] = (float *) malloc(n_args_count * sizeof(float));
    }
    float **w = (float **) malloc(iter_max * sizeof(float *));
    for (int i = 0; i < iter_max; i++) {
        w[i] = (float *) malloc(number_of_agents * sizeof(float));
    }
    float ***P = (float ***) malloc(iter_max * sizeof(float **));
    for (int i = 0; i < iter_max; i++) {
        P[i] = (float **) malloc(number_of_agents * sizeof(float *));
        for (int j = 0; j < number_of_agents; j++) {
            P[i][j] = (float *) malloc(n_args_count * sizeof(float));
        }
    }
    float **F = (float **) malloc(iter_max * sizeof(float *));
    for (int i = 0; i < iter_max; i++) {
        F[i] = (float *) malloc(number_of_agents * sizeof(float));
    }
    int t = 0;
    step_ind[t] = 0.05f;
    step_vol[t] = 0.05f;
    // w[t] = 50
    for (int i = 0; i < number_of_agents; i++) {
        w[t][i] = max_weight / 2;
    }
    // P[t] = generate agents
    generate_agents(P[t], number_of_agents, n_args_count);
    float *p_gbest = (float *) malloc(n_args_count * sizeof(float));
    copy_1d(p_gbest, P[t][0], n_args_count);
    for (int i = 1; i < number_of_agents; i++) {

        if (f(p_gbest, n_args_count) > f(P[t][i], n_args_count)) {
//            p_gbest = P[t][i];
            copy_1d(p_gbest, P[t][i], n_args_count);
        }
    }
    p_gbest_list[t] = p_gbest;

    // значение функции для каждого агента
    for (int i = 0; i < number_of_agents; i++) {
        F[t][i] = f(P[t][i], n_args_count);
    }
    // макс кол-во иттераций
    // критерий останова может быть и другим
    // t не только как поколение, но и кол-во иттераций
    float *r1 = (float *) malloc(n_args_count * sizeof(float));
    float *r2 = (float *) malloc(n_args_count * sizeof(float));
    float *I_t = (float *) malloc(n_args_count * sizeof(float));
    float **P_mul_F = (float **) malloc(number_of_agents * sizeof(float *));
    for (int i = 0; i < number_of_agents; i++) {
        P_mul_F[i] = (float *) malloc(n_args_count * sizeof(float));
    }
    float *delta_F;
    float *B_t = (float *) malloc(n_args_count * sizeof(float));
    float sm = 0;  // сумма
    float sm2 = 0;
    float *p_gbest_t = (float *) malloc(n_args_count * sizeof(float));
    while (t < iter_max - 1) {
        t += 1;
        step_ind[t] = step_ind[0] * exp(-y * t / iter_max);
        step_vol[t] = step_vol[0] * exp(-y * t / iter_max);
//        printf("%i\n", t);

        copy_2d(P[t], (const float **) P[t - 1], number_of_agents, n_args_count);
        copy_1d(w[t], w[t - 1], number_of_agents);
        // для каждого агента выполнить
        for (int i = 0; i < number_of_agents; i++) {
            for (int j = 0; j < n_args_count; j++) {
                r1[j] = random_uniform2(0, 1) * step_ind[t];
            }
            P[t][i] = add_arrays(P[t][i], r1, n_args_count);

            F[t][i] = f(P[t][i], n_args_count); // значение f для P_it
            if (F[t][i] >= F[t - 1][i]) {
                copy_1d(P[t][i], P[t - 1][i], n_args_count);
//                P[t][i] = P[t - 1][i];
                F[t][i] = f(P[t][i], n_args_count);
            }
        }
        for (int i = 0; i < number_of_agents; i++) {
            if (max(sub_arrays(F[t], F[t - 1], number_of_agents), number_of_agents) != 0) {
                // кормление
                w[t][i] +=
                        (F[t][i] - F[t - 1][i]) / (max(sub_arrays(F[t], F[t - 1], number_of_agents), number_of_agents));
            }
        }
        // вычисляем вектор коллективно-инстинктивного перемещения
        delta_F = sub_arrays(F[t], F[t - 1], number_of_agents);
        for (int i = 0; i < number_of_agents; i++) {
            P_mul_F[i] = mul_array_number(sub_arrays(P[t][i], P[t - 1][i], n_args_count), delta_F[i], n_args_count);
        }
        for (int j = 0; j < n_args_count; j++) {
            I_t[j] = sum_2d((const float **) P_mul_F, number_of_agents, j);
        }
        I_t = div_array_number(I_t, sum_1d(delta_F, number_of_agents), n_args_count);
        // Применяем оператор коллективно-инстинктивного перемещения к каждому агенту
        for (int i = 0; i < number_of_agents; i++) {
            P[t][i] = add_arrays(P[t][i], I_t, n_args_count);
        }

        // Вычисляем Бариоцентр
        for (int j = 0; j < n_args_count; j++) {
            sm = 0;
            for (int i = 0; i < number_of_agents; i++) {
                sm += P[t][i][j] * w[t][i];
            }
            B_t[j] = sm;
        }
        sm2 = sum_1d(w[t], number_of_agents);
        B_t = div_array_number(B_t, sm2, n_args_count);

        // для каждого агента выполнять
        for (int i = 0; i < number_of_agents; i++) {
            for (int j = 0; j < number_of_agents; j++) {
                r2[j] = random_uniform2(0, 1) * step_ind[t];
            }
            if (sum_1d(w[t], number_of_agents) > sum_1d(w[t - 1], number_of_agents)) {
                for (int j = 0; j < n_args_count; j++) {
                    P[t][i][j] -= step_vol[t] * r2[j] * (P[t][i][j] - B_t[j]) / fabsf((P[t][i][j] - B_t[j]));
                }
            } else {
                for (int j = 0; j < n_args_count; j++) {
                    P[t][i][j] += step_vol[t] * r2[j] * (P[t][i][j] - B_t[j]) / fabsf((P[t][i][j] - B_t[j]));
                }
            }
        }
        copy_1d(p_gbest_t, P[t][0], n_args_count);
        for (int i = 0; i < number_of_agents; i++) {
            if (f(p_gbest_t, n_args_count) > f(P[t][i], n_args_count)) {
                copy_1d(p_gbest_t, P[t][i], n_args_count);
            }
        }
        if (f(p_gbest_t, n_args_count) < f(p_gbest, n_args_count)) {
            copy_1d(p_gbest, p_gbest_t, n_args_count);
        }
        copy_1d(p_gbest_list[t], p_gbest, n_args_count);
    }
    clock_t end = clock();
    Result result;
    result.best_solution = p_gbest;
    result.best_y = f(p_gbest, n_args_count);
    result.time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    return result;
}

Result test_Rastrigen(int number_of_agents_, int n_args_count_, int iter) {
    Result res;
    res = main_function((float (*)(float *, int)) f1, generate_agents1, n_args_count_, iter, number_of_agents_, 100);
    return res;
}

Result test_Ekli(int number_of_agents_, int n_args_count_, int iter) {
    Result res;
    res = main_function((float (*)(float *, int)) f2, generate_agents2, n_args_count_, iter, number_of_agents_, 100);
    return res;
}

Result test_Sphere(int number_of_agents_, int n_args_count_, int iter) {
    Result res;
    res = main_function((float (*)(float *, int)) f3, generate_agents3, n_args_count_, iter, number_of_agents_, 100);
    return res;
}

Result test_Rosenbock(int number_of_agents_, int n_args_count_, int iter) {
    Result res;
    res = main_function((float (*)(float *, int)) f4, generate_agents4, n_args_count_, iter, number_of_agents_, 100);
    return res;
}

Result test_Bila(int number_of_agents_, int n_args_count_, int iter) {
    Result res;
    res = main_function((float (*)(float *, int)) f5, generate_agents5, n_args_count_, iter, number_of_agents_, 100);
    return res;
}

Result test_Goldsheina_Praisa(int number_of_agents_, int n_args_count_, int iter) {
    Result res;
    res = main_function((float (*)(float *, int)) f6, generate_agents6, n_args_count_, iter, number_of_agents_, 100);
    return res;
}

Result test_Buta(int number_of_agents_, int n_args_count_, int iter) {
    Result res;
    res = main_function((float (*)(float *, int)) f7, generate_agents7, n_args_count_, iter, number_of_agents_, 100);
    return res;
}


int main() {

//    printf("Hello, World!\n");
    int number_of_agents_ = 50;
    int n_args_count_ = 2;
    int iter = 500;
    Result res;
    res = test_Sphere(number_of_agents_, n_args_count_, iter);
    output_array1d(res.best_solution, n_args_count_);
    printf("%f\n", res.best_y);
    printf("%f", res.time_spent);

//    test();
    return 0;
}
