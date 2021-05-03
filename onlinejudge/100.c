#include <stdio.h>
#include <string.h>

#define MAX_LINE 256

int algorithm(int n);

int
algorithm(int n)
{
        /* printf("%d", n); */
        if (n == 1) {
                /* printf("\n"); */
                return 1;
        }
        else if (n % 2 == 0) {
                /* printf(" "); */
                return 1 + algorithm(n / 2);
        } else {
                /* printf(" "); */
                return 1 + algorithm(3*n + 1);
        }
}

int
main(int argc, char **argv)
{
        int i, j, n, count, max_count;
        char line[MAX_LINE];


        while (fgets(line, sizeof(line), stdin)) {
                if (strcmp(line, "\n") == 0)
                        break;
                sscanf(line, "%d %d\n", &i, &j);
                max_count = 0;
                n = i;
                for (n = i; n <= j; n++) {
                        count = algorithm(n);
                        if (count > max_count)
                                max_count = count;
                }
                printf("%d %d %d\n", i, j, max_count);
        }
        return 0;
}
