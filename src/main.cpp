#include <iostream>

extern void func1();

int main()
{
  std::cout<< "hello from main \n";
  func1();
  return 0;
}
