/*
 * =============================================================================
 *
 *       Filename:  parseaproduct.cpp
 *
 *    Description:  functional programming using cpp udemy course
 *    Section 2-1 lecture 5
 *
 *        Version:  1.0
 *        Created:  26/11/18 14:31:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Myoungki Jung (mj), myoungki.jung@gmail.com
 *   Organization:  Lunarpulse
 *
 * =============================================================================
 */

#include <fplus/fplus.hpp>

float
str_to_float (const std::string & str)
{
  float result;
  std::istringstream (str) >> result;
  return result;
}

int
str_to_int (const std::string & str)
{
  int result;
  std::istringstream (str) >> result;
  return result;
}

template <typename F, typename Cont>
Cont transform_vec (F f, const Cont &xs){
	Cont ys;
	ys.reserve(xs.size());
	std::transform(std::begin(xs), std::end(xs), std::back_inserter(ys), f);
	return ys;
}

template < typename Pred>
auto curried_transform(Pred f){
	return [f](const std::vector<int>& xs){
		std::vector<int> ys;
		ys.reserve(xs.size());
		std::transform(std::begin(xs), std::end(xs), std::back_inserter(ys), f);
		return ys;

	};
}
 
int
main ()
{
  const std::string input = "1,5,4,7,2,2,3";
  const auto parts = fplus::split (',', false, input);

	std::vector<int> xs = {0,2,1,2,3,4};
  const auto nums_int_std = transform_vec ( [](const auto a){
		  	return a*a;
		  }, xs);
  
  std::cout <<fplus::show_cont (nums_int_std) << std::endl;
 const auto nums_int_std_curried = curried_transform( [](const auto a){
		  	return a*a;
		  })( xs);
  std::cout <<fplus::show_cont (nums_int_std_curried ) << std::endl;
  const auto nums_int = fplus::transform (str_to_int, parts);

  std::cout <<fplus::show_cont (nums_int) << std::endl;
  const auto result_int = fplus::reduce (std::multiplies< int >(), 1, nums_int);

  std::cout << result_int << std::endl;
  const auto nums = fplus::transform (str_to_float, parts);

  const auto result = fplus::reduce (std::plus< float >(), 1, nums);

  std::cout << result << std::endl;

  int val = 42;
  const auto add_value = [val](int x)-> int{
	  return val+ x;
  };
  const auto add_value_auto = [val](auto x){
	  return val+ x;
  };


  std::cout<<val<<" "<< add_value_auto(10)<<" "<< val<<std::endl;
  std::cout<<val<<std::endl;

  std::cout<<val<<" "<< add_value(20)<<" "<< val<<std::endl;
  std::cout<<val<<std::endl;

  val  = 23;
  std::cout<<val<<" "<< add_value(10)<<" "<< val<<std::endl;
  std::cout<<val<<std::endl;
//mutation with [&val]

//  42 52 42
//  42
//  23 33 23
//  23

//immutability with [val]

//  42 52 42
//  42
//  23 52 23
//  23


}

// Exercise:
//
//     Modify the code,
//     so that the numbers are not multiplied but added.
//
//     Additionally change it
//     so that is works with floating pofloat numbers too.
//     For this you should parse doubles instead of floats.
