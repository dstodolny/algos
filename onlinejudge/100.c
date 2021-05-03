#include <stdio.h>
#include <string.h>

#define MAX_LINE 256

int algorithm(int n);

int
algorithm(int n)
{
        if (n == 1)
                return 1;
        else if (n % 2 == 0)
                return 1 + algorithm(n / 2);
        else
                return 1 + algorithm(3*n + 1);
}

int
main(int argc, char **argv)
{
        int i, j, from, to, count, max_count;
        char line[MAX_LINE];


        while (fgets(line, sizeof(line), stdin)) {
                if (strcmp(line, "\n") == 0)
                        break;
                sscanf(line, "%d %d\n", &i, &j);
                max_count = 0;
                from = i<j ? i : j;
                to = i<j ? j : i;
                for (from = i<j ? i : j; from <= to; from++) {
                        count = algorithm(from);
                        if (count > max_count)
                                max_count = count;
                }
                printf("%d %d %d\n", i, j, max_count);
        }
        return 0;
}
