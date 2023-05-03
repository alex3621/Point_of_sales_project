#include <iostream>
#include "NonPerishable.h"

namespace sdds
{
    char NonPerishable::getType() const
    {
        return 'N';
    }

    std::ostream &NonPerishable::write(std::ostream &ostr)
    {
        if (Item::operator bool())
        {
            Item::write(ostr);
            if (Item::displayTypeAttribute == POS_LIST)
            {
                ostr << "     N / A   |";
            }
            else
            {
                ostr << "=============^" << std::endl;
            }
        }
        return ostr;
    }
}