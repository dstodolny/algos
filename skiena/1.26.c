/*
 * 1.26 - Nearest Neighbor and Closest Pair implementation
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>

#define MAX_BUF 256
#define MAX_TOUR 4096

struct point {
        int x;
        int y;
};

void nearest_neighbor(struct point points[], char *tour, int n);
int squared_distance(struct point p1, struct point p2);
void pop(struct point p, struct point points[], int *n);
void closest_pair(struct point points[], char *tour, int n);

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
                sd_min = squared_distance(p, p_next);

                for (j = 1; j < n_left; j++) {
                        sd = squared_distance(p, unvisited[j]);
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
 * squared_distance - Squared Euclidean distance
 */
int
squared_distance(struct point p1, struct point p2)
{
        int dx = p2.x - p1.x;
        int dy = p2.y - p1.y;
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
closest_pair(struct point points[], char *tour, int n)
{
}

int
main(int argc, char **argv)
{
        int i;
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
        char *tour1 = "(0, 0)\n(1, 1)\n(2, 0)\n(2, -1)\n(0, -3)\n(-3, -1)\n(-3, 1)\n(0, 3)\n(0, 0)\n";
        char *tour2 = "(0, 0)\n(-1, 0)\n(1, 0)\n(3, 0)\n(-5, 0)\n(-21, 0)\n(11, 0)\n(0, 0)\n";
        char tour[MAX_TOUR];

        nearest_neighbor(points1, tour, 8);
        assert(strcmp(tour, tour1) == 0);

        nearest_neighbor(points2, tour, 7);
        assert(strcmp(tour, tour2) == 0);

        return 0;
}
