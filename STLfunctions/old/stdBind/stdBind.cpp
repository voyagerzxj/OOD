// stdBind.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// adapted from example in https://oopscenities.net/2012/02/24/c11-stdfunction-and-stdbind/

#include <functional>
#include <iostream>
#include <string>
#include <vector>

void execute(const std::vector<std::function<void()>>& fs)
{
  for (auto& f : fs)
    f();
}

void show_text(const std::string& t)
{
  std::cout << "\n  Text: " << t;
}

int main()
{
  std::vector<std::function<void()>> x;
  x.push_back(std::bind(show_text, "Bound function"));
  execute(x);

  std::cout << "\n\n";
}