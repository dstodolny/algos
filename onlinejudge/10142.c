#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define DEBUG

#define MAX_LINE 256
#define MAX_BUF 8
#define MAX_NAME 80
#define MAX_CANDIDATES 20
#define MAX_BALLOTS 1000

struct candidate {
        char name[MAX_NAME];
        int votes;
};

int
main(int argc, char **argv)
{
        int cases, n, m, i, j, k, weakest;
        char line[MAX_LINE], buf[MAX_BUF], *lp, *bp;
        int votes[MAX_BALLOTS][MAX_CANDIDATES];
        struct candidate *candidates;


        fgets(line, sizeof(line), stdin);
        cases = atoi(line);
        for (i = 0; i < cases; i++) {
                fgets(line, sizeof(line), stdin); /* Read empty line */
                fgets(line, sizeof(line), stdin);

                n = atoi(line);

                if ((candidates = malloc(n*sizeof(struct candidate))) == NULL)
                        exit(1);

                /* Read candidate names */
                for (j = 0; j < n && j < MAX_CANDIDATES; j++) {
                        fgets(line, sizeof(line), stdin);
                        line[strcspn(line, "\n")] = '\0';
                        strcpy(candidates[j].name, line);
                        candidates[j].votes = 0;
                }

                /* Read votes */
                for (j = 0; j < MAX_BALLOTS; j++) {
                        fgets(line, sizeof(line), stdin);
                        if (line[0] == '\n')
                                break;
                        for (lp = line, k = 0; *lp; lp++) {
                                if (isdigit(*lp)) {
                                        bp = buf;
                                        *bp++ = *lp;
                                        if (*(lp+1) && isdigit(*(lp+1)))
                                                *bp++ = *(++lp);
                                        *bp = '\0';
                                        votes[j][k] = atoi(buf);
                                        k++;
                                }
                        }

                }
                m = j;          /* Store the number of ballots */

                /* Phase 1 - count votes */
                for (j = 0; j < m; j++)
                        candidates[votes[j][0]-1].votes++;
                for (j = 0; j < n; j++) {
                        if (candidates[j].votes > 0.5 * m) {
                                printf("%s\n", candidates[j].name);
                                return 0;
                        }
                }
                /* Phase 2 - eliminate the weakest */
                /* Find the weakest candidate */
                weakest = 0;
                for (j = 1; j < n; j++) {
                        if (candidates[j].votes < candidates[weakest].votes)
                                weakest = j;
                }

#ifdef DEBUG
                for (j = 0; j < n; j++)
                        printf("%s: %d\n", candidates[j].name, candidates[j].votes);
#endif

                free(candidates);
        }

#ifdef DEBUG
        for (i = 0; i < j; i++) {
                for (k = 0; k < n; k++) {
                        printf("%d ", votes[i][k]);
                }
                printf("\n");
        }
#endif


        return 0;
}
