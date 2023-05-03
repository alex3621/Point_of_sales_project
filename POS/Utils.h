#ifndef UTILS_H
#define UTILS_H
#define _CRT_SECURE_NO_WARNINGS
#include <ctime>

namespace sdds
{
    void getSystemDate(int &year, int &mon, int &day, int &hour, int &min, bool dateOnly);
    int uniqueDateValue(int year, int mon, int day, int hour, int min);
    int daysOfMonth(int year, int month);
}

#endif