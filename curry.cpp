/*
 * =============================================================================
 *
 *       Filename:  curry.cpp
 *
 *    Description:  curried functional call
 *    section: 2.10
 *    
 *
 *        Version:  1.0
 *        Created:  26/11/18 18:22:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Myoungki Jung (mj), myoungki.jung@gmail.com
 *   Organization:  Lunarpulse
 *
 * =============================================================================
 */

#include <fplus/fplus.hpp>
#include <assert.h>

std::function<int(int)> add_curried(int a)
{
	return [a](int b){
		return a+b;
	};
}

/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  is_even
 *  Description: returns even for true and odd for false 
 * =============================================================================
 */
bool
is_even (int x )
{
	return x%2 == 0;
}		/* -----  end of function is_even  ----- */

template < typename Pred, typename Cont > Cont
keep_if (Pred predicate, const Cont & xs)
{
  Cont ys;
for (const auto x:xs)
    {
      if (predicate (x))
	ys.push_back (x);
    }
  return ys;
}

template < typename Pred> 
auto keep_if_c (Pred predicate)
{
	return [predicate](const std::vector<int> &xs){
		
		std::vector<int>ys;
		for (const auto x:xs)
		{
			if (predicate (x))
				ys.push_back (x);
		}
		return ys;
	};
}
/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  curried_sqr
 *  Description:  
 * =============================================================================
 */
auto curried_sqr ( int a )
{
	return [a](){
		return a*a;
	};
}		/* -----  end of function curried_sqr  ----- */

template < typename Pred, typename Cont > 
auto curried_sqr_fwd (Pred f)
{
	return [f](const Cont & xs){
		Cont ys;
		for (const auto x:xs)
		{
			if (f(x))
				ys.push_back (x);
		}
		return ys;

	};
}

/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  add_four_curried
 *  Description: curried add_four(a,b,c,d) 
 * =============================================================================
 */
auto add_four_curried ( int a )
{
	return [a](int b){
		return [a, b](int c){
			return[a, b, c](int d){
				return a+b+c+d;
			};
		};
	};
}		/* -----  end of function add_four_curried  ----- */

int main()
{
	std::vector<int> xs = {0,2,1,2,3,4};
        auto ys=fplus::transform(add_curried(3),xs);
	    assert(add_curried(3)(4)==7);
	    assert(curried_sqr(3)()==9);

	    std::vector<std::vector<int>> xss =
		            {{0,1,2}, {3,4,5}};

	    fplus::transform(fplus::fwd::transform(fplus::square<int>),xss);
	    // fplus::transform(fplus::transform(curried_sqr),xss);

	    assert(add_four_curried(1)(2)(3)(4) == 1+2+3+4);

	    fplus::transform(keep_if_c(is_even), xss);

	    return 1;
}
// Exercise 1:
//     Square every inner value of xss, so
//     {{0,1,2}, {3,4,5}}
//     turns into
//     {{0,1,4}, {9,16,25}}
//     Try out different possibilities to achieve your goal.

// Exercise 2:
//     Use nested lambda expressions
//     to make a fully curried version of add_four.
//     add_four (Int, Int, Int, Int) -> Int
//     add_four_curried : Int -> Int -> Int -> Int -> Int
//     so that
//     add_four(1,2,3,4)
//     means the same as
//     add_four_curried(1)(2)(3)(4)

