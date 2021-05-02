/*
 * 61.c - Rotate List
 *
 * Given the head of a linked list, rotate the list to the right by k
 * places.
 */
#include <assert.h>
#include "algos.h"

struct ListNode {
        int val;
        struct ListNode *next;
};

struct ListNode *rotateRight(struct ListNode* head, int k);

struct ListNode *
rotateRight(struct ListNode *head, int k)
{
        int n = 0;
        int i;
        struct ListNode *lp, *tmp;

        if (!head || !head->next)
                return head;

        for (lp = head; lp->next != NULL; lp=lp->next)
                n++;
        tmp = lp;
        n++;

        if (k % n == 0)
                return head;

        for (i = 0, lp = head; i<n-(k%n)-1; i++, lp=lp->next)
                ;

        tmp->next = head;
        tmp = lp->next;
        lp->next = NULL;

        return tmp;
}

int
main(int argc, char **argv)
{
        struct ListNode L5 = {.val = 5, .next = NULL};
        struct ListNode L4 = {.val = 4, .next = &L5};
        struct ListNode L3 = {.val = 3, .next = &L4};
        struct ListNode L2 = {.val = 2, .next = &L3};
        struct ListNode L1 = {.val = 1, .next = &L2};

        struct ListNode *lp;

        lp = rotateRight(&L1, 0);
        assert(lp == &L1);

        lp = rotateRight(lp, 1);
        assert(lp == &L5);

        lp = rotateRight(lp, 1);
        assert(lp == &L4);

        lp = rotateRight(lp, 3);
        assert(lp == &L1);

        lp = rotateRight(lp, 3);
        assert(lp == &L3);

        return 0;
}
