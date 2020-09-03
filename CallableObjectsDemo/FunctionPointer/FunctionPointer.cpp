#include "FunctionPointer.h"
#include "../invoke/Invoke.h"
#include <functional>

#ifdef TEST_FUNCTIONPOINTER

int main()
{
  std::cout << "\n  demonstrating Function Pointers";
  std::cout << "\n  ===============================";
  std::cout << "\n";

  std::cout << "\n  Demonstrating non-member function pointers";
  std::cout << "\n  ------------------------------------------";

  // call global function
  say();

  // invoke global function
  invoke(say);
  
  // call global function via function pointer
  FPvv pSay = say;
  pSay();

  // invoke function pointer
  invoke(pSay);

  // call global function with argument
  sayType("a string");

  // invoke global function with argument
  invoke<FPvp<const std::string&>, const std::string&>(sayType, "a string");

  // call function pointer with argument
  FPvp<const std::string&> pSayType = sayType;
  pSayType("another string");

  // invoke function pointer with argument
  invoke(pSayType, "another string");

  // call global function with argument and return value
  bool result1 = same<bool, bool>(true);

  // invoke global function with argument and return value
  bool result2 = invoke<bool>(same<bool,bool>, true);

  if(result1)
  {
    std::cout << "\n  same<bool, bool>(true) returns true";
  }
  else
  {
    std::cout << "\n  same<bool, bool>(true) returns false";
  }

  // call function pointer with argument and return value
  FPrp<bool, int> pSame = same;
  result1 = pSame(42);

  // invoke function pointer with argument and return value
  result2 = invoke<bool>(pSame, 42);

  if (result2)
  {
    std::cout << "\n  same<bool, int>(42) returns true";
  }
  else
  {
    std::cout << "\n  same<bool, int>(42) returns false";
  }
  std::cout << "\n";

  std::cout << "\n  Demonstrating member function pointers";
  std::cout << "\n  --------------------------------------";

  // call member function
  using Tbi = FunctionPointer<bool, int>;
  Tbi fp(42);
  fp.say();

  // call member function pointer
  Tbi::FPvvm p_vvm = &Tbi::say;
  (fp.*p_vvm)();

  // invoke member function pointer
  // - need trick here because member function pointers are not callable objects
  std::function<void(Tbi&)> cov = &Tbi::say;
  invoke(cov, fp);

  // call member function with argument
  fp.sayType(42);

  // call member function pointer with argument
  Tbi::FPvpm p_vim = &Tbi::sayType;
  (fp.*p_vim)(42);

  // invoke member function with argument - needs the trick
  std::function<void(Tbi&, int)> cob = &Tbi::sayType;
  invoke(cob, fp, 42);

  // call member function with argument and return value
  result1 = fp.same(53);
  if (result1)
    std::cout << "\n  53 == 42";
  else
    std::cout << "\n  53 != 42";

  // call member function pointer with argument and return value
  Tbi::FPrpm p_bim = &Tbi::same;
  result2 = (fp.*p_bim)(53);
  if (result2)
    std::cout << "\n  53 == 42";
  else
    std::cout << "\n  53 != 42";

  // invoke member function with argument and return value
  std::function<bool (Tbi&, int)> co = &Tbi::same;
  bool result3 = invoke<bool>(co, fp, 53);
  if (result3)
    std::cout << "\n  53 == 42";
  else
    std::cout << "\n  53 != 42";

  std::cout << "\n\n";
  return 0;
}

#endif

