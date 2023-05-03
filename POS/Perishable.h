#ifndef PERISHABLE_H
#define PERISHABLE_H
#include "Item.h"
#include "Date.h"

namespace sdds
{
    class Perishable : public Item
    {

    public:
        Date expiry_date;
        char getType() const;
        Perishable();
        std::istream &read(std::istream &istr);
        std::ostream &write(std::ostream &ostr);
        std::ofstream &save(std::ofstream &ostr);
        std::ifstream &load(std::ifstream &istr);
    };
    std::ofstream &operator<<(std::ofstream &ostr, Perishable &perishable);
}

#endif