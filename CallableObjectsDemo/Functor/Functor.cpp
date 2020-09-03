///////////////////////////////////////////////////////////////////////
// Functor.cpp - Demonstrate Functors                                //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2017         //
///////////////////////////////////////////////////////////////////////

#ifdef TEST_FUNCTOR

#include "Functor.h"
#include "../Invoke/Invoke.h"
#include <string>
#include <iostream>

int main()
{
  std::cout << "\n  Demonstrating Functors";
  std::cout << "\n  ======================";
  std::cout << "\n";

  Functor<int> f(42);

  // call functor's operator()
  std::cout << "\n  Functor's " << f(42);
  
  // invoke functor
  std::cout << "\n  Functor's " << invoke<std::string>(f, 53);
  std::cout << "\n";

  Functor<std::string> g("Hello CSE687 World");
  
  // call functor's operator()
  std::cout << "\n  Functor's " << g("Hello CSE687 World");
  
  // invoke functor
  std::cout << "\n  Functor's " << invoke<std::string>(g, "Hello");
  std::cout << "\n";

  std::cout << "\n\n";
}

#endif
