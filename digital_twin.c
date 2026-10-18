```
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <math.h>

double get_q(double x)
{
    if (x < 10) return 2 * x + 1;
    if (x < 20) return 1.2 * x + 9;
    return 0.8 * x + 17;
}

int main() 
{
    setlocale(LC_ALL, "RUS");

    double x, q, q0;
    int series = 0, dir = 0;
    int n = 0;
    double sum = 0, sum_sq = 0;

    printf("Введите целевое значение Q0: ");
    if (scanf("%lf", &q0) != 1)
    {
        printf("Ошибка ввода Q0\n");
        return 1;
    }

    printf("Введите показания датчика (любой символ для выхода):\n");

    while (scanf("%lf", &x) == 1) 
    {
        q = get_q(x);
        n++;
        sum += q;
        sum_sq += q * q;

        int curr_dir = (q > q0) ? 1 : (q < q0) ? -1 : 0; // контроль (4 подряд в одну сторону от Q0)

        if (curr_dir == 0) 
        {
            series = 0; dir = 0;
        }
        else if (curr_dir == dir) 
        {
            series++;
        }
        else 
        {
            dir = curr_dir; series = 1;
        }

        printf("X=%.1f -> Q=%.1f ", x, q);
        if (series >= 4) printf("[ТРЕВОГА!]\n");
        else printf("[норма]\n");
    }

    if (n == 0) return 0;

    // статистика
    double mean = sum / n;
    double var = (sum_sq / n) - (mean * mean);
    if (var < 0) var = 0;
    double std = sqrt(var);

    printf("\n--- Статистика ---\n");
    printf("Среднее: %.2f\n", mean);
    printf("Дисперсия: %.2f\n", var);
    printf("Станд. отклонение: %.2f\n", std);
    printf("Диапазон [mean-std, mean+std]: [%.2f, %.2f]\n", mean - std, mean + std);

    return 0;
}
```
