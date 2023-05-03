#include <iostream>
#include "PosIO.h"

namespace sdds
{
    PosIO::~PosIO()
    {
        ;
    }
    std::ostream &operator<<(std::ostream &ostr, PosIO &PosIO)
    {
        PosIO.write(ostr);
        return ostr;
    }
    std::ofstream &operator<<(std::ofstream &ostr, PosIO &PosIO)
    {
        PosIO.save(ostr);
        return ostr;
    }
    std::istream &operator>>(std::istream &istr, PosIO &PosIO)
    {
        PosIO.read(istr);
        return istr;
    }
    std::ifstream &operator>>(std::ifstream &istr, PosIO &PosIO)
    {
        PosIO.load(istr);
        return istr;
    }
}