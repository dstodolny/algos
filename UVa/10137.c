#include <stdio.h>

#define MAX_LINE 256

int calculate(int *arr, int n);

int
calculate(int *arr, int n)
{
        int i;
        int total, rest, average, result;

        total = 0;
        result = 0;

        for (i = 0; i < n; i++) {
                total += *(arr+i);
        }

        rest = total % n;
        average = total / n;

        for (i = 0; i < n; i++) {
                if (*(arr+i) > average) {
                        result += *(arr+i) - average;
                        if (rest > 0) {
                                result -= 1;
                                rest -= 1;
                        }
                }

        }
        return result;
}

int
main(int argc, char **argv)
{
        char line[MAX_LINE];
        int n, s[1000], d, c, i, result;

        while (fgets(line, sizeof(line), stdin)) {
                sscanf(line, "%d\n", &n);
                if (n == 0)
                        break;
                for (i = 0; i < n; i++) {
                        fgets(line, sizeof(line), stdin);
                        sscanf(line, "%d.%d\n", &d, &c);
                        s[i] = (d * 100) + c;
                }
                result = calculate((int *)&s, n);
                printf("$%d.%02d\n", result/100, result%100);
        }
        return 0;
}
