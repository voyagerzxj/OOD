///////////////////////////////////////////////////////////////////////
// stdFunction.cpp - demonstrate use of std::function                //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Fall 2018           //
///////////////////////////////////////////////////////////////////////

// https://oopscenities.net/2012/02/24/c11-stdfunction-and-stdbind/

#include <functional>
#include <iostream>
#include <string>
#include <vector>

//----< execute vector of callable objects >---------------------------

void execute(const std::vector<std::function<void()>>& fs, std::string msg = "")
{
  for (auto& f : fs)
  {
    f();
    std::cout << msg;
  }
}
//----< used in binding demo >-----------------------------------------

void show_text(const std::string& t)
{
  std::cout << "\n  Text: " << t;
}
//----< variadic template function >-----------------------------------

template <typename T>  // specialization stops recursion, below
void show(T t)
{
  std::cout << t;
}

template <typename T, typename... Rest>
void show(T t, Rest... rest)
{
  std::cout << t << " ";
  show(rest...);
}

//----< std::bind can't accept variadic function - these are substitutes >----

template<typename T>
void show3(T t1, T t2, T t3)
{
  show(t1, t2, t3);
}

template<typename U, typename V, typename W>
void show3(U u, V v, W w)
{
  show(u, v, w);
}

//----< variadic execution function >----------------------------------

template <typename T>  // specialization stops recursion
void compositeExecution(T t)
{
  t();
}

template <typename T, typename... Rest>
void compositeExecution(T t, Rest... rest)
{
  t();
  compositeExecution(rest...);
}

//----< demo starts here >---------------------------------------------

int main()
{
  std::function<void(std::string)> put = [](std::string s) { std::cout << s; };
  std::string indentedNewLine = "\n  ";
  std::string newLine = "\n";

  std::cout << "\n  Using variadic template functions and std::bind";
  std::cout << "\n =================================================";
  put(newLine);

  std::cout << "\n  demonstrating variadic function taking arbitrary number of arguments";
  std::cout << "\n ----------------------------------------------------------------------";

  put(indentedNewLine);
  show(1, 2.3, "some text");
  put(newLine);

  std::cout << "\n  demonstrating std::bind";
  std::cout << "\n -------------------------";

  auto e = std::bind(show_text, "Bound function");
  e();
  put(newLine);

  std::cout << "\n  demonstrating std::bind using placeholders";
  std::cout << "\n --------------------------------------------";

  // std::bind can't accept variadic template functions, so using show3

  using namespace std::placeholders;
  auto f = std::bind(show3<std::string>, _1, _2, _3);
  put(indentedNewLine);
  f("one", "two", "three");

  auto g = std::bind(show3<int, double, const char*>, 1, _1, _2);
  put(indentedNewLine);
  g(3.1415927, "pi");

  auto h = std::bind(show3<const char*>, "alpha", "beta", _1);
  put(indentedNewLine);
  h("gamma");

  auto i = std::bind(show3<double>, 1.0/3, 1.0/9, 1.0/27);
  put(indentedNewLine);
  i();
  put(newLine);

  std::cout << "\n  demonstrating executing bindings";
  std::cout << "\n ----------------------------------";

  std::vector<std::function<void()>> x;
  x.push_back(e);

  auto e2 = std::bind(f, "one", "two", "three");
  x.push_back(e2);

  auto e3 = std::bind(g, 3.1415927, "pi");
  x.push_back(e3);

  auto e4 = std::bind(h, "gamma");
  x.push_back(e4);

  x.push_back(i);

  execute(x, indentedNewLine);

  std::cout << "\n  demonstrating composite execution with std::bind";
  std::cout << "\n --------------------------------------------------";

  auto d = std::bind(put, indentedNewLine);
  auto c = []() { std::cout << "!"; };
  compositeExecution(e, d, e2, d, e3, d, e4, d, c, c, c, c);

  std::cout << "\n\n";
}