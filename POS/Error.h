#ifndef ERROR_H
#define ERROR_H

namespace sdds
{
    class Error
    {
        char *description;

    public:
        Error();
        Error(const char *);
        ~Error();
        Error(const Error &);
        Error &operator=(const Error &);
        Error &operator=(const char *);
        operator bool() const;
        Error &clear();
        std::ostream &display(std::ostream &ostr);
        Error &selfRefer();
        // std::ostream &operator<<(std::ostream &ostr) const;
        const char *getError();
    };
    std::ostream &operator<<(std::ostream &ostr, Error &right);
}

#endif