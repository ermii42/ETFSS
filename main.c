#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "math.h"

#define PI 3.1415926535897931159979635

float random_uniform(float min, float max) {
    return min + (max - min) / RAND_MAX * rand();
}

float *add_arrays(float arr[], float plus[], int n_args_count) {
    float *result = (float *) malloc(n_args_count * sizeof(float));
    result = arr;
    for (int i = 0; i < n_args_count; i++) {
        result[i] += plus[i];
    }
    return result;
}

float *sub_arrays(float arr[], float minus[], int n_args_count) {
    float *result = (float *) malloc(n_args_count * sizeof(float));
    result = arr;
    for (int i = 0; i < n_args_count; i++) {
        result[i] -= minus[i];
    }
    return result;
}

float *mul_arrays(float arr[], float mul[], int n_args_count) {
    float *result = (float *) malloc(n_args_count * sizeof(float));
    result = arr;
    for (int i = 0; i < n_args_count; i++) {
        result[i] *= mul[i];
    }
    return result;
}

float *div_arrays(float arr[], float div[], int n_args_count) {
    float *result = (float *) malloc(n_args_count * sizeof(float));
    result = arr;
    for (int i = 0; i < n_args_count; i++) {
        result[i] /= div[i];
    }
    return result;
}

float *add_array_number(float arr[], float number, int n_args_count) {
    float *result = (float *) malloc(n_args_count * sizeof(float));
    result = arr;
    for (int i = 0; i < n_args_count; i++) {
        result[i] += number;
    }
    return result;
}

float *sub_array_number(float arr[], float number, int n_args_count) {
    float *result = (float *) malloc(n_args_count * sizeof(float));
    result = arr;
    for (int i = 0; i < n_args_count; i++) {
        result[i] -= number;
    }
    return result;
}

float *mul_array_number(float arr[], float number, int n_args_count) {
    float *result = (float *) malloc(n_args_count * sizeof(float));
    result = arr;
    for (int i = 0; i < n_args_count; i++) {
        result[i] *= number;
    }
    return result;
}

float *div_array_number(float arr[], float number, int n_args_count) {
    float *result = (float *) malloc(n_args_count * sizeof(float));
    result = arr;
    for (int i = 0; i < n_args_count; i++) {
        result[i] /= number;
    }
    return result;
}

float max(float arr[], int n) {
    float result = arr[0];
    for (int i = 1; i < n; i++) {
        if (result < arr[i]) {
            result = arr[i];
        }
    }
    return result;
}

//void main_function(float* (*f)(float *, float), float** (*generate_agents)(float *, float), int n_args_count, int iter_max, int number_of_agents, float max_weight){
//    float step_ind[iter_max]
//}
float f1(float *x, int n_args_count) { // Тестовая функция Растригина
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
            arr[i][j] = random_uniform(-5.12f, 5.12f);
        }
    }
}
//void test(){
//    float *step_ind = (float *) malloc(iter_max);
//}

void main_function(float (*f)(float *, int), void (*generate_agents)(float **, int, int), int n_args_count,
                   int iter_max, int number_of_agents, float max_weight) {


    int y = 5;
    float *step_ind = (float *) malloc(iter_max);
    float *step_vol = (float *) malloc(iter_max);
    float **p_qbest_list = (float **) malloc(iter_max * sizeof(float *));
    for (int i = 0; i < iter_max; i++) {
        p_qbest_list[i] = (float *) malloc(n_args_count * sizeof(float));
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
    // w[t] += 50
    for (int i = 0; i < number_of_agents; i++) {
        w[t][i] = max_weight / 2;
    }
    // P[t] = generate agents
    generate_agents(P[t], number_of_agents, n_args_count);
    float *p_qbest = (float *) malloc(n_args_count * sizeof(float));
    p_qbest = P[t][0];
    for (int i = 1; i < number_of_agents; i++) {

        if (f(p_qbest, n_args_count) > f(P[t][i], n_args_count)) {
            p_qbest = P[t][i];
        }
    }
    p_qbest_list[t] = p_qbest;
    for (int i = 0; i < number_of_agents; i++) {
        F[t][i] = f1(P[t][i], n_args_count);
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
    float delta_F;
    while (t < iter_max - 1) {
        t++;
        step_ind[t] = step_ind[0] * exp(-y * t / iter_max);
        step_vol[t] = step_vol[0] * exp(-y * t / iter_max);

        P[t] = P[t - 1];
        P[t] = P[t - 1];
        // для каждого агента выполнить
        for (int i = 0; i < number_of_agents; i++) {
            for (int j = 0; j < number_of_agents; j++) {
                r1[j] = random_uniform(0, 1) * step_ind[t];
            }
            P[t][i] = add_arrays(P[t][i], r1, n_args_count);

            F[t][i] = f(P[t][i], n_args_count); // значение f для P_it
            if (F[t][i] >= F[t - 1][i]) {
                P[t][i] = P[t - 1][i];
                F[t][i] = f(P[t][i], n_args_count);
            }
        }
//        for (int i = 0; i < number_of_agents; i++) {
//            if (max(sub_arrays(F[t], F[t - 1], number_of_agents), number_of_agents) != 0) {
//                // кормление
//                w[t][i] =
//                        (F[t][i] - F[t - 1][i]) / (max(sub_arrays(F[t], F[t - 1], number_of_agents), number_of_agents));
//            }
//        }
        // вычисляем вектор коллективно-инстинктивного перемещения
//        delta_F = F[t] - F[t - 1];
//        for(int i=0; i<number_of_agents; i++){
//            P_mul_F[i] = mul_arrays()
//        }
    }
//    for(int i=0; i<number_of_agents; i++){
//        for (int j = 0; j < n_args_count; j++) {
//            printf("%f ", P[t][i][j]);
//        }
//        printf("\n");
//    }
//    printf("\n");
//    printf("%f %f", p_qbest[0], p_qbest[1]);
//    printf("\n");
//
//
//    for(int i=0; i<number_of_agents; i++){
//        printf("%f ", F[t][i]);
//    }
//    printf("\n");
//    for(int i=0; i<number_of_agents; i++){
//        printf("%f ", w[t][i]);
//    }
//    printf("\n");
}

int main() {
    srand(time(NULL));
    printf("Hello, World!\n");
    int number_of_agents_ = 2;
    int n_args_count_ = 2;
    float *arr = (float *) malloc(2);
    arr[0] = -3.300257;
    arr[1] = 4.033404;
    main_function(f1, generate_agents1, n_args_count_, 2, number_of_agents_, 100);
//    printf("%f", f1(arr, 2));
    return 0;
}
