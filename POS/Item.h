#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <fstream>
#include "POS.h"
#include "PosIO.h"
#include "Error.h"

namespace sdds
{
    class Item : public PosIO
    {
        char SKU[MAX_NAME_LEN + 1];
        char *Name;
        double Price;
        bool Taxed;
        int Quantity;

    protected:
        int displayTypeAttribute;
        Error errorState;
        virtual char getType() const = 0;

    public:
        Item();
        Item(const Item &rightItem);
        Item &operator=(const Item &rightItem);
        ~Item();
        bool operator==(Item &rightItem);
        bool operator==(const char *sku);
        bool operator>(Item &rightItem);
        int operator+=(int value);
        int operator-=(int value);
        operator bool() const;
        Item &displayType(int value);
        double cost() const;
        int quantity() const;
        Item &clear();
        std::ostream &write(std::ostream &ostr);
        std::istream &read(std::istream &istr);
        std::ofstream &save(std::ofstream &ostr);
        std::ifstream &load(std::ifstream &istr);
        std::ostream &bprint(std::ostream &ostr) const;
        bool taxQuery() const;
        char *SKU_Query();
        void minusQuantity();
    };

    double operator+=(double &value, Item &rightItem);
    double operator-=(double &value, Item &rightItem);

}

#endif