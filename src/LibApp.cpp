#include <fstream>
#include <cstring>
#include "../include/LibApp.h"
#include "../include/Menu.h"
#include "../include/Book.h"
#include "../include/PublicationSelector.h"
#include "../include/Date.h"

namespace myproject
{
  bool LibApp::confirm(const char *message)
  {
    Menu m1(message);
    m1 << "Yes";
    return m1.run() == 1;
  }

  void LibApp::load()
  {
    std::cout << "Loading Data" << std::endl;

    std::ifstream fin(m_filename);
    char ch{};
    int i = 0;
    for (i = 0; !fin.eof(); i++)
    {
      fin >> ch;
      fin.ignore();
      if (fin)
      {
        if (ch == 'P')
        {
          m_ppa[i] = new Publication();
        }
        else if (ch == 'B')
        {
          m_ppa[i] = new Book();
        }
        if (m_ppa[i])
        {
          fin >> *m_ppa[i];
          m_nolp++;
          m_llrn = m_ppa[i]->getRef();
        }
      }
    }
    fin.close();
  }

  void LibApp::save()
  {
    std::cout << "Saving Data" << std::endl;
    std::ofstream fout(m_filename);

    for (int i = 0; i < m_nolp; i++)
    {
      if (m_ppa[i]->getRef() != 0)
      {
        fout << *m_ppa[i] << std::endl;
      }
    }

    fout.close();
  }

  int LibApp::search(int type)
  {
    int index = -1;
    char t_title[256];
    unsigned int userInput{};
    PublicationSelector ps("Select one of the following found matches:");

    userInput = m.run();
    if (userInput)
    {
      std::cout << "Publication Title: ";
      std::cin.get(t_title, 256);

      for (int i = 0; i < m_nolp; i++)
      {
        if (userInput == 1 && m_ppa[i]->type() == 'B')
        {
          if (m_ppa[i]->getRef() != 0)
          {
            if (type == 1 && strstr(*m_ppa[i], t_title))
            {
              ps << m_ppa[i];
            }
            else if (type == 2 && m_ppa[i]->onLoan() && strstr(*m_ppa[i], t_title))
            {
              ps << m_ppa[i];
            }
            else if (type == 3 && !m_ppa[i]->onLoan() && strstr(*m_ppa[i], t_title))
            {
              ps << m_ppa[i];
            }
          }
        }
        else if (userInput == 2 && m_ppa[i]->type() == 'P')
        {
          if (m_ppa[i]->getRef() != 0)
          {
            if (type == 1 && strstr(*m_ppa[i], t_title))
            {
              ps << m_ppa[i];
            }
            else if (type == 2 && m_ppa[i]->onLoan() && strstr(*m_ppa[i], t_title))
            {
              ps << m_ppa[i];
            }
            else if (type == 3 && !m_ppa[i]->onLoan() && strstr(*m_ppa[i], t_title))
            {
              ps << m_ppa[i];
            }
          }
        }
      }
      if (ps)
      {
        ps.sort();
        int ref = ps.run();
        if (ref)
        {
          // std::cout << "Selected Library Reference Number: " << ref << std::endl;
          for (int i = 0; i < 100; i++)
          {
            if (ref == m_ppa[i]->getRef())
            {
              std::cout << *m_ppa[i] << std::endl;
              index = i;
              i = 100;
            }
          }
        }
        else
        {
          std::cout << "Aborted!" << std::endl;
        }
      }
      else
      {
        std::cout << "No matches found!" << std::endl;
      }
    }
    else
    {
      std::cout << "Aborted!" << std::endl;
    }

    return index;
  }

  Publication *LibApp::getPub(int libRef) const
  {
    int index;
    for (int i = 0; i < m_nolp; i++)
    {
      if (m_ppa[i]->getRef() == libRef)
      {
        index = i;
      }
    }
    return m_ppa[index];
  }

  void LibApp::returnPub()
  {
    std::cout << "Return publication to the library" << std::endl;
    double penalty = 0.5;
    int dateDiff{}, index = search(2);

    if (index > 0)
    {
      if (confirm("Return Publication?"))
      {
        Date currentDate{};
        dateDiff = currentDate - m_ppa[index]->checkoutDate();
        if (dateDiff > 15)
        {
          penalty = penalty * (dateDiff - 15);
          std::cout << "Please pay $" << std::fixed << std::setprecision(2) << penalty << " penalty for being " << dateDiff - 15 << " days late!" << std::endl;
        }
        m_ppa[index]->set(0);
        m_changed = true;
        std::cout << "Publication returned" << std::endl;
      }
    }
  }

  void LibApp::newPublication()
  {
    unsigned int userInput{};
    Publication *newPub{};
    bool keep = true;
    if (m_nolp == MYPROJECT_LIBRARY_CAPACITY)
    {
      std::cout << "Library is at its maximum capacity!" << std::endl;
    }
    else
    {
      std::cout << "Adding new publication to the library" << std::endl;
      userInput = m.run();
      if (userInput == 1)
      {
        newPub = new Book;
      }
      else if (userInput == 2)
      {
        newPub = new Publication;
      }
      else if (userInput == 0)
      {
        keep = false;
      }

      if (keep)
      {
        newPub->read(std::cin);
        if (std::cin.fail())
        {
          std::cin.clear();
          std::cin.ignore(10000);
          std::cout << "Aborted!" << std::endl;
        }
        else
        {
          if (confirm("Add this publication to the library?"))
          {
            if (newPub)
            {
              m_llrn++;
              newPub->setRef(m_llrn);
              m_ppa[m_nolp] = newPub;
              m_nolp++;
              m_changed = true;
              std::cout << "Publication added" << std::endl;
            }
            else
            {
              std::cout << "Failed to add publication!" << std::endl;
            }
          }
          else
          {
            std::cout << "Aborted!" << std::endl;
          }
        }
      }
      else
      {
        std::cout << "Aborted!" << std::endl;
      }
    }
  }

  void LibApp::removePublication()
  {
    int index;
    std::cout << "Removing publication from the library" << std::endl;
    index = search(1);
    if (index != -1)
    {
      if (confirm("Remove this publication from the library?"))
      {
        m_ppa[index]->setRef(0);
        m_changed = true;
        std::cout << "Publication removed" << std::endl;
      }
    }
  }

  void LibApp::checkOutPub()
  {
    std::cout << "Checkout publication from the library" << std::endl;
    int memberid{};
    bool keep = true;
    int index = search(3);
    if (index > 0)
    {
      if (confirm("Check out publication?"))
      {
        std::cout << "Enter Membership number: ";
        do
        {
          std::cin >> memberid;
          if (memberid > 9999 && memberid < 100000)
          {
            m_ppa[index]->set(memberid);
            m_changed = true;
            keep = false;
            std::cout << "Publication checked out" << std::endl;
          }
          else
          {
            std::cout << "Invalid membership number, try again: ";
          }
        } while (keep);
      }
    }
  }

  // public
  LibApp::LibApp(const char *filename) : m_mainMenu("ShelfStack"),
                                         m_exitMenu("Changes have been made to the data, what would you like to do?"),
                                         m("Choose the type of publication:")
  {
    if (filename)
    {
      strcpy(m_filename, filename);
    }
    m << "Book"
      << "Publication";
    m_changed = false;

    m_mainMenu << "Add New Publication"
               << "Remove Publication"
               << "Checkout publication from library"
               << "Return publication to library";
    m_exitMenu << "Save changes and exit"
               << "Cancel and go back to the main menu";

    load();
  }

  void LibApp::run()
  {
    bool keep = true;

    while (keep)
    {
      unsigned int result = m_mainMenu.run();
      if (result == 1)
      {
        newPublication();
        std::cout << std::endl;
      }
      else if (result == 2)
      {
        removePublication();
        std::cout << std::endl;
      }
      else if (result == 3)
      {
        checkOutPub();
        std::cout << std::endl;
      }
      else if (result == 4)
      {
        returnPub();
        std::cout << std::endl;
      }
      else if (result == 0)
      {
        if (m_changed == false)
        {
          keep = false;
          std::cout << std::endl;
        }
        else if (m_changed == true)
        {
          result = m_exitMenu.run();
          if (result == 1)
          {
            save();
            keep = false;
            std::cout << std::endl;
          }
          else if (result == 2)
          {
            std::cout << std::endl;
            keep = true; // doesnt change and loop continues
          }
          else if (result == 0)
          {
            if (confirm("This will discard all the changes are you sure?") == 1)
            {
              keep = false;
              std::cout << std::endl;
            }
            else
            {
              keep = true; // keeps going
            }
          }
        }
      }
    }
    std::cout << "-------------------------------------------" << std::endl
              << "Thanks for using ShelfStack" << std::endl;
  }

  LibApp::~LibApp()
  {
    for (int i = 0; i < m_nolp; i++)
    {
      delete m_ppa[i];
    }
  }

} // namespace myproject
