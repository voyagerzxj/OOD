/////////////////////////////////////////////////////////////////////////
// TestInvoke.cpp - tests parameterized invokers for callable objects  //
//                                                                     //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2017           //
/////////////////////////////////////////////////////////////////////////
/*
*  - Check out Functor, Lambda, and Function Pointer projects in this
*    solution for demonstrations with a large set of targets.
*/
#include "Invoke.h"
#include<iostream>

// global function - simplest callable object

std::string test(std::string msg)
{
  std::cout << "\n  test() here with msg: \"" << msg.c_str() << "\"";
  return msg;
}

int main()
{

  std::cout << "\n  Brief Test of Invoker";
  std::cout << "\n  =====================";
  std::cout << "\n";

  std::cout << "\n  " << invoke<std::string>(test, "hello CSE687 World").c_str();

  std::cout << "\n\n";
  return 0;
}