#ifndef POSIO_H
#define POSIO_H
#include <iostream>

namespace sdds
{
    class PosIO
    {
    public:
        virtual std::ostream &write(std::ostream &ostr) = 0;
        virtual std::istream &read(std::istream &istr) = 0;
        virtual std::ofstream &save(std::ofstream &ostr) = 0;
        virtual std::ifstream &load(std::ifstream &istr) = 0;
        virtual ~PosIO() = 0;
    };
    std::ostream &operator<<(std::ostream &ostr, PosIO &PosIO);
    std::ofstream &operator<<(std::ofstream &ostr, PosIO &PosIO);
    std::istream &operator>>(std::istream &istr, PosIO &PosIO);
    std::ifstream &operator>>(std::ifstream &istr, PosIO &PosIO);

}
#endif