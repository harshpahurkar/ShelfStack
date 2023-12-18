#include <fstream>
#include <iostream>
#include "../include/LibApp.h"
#include "../include/Date.h"

void runLibApp(const char *filename)
{
   char ch{};
   myproject::LibApp theApp(filename);
   theApp.run();
   std::ifstream file(filename);
   while (file)
   {
      if (file.get(ch))
         std::cout << ch;
   }
}
int main()
{
   myproject::sdds_day = 10;
   myproject::sdds_mon = 8;
   myproject::sdds_year = 2023;
   myproject::sdds_test = true;
   runLibApp("data/LibRecs.txt");
   return 0;
}
