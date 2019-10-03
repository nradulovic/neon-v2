/*
 * File:   stdio.c
 * Author: Nenad.Radulovic
 *
 * Created on 15. avgust 2019., 11.01
 */

#include "conio.h"
#include "sys/nstdio.h"

char getch(void)
{
    return nstdio_getc(&nstdio_buff);
}

void putch(char c)
{
    nstdio_putc(&nstdio_buff, c);
}