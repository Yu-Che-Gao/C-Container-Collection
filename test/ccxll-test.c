#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/ccxll.h"

#define INCR_LOOP1(_a, _b)          for (int _a = 0; _a < (_b); _a++)
#define INCR_LOOP2(_a, _b, _c, _d)  INCR_LOOP1(_a, _b)  INCR_LOOP1(_c, _d)


int main(void)
{
    /* Test 0 */
    /* Demonstration */

    printf("Test 0: \n\n");

    {
        ccxll(char*) msg;
        ccxll_init(msg);

        ccxll_iter(char*) msg_iter;
        ccxll_iter_init(msg_iter, msg);

        ccxll_push_back(msg, "Hello everyone:\n");
        ccxll_push_back(msg, "Welcome to C Container Collection Project!\n");

        CCXLL_TRAVERSAL(msg, msg_iter)
            printf("%s", ccxll_iter_dref(msg_iter));

        ccxll_free(msg);
    }


    /* Test 1 */
    /* Push Back */

    printf("\n\nTest 1: \n");

    {
        ccxll(char*) list;
        ccxll_init(list);

        char *num_str[10] = { "five" , "six", "four", "seven", "three",
                              "eight", "two", "nine", "one"  , "ten"    };

        int cnt = 0;

        while (puts("") && cnt < 10)
        {
            ccxll_iter(char*) iter;
            ccxll_iter_init(iter, list);

            ccxll_push_front(list, num_str[cnt++]);
            ccxll_push_back (list, num_str[cnt++]);

            CCXLL_TRAVERSAL(list, iter)
                printf("%s ", ccxll_iter_dref(iter));
        }

        ccxll_free(list);
    }


    /* Test 2 */
    /* Push Back */

    printf("\n\nTest 2: ");

    {
        ccxll(int) list;
        ccxll_init(list);

        int cnt = 0;

        while (cnt < 10000000)
            ccxll_push_back(list, cnt++);

        ccxll_free(list);

        puts("Test deallocation.");
    }


    /* Test 3 */
    /* Push Back */

    printf("\n\nTest 3: ");

    {
        typedef struct
        {
            char *msg[2];

        }   msg_struct;

        ccxll(msg_struct) list;
        ccxll_init(list);

        ccxll_iter(msg_struct) iter;
        ccxll_iter_init(iter, list);

        msg_struct msg_1, msg_2;

        msg_1.msg[0] = "Push";
        msg_1.msg[1] = "back";
        msg_2.msg[0] = "two";
        msg_2.msg[1] = "structs.\n";

        ccxll_push_back(list, msg_1);
        ccxll_push_back(list, msg_2);

        CCXLL_TRAVERSAL(list, iter)
            printf("%s ", ccxll_iter_dref(iter).msg[0]),
            printf("%s ", ccxll_iter_dref(iter).msg[1]);

        ccxll_free(list);
    }


    /* Test 4 */
    /* Iter Incr */

    printf("\n\nTest 4: ");

    {
        ccxll(int) list;
        ccxll_init(list);

        ccxll_iter(int) iter;
        ccxll_iter_init(iter, list);

        CCXLL_TRAVERSAL(list, iter)
            printf("%d", ccxll_iter_dref(iter));

        if (ccxll_iter_incr(iter) == NULL)
            puts("The iterator points to the tail.");

        (void)ccxll_iter_dref(iter);

        ccxll_free(list);
    }


    /* Test 5 */
    /* Back and Front */

    printf("\n\nTest 5: ");

    {
        ccxll(char*) list;
        ccxll_init(list);

        ccxll_iter(char*) iter;
        ccxll_iter_init(iter, list);

        (void)ccxll_front(list);
        (void)ccxll_back(list);
        ccxll_push_front(list, "Failed ");
        ccxll_push_front(list, "to access.\n");
        ccxll_back(list)  = "Element access ";
        ccxll_front(list) = "succeed.\n";

        CCXLL_BACKWARD_TRAVERSAL(list, iter)
            printf("%s", ccxll_iter_dref(iter));

        ccxll_free(list);
    }


    /* Test 6 */
    /* Push and Pop */

    printf("\n\nTest 6: ");

    {
        ccxll(int) list;
        ccxll_init(list);

        ccxll_iter(int) iter;
        ccxll_iter_init(iter, list);

        ccxll_pop_front(list);

        ccxll_push_front(list, 1);
        ccxll_pop_front (list);

        ccxll_push_back(list, 1);
        ccxll_push_back(list, 2);
        ccxll_pop_back (list);

        CCXLL_TRAVERSAL(list, iter)
            printf("'%d' == '1'\n",  ccxll_iter_dref(iter));

        ccxll_free(list);
    }


    /* Test 7 */
    /* Push and Clear */

    printf("\n\nTest 7: \n");

    {
        ccxll(int) list;
        ccxll_init(list);

        puts("\nPushing back 10^7 elements...");
        for (int cnt = 0; cnt < 10000000; cnt++)
            ccxll_push_back(list, cnt);
        puts("Clearing the ccxll container...");
        ccxll_clear(list);

        puts("\nPushing back 10^7 elements...");
        for (int cnt = 0; cnt < 10000000; cnt++)
            ccxll_push_back(list, cnt);
        puts("Deallocating the ccxll container...");
        ccxll_free(list);
    }


    /* Test 8 */
    /* Packed */

    printf("\n\nTest 8: \n\n");

    {
        ccxll_pckd(char) list;
        ccxll_init(list);

        ccxll_iter(char) iter;
        ccxll_iter_init(iter, list);

        for (int cnt = 0; cnt < 10000000; cnt++)
            ccxll_push_back(list, cnt);

        char var = 0;

        CCXLL_TRAVERSAL(list, iter)
            if (var != 127)  printf("%03d ", (var = ccxll_iter_dref(iter)));
            else  break;

        puts("");

        ccxll_free(list);
    }


    /* Test 9 */
    /* Insert and Erase */

    printf("\n\nTest 9: \n\n");

    {
        ccxll_pckd(int) list;
        ccxll_init(list);

        ccxll_iter_pckd(int) iter;
        ccxll_iter_init(iter, list);

        for (int cnt = 0; cnt < 6; cnt++)
            ccxll_push_back(list, 2 * cnt + 1);

        CCXLL_TRAVERSAL(list, iter)
            printf("%d ", ccxll_iter_dref(iter));

        ccxll_iter_head(iter, list);

        for (int cnt = 0; cnt <= 6; cnt++)
        {
            ccxll_iter_incr(iter);
            ccxll_insert(iter, 2 * cnt);
            ccxll_iter_incr(iter);
        }

        printf("-> ");
        CCXLL_TRAVERSAL(list, iter)
            printf("%d ", ccxll_iter_dref(iter));

        ccxll_iter_begin(iter, list);

        for (int cnt = 0; cnt <= 5; cnt++)
        {
            ccxll_iter_incr(iter);
            ccxll_erase(iter);
        }

        printf("-> ");
        CCXLL_TRAVERSAL(list, iter)
            printf("%d ", ccxll_iter_dref(iter));

        ccxll_iter_begin(iter, list);

        for (int cnt = 0; cnt <= 5; cnt++)
            ccxll_erase(iter);

        printf("-> ");
        CCXLL_TRAVERSAL(list, iter)
            printf("%d ", ccxll_iter_dref(iter));

        ccxll_iter_begin(iter, list);

        ccxll_erase(iter);

        puts("-> (none)");
        CCXLL_TRAVERSAL(list, iter)
            printf("%d ", ccxll_iter_dref(iter));

        ccxll_free(list);
    }


    /* Test 10 */
    /* Move Range */

    printf("\n\nTest 10: \n\n");

    {
        ccxll(int) list;
        ccxll_init(list);

        ccxll_iter(int) iter, move[3];
        ccxll_iter_init(iter, list);
        ccxll_iter_init(move[0], list);
        ccxll_iter_init(move[1], list);
        ccxll_iter_init(move[2], list);

        int pos[8][3] = { {2, 4, 6} , {-1, 2, 0}, {0, -1, -2}, {1, -1, 2},
                          {-4, 0, 3}, {0, 2, 0} , {1, 0, -1} , {1, -1, 1} };

        for (int cnt = 0; cnt < 7; cnt++)
            ccxll_push_back(list, cnt + 'A');

        ccxll_iter_head(move[0], list);
        ccxll_iter_head(move[1], list);
        ccxll_iter_head(move[2], list);

        CCXLL_TRAVERSAL(list, iter)
            printf("%c ", ccxll_iter_dref(iter));

        for (int cnt = 0; cnt < 8; cnt++)
        {
            ccxll_iter_advance(move[0], pos[cnt][0]);
            ccxll_iter_advance(move[1], pos[cnt][1]);
            ccxll_iter_advance(move[2], pos[cnt][2]);

            ccxll_move_range(move[0], move[1], move[2]);

            printf("/ ");
            CCXLL_TRAVERSAL(list, iter)
                printf("%c ", ccxll_iter_dref(iter));
        }

        puts("= A C E D B F G /");

        ccxll_free(list);
    }


    /* Test 11 */
    /* Merge Range */

    printf("\n\nTest 11: \n\n");

    {
        ccxll(int) list;
        ccxll_init(list);

        ccxll_iter(int) iter, iters[4];
        ccxll_iter_init(iter, list);
        INCR_LOOP1(cnt, 4)  ccxll_iter_init(iters[cnt], list);

        int str1[] = {0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5, 7, 9, 11, 13, 15};

        for (int cnt = 0; cnt < 2; cnt++)
        {
            INCR_LOOP1(cnt, 16)  ccxll_push_back(list, str1[cnt]);

            CCXLL_TRAVERSAL(list, iter)
                printf("%d ", ccxll_iter_dref(iter));

            printf("-> ");

            switch (cnt)
            {
                case 0:
                INCR_LOOP1(cnt, 3)  ccxll_iter_begin(iters[cnt], list);
                INCR_LOOP1(cnt, 3)  ccxll_iter_advance(iters[cnt], 8 * cnt);

                ccxll_merge_range(iters[0], iters[1], iters[2], iters[3]);
                break;

                case 1:
                ccxll_sort(list, iters);
                break;
            }

            CCXLL_TRAVERSAL(list, iter)
                printf("%d ", ccxll_iter_dref(iter));

            puts("");

            ccxll_clear(list);
        }

        ccxll_free(list);
    }


    /* Test 12 */
    /* Sort */

    printf("\n\nTest 12: \n\n");

    {
        ccxll(int) list;
        ccxll_init(list);

        ccxll_iter(int) iter, iters[4];
        ccxll_iter_init(iter, list);
        INCR_LOOP1(cnt, 4)  ccxll_iter_init(iters[cnt], list);

        int length = 1000;
        srand(time(NULL));

        INCR_LOOP1(cnt, length)  ccxll_push_back(list, rand());

        ccxll_sort(list, iters);

        CCXLL_TRAVERSAL(list, iter)
            printf("Max = %10d\r", ccxll_iter_dref(iter));

        puts("");

        ccxll_free(list);
    }


    /* Test 13 */
    /* Sort Parallel */

    printf("\n\nTest 13: \n\n");

    {
        const int n = 2;

        ccxll(int) list, lists[n];
        ccxll_init(list);
        INCR_LOOP1(i, n)  ccxll_init(lists[i]);

        ccxll_iter(int) iter, iters[n][4];
        ccxll_iter_init(iter, list);
        INCR_LOOP2(i, n, j, 4)  ccxll_iter_init(iters[i][j], lists[i]);

        int length = 10000;
        INCR_LOOP1(cnt, length)  ccxll_push_back(list, length - cnt);

        ccxll_sort_openmp(list, lists, iters, n);

        CCXLL_TRAVERSAL(list, iter)
            printf("Ten thousand = %05d\r", ccxll_iter_dref(iter));

        puts("");

        ccxll_free(list);
        INCR_LOOP1(i, n)  ccxll_free(lists[i]);
    }


    return 0;
}