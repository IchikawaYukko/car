/*========================================
 *    car.c: CAR version 1.00
 *
 * Original Copyright:
 *    sl.c: SL version 5.03
 *        Copyright 1993,1998,2014-2015
 *                  Toyoda Masashi
 *                  (mtoyoda@acm.org)
 *        Last Modified: 2014/06/03
 *========================================
 */
/* car version 1.00 : Fork from sl.                                          */
/*                                              by KusaReMKN      2022/12/31 */
/* sl version 5.03 : Fix some more compiler warnings.                        */
/*                                              by Ryan Jacobs    2015/01/19 */
/* sl version 5.02 : Fix compiler warnings.                                  */
/*                                              by Jeff Schwab    2014/06/03 */
/* sl version 5.01 : removed cursor and handling of IO                       */
/*                                              by Chris Seymour  2014/01/03 */
/* sl version 5.00 : add -c option                                           */
/*                                              by Toyoda Masashi 2013/05/05 */
/* sl version 4.00 : add C51, usleep(40000)                                  */
/*                                              by Toyoda Masashi 2002/12/31 */
/* sl version 3.03 : add usleep(20000)                                       */
/*                                              by Toyoda Masashi 1998/07/22 */
/* sl version 3.02 : D51 flies! Change options.                              */
/*                                              by Toyoda Masashi 1993/01/19 */
/* sl version 3.01 : Wheel turns smoother                                    */
/*                                              by Toyoda Masashi 1992/12/25 */
/* sl version 3.00 : Add d(D51) option                                       */
/*                                              by Toyoda Masashi 1992/12/24 */
/* sl version 2.02 : Bug fixed.(dust remains in screen)                      */
/*                                              by Toyoda Masashi 1992/12/17 */
/* sl version 2.01 : Smoke run and disappear.                                */
/*                   Change '-a' to accident option.                         */
/*                                              by Toyoda Masashi 1992/12/16 */
/* sl version 2.00 : Add a(all),l(long),F(Fly!) options.                     */
/*                                              by Toyoda Masashi 1992/12/15 */
/* sl version 1.02 : Add turning wheel.                                      */
/*                                              by Toyoda Masashi 1992/12/14 */
/* sl version 1.01 : Add more complex smoke.                                 */
/*                                              by Toyoda Masashi 1992/12/14 */
/* sl version 1.00 : SL runs vomiting out smoke.                             */
/*                                              by Toyoda Masashi 1992/12/11 */

#include <curses.h>
#include <signal.h>
#include <unistd.h>
#include "car.h"

int add_car(int x);
int my_mvaddstr(int y, int x, char *str);

int CARLENGTH = 24;
int CARS      =  1;

int my_mvaddstr(int y, int x, char *str)
{
    for ( ; x < 0; ++x, ++str)
        if (*str == '\0')  return ERR;
    for ( ; *str != '\0'; ++str, ++x)
        if (mvaddch(y, x, *str) == ERR)  return ERR;
    return OK;
}

int main(int argc, char *argv[])
{
    int x;
    extern int CARLENGTH, CARS;

    CARS = argc;
    CARLENGTH = 24 * CARS;

    initscr();
    signal(SIGINT, SIG_IGN);
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    leaveok(stdscr, TRUE);
    scrollok(stdscr, FALSE);

    for (x = COLS - 1; ; --x) {
        if (add_car(x) == ERR) break;
        getch();
        refresh();
        usleep(40000);
    }
    mvcur(0, COLS - 1, LINES - 1, 0);
    endwin();

    return 0;
}


int add_car(int x)
{
    static char *sl[CARPATTERNS][CARHEIGHT + 1]
        = {{CAR1, CAR2, CAR3, CAR4, CAR11, CAR12, DELLN},
           {CAR1, CAR2, CAR3, CAR4, CAR21, CAR22, DELLN},
           {CAR1, CAR2, CAR3, CAR4, CAR31, CAR32, DELLN},
           {CAR1, CAR2, CAR3, CAR4, CAR41, CAR42, DELLN}};

    int i, j, y;

    if (x < - CARLENGTH)  return ERR;
    y = LINES / 2 - 3;

    for (i = 0; i <= CARHEIGHT; ++i) {
        for (j = 0; j < CARS; ++j) {
            my_mvaddstr(y + i, x + 24 * j,
                    sl[(CARLENGTH + x + (1 << j)) / 3 % CARPATTERNS][i]);
        }
    }

    return OK;
}
