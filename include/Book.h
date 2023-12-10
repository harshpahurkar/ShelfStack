#ifndef MYPROJECT_BOOK_H_
#define MYPROJECT_BOOK_H_

#include "Publication.h"

namespace myproject
{
  class Book : public Publication
  {
  private:
    char *m_author{nullptr};

  public:
    // Constructor
    Book();

    // Rule of three
    Book(const Book &src);
    Book &operator=(const Book &src);
    ~Book();

    // Methods
    char type() const;
    std::ostream &write(std::ostream &os) const;
    std::istream &read(std::istream &istr);
    void set(int member_id);
    operator bool();
  };
}

#endif