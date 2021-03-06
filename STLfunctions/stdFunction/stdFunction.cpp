///////////////////////////////////////////////////////////////////////
// stdFunction.cpp - demonstrate use of std::function                //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Fall 2018           //
///////////////////////////////////////////////////////////////////////

// adapted from  https://oopscenities.net/2012/02/24/c11-stdfunction-and-stdbind/

#include <functional>
#include <iostream>
#include <string>
#include <vector>

void execute(const std::vector<std::function<void()>>& fs)
{
  for (auto& f : fs)
    f();
}

void plain_old_func()
{
  std::cout << "\n  I'm a plain old function";
}

class functor
{
public:
  void operator()() const
  {
    std::cout << "\n  I'm a functor";
  }
};

int main()
{
  std::function<void(std::string)> put = [](std::string s) { std::cout << s; };
  std::string indentedNewLine = "\n  ";
  std::string newLine = "\n";

  std::cout << "\n  Demonstrating std::function";
  std::cout << "\n =============================";
  put(newLine);

  std::vector<std::function<void()>> x;
  x.push_back(plain_old_func);

  functor functor_instance;
  x.push_back(functor_instance);
  x.push_back([]()
  {
    std::cout << "\n  Hi, I'm a lambda expression";
  });

  execute(x);

  std::cout << "\n\n";
}