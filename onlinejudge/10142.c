#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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
void candidate_remove(struct candidate **headp, int index);
struct candidate *candidate_search(struct candidate *head, int index);
void candidate_free(struct candidate *head);
void read_candidates(struct candidate **head, int n);
int read_ballots(int votes[][MAX_CANDIDATES]);
void count_votes(struct candidate *head, int votes[][MAX_CANDIDATES], int ballots_num, int candidates_num);
int find_winning_votes(struct candidate *head, int ballots_num, int candidates_num);
void remove_losers(struct candidate **head, int votes[][MAX_CANDIDATES], int ballots_num);
void remove_vote(int *ballot, int index);

void
candidate_insert(struct candidate **headp, int index, char *name)
{
        struct candidate *cnd, *new;
        if ((new = malloc(sizeof(struct candidate))) == NULL)
                exit(1);
        new->index = index;
        new->votes = 0;
        new->next = NULL;
        strcpy(new->name, name);

        if (*headp == NULL) {
                *headp = new;
                return;
        }

        for (cnd = *headp; cnd->next != NULL; cnd=cnd->next)
                ;
        cnd->next = new;
}

void
candidate_remove(struct candidate **headp, int index)
{
        struct candidate *head = *headp;
        struct candidate *prev = NULL;

        if (index <= 0)
                return;

        if (head != NULL && head->index == index ) {
                *headp = head->next;
                free(head);
                return;
        }

        while (head != NULL && head->index != index) {
                prev = head;
                head = head->next;
        }

        if (head == NULL)
                return;

        prev->next = head->next;
        free(head);
}

struct candidate *
candidate_search(struct candidate *head, int index)
{
        while(head != NULL) {
                if (head->index == index)
                        return head;
                head = head->next;
        }
        return NULL;
}

void
candidate_free(struct candidate *head)
{
        struct candidate *tmp;

        while (head != NULL) {
                tmp = head;
                head = head->next;
                free(tmp);
        }
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
                lp = fgets(line, sizeof(line), stdin);
                if (lp == NULL || line[0] == '\n')
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

        return i;
}


void
count_votes(struct candidate *head, int votes[][MAX_CANDIDATES], int ballots_num, int candidates_num)
{
        int i, index;
        struct candidate *cnd;

        if (head == NULL)
                return;

        for (cnd = head; cnd != NULL; cnd=cnd->next) {
                cnd->votes = 0;
        }

        for (i = 0; i < ballots_num; i++) {
                index = votes[i][0];
                if ((cnd = candidate_search(head, index)) == NULL)
                        exit(1);
                cnd->votes++;
        }
}

int
find_winning_votes(struct candidate *head, int ballots_num, int candidates_num)
{
        struct candidate *cnd;

        /* Check for a single winner */
        for (cnd = head; cnd != NULL; cnd=cnd->next) {
                if (cnd->votes > 0.5 * ballots_num) {
                        return cnd->votes;
                }
        }

        /* Check for multiple winners */
        for (cnd = head; cnd->next != NULL; cnd=cnd->next) {
                if (cnd->votes != cnd->next->votes)
                        return 0;
        }
        return cnd->votes;
}

void
remove_losers(struct candidate **headp, int votes[][MAX_CANDIDATES], int ballots_num)
{
        int i, j;
        struct candidate *head, *losers[MAX_CANDIDATES];
        int losing_votes, nlosers;

        if (*headp == NULL)
                return;

        losing_votes = (*headp)->votes;

        /* Find the lowest number of votes */
        for (head=*headp; head != NULL; head=head->next) {
                if (head->votes < losing_votes)
                        losing_votes = head->votes;
        }

        /* Find all losers */
        nlosers = 0;
        for (head=*headp; head != NULL; head=head->next) {
                if (head->votes == losing_votes) {
                        losers[nlosers++] = head;
                }
        }

        /* For each loser remove his votes from ballots and remove the
         * loser from the candidates list */
        for (i = 0; i < nlosers; i++) {
                for (j = 0; j < ballots_num; j++) {
                        remove_vote((int *)votes[j], losers[i]->index);
                }
                candidate_remove(headp, losers[i]->index);
        }
}

void
remove_vote(int *ballot, int vote)
{
        int *bp;
        for (bp = ballot; *bp != vote && bp < ballot + MAX_CANDIDATES; bp++)
                ;
        for ( ; bp < ballot + MAX_CANDIDATES - 1; bp++) {
                *bp = *(bp + 1);
        }
}

int
main(int argc, char **argv)
{
        char line[MAX_LINE];
        int cases, i, candidates_num, ballots_num, votes_num;
        struct candidate *cnd_head, *cnd;
        int votes[MAX_BALLOTS][MAX_CANDIDATES];

        fgets(line, sizeof(line), stdin);
        cases = atoi(line);
        fgets(line, sizeof(line), stdin); /* Read empty line */
        for (i = 0; i < cases; i++) {
                cnd_head = NULL;
                fgets(line, sizeof(line), stdin);
                candidates_num = atoi(line);

                read_candidates(&cnd_head, candidates_num);
                ballots_num = read_ballots(votes);

                count_votes(cnd_head, votes, ballots_num, candidates_num);

                while (candidates_num > 0) {
                        votes_num = find_winning_votes(cnd_head, ballots_num, candidates_num);
                        if (votes_num > 0) {
                                for (cnd = cnd_head; cnd != NULL; cnd=cnd->next) {
                                        if (cnd->votes == votes_num)
                                                printf("%s\n", cnd->name);
                                }
                                if (i < cases - 1)
                                        printf("\n");
                                candidate_free(cnd_head);
                                break;
                        }
                        remove_losers(&cnd_head, votes, ballots_num);
                        candidates_num--;
                        count_votes(cnd_head, votes, ballots_num, candidates_num);

                }
        }
}
