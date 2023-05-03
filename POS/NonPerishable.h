#ifndef NONPERISHABLE_H
#define NONPERISHABLE_H
#include "Item.h"
#include <iostream>

namespace sdds
{
    class NonPerishable : public Item
    {

    public:
        char getType() const;
        std::ostream &write(std::ostream &ostr);
    };
}
#endif