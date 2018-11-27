/*
 * =============================================================================
 *
 *       Filename:  comment_fn.cpp
 *
 *    Description: functional programming in Cpp
 *    section 2 lecture 8 
 *
 *        Version:  1.0
 *        Created:  26/11/18 15:55:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Myoungki Jung (mj), myoungki.jung@gmail.com
 *   Organization:  Lunarpulse
 *
 * =============================================================================
 */

#include <fplus/fplus.hpp>

int
str_to_int (const std::string & str)
{
  int result;
  std::istringstream (str) >> result;
  return result;
}

/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  sum
 *  Description:  
 * =============================================================================
 */
template < typename Container, typename T = typename Container::value_type >
  T sum (const Container & cont)
{
  return fplus::sum (cont);
}				/* -----  end of function sum  ----- */

/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  product
 *  Description:  
 * =============================================================================
 */
template < typename Container, typename T = typename Container::value_type >
  T product (const Container & cont)
{
  return fplus::product (cont);
}				/* -----  end of function product  ----- */

template < typename Cont >
  typename Cont::value_type product_sol (const Cont & xs)
{
  return fplus::reduce (std::multiplies < typename Cont::value_type > (), 1,
			xs);
}

template < typename Cont > typename Cont::value_type sum_sol (const Cont & xs)
{
  return fplus::reduce (std::plus < typename Cont::value_type > (), 0, xs);
}

int
main ()
{
  const std::string input = "1,5,4,7,2,2,3";
  const auto parts = fplus::split (',', false, input);
  const auto nums = fplus::transform (str_to_int, parts);

  const auto result_sol_product = product_sol (nums);
  std::cout << result_sol_product << std::endl;

  const auto result_sol_sum = sum_sol (nums);
  std::cout << result_sol_sum << std::endl;

  const auto result = product (nums);
  std::cout << result << std::endl;

  const auto result_sum = sum (nums);
  std::cout << result_sum << std::endl;
  // C++ 14
  const auto lamda_product =[](const auto & xs) {
    return fplus::reduce (std::multiplies < int >(), 1, xs);
  };

  const auto lamda_sum =[](const auto & xs) {
    return fplus::reduce (std::plus < int >(), 0, xs);
  };
  const auto result_lamda_product = lamda_product (nums);
  std::cout << result_lamda_product << std::endl;

  const auto result_lamda_sum = lamda_sum (nums);
  std::cout << result_lamda_sum << std::endl;

}

// Exercise:
//     Implement the functions product and sum.
// Bonus:
//     Make them function templates
//     to work with different types of values.
