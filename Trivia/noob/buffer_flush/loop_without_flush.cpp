
// Below is C++ program
#include <iostream>
#include <thread>
#include <chrono>
 
int main()
{
  for (int i = 1; i <= 5; ++i)
  {
      std::cout << i << " ";
      std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  std::cout << endl;
  return 0;
}
