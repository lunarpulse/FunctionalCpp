/*
 * =============================================================================
 *
 *       Filename:  correctnessfollowsfromexpressiveness.cpp
 *
 *    Description:  udemy practice
 *
 *        Version:  1.0
 *        Created:  26/11/18 13:28:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Myoungki Jung (mj), myoungki.jung@gmail.com
 *   Organization:  Lunarpulse
 *
 * =============================================================================
 */
#include <cassert>
#include <vector>
#include <fplus/fplus.hpp>

using namespace std;

bool
is_even (int x)
{
  return x % 2 == 0;
}

template < typename F, typename T >
  vector < T > transform_vec (F f, const vector < T > &xs)
{
  vector < T > ys;
  ys.reserve (xs.size ());
  transform (begin (xs), end (xs), back_inserter (ys), f);
  return ys;
}

/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  keep_if
 *  Description:  keep if with predicate and for 
 * =============================================================================
 */
template < typename Pred, typename Cont > Cont
keep_if (Pred predicate, const Cont & xs)
{
  Cont ys;
for (const auto x:xs)
    {
      if (predicate (x))
	ys.pushback (x);
    }
  return ys;
}				/* -----  end of function keep_if  ----- */

int
main ()
{
  std::vector < int >xs = {
    0, 1, 2, 3, 4
  };
  const auto ys = transform_vec(is_even, xs);
  assert (ys == std::vector < int >({0, 2, 4}));
  std::list < int >xsl = {
    0, 1, 2, 3, 4
  };
  const auto ysl = fplus::keep_if (is_even, xsl);
  assert (ysl == std::list < int >({0, 2, 4}));
}

// Then run some tests with it.

// Bonus:
// See if you can make it work
// for different container types
// (e.g. std::list and std::vector).
