#include <iostream>
#include <string.h>
#include "PosApp.h"

using namespace std;

namespace sdds
{
    void PosApp::addItem()
    {
        action_title(std::cout, "Adding Item to the store");
        if (nptr >= MAX_NO_ITEMS)
        {
            std::cout << "Inventory Full!" << std::endl;
        }
        else
        {
            char ch;
            Item *newItem;
            std::cout << "Is the Item perishable? (Y)es/(N)o: ";
            cin >> ch;
            if (ch == 'y')
            {
                newItem = new Perishable;
                do
                {
                    std::cin >> *newItem;
                    if (!*newItem)
                    {
                        cin.clear();
                        cin.ignore(2000);
                        std::cout << *newItem;
                        std::cout << ", try again...\n";
                    }
                } while (!*newItem);
            }
            else
            {
                newItem = new NonPerishable;
                do
                {
                    std::cin >> *newItem;
                    if (!*newItem)
                    {
                        cin.clear();
                        cin.ignore(2000);
                        std::cout << *newItem;
                        std::cout << ", try again...\n";
                    }
                } while (!*newItem);
            }
            Iptr[nptr++] = newItem;
            action_title(std::cout, "DONE!");
        }
    }
    void PosApp::removeItem()
    {
        int index;
        action_title(std::cout, "Remove Item");
        index = selectItem() - 1;
        printRemove(std::cout, index);
        removeItemFromList(index);
    }
    void PosApp::stockItem()
    {
        action_title(std::cout, "Select an item to stock");
        stockSelect(std::cout);
    }
    void PosApp::listItems()
    {
        listItem(std::cout, true);
    }
    void PosApp::POS()
    {
        action_title(std::cout, "Starting Point of Sale");
        POSloop(std::cout, std::cin);
    }
    void PosApp::saveRecs()
    {
        int i = 0;
        action_title(std::cout, "Saving Data");
        std::ofstream output(fileName);
        for (i = 0; i < nptr; i++)
        {
            output << *Iptr[i];
            output << '\n';
        }
        for (i = 0; i < nptr; i++)
        {
            delete Iptr[i];
        }
    }
    void PosApp::loadRecs()
    {
        std::ifstream input(fileName);
        char ch;
        action_title(std::cout, "Loading Items");

        clear();
        if (!input)
        {
            std::ofstream output(fileName);
            output.close();
        }
        while (input.get(ch) && nptr < MAX_NO_ITEMS)
        {
            if (ch == 'P')
            {
                input.ignore();
                Iptr[nptr] = new Perishable;
                if (Iptr[nptr])
                {
                    input >> *Iptr[nptr];
                    input.ignore();
                    nptr++;
                }
            }
            else
            {
                input.ignore();
                Iptr[nptr] = new NonPerishable;
                if (Iptr[nptr])
                {
                    input >> *Iptr[nptr];
                    input.ignore();
                    nptr++;
                }
            }
        }
        input.close();
    }
    PosApp::PosApp(const char *file)
    {
        nptr = 0;
        if (file != nullptr)
        {
            strcpy(fileName, file);
        }
    }

    void PosApp::menu()
    {
        int selection;
        do
        {
            bool success = false;
            cout << "The Sene-Store" << endl;
            cout << "1- List items" << endl;
            cout << "2- Add item" << endl;
            cout << "3- Remove item" << endl;
            cout << "4- Stock item" << endl;
            cout << "5- POS" << endl;
            cout << "0- exit program" << endl;
            cout << "> ";
            do
            {
                cin >> selection;
                if (selection == 1)
                {
                    listItems();
                    success = true;
                }
                else if (selection == 2)
                {
                    addItem();
                    success = true;
                }
                else if (selection == 3)
                {
                    removeItem();
                    success = true;
                }
                else if (selection == 4)
                {
                    stockItem();
                    success = true;
                }
                else if (selection == 5)
                {
                    POS();
                    success = true;
                }
                else if (cin.fail())
                {
                    cout << "Invalid Integer, try again: ";
                    cin.clear();
                    cin.ignore(2000, '\n');
                }
                else if (selection == 0)
                {
                    success = true;
                }

                else
                {
                    cout << "[0<=value<=5], retry: > ";
                }
            } while (success == false);

        } while (selection != 0);
        saveRecs();
        std::cout << "Goodbye!" << std::endl;
    }
    void PosApp::run()
    {
        loadRecs();
        menu();
    }

    std::ostream &PosApp::action_title(std::ostream &ostr, const char *message)
    {
        ostr << ">>>> ";
        ostr.unsetf(ios::right);
        ostr.unsetf(ios::fixed);
        ostr.width(72);
        ostr.fill('.');
        ostr.setf(std::ios::left);
        ostr.setf(std::ios::fixed);
        ostr << message;
        ostr.unsetf(std::ios::left);
        ostr.unsetf(std::ios::fixed);
        ostr.fill(' ');
        ostr << std::endl;
        return ostr;
    }

    void PosApp::clear()
    {
        int i = 0;
        for (i = 0; i < nptr; i++)
        {
            delete Iptr[i];
            Iptr[i] = nullptr;
        }
        nptr = 0;
    }

    void PosApp::sort()
    {
        int i, j;
        Item *temp;

        for (i = nptr - 1; i > 0; i--)
        {
            for (j = 0; j < i; j++)
            {
                if (*Iptr[j] > *Iptr[j + 1])
                {
                    temp = Iptr[j];
                    Iptr[j] = Iptr[j + 1];
                    Iptr[j + 1] = temp;
                }
            }
        }
    }

    std::ostream &PosApp::listItem(std::ostream &ostr, bool show)
    {
        double totalAsset = 0;
        int i = 0;
        action_title(ostr, "Listing Items");
        sort();
        ostr << " Row | SKU    | Item Name          | Price |TX |Qty |   Total | Expiry Date |" << std::endl;
        ostr << "-----|--------|--------------------|-------|---|----|---------|-------------|" << std::endl;

        for (i = 0; i < nptr; i++)
        {
            ostr.width(4);
            ostr << (i + 1);
            ostr << " | ";
            Iptr[i]->displayType(1);
            ostr << *Iptr[i];
            ostr << std::endl;
            totalAsset += *Iptr[i];
        }
        ostr << "-----^--------^--------------------^-------^---^----^---------^-------------^" << std::endl;
        if (show)
        {
            ostr << "                               Total Asset: $  |";
            ostr.width(14);
            ostr << totalAsset;
            ostr.width(1);
            ostr << '|';
            ostr << std::endl;
            ostr << "-----------------------------------------------^--------------^" << std::endl;
        }
        // ostr << std::endl;
        return ostr;
    }

    int PosApp::selectItem()
    {
        int selection;
        bool pass = false;
        action_title(std::cout, "Item Selection by row number");
        std::cout << "Press <ENTER> to start....";
        std::cin.ignore();
        std::cin.ignore(2000, '\n');
        listItem(std::cout, false);
        std::cout << "Enter the row number: ";
        do
        {
            std::cin >> selection;
            if (cin.fail())
            {
                std::cout << "Invalid Integer, try again: ";
                cin.clear();
                cin.ignore(2000, '\n');
            }
            else if (selection < 1 || selection > nptr)
            {
                std::cout << "[1<=value<=" << nptr << "], retry: Enter the row number: ";
            }
            else
            {
                pass = true;
            }
        } while (!pass);
        return selection;
    }

    void PosApp::removeItemFromList(int index)
    {
        int i = 0;
        delete Iptr[index];
        for (i = index + 1; i < nptr; i++)
        {
            Iptr[i - 1] = Iptr[i];
        }
        Iptr[nptr - 1] = nullptr;
        nptr--;
    }

    void PosApp::stockSelect(std::ostream &ostr)
    {
        int selection, quantity;
        bool pass = false;
        selection = selectItem();
        ostr << "Selected Item:\n";
        Iptr[selection - 1]->displayType(POS_FORM);
        ostr << *Iptr[selection - 1];
        ostr << "Enter quantity to add: ";
        do
        {
            std::cin >> quantity;
            if (cin.fail())
            {
                std::cout << "Invalid Integer, try again: ";
                cin.clear();
                cin.ignore(2000, '\n');
            }
            else if (quantity < 1 || (Iptr[selection - 1]->quantity() + quantity) > MAX_STOCK_NUMBER)
            {
                std::cout << "[1<=value<=" << MAX_STOCK_NUMBER - (Iptr[selection - 1]->quantity()) << "], retry: Enter quantity to add: ";
            }
            else
            {
                *Iptr[selection - 1] += quantity;
                pass = true;
                action_title(std::cout, "DONE!");
            }
        } while (!pass);
    }

    Item *PosApp::search(const char *SKU)
    {
        int i = 0;
        Item *address = nullptr;
        for (i = 0; i < nptr; i++)
        {
            if (strcmp(SKU, Iptr[i]->SKU_Query()) == 0)
            {
                address = Iptr[i];
            }
        }
        return address;
    }

    void PosApp::POSloop(std::ostream &ostr, std::istream &istr)
    {
        Bill bill;
        bool exit = false;
        char SKU[MAX_SKU_LEN + 1];
        Item *address;
        bill.clear();
        istr.ignore();
        do
        {
            ostr << "Enter SKU or <ENTER> only to end sale...\n> ";
            // istr >> SKU;
            istr.getline(SKU, MAX_SKU_LEN + 1);
            address = search(SKU);
            if (strlen(SKU) == 0)
            {
                exit = true;
            }
            else if (address == nullptr)
            {
                ostr << "!!!!! Item Not Found !!!!!\n";
            }
            else if (address->quantity() == 0)
            {
                ostr << "Item out of stock" << std::endl;
            }
            else
            {
                address->displayType(POS_FORM);
                bill.add(address);
                address->minusQuantity();
                ostr << *address;
                ostr << std::endl;
                ostr << ">>>>> Added to bill" << std::endl;
                ostr.setf(std::ios::left);
                ostr.setf(std::ios::fixed);
                ostr.precision(2);
                ostr << ">>>>> Total: " << bill.total() << std::endl;
                ostr.unsetf(std::ios::left);
                ostr.unsetf(std::ios::fixed);
            }
        } while (exit == false);
        bill.print(std::cout);
    }

    void PosApp::printRemove(std::ostream &ostr, int index)
    {
        ostr << "Removing...." << std::endl;
        Iptr[index]->displayType(POS_FORM);
        ostr << *Iptr[index];
        ostr << ">>>> DONE!..................................................................." << std::endl;
    }
}
