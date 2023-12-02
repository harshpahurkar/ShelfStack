#ifndef MYPROJECT_STREAMABLE_H__
#define MYPROJECT_STREAMABLE_H__

#include <iostream>

namespace myproject
{
    class Streamable
    {
    public:
        virtual std::ostream &write(std::ostream &os) const = 0;
        virtual std::istream &read(std::istream &is) = 0;
        virtual bool conIO(std::ios &ios) const = 0;
        virtual operator bool() = 0;
        virtual ~Streamable();
    };

    std::ostream &operator<<(std::ostream &os, const Streamable &stream);
    std::istream &operator>>(std::istream &is, Streamable &stream);
}

#endif
