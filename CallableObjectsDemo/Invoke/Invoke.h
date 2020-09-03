#pragma once
///////////////////////////////////////////////////////////////////////
// Invoke.h - Defines parameterized invokers for callable objects    //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2017         //
///////////////////////////////////////////////////////////////////////

// invoke callable object of type void T()

template <typename T>
void invoke(T t)
{
  t();
}

// invoke callable object of type void T(A a)

template <typename T, typename A>
void invoke(T t, A a)
{
  t(a);
}

// invoke callable object of type R T(A a)

template <typename R, typename T, typename A>
R invoke(T t, A a)
{
  return t(a);
}

// invoke callable object R C::T(A)
// - requires binding T to std::function

template<typename R, typename T, typename C, typename A>
R invoke(T t, C c, A a)
{
  return t(c, a);
}
