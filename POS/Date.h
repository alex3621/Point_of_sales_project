#ifndef DATE_H
#define DATE_H
#include "Error.h"
#include <iostream>

namespace sdds
{
    class Date
    {
        int year;
        int month;
        int day;
        int hour;
        int minute;
        bool dateOnlystatus;
        Error status;
        int compare(const Date &date2); // returns 1 if left object bigger, 2 if same, 3 if smaller

    public:
        Date();
        Date(int year, int month, int day);
        Date(int year, int month, int day, int hour, int min = 0);
        void dateOnly(bool);
        void validate();
        operator bool() const;
        Error &error();
        std::ostream &display(std::ostream &ostr);
        std::istream &input(std::istream &istr);
        bool operator!=(const Date &date2);
        bool operator==(const Date &date2);
        bool operator<(const Date &date2);
        bool operator>(const Date &date2);
        bool operator>=(const Date &date2);
        bool operator<=(const Date &date2);
        bool getDateStatus() const;
    };

    std::ostream &operator<<(std::ostream &ostr, Date &right);
    std::istream &operator>>(std::istream &istr, Date &right);
}

#endif