#ifndef MYPROJECT_MENU_H__
#define MYPROJECT_MENU_H__

#include <iostream>
#include <iomanip>
#define MAX_MENU_ITEMS 20

#include <cstring>

namespace myproject
{

  class MenuItem
  {
  private:
    char *m_item;
    MenuItem();
    MenuItem(const char *item);
    // copying of MenuItem is not allowed
    MenuItem(MenuItem &menuItem) = delete;
    MenuItem &operator=(MenuItem &menuItem) = delete;
    operator bool() const;
    operator const char *() const;
    std::ostream &display(std::ostream &os, const char *item) const;
    ~MenuItem();

    friend class Menu;
  };

  class Menu
  {
  private:
    MenuItem *m_title{nullptr};
    MenuItem *m_items[MAX_MENU_ITEMS]{nullptr};
    int m_count{};

    Menu(Menu &menu) = delete;
    Menu &operator=(Menu &menu) = delete;

  public:
    Menu();
    Menu(const char *title);

    std::ostream &displayTitle(std::ostream &os, const Menu &menu) const;
    std::ostream &displayMenu(std::ostream &os, const Menu &menu) const;

    unsigned int run() const;
    unsigned int operator~() const;

    Menu &operator<<(const char *menuitemContent);

    operator int() const;
    operator unsigned int() const;
    operator bool() const;

    const char *operator[](unsigned int itemNum) const;

    ~Menu();
  };

  std::ostream &operator<<(std::ostream &os, const Menu &menu);
}

#endif