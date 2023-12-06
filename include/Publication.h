#ifndef MYPROJECT_PUBLICATION_H__
#define MYPROJECT_PUBLICATION_H__

#include "Streamable.h"
#include "Lib.h"
#include "Date.h"

namespace myproject
{
    class Publication : public Streamable
    {
    private:
        char *m_title{nullptr};
        char m_shelfId[MYPROJECT_SHELF_ID_LEN + 1]{};
        int m_membership{};
        int m_libRef{};
        Date m_date{};

    public:
        Publication();

        // Modifiers
        virtual void set(int member_id);
        void setRef(int value);
        void resetDate();

        // Queries
        virtual char type() const;
        bool onLoan() const;
        Date checkoutDate() const;
        bool operator==(const char *title) const;
        operator const char *() const;
        int getRef() const;

        // Streamable implementation
        bool conIO(std::ios &io) const;
        std::ostream &write(std::ostream &os) const;
        std::istream &read(std::istream &istr);
        operator bool();

        // Rule of three
        Publication(const Publication &p);
        Publication &operator=(const Publication &p);
        ~Publication();
    };
}

#endif
