#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include <string>

#include "../include/Book.h"

namespace myproject
{
  Book::Book() : Publication()
  {
    m_author = nullptr;
  }

  // Rule of three
  Book::Book(const Book &src) : Publication(src)
  {
    *this = src;
  }

  Book &Book::operator=(const Book &src)
  {
    if (src)
    {
      if (*this != src)
      {
        Publication::operator=(src);
        if (m_author)
        {
          delete[] m_author;
        }
        m_author = new char[strlen(src.m_author) + 1];
        strcpy(m_author, src.m_author);
      }
    }
    return *this;
  }

  Book::~Book()
  {
    delete[] m_author;
  }

  // Methods
  char Book::type() const
  {
    return 'B';
  }

  void Book::set(int member_id)
  {
    Publication::set(member_id);
    resetDate();
  }

  Book::operator bool()
  {
    return (m_author && m_author[0] != '\0' && Publication::operator bool());
  }

  std::ostream &Book::write(std::ostream &os) const
  {
    if (*this)
    {
      Publication::write(os);
      if (conIO(os))
      {

        char tempAuthor[MYPROJECT_AUTHOR_WIDTH + 1] = {'\0'};
        strncpy(tempAuthor, m_author, MYPROJECT_AUTHOR_WIDTH);

        if (m_author)
        {
          os << ' ' << std::setw(MYPROJECT_AUTHOR_WIDTH) << std::left << std::setfill(' ') << tempAuthor << " |";
        }
      }
      else
      {
        os << '\t' << m_author;
      }
    }

    return os;
  }

  std::istream &Book::read(std::istream &istr)
  {
    char tempAuthor[256]{};

    Publication::read(istr);

    if (m_author)
    {
      delete[] m_author;
      m_author = nullptr;
    }

    if (conIO(istr))
    {
      istr.ignore();
      std::cout << "Author: ";
    }
    else
    {
      istr.ignore(1000, '\t');
    }

    istr.get(tempAuthor, 256);

    if (!istr.fail())
    {
      m_author = new char[strlen(tempAuthor) + 1];
      strcpy(m_author, tempAuthor);
    }

    return istr;
  }

}