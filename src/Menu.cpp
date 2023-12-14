#include "../include/Menu.h"

namespace myproject
{
  MenuItem::MenuItem()
  {
    m_item = nullptr;
  }

  MenuItem::MenuItem(const char *item)
  {
    m_item = new char[strlen(item) + 1];
    strcpy(m_item, item);
  }

  MenuItem::operator bool() const
  {
    return m_item != nullptr ? true : false;
  }
  MenuItem::operator const char *() const
  {
    return m_item;
  }
  std::ostream &MenuItem::display(std::ostream &os, const char *item) const
  {
    if (item != nullptr)
    {
      os << std::setfill(' ') << item;
    }
    return os;
  }

  MenuItem::~MenuItem()
  {
    delete[] m_item;
    // std::cout << "here menuItem" << std::endl;
  }

  // ###########################################################

  Menu::Menu()
  {
    m_title = nullptr;
    m_count = 0;
    for (int i = 0; i < MAX_MENU_ITEMS; i++)
    {
      m_items[i] = nullptr;
    }
  }

  Menu::Menu(const char *title)
  {
    for (int i = 0; i < MAX_MENU_ITEMS; i++)
    {
      m_items[i] = nullptr;
    }
    m_count = 0;
    m_title = new MenuItem(title);
  }

  std::ostream &Menu::displayTitle(std::ostream &os, const Menu &menu) const
  {
    if (m_title != nullptr)
    {
      // std::cout << "it came here" << std::endl;
      os << menu.m_title->m_item;
      // std::cout << "it came here" << std::endl;
    }
    return os;
  }

  std::ostream &Menu::displayMenu(std::ostream &os, const Menu &menu) const
  {

    displayTitle(os, menu) << std::endl;
    for (int i = 0; i < m_count; i++)
    {
      os << " " << i + 1 << "- ";
      os << m_items[i]->m_item << std::endl;
    }

    os << " 0- Exit" << std::endl
       << "> ";

    return os;
  }

  unsigned int Menu::run() const
  {
    bool validInput = false;
    unsigned int selection = 0;

    displayMenu(std::cout, *this);

    while (!validInput)
    {
      std::cin.clear();
      std::string input;
      getline(std::cin, input);

      bool isNumeric = true;
      for (int i = 0; i < int(input.length()) && isNumeric; ++i)
      {
        char c = input[i];
        if (!std::isdigit(c))
        {
          isNumeric = false;
        }

        if (isNumeric)
        {
          selection = std::stoi(input);
          if (selection <= (unsigned int)(m_count))
          {
            validInput = true;
          }
        }

        if (!validInput)
        {
          std::cout << "Invalid Selection, try again: ";
        }
      }
    }
    return selection;
  }

  unsigned int Menu::operator~() const
  {
    return run();
  }

  Menu &Menu::operator<<(const char *menuitemContent)
  {
    bool keepLoop = true;
    for (unsigned int i = 0; i < MAX_MENU_ITEMS && keepLoop; i++)
    {
      if (m_items[i] == nullptr)
      {
        m_items[i] = new MenuItem(menuitemContent);
        m_count++;
        keepLoop = false;
      }
      else
      {
        keepLoop = true;
      }
    }

    return *this;
  }

  Menu::operator int() const
  {
    return m_count;
  }

  Menu::operator unsigned int() const
  {
    return (unsigned int)m_count;
  }

  Menu::operator bool() const
  {
    return m_count >= 1 ? true : false;
  }

  std::ostream &operator<<(std::ostream &os, const Menu &menu)
  {
    return menu.displayTitle(os, menu);
  }

  const char *Menu::operator[](unsigned int itemNum) const
  {
    const char *result = nullptr;

    if (m_count > 0)
    {
      result = *m_items[itemNum % m_count];
    }

    return result;
  }

  Menu::~Menu()
  {
    delete m_title;
    for (int i = 0; i < m_count; i++)
    {
      delete m_items[i];
    }
  }
}
