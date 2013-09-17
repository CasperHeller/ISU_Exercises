#include <cstdlib>
#include <iostream>
#include <ctime>

int main ()
{
  timespec ts;
  
  if ( clock_gettime(CLOCK_MONOTONIC, &ts) )
    return EXIT_FAILURE;
  
  std::cout << "Monotonic time" << std::endl;
  std::cout << "seconds: " << ts.tv_sec << std::endl;
  std::cout << "nanoseconds: " << ts.tv_nsec << std::endl;
  
  return EXIT_SUCCESS;
}