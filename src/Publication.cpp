#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include <string>
#include "../include/Publication.h"

namespace myproject
{
    Publication::Publication()
    {
        m_title = nullptr;
        m_shelfId[0] = '\0';
        m_membership = 0;
        m_libRef = -1;
        m_date = {};
    }

    void Publication::set(int member_id)
    {
        if (member_id > 9999 && member_id < 100000)
        {
            m_membership = member_id;
        }
        else
        {
            m_membership = 0;
        }
    }

    void Publication::setRef(int value)
    {
        if (value)
        {
            m_libRef = value;
        }
        else
        {
            m_libRef = 0;
        }
    }

    void Publication::resetDate()
    {
        m_date.setToToday();
    }

    // Queries
    char Publication::type() const
    {
        return 'P';
    }
    bool Publication::onLoan() const
    {
        return m_membership ? true : false;
    }
    Date Publication::checkoutDate() const
    {
        return m_date;
    }

    bool Publication::operator==(const char *title) const
    {
        return strstr(m_title, title);
    }

    Publication::operator const char *() const
    {
        return m_title;
    }

    int Publication::getRef() const
    {
        return m_libRef;
    }

    // Streamable implementation
    bool Publication::conIO(std::ios &io) const
    {
        return ((&io == &std::cout) || (&io == &std::cin));
    }

    std::ostream &Publication::write(std::ostream &os) const
    {
        if (*this && !os.fail())
        {
            if (conIO(os))
            {
                char tempTitle[MYPROJECT_TITLE_WIDTH + 1] = {'\0'};
                strncpy(tempTitle, m_title, MYPROJECT_TITLE_WIDTH);

                os << "| " << std::setw(MYPROJECT_SHELF_ID_LEN) << std::left << m_shelfId << " | ";
                os << std::setfill('.') << std::setw(MYPROJECT_TITLE_WIDTH) << tempTitle << " | ";
                os << std::setfill(' ') << std::setw(MYPROJECT_MEMBERSHIP);
                m_membership ? os << m_membership : os << " N/A ";
                os << " | " << m_date << " |";
            }
            else
            {
                os << type() << "\t" << m_libRef << "\t" << m_shelfId << "\t" << m_title << "\t" << m_membership << "\t" << m_date;
            }
        }
        return os;
    }

    std::istream &Publication::read(std::istream &istr)
    {

        if (m_title)
        {
            delete[] m_title;
        }
        m_title = nullptr;
        m_shelfId[0] = '\0';
        m_membership = 0;
        m_libRef = -1;
        m_date = {};

        char tempTitle[256] = {};
        char tempShelfId[MYPROJECT_SHELF_ID_LEN + 1] = {};
        int tempMembership = 0;
        int tempLibRef = -1;
        Date tempDate = {};

        if (conIO(istr))
        {
            std::cout << "Shelf No: ";
            istr.getline(tempShelfId, MYPROJECT_SHELF_ID_LEN + 1);
            if (strlen(tempShelfId) != MYPROJECT_SHELF_ID_LEN)
            {
                istr.setstate(std::ios::failbit);
            }
            std::cout << "Title: ";
            istr.getline(tempTitle, 256);
            std::cout << "Date: ";
            istr >> tempDate;
        }
        else
        {
            istr >> tempLibRef;
            istr.ignore();
            istr.getline(tempShelfId, MYPROJECT_SHELF_ID_LEN + 1, '\t');
            istr.getline(tempTitle, 256, '\t');
            istr >> tempMembership;
            istr.ignore();
            istr >> tempDate;
        }

        if (!tempDate)
        {
            istr.setstate(std::ios::failbit);
        }

        if (!istr.fail())
        {
            m_title = new char[strlen(tempTitle) + 1];
            strcpy(m_title, tempTitle);
            strcpy(m_shelfId, tempShelfId);
            m_membership = tempMembership;
            m_libRef = tempLibRef;
            m_date = tempDate;
        }

        return istr;
    }

    Publication::operator bool()
    {
        return m_title != nullptr && m_shelfId[0] != '\0';
    }

    // Rule of three
    Publication::Publication(const Publication &p)
    {
        *this = p;
    }

    Publication &Publication::operator=(const Publication &p)
    {
        if (p)
        {
            if (this != &p)
            {
                if (m_title)
                {
                    delete[] m_title;
                    m_title = nullptr;
                }

                m_title = new char[strlen(p.m_title) + 1];
                strcpy(m_title, p.m_title);
                m_date = p.m_date;
                strcpy(m_shelfId, p.m_shelfId);
                m_membership = p.m_membership;
                m_libRef = p.m_libRef;
            }
        }
        return *this;
    }

    Publication::~Publication()
    {
        delete[] m_title;
    }
}
