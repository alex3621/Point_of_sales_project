#include <iostream>
#include "Item.h"
#include <string.h>
#include "PosIO.h"
#include "Error.h"

namespace sdds
{
    Item::Item()
    {
        SKU[0] = '\0';
        Name = nullptr;
    }
    Item::Item(const Item &rightItem)
    {
        *this = rightItem;
    }
    Item &Item::operator=(const Item &rightItem)
    {
        if (this != &rightItem)
        {
            delete[] Name;
            strcpy(SKU, rightItem.SKU);
            Name = new char[strlen(rightItem.Name) + 1];
            strcpy(Name, rightItem.Name);
            Price = rightItem.Price;
            Taxed = rightItem.Taxed;
            Quantity = rightItem.Quantity;
        }
        return *this;
    }
    Item::~Item()
    {
        delete[] Name;
    }
    bool Item::operator==(Item &rightItem)
    {
        return (strcmp(SKU, rightItem.SKU) == 0);
    }
    bool Item::operator>(Item &rightItem)
    {
        return (strcmp(Name, rightItem.Name) > 0);
    }
    int Item::operator+=(int value)
    {
        Quantity += value;
        if (Quantity > MAX_STOCK_NUMBER)
        {
            Quantity = MAX_STOCK_NUMBER;
            errorState = ERROR_POS_QTY;
        }
        return Quantity;
    }
    int Item::operator-=(int value)
    {
        if (value > Quantity)
        {
            Quantity = 0;
            errorState = ERROR_POS_STOCK;
        }
        else
        {
            Quantity -= value;
        }
        return Quantity;
    }
    Item::operator bool() const
    {
        return (!errorState);
    }
    Item &Item::displayType(int value)
    {
        displayTypeAttribute = value;
        return *this;
    }
    double Item::cost() const
    {
        double temp = Price;
        if (Taxed)
        {
            temp = Price * (1 + TAX);
        }
        return temp;
    }
    int Item::quantity() const
    {
        return Quantity;
    }
    Item &Item::clear()
    {
        errorState.clear();
        return *this;
    }
    std::ostream &Item::write(std::ostream &ostr)
    {
        char temp[21];
        if (!errorState)
        {
            if (displayTypeAttribute == POS_LIST)
            {
                ostr.width(7);
                ostr.setf(std::ios::left);
                ostr << SKU;
                ostr.width(1);
                ostr << '|';
                if (strlen(Name) <= 20)
                {
                    ostr.width(20);
                    ostr << Name;
                    ostr << '|';
                }
                else
                {
                    ostr.width(20);
                    strncpy(temp, Name, 20);
                    temp[20] = '\0';
                    ostr << temp;
                    ostr << '|';
                }
                ostr.width(1);
                ostr.width(7);
                ostr.unsetf(std::ios::left);
                ostr.setf(std::ios::right);
                ostr.setf(std::ios::fixed);
                ostr.precision(2);
                ostr << Price;
                ostr.width(1);
                ostr << '|';
                ostr << ' ';
                if (Taxed)
                {
                    ostr << 'X';
                }
                else
                {
                    ostr << ' ';
                }
                ostr << " |";
                ostr.width(4);
                ostr << Quantity;
                ostr.width(1);
                ostr << '|';
                ostr.width(9);
                if (Taxed)
                {
                    ostr << (Price * (1 + TAX) * Quantity);
                }
                else
                {
                    ostr << (Quantity * Price);
                }

                ostr.width(1);
                ostr << '|';
                ostr.unsetf(std::ios::right);
            }
            else
            {
                ostr << "=============v" << std::endl;
                ostr << "Name:        " << Name << std::endl;
                ostr << "Sku:         " << SKU << std::endl;
                ostr.setf(std::ios::left);
                ostr.setf(std::ios::fixed);
                ostr.precision(2);
                ostr << "Price:       " << Price << std::endl;
                ostr << "Price + tax: ";
                if (Taxed)
                {
                    // ostr.width(5);
                    ostr.setf(std::ios::left);
                    ostr.setf(std::ios::fixed);
                    ostr.precision(2);
                    ostr << (Price + Price * TAX);
                    ostr.unsetf(std::ios::left);
                    ostr.unsetf(std::ios::fixed);
                }
                else
                {
                    ostr << "N/A";
                }
                ostr << std::endl;
                ostr << "Stock Qty:   ";
                ostr << Quantity << std::endl;
            }
        }
        else
        {
            errorState.display(ostr);
        }
        return ostr;
    }
    std::istream &Item::read(std::istream &istr)
    {
        char tempSKU[100], tempName[100], tempTaxed[100];
        double tempPrice;
        int tempQuantity;
        bool proceed = false;
        std::cout << "Sku" << std::endl;
        do
        {
            std::cout << "> ";
            istr >> tempSKU;
            if (strlen(tempSKU) > MAX_SKU_LEN)
            {
                std::cout << ERROR_POS_SKU << std::endl;
                proceed = false;
            }
            else
            {

                strcpy(SKU, tempSKU);
                proceed = true;
            }
        } while (proceed == false);
        std::cout << "Name" << std::endl;
        istr.ignore(1000, '\n');
        do
        {
            std::cout << "> ";
            istr.getline(tempName, 100, '\n');
            if (strlen(tempName) > MAX_NAME_LEN)
            {
                std::cout << ERROR_POS_NAME << std::endl;
                proceed = false;
            }
            else
            {
                Name = new char[strlen(tempName) + 1];
                strcpy(Name, tempName);
                proceed = true;
            }
        } while (proceed == false);

        std::cout << "Price" << std::endl;
        do
        {
            std::cout << "> ";
            istr >> tempPrice;
            if (tempPrice <= 0)
            {
                std::cout << ERROR_POS_PRICE << std::endl;
                proceed = false;
                istr.clear();
                istr.ignore(1000, '\n');
            }
            else
            {
                Price = tempPrice;
                proceed = true;
            }
        } while (proceed == false);
        std::cout << "Taxed?" << std::endl;
        std::cout << "(Y)es/(N)o: ";
        do
        {
            istr >> tempTaxed;
            if (strcmp(tempTaxed, "y\0") == 0 || strcmp(tempTaxed, "n\0") == 0)
            {
                if (strcmp(tempTaxed, "y\0") == 0)
                {
                    Taxed = true;
                }
                else
                {
                    Taxed = false;
                }
                proceed = true;
            }
            else
            {
                std::cout << "Only 'y' and 'n' are acceptable: ";
                proceed = false;
            }
        } while (proceed == false);
        std::cout << "Quantity" << std::endl;
        do
        {
            std::cout << "> ";
            istr >> tempQuantity;
            if (tempQuantity <= 0 || tempQuantity > MAX_STOCK_NUMBER)
            {
                std::cout << ERROR_POS_QTY << std::endl;
                istr.clear();
                istr.ignore(1000, '\n');
                proceed = false;
            }
            else
            {
                Quantity = tempQuantity;
                proceed = true;
            }
        } while (proceed == false);

        return istr;
    }
    std::ofstream &Item::save(std::ofstream &ostr)
    {
        if (errorState)
        {
            std::cerr << errorState;
        }
        else
        {
            ostr.setf(std::ios::fixed);
            ostr.precision(2);
            ostr << getType() << ',' << SKU << ',' << Name << ',' << Price << ',' << Taxed << ',' << Quantity;
        }

        return ostr;
    }
    std::ifstream &Item::load(std::ifstream &istr)
    {
        char tempSKU[100], tempName[100];
        double tempPrice;
        int tempQuantity, tempTaxed;
        bool keepChecking = true;
        errorState.clear();

        istr.getline(tempSKU, 100, ',');
        istr.getline(tempName, 100, ',');
        istr >> tempPrice;
        istr.ignore();
        istr.clear();
        istr >> tempTaxed;
        istr.ignore();
        istr.clear();
        istr >> tempQuantity;

        if (!istr.fail())
        {
            if (strlen(tempSKU) > MAX_SKU_LEN)
            {
                errorState = ERROR_POS_SKU;
                keepChecking = false;
            }
            if (keepChecking)
            {
                if (strlen(tempName) > MAX_NAME_LEN)
                {
                    errorState = ERROR_POS_NAME;
                    keepChecking = false;
                }
            }
            if (keepChecking)
            {
                if (tempPrice <= 0)
                {
                    errorState = ERROR_POS_PRICE;
                    keepChecking = false;
                }
            }
            if (keepChecking)
            {
                if (tempTaxed != 0 && tempTaxed != 1)
                {

                    errorState = ERROR_POS_TAX;
                    keepChecking = false;
                }
            }
            if (keepChecking)
            {
                if (tempQuantity <= 0 || tempQuantity > MAX_STOCK_NUMBER)
                {
                    errorState = ERROR_POS_QTY;
                    keepChecking = false;
                }
            }

            if (keepChecking)
            {
                strcpy(SKU, tempSKU);
                delete[] Name;
                Name = new char[strlen(tempName) + 1];
                strcpy(Name, tempName);
                Price = tempPrice;
                Taxed = tempTaxed;
                Quantity = tempQuantity;
            }
        }

        return istr;
    }
    std::ostream &Item::bprint(std::ostream &ostr) const
    {
        char temp[21];
        ostr << "| ";
        ostr.setf(std::ios::left);
        if (strlen(Name) <= 20)
        {
            ostr.width(20);
            ostr << Name;
            ostr << '|';
        }
        else
        {
            ostr.width(20);
            strncpy(temp, Name, 20);
            temp[20] = '\0';
            ostr << temp;
            ostr << '|';
        }
        ostr.width(10);
        ostr.unsetf(std::ios::left);
        ostr.setf(std::ios::right);
        ostr.setf(std::ios::fixed);
        ostr.precision(2);
        if (Taxed)
        {
            ostr << (Price * (1 + TAX));
        }
        else
        {
            ostr << Price;
        }

        ostr << " |";
        if (Taxed)
        {
            ostr << "  T  |";
        }
        else
        {
            ostr << "     |";
        }
        ostr.unsetf(std::ios::right);
        ostr.unsetf(std::ios::fixed);
        ostr << std::endl;
        return ostr;
    }

    double operator+=(double &value, Item &rightItem)
    {

        value += rightItem.cost() * rightItem.quantity();
        return value;
    }

    double operator-=(double &value, Item &rightItem)
    {
        return (value -= rightItem.cost() * rightItem.quantity());
    }

    bool Item::operator==(const char *sku)
    {
        return (strcmp(SKU, sku) == 0);
    }

    bool Item::taxQuery() const
    {
        return Taxed;
    }

    char *Item::SKU_Query()
    {
        return SKU;
    }

    void Item::minusQuantity()
    {
        Quantity--;
    }

}
