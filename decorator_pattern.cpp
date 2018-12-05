/*
 * =============================================================================
 *
 *       Filename:  decorator_pattern.cpp
 *
 *    Description:  decorator pattern with functional programming concept
 *
 *        Version:  1.0
 *        Created:  29/11/18 14:42:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Myoungki Jung (mj), myoungki.jung@gmail.com
 *   Organization:  Lunarpulse
 *
 * =============================================================================
 */

#include <cassert>
#include <functional>
#include <iostream>
#include <string>
#include <memory>
template<typename T>
T square (T x)
{
  return x * x;
}

// decorate_with_logging : (String, (Int -> Int)) -> (Int -> Int)

/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  decorate_with_logging
 *  Description:  
 * =============================================================================
 */
template < typename F, typename T >
auto decorate_with_logging (const std::string &str, F f)
{
  return[str, f] (T x) -> T
  {
    T r = f(x);
    std::cout << str << ": " << x << " ==> " << r << std::endl;
    return r;
  };
}				/* -----  end of function decorate_with_logging  ----- */

int
main ()
{
  const auto
	    logging_square = decorate_with_logging<decltype(square<int>), int> ("Square", square<int>);

  int
    a = logging_square (4);
  int
    b = logging_square (5);

  assert (a == 16);
  assert (b == 25);

  // The console should show something like
  // Square: 4 => 16
  // Square: 5 => 25
}

// Exercise:
//     Implement decorate_with_logging so that
//     it works like shown above.
