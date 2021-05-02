/*
 * 739.c - Daily Temperatures
 *
 * Given a list of daily temperatures T, return a list such that, for
 * each day in the input, tells you how many days you would have to wait
 * until a warmer temperature. If there is no future day for which this
 * is possible, put 0 instead.
 *
 * For example, given the list of temperatures T = [73, 74, 75, 71, 69,
 * 72, 76, 73], your output should be [1, 1, 4, 2, 1, 1, 0, 0].
 *
 * Note: The length of temperatures will be in the range [1,
 * 30000]. Each temperature will be an integer in the range [30, 100].
 */
#include <stdio.h>
#include <assert.h>
#include "algos.h"

int *daily_temperatures(int *t, int n, int *m);

/**
 * Note: The returned array must be malloced, assume caller calls
 * free().
 */
int
*daily_temperatures(int *t, int n, int *m)
{
        int *result = (int *)Calloc(n, sizeof(int));
        for (int i = 0; i < n; i++) {
                for (int j = i+1, count = 0; j < n; j++, count++) {
                        if (t[j] > t[i]) {
                                result[i] = ++count;
                                break;
                        }
                }
        }
        *m = n;
        return result;
}

int
main(int argc, char **argv)
{
        int T1[] = {73, 74, 75, 71, 69, 72, 76, 73};
        int T2[] = {30, 30, 30, 30, 30, 30, 30, 30};
        int R1[] = {1, 1, 4, 2, 1, 1, 0, 0};
        int R2[] = {0, 0, 0, 0, 0, 0, 0, 0};

        int n, m, *res;

        n = 8;

        res = daily_temperatures(T1, n, &m);
        assert(m == 8);
        for (int i = 0; i < m; i++) {
                assert(res[i] == R1[i]);
        }
        Free(res);

        res = daily_temperatures(T2, n, &m);
        assert(m == 8);
        for (int i = 0; i < m; i++) {
                assert(res[i] == R2[i]);
        }

        return 0;
}
