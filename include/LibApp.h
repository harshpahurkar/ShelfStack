#ifndef MYPROJECT_LIBAPP_H
#define MYPROJECT_LIBAPP_H

#include "Menu.h"
#include "Publication.h"

namespace myproject
{
  class LibApp : public Menu
  {
    char m_filename[256]{};
    Publication *m_ppa[MYPROJECT_LIBRARY_CAPACITY]{}; // stored all publications
    int m_nolp{};                                     // number of loaded publicaitons
    int m_llrn{};                                     // holds last reference number read from file

    bool m_changed{}; // A flag to keep track of changes made to the application
                      // data
    Menu m_mainMenu{};
    Menu m_exitMenu{};
    Menu m{};
    bool confirm(const char *message);
    void load();              // prints: "Loading Data"<NEWLINE>
    void save();              // prints: "Saving Data"<NEWLINE>
    int search(int type = 1); // 1 : ALL, 2 : On Loan, 3 : Not on Loan
    Publication *getPub(int libRef) const;

    void returnPub(); /*  Calls the search() method.
                          prints "Returning publication"<NEWLINE>
                          prints "Publication returned"<NEWLINE>
                          sets m_changed to true;
                      */
    void newPublication();
    void removePublication();
    void checkOutPub();

  public:
    LibApp(const char *filename = nullptr);
    void run();
    ~LibApp();
  };
} // namespace sdds
#endif // !SDDS_LIBAPP_H
