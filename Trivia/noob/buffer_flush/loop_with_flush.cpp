
// C++ program to demonstrate the
// use of flush function
#include <iostream>
#include <thread>
#include <chrono>

int main()
{
   for (int i = 1; i <= 5; ++i)
   {
      std::cout << i << " " << std::flush;
      std::this_thread::sleep_for(std::chrono::seconds(1));
   }
   return 0;
}
