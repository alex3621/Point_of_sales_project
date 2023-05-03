#ifndef POS_H
#define POS_H
#include <iostream>

namespace sdds
{
#define MAX_NO_ITEMS 200
#define MAX_NAME_LEN 40

#define POS_LIST 1
#define POS_FORM 2

#define TAX 0.13
#define MAX_SKU_LEN 7
#define MIN_YEAR 2000
#define MAX_YEAR 2030
#define MAX_STOCK_NUMBER 99
#define MAX_NO_ITEMS 200
#define MAX_FILE_NAME 129

#define ERROR_POS_SKU "SKU too long"
#define ERROR_POS_NAME "Item name too long"
#define ERROR_POS_PRICE "Invalid price value"
#define ERROR_POS_TAX "Invalid tax status"
#define ERROR_POS_QTY "Invalid quantity value"
#define ERROR_POS_STOCK "Item out of stock"
#define ERROR_POS_EMPTY "Invalid Empty Item"
}

#endif