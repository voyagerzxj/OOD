///////////////////////////////////////////////////////////////////////
// Lambda.cpp - Demonstrate Lambdas                                  //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2017         //
///////////////////////////////////////////////////////////////////////

#include <string>
#include <iostream>
#include "../Invoke/Invoke.h"

int main()
{
  std::cout << "\n  Demonstrate Lamdbas";
  std::cout << "\n  ===================";
  std::cout << "\n";

  std::string epilogue = " - That's all Folks!";

  auto lam = [=](const std::string& msg)
  {
    return msg + epilogue;
  };

  // call lambda's code block using captured data
  std::cout << "\n  " << lam("hello CSE687 World");

  // invoke lambda
  std::cout << "\n  " << invoke<std::string>(lam, "Hello CSE687 World");

  std::cout << "\n\n";
  return 0;
}