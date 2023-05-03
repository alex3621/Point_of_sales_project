#include <iostream>
#include "Date.h"
#include "Utils.h"
#include "POS.h"

namespace sdds
{
    Date::Date()
    {
        this->dateOnlystatus = false;
        getSystemDate(this->year, this->month, this->day, this->hour, this->minute, this->dateOnlystatus);
    }
    Date::Date(int year, int month, int day)
    {
        dateOnlystatus = true;
        this->year = year;
        this->month = month;
        this->day = day;
        validate();
    }
    Date::Date(int year, int month, int day, int hour, int min)
    {
        dateOnlystatus = false;
        this->year = year;
        this->month = month;
        this->day = day;
        this->hour = hour;
        this->minute = min;
        validate();
    }
    void Date::dateOnly(bool status)
    {
        dateOnlystatus = status;
        if (status == true)
        {
            hour = 0;
            minute = 0;
        }
    }

    void Date::validate()
    {
        bool check = true;
        if (year < MIN_YEAR || year > MAX_YEAR)
        {
            status = "Invalid Year";
            check = false;
        }
        if (check)
        {
            if (month < 1 || month > 12)
            {
                status = "Invalid Month";
                check = false;
            }
        }
        if (check)
        {
            if (day < 1 || day > daysOfMonth(year, month))
            {
                status = "Invalid Day";
                check = false;
            }
        }
        if (check)
        {
            if (hour < 0 || hour > 23)
            {
                status = "Invalid Hour";
                check = false;
            }
        }
        if (check)
        {
            if (minute < 0 || minute > 59)
            {
                status = "Invlid Minute";
                check = false;
            }
        }
    }
    int Date::compare(const Date &date2)
    {
        bool check = true;
        int result;
        if (this->year > date2.year)
        {
            check = false;
            result = 1;
        }
        if (check && date2.year > this->year)
        {
            check = false;
            result = 3;
        }
        if (check)
        {
            if (this->month > date2.month)
            {
                check = false;
                result = 1;
            }
            if (check && date2.month > this->month)
            {
                check = false;
                result = 3;
            }
            if (check)
            {
                if (this->day > date2.day)
                {
                    check = false;
                    result = 1;
                }
                if (check && date2.day > this->day)
                {
                    check = false;
                    result = 3;
                }
                if (check)
                {
                    if (this->hour > date2.hour)
                    {
                        check = false;
                        result = 1;
                    }
                    if (check && date2.hour > this->hour)
                    {
                        check = false;
                        result = 3;
                    }
                    if (check)
                    {
                        if (this->minute > date2.minute)
                        {
                            check = false;
                            result = 1;
                        }
                        if (check && date2.minute > this->minute)
                        {
                            check = false;
                            result = 3;
                        }
                        if (check)
                        {
                            result = 2;
                            check = false;
                        }
                    }
                }
            }
        }

        return result;
    }

    bool Date::operator==(const Date &date2)
    {
        return (this->compare(date2) == 2);
    }
    bool Date::operator!=(const Date &date2)
    {
        return !(this->compare(date2) == 2);
    }
    bool Date::operator<(const Date &date2)
    {
        return (this->compare(date2) == 3);
    }
    bool Date::operator>(const Date &date2)
    {
        return (this->compare(date2) == 1);
    }
    bool Date::operator>=(const Date &date2)
    {
        return (this->compare(date2) == 2 || this->compare(date2) == 1);
    }
    bool Date::operator<=(const Date &date2)
    {
        return (this->compare(date2) == 2 || this->compare(date2) == 3);
    }

    Date::operator bool() const
    {
        return (!status);
    }

    Error &Date::error()
    {
        return status.selfRefer();
    }

    std::ostream &Date::display(std::ostream &ostr)
    {
        if (!status)
        {
            if (dateOnlystatus)
            {
                ostr << year << '/';
                if (month < 10)
                {
                    ostr << '0' << month;
                }
                else
                {
                    ostr << month;
                }

                ostr << '/';

                if (day < 10)
                {
                    ostr << '0' << day;
                }
                else
                {
                    ostr << day;
                }
            }
            else
            {
                ostr << year << '/';
                if (month < 10)
                {
                    ostr << '0' << month;
                }
                else
                {
                    ostr << month;
                }

                ostr << '/';

                if (day < 10)
                {
                    ostr << '0' << day;
                }
                else
                {
                    ostr << day;
                }

                ostr << ", ";

                if (hour < 10)
                {
                    ostr << '0' << hour;
                }
                else
                {
                    ostr << hour;
                }

                ostr << ':';

                if (minute < 10)
                {
                    ostr << '0' << minute;
                }
                else
                {
                    ostr << minute;
                }
            }
        }
        else
        {
            if (dateOnlystatus)
            {
                ostr << status << '(' << year << '/';
                if (month < 10)
                {
                    ostr << '0' << month;
                }
                else
                {
                    ostr << month;
                }

                ostr << '/';

                if (day < 10)
                {
                    ostr << '0' << day;
                }
                else
                {
                    ostr << day;
                }
                ostr << ')';
            }
            else
            {
                ostr << status << '(';
                ostr << year << '/';
                if (month < 10)
                {
                    ostr << '0' << month;
                }
                else
                {
                    ostr << month;
                }

                ostr << '/';

                if (day < 10)
                {
                    ostr << '0' << day;
                }
                else
                {
                    ostr << day;
                }

                ostr << ", ";

                if (hour < 10)
                {
                    ostr << '0' << hour;
                }
                else
                {
                    ostr << hour;
                }

                ostr << ':';

                if (minute < 10)
                {
                    ostr << '0' << minute;
                }
                else
                {
                    ostr << minute;
                }
                ostr << ')';
            }
        }

        return ostr;
    }

    std::ostream &operator<<(std::ostream &ostr, Date &right)
    {
        right.display(ostr);
        return ostr;
    }

    std::istream &operator>>(std::istream &istr, Date &right)
    {
        right.input(istr);
        return istr;
    }

    std::istream &Date::input(std::istream &istr)
    {
        bool check = true;
        status.clear();
        year = 0;
        month = 0;
        day = 0;
        hour = 0;
        minute = 0;
        if (dateOnlystatus)
        {
            istr >> year;
            if (!istr.fail())
            {
                istr.ignore();
            }
            else
            {
                status = "Cannot read year entry";
                check = false;
            }
            if (check)
            {
                istr >> month;
                if (!istr.fail())
                {
                    istr.ignore();
                }
                else
                {
                    status = "Cannot read month entry";
                    check = false;
                }
                if (check)
                {
                    istr >> day;

                    if (istr.fail())
                    {
                        status = "Cannot read day entry";
                        check = false;
                    }
                    if (check)
                    {
                        validate();
                    }
                }
            }
        }
        else
        {
            istr >> year;
            if (!istr.fail())
            {
                istr.ignore();
            }
            else
            {
                status = "Cannot read year entry";
                check = false;
            }
            if (check)
            {
                istr >> month;
                if (!istr.fail())
                {
                    istr.ignore();
                }
                else
                {
                    status = "Cannot read month entry";
                    check = false;
                }
                if (check)
                {
                    istr >> day;
                    if (!istr.fail())
                    {
                        istr.ignore();
                    }
                    else
                    {
                        status = "Cannot read day entry";
                        check = false;
                    }
                    if (check)
                    {
                        istr >> hour;
                        if (!istr.fail())
                        {
                            istr.ignore();
                        }
                        else
                        {
                            status = "Cannot read hour entry";
                            check = false;
                        }
                        if (check)
                        {
                            istr >> minute;
                            if (istr.fail())
                            {
                                status = "Cannot read minute entry";
                                check = false;
                            }
                            if (check)
                            {
                                validate();
                            }
                        }
                    }
                }
            }
        }
        return istr;
    }

    bool Date::getDateStatus() const
    {
        return dateOnlystatus;
    }
}