#pragma once
///////////////////////////////////////////////////////////////////////
// Functor.h - Demonstrate Functors                                  //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2017         //
///////////////////////////////////////////////////////////////////////

#include <string>
#include <iostream>

///////////////////////////////////////////////////////////////////////
// Functor class
// - demonstrates sytax and semantics

template <typename Parameter>
class Functor
{
public:
  Functor(Parameter p = Parameter()) : p_(p) 
  {
  }

  std::string operator()(Parameter p)
  {
    std::cout << "\n  Functor instance accepted parameter \"" << p << "\"";
    std::cout << "\n  Functor instance holds parameter \"" << p_ << "\"";
    if (p == p_)
      return "parameter and value are the same";
    else
      return "parameter and value are different";
  }
private:
  Parameter p_;
};

