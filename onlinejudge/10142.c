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
        int index;
        int votes;
        struct candidate *next;
};

void candidate_insert(struct candidate **headp, int index, char *name);
void read_candidates(struct candidate **head, int n);
int read_ballots(int votes[][MAX_CANDIDATES]);
void print_candidates(struct candidate *head);
void print_votes(int votes[][MAX_CANDIDATES], int ballots_num, int candidate_num);

struct candidate *cnd_head;
int votes[MAX_BALLOTS][MAX_CANDIDATES];

void
candidate_insert(struct candidate **headp, int index, char *name)
{
        struct candidate *new;
        if ((new = malloc(sizeof(struct candidate))) == NULL)
                exit(1);
        new->index = index;
        new->votes = 0;
        strcpy(new->name, name);
        new->next = *headp;
        *headp = new;
}

/*
 * read_candidates - read n candidates
 */
void
read_candidates(struct candidate **head, int n)
{
        int i;
        char line[MAX_LINE];

        for (i = 0; i < n && i < MAX_CANDIDATES; i++) {
                fgets(line, sizeof(line), stdin);
                line[strcspn(line, "\n")] = '\0';
                candidate_insert(head, i+1, line);
        }
}

/*
 * read_ballots - read available ballots into votes and return their
 * number
 */
int
read_ballots(int votes[][MAX_CANDIDATES])
{
        int i, j;
        char line[MAX_LINE], buf[MAX_BUF], *lp, *bp;


        for (i = 0; i < MAX_BALLOTS; i++) {
                fgets(line, sizeof(line), stdin);
                if (line[0] == '\n')
                        break;
                for (lp = line, j = 0; *lp; lp++) {
                        if (isdigit(*lp)) {
                                bp = buf;
                                *bp++ = *lp;
                                if (*(lp+1) && isdigit(*(lp+1)))
                                        *bp++ = *(++lp);
                                *bp = '\0';
                                votes[i][j] = atoi(buf);
                                j++;
                        }
                }
        }

        return j;
}

void
print_candidates(struct candidate *head)
{
        while(head != NULL) {
                printf("%d\t%s: %d\n", head->index, head->name, head->votes);
                head = head->next;
        }
}

void
print_votes(int ballots_num, int candidates_num)
{
        int i, j;
        for (i = 0; i < ballots_num; i++) {
                for (j = 0; j < candidates_num; j++) {
                        printf("%d ", votes[i][j]);
                }
                printf("\n");
        }
}


/* void */
/* candlst_deinit(struct cnd *candlst) */
/* { */
/*         struct cnd *tmp; */
/*  */
/*         while (candlst != null) { */
/*                 tmp = head; */
/*                 candlst = candlst->next; */
/*                 free(tmp); */
/*         } */
/* } */


int
main(int argc, char **argv)
{
        char line[MAX_LINE];
        int cases, i, candidates_num, ballots_num;

        fgets(line, sizeof(line), stdin);
        cases = atoi(line);
        for (i = 0; i < cases; i++) {
                cnd_head = NULL;
                fgets(line, sizeof(line), stdin); /* Read empty line */
                fgets(line, sizeof(line), stdin);
                candidates_num = atoi(line);

                read_candidates(candidates_num);
                ballots_num = read_ballots();

                print_candidates();
                print_votes(ballots_num, candidates_num);
        }
}


/* int */
/* main(int argc, char **argv) */
/* { */
/*         int cases, n, m, i, j, k, weakest; */
/*         char line[MAX_LINE], buf[MAX_BUF], *lp, *bp; */
/*         int votes[MAX_BALLOTS][MAX_CNDS]; */
/*         struct cnd *cnds; */
/*  */
/*  */
/*         fgets(line, sizeof(line), stdin); */
/*         cases = atoi(line); */
/*         for (i = 0; i < cases; i++) { */
/*                 fgets(line, sizeof(line), stdin); /\* Read empty line *\/ */
/*                 fgets(line, sizeof(line), stdin); */
/*  */
/*                 n = atoi(line); */
/*  */
/*                 if ((cnds = malloc(n*sizeof(struct cnd))) == NULL) */
/*                         exit(1); */
/*  */
/*                 /\* Read cnd names *\/ */
/*                 for (j = 0; j < n && j < MAX_CNDS; j++) { */
/*                         fgets(line, sizeof(line), stdin); */
/*                         line[strcspn(line, "\n")] = '\0'; */
/*                         strcpy(cnds[j].name, line); */
/*                         cnds[j].votes = 0; */
/*                 } */
/*  */
/*                 /\* Read votes *\/ */
/*                 for (j = 0; j < MAX_BALLOTS; j++) { */
/*                         fgets(line, sizeof(line), stdin); */
/*                         if (line[0] == '\n') */
/*                                 break; */
/*                         for (lp = line, k = 0; *lp; lp++) { */
/*                                 if (isdigit(*lp)) { */
/*                                         bp = buf; */
/*                                         *bp++ = *lp; */
/*                                         if (*(lp+1) && isdigit(*(lp+1))) */
/*                                                 *bp++ = *(++lp); */
/*                                         *bp = '\0'; */
/*                                         votes[j][k] = atoi(buf); */
/*                                         k++; */
/*                                 } */
/*                         } */
/*  */
/*                 } */
/*                 m = j;          /\* Store the number of ballots *\/ */
/*  */
/*                 /\* Phase 1 - count votes *\/ */
/*                 for (j = 0; j < m; j++) */
/*                         cnds[votes[j][0]-1].votes++; */
/*                 for (j = 0; j < n; j++) { */
/*                         if (cnds[j].votes > 0.5 * m) { */
/*                                 printf("%s\n", cnds[j].name); */
/*                                 return 0; */
/*                         } */
/*                 } */
/*                 /\* Phase 2 - eliminate the weakest *\/ */
/*                 /\* Find the weakest cnd *\/ */
/*                 weakest = 0; */
/*                 for (j = 1; j < n; j++) { */
/*                         if (cnds[j].votes < cnds[weakest].votes) */
/*                                 weakest = j; */
/*                 } */
/*  */
/* #ifdef DEBUG */
/*                 for (j = 0; j < n; j++) */
/*                         printf("%s: %d\n", cnds[j].name, cnds[j].votes); */
/* #endif */
/*  */
/*                 free(cnd); */
/*         } */
/*  */
/* #ifdef DEBUG */
/*         for (i = 0; i < j; i++) { */
/*                 for (k = 0; k < n; k++) { */
/*                         printf("%d ", votes[i][k]); */
/*                 } */
/*                 printf("\n"); */
/*         } */
/* #endif */
/*  */
/*  */
/*         return 0; */
/* } */
