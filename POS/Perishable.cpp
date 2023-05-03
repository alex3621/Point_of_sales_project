#include <iostream>
#include "Perishable.h"
#include "Date.h"

namespace sdds
{
    Perishable::Perishable()
    {
        expiry_date.dateOnly(true);
    }
    char Perishable::getType() const
    {
        return 'P';
    }
    std::istream &Perishable::read(std::istream &istr)
    {
        Item::read(istr);
        if (!istr.fail() && !errorState)
        {
            Date tempDate;
            tempDate.dateOnly(true);
            std::cout << "Expiry date (YYYY/MM/DD)" << std::endl;
            std::cout << "> ";
            istr >> tempDate;
            tempDate.validate();
            if (tempDate)
            {
                this->expiry_date = tempDate;
            }
            else
            {
                errorState = tempDate.error();
            }
        }
        return istr;
    }
    std::ostream &Perishable::write(std::ostream &ostr)
    {
        Item::write(ostr);
        if (!errorState)
        {
            if (this->displayTypeAttribute == POS_LIST)
            {
                ostr << "  " << expiry_date << ' ' << '|';
            }
            else
            {
                ostr << "Expiry date: " << expiry_date << std::endl;
                ostr << "=============^" << std::endl;
            }
        }
        return ostr;
    }
    std::ofstream &Perishable::save(std::ofstream &ostr)
    {
        Item::save(ostr);
        if (!errorState)
        {
            ostr << ',';
            ostr << expiry_date;
        }
        return ostr;
    }
    std::ifstream &Perishable::load(std::ifstream &istr)
    {
        Item::load(istr);
        if (!istr.fail() && !errorState)
        {
            Date tempDate;
            tempDate.dateOnly(true);
            istr.ignore();
            istr >> tempDate;
            tempDate.validate();
            if (tempDate)
            {
                this->expiry_date = tempDate;
            }
            else
            {
                errorState = tempDate.error();
            }
        }
        return istr;
    }

    std::ofstream &operator<<(std::ofstream &ostr, Perishable &perishable)
    {
        perishable.save(ostr);
        return ostr;
    }

}