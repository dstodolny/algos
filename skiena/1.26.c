/*
 * 1.26 - Nearest Neighbor and Closest Pair implementation
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUF 256
#define MAX_TOUR 4096

struct point {
        int x;
        int y;
};

void nearest_neighbor(struct point points[], char *tour, int n);
int dist(struct point *p1, struct point *p2);
void pop(struct point p, struct point points[], int *n);
void closest_pair(struct point points[], char *tour, struct point *start, int n);
void pop_pair(struct point *(*pairs)[2], struct point **pair, int *n);
void pop_all(struct point *(*pairs)[2], struct point *p, int *n);
void print_pair(struct point **pair);
void print_pairs(struct point *(*pairs)[2], int n);
void generate_tour(struct point *(*pairs)[2], char *tour, struct point *start, int pn, int n);
int points_eq(struct point *p1, struct point *p2);

/*
 * NearestNeighbor(P)
 *     Pick and visit an initial point p_0 from P
 *     p = p_0
 *     i = 0
 *     While there are still unvisited points
 *         i = i + 1
 *         Select pi to be the closest unvisited point to p_(i-1)
 *         Visit p_i
 *     Return to p_0 from p_(n-1)
 */
void
nearest_neighbor(struct point points[], char *tour, int n)
{
        int i, j, n_left, sd, sd_min;
        char buf[MAX_BUF];
        struct point p, p_next, unvisited[n-1];

        strcpy(tour, "");

        if (n < 1)
                return;

        sprintf(buf, "(%d, %d)\n", points[0].x, points[0].y);
        strcat(tour, buf);

        if (n == 1) {
                return;
        }

        n_left = n-1;
        for (i = 1; i < n; i++)
                unvisited[i-1] = points[i];

        p = points[0];
        while (n_left > 0) {
                p_next = unvisited[0];
                sd_min = dist(&p, &p_next);

                for (j = 1; j < n_left; j++) {
                        sd = dist(&p, &unvisited[j]);
                        if (sd < sd_min) {
                                sd_min = sd;
                                p_next = unvisited[j];
                        }
                }
                p = p_next;
                pop(p_next, unvisited, &n_left);

                sprintf(buf, "(%d, %d)\n", p_next.x, p_next.y);
                strcat(tour, buf);
        }
        sprintf(buf, "(%d, %d)\n", points[0].x, points[0].y);
        strcat(tour, buf);
}

/*
 * dist - Squared Euclidean distance
 */
int
dist(struct point *p1, struct point *p2)
{
        int dx = p2->x - p1->x;
        int dy = p2->y - p1->y;
        return dx*dx + dy*dy;
}

/*
 * pop - Remove point p from points and decrement n
 */
void
pop(struct point p, struct point *points, int *n)
{
        int i;

        for (i = 0; i < *n; i++) {
                if (p.x == points[i].x && p.y == points[i].y)
                        break;
        }
        for (; i < (*n)-1; i++) {
                points[i] = points[i+1];
        }
        (*n)--;
}

/*
 * ClosestPair(P)
 *     Let n be the number of points in set P.
 *     For i = 1 to n - 1 do
 *         d = infinity
 *         For each pair of endpoints (s, t) from distinct vertex chains
 *             if dist(s, t) <= d then s_m = s, t_m = t, and d = dist(s, t)
 *         Connect (s_m, t_m) by an edge
 *     Connect the two endpoints by an edge
 */
void
closest_pair(struct point points[], char *tour, struct point *start, int n)
{
        struct point **pair_m, *(*pairs)[2], *(*cpairs)[2];
        int i, j, k, pn, cpn;
        unsigned d, d_min;

        pn = n*(n-1)/2;
        cpn = 0;
        if ((pairs = malloc(pn*2*sizeof(struct point *))) == NULL)
                exit(1);
        if ((cpairs = malloc(pn*2*sizeof(struct point *))) == NULL)
                exit(1);
;
        for (i = 0, k = 0; i < n-1; i++) {
                for (j = i+1; j < n; j++, k++) {
                        pairs[k][0] = &points[i];
                        pairs[k][1] = &points[j];
                }
        }

        while (pn > 0) {
                d_min = -1;
                for (i = 0; i < pn; i++) {
                        d = dist(pairs[i][0], pairs[i][1]);
                        if (d < d_min) {
                                d_min = d;
                                pair_m = pairs[i];
                        }
                }

                cpairs[cpn][0] = pair_m[0];
                cpairs[cpn][1] = pair_m[1];
                cpn++;

                pop_pair(pairs, pair_m, &pn);
        }

        generate_tour(cpairs, tour, start, cpn, n);

        free(pairs);
        free(cpairs);
}

void
pop_pair(struct point *(*pairs)[2], struct point **pair, int *n)
{
        int i;

        for (i = 0; i < *n; i++) {
                if (points_eq(pairs[i][0], pair[0]) && points_eq(pairs[i][1], pair[1]))
                        break;

        }

        for ( ; i < (*n)-1; i++) {
                pairs[i][0] = pairs[i+1][0];
                pairs[i][1] = pairs[i+1][1];
        }
        (*n)--;
}

void
pop_all(struct point *(*pairs)[2], struct point *p, int *n)
{
        int i;

        for (i = *n-1; i >= 0; i--) {
                if (points_eq(p, pairs[i][0]) || points_eq(p, pairs[i][1])) {
                        pop_pair(pairs, pairs[i], n);
                }
        }
}

void
print_pair(struct point **pair)
{
        printf("[(%d, %d), (%d, %d)]\n", pair[0]->x, pair[0]->y, pair[1]->x, pair[1]->y);
}

void
print_pairs(struct point *(*pairs)[2], int n)
{
        int i;
        for (i = 0; i < n; i++)
                printf("[(%d, %d), (%d, %d)]\n", pairs[i][0]->x, pairs[i][0]->y,
                       pairs[i][1]->x, pairs[i][1]->y);
        printf("\n");
}

void
generate_tour(struct point *(*pairs)[2], char *tour, struct point *start, int pn, int n)
{
        int i;
        char buf[MAX_BUF];
        struct point *p1, *p2;

        p1 = start;
        for (i = 0; i < pn; i++) {
                if (points_eq(p1, pairs[i][0])) {
                        p2 = pairs[i][1];
                        break;
                } else if (points_eq(p1, pairs[i][1])) {
                        p2 = pairs[i][0];
                        break;
                }
        }
        strcpy(tour, "");
        while (n > 1) {
                sprintf(buf, "(%d, %d)\n", p1->x, p1->y);
                strcat(tour, buf);
                pop_all(pairs, p1, &pn);

                for (i = 0; i < pn; i++) {
                        if (points_eq(p2, pairs[i][0])) {
                                p1 = pairs[i][0];
                                p2 = pairs[i][1];
                                break;
                        }
                        else if (points_eq(p2, pairs[i][1])) {
                                p1 = pairs[i][1];
                                p2 = pairs[i][0];
                                break;
                        }
                }
                n--;
        }
        sprintf(buf, "(%d, %d)\n(%d, %d)\n", p2->x, p2->y, start->x, start->y);
        strcat(tour, buf);
}

/*
 * points_eq - return 1 if points are equal, 0 otherwise
 */
int
points_eq(struct point *p1, struct point *p2)
{
        return p1->x == p2->x && p1->y == p2->y;
}

int
main(int argc, char **argv)
{
        struct point points1[8] = {
                { .x = 0, .y = 0 },
                { .x = 0, .y = 3 },
                { .x = -3, .y = -1 },
                { .x = 2, .y = -1 },
                { .x = 2, .y = 0 },
                { .x = 0, .y = -3 },
                { .x = -3, .y = 1 },
                { .x = 1, .y = 1 }
        };
        struct point points2[7] = {
                { .x = 0, .y = 0 },
                { .x = -21, .y = 0 },
                { .x = -1, .y = 0 },
                { .x = -5, .y = 0 },
                { .x = 11, .y = 0 },
                { .x = 1, .y = 0 },
                { .x = 3, .y = 0 }
        };
        struct point points3[6] = {
                { .x = 0, .y = -2 },
                { .x = 0, .y = 2 },
                { .x = -3, .y = 2 },
                { .x = 3, .y = 2 },
                { .x = 3, .y = -2 },
                { .x = -3, .y = -2 }
        };

        char *tour_a = "(0, 0)\n(1, 1)\n(2, 0)\n(2, -1)\n(0, -3)\n(-3, -1)\n(-3, 1)\n(0, 3)\n(0, 0)\n";
        char *tour_b = "(0, 0)\n(-1, 0)\n(1, 0)\n(3, 0)\n(-5, 0)\n(-21, 0)\n(11, 0)\n(0, 0)\n";
        char *tour_c = "(-3, 2)\n(0, 2)\n(3, 2)\n(3, -2)\n(0, -2)\n(-3, -2)\n(-3, 2)\n";
        char *tour_d = "(-21, 0)\n(-5, 0)\n(-1, 0)\n(0, 0)\n(1, 0)\n(3, 0)\n(11, 0)\n(-21, 0)\n";
        char *tour_e = "(2, -1)\n(2, 0)\n(1, 1)\n(0, 0)\n(0, 3)\n(-3, 1)\n(-3, -1)\n(0, -3)\n(2, -1)\n";

        char tour[MAX_TOUR];

        nearest_neighbor(points1, tour, 8);
        assert(strcmp(tour, tour_a) == 0);

        nearest_neighbor(points2, tour, 7);
        assert(strcmp(tour, tour_b) == 0);

        closest_pair(points3, tour, &points3[2], 6);
        assert(strcmp(tour, tour_c) == 0);

        closest_pair(points1, tour, &points1[3], 8);
        assert(strcmp(tour, tour_e) == 0);

        closest_pair(points2, tour, &points2[1], 7);
        assert(strcmp(tour, tour_d) == 0);

        return 0;
}
