#ifndef POSAPP_H
#define POSAPP_H
#include <iostream>
#include "POS.h"
#include "Item.h"
#include "Perishable.h"
#include "NonPerishable.h"
#include "Bill.h"
namespace sdds
{
    class PosApp
    {
        char fileName[MAX_FILE_NAME];
        int nptr;
        Item *Iptr[MAX_NO_ITEMS];

    public:
        PosApp(const char *);
        PosApp(const PosApp &) = delete;
        PosApp &operator=(const PosApp) = delete;
        std::ostream &action_title(std::ostream &ostr, const char *message);
        void menu();
        void run();
        void addItem();
        void removeItem();
        void stockItem();
        void listItems();
        void POS();
        void saveRecs();
        void loadRecs();
        void clear();
        void sort();
        std::ostream &listItem(std::ostream &ostr, bool show);
        int selectItem();
        void removeItemFromList(int index);
        void stockSelect(std::ostream &ostr);
        Item *search(const char *SKU);
        void POSloop(std::ostream &ostr, std::istream &istr);
        void printRemove(std::ostream &ostr, int index);
    };
}

#endif