#include "../include/Streamable.h"

namespace myproject
{
    std::ostream &operator<<(std::ostream &os, const Streamable &stream)
    {
        stream.write(os);
        return os;
    }
    std::istream &operator>>(std::istream &is, Streamable &stream)
    {
        stream.read(is);
        return is;
    }

    Streamable::~Streamable(){};
}
