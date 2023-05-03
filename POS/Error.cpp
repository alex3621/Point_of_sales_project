#include <iostream>
#include <string.h>
#include "Error.h"

namespace sdds
{
    Error::Error()
    {
        description = nullptr;
    }
    Error::Error(const char *message)
    {
        description = new char[strlen(message) + 1];
        strcpy(description, message);
    }
    Error::~Error()
    {
        delete[] description;
    }
    Error::Error(const Error &rightError)
    {
        if (rightError.description == nullptr)
        {
            description = nullptr;
        }
        else
        {
            description = new char[strlen(rightError.description) + 1];
            strcpy(description, rightError.description);
        }
    }
    Error &Error::operator=(const Error &rightError)
    {
        if (this != &rightError)
        {
            if (rightError.description == nullptr)
            {
                description = nullptr;
            }
            else
            {
                delete[] description;
                description = nullptr;
                description = new char[strlen(rightError.description) + 1];
                strcpy(description, rightError.description);
            }
        }
        return *this;
    }
    Error &Error::operator=(const char *errorText)
    {
        delete[] description;
        if (errorText == nullptr)
        {
            description = nullptr;
        }
        else
        {
            description = new char[strlen(errorText) + 1];
            strcpy(description, errorText);
        }
        return *this;
    }
    Error::operator bool() const
    {
        return (!(description == nullptr));
    }

    Error &Error::clear()
    {
        delete[] description;
        description = nullptr;
        return *this;
    }

    std::ostream &operator<<(std::ostream &ostr, Error &right)
    {
        right.display(ostr);
        return ostr;
    }

    std::ostream &Error::display(std::ostream &ostr)
    {
        if (description != nullptr)
        {
            ostr << description;
        }
        return ostr;
    }

    Error &Error::selfRefer()
    {
        return *this;
    }
}