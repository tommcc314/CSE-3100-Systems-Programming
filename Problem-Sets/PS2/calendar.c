#include <stdio.h>
#include "calendar.h"

int numDaysInMonth(int month, int year){
    switch(month){
    case JAN:
        return 31;
        break;
    case FEB:
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) ? 29 : 28;
        break;
    case MAR:
        return 31;
        break;
    case APR:
        return 30;
        break;
    case MAY:
        return 31;
        break;
    case JUN:
        return 30;
        break;
    case JUL:
        return 31;
        break;
    case AUG:
        return 31;
        break;
    case SEP:
        return 30;
        break;
    case OCT:
        return 31;
        break;
    case NOV:
        return 30;
        break;
    case DEC:
        return 31;
        break;
    default:
        return -1;
    }
}

int numFirstMondays(int startYear, int endYear, int janFirstWeekday)
{
    int weekday = janFirstWeekday, res = 0;
    for (int year = startYear; year <= endYear; ++year) {
        for (int month = 1; month <= 12; ++month) {
            if (weekday == 1) res++;
            weekday = (weekday + numDaysInMonth(month, year)) % 7;
        }
    }
    return res;
}
