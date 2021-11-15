#include<stdio.h>
#include<stdlib.h>
#include "declrns.h"

//Additional date-time functions:
time ip_time(time t)
{
    printf("\n Hours: "); scanf("%d", &t.hrs);
    printf("\n Minutes: "); scanf("%d", &t.mins);
    return t;
};
date ip_date(date d)
{
    printf("\n Year: "); scanf("%d", &d.yr);
    printf("\n Month: "); scanf("%d", &d.mnt);
    printf("\n Day: "); scanf("%d", &d.day);
    return d;
};
void op_time(time t)
{
    printf("\n Hours: %d", t.hrs);
    printf("\n Minutes: %d", t.mins);
};
void op_date(date d)
{
    printf("\n %d/%d/%d", d.day, d.mnt, d.yr);
};