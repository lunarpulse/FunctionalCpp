/*
 * =============================================================================
 *
 *       Filename:  function_composition.cpp
 *
 *    Description:  functional programming in Cpp
 *    section 2.13
 *
 *        Version:  1.0
 *        Created:  27/11/18 00:39:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Myoungki Jung (mj), myoungki.jung@gmail.com
 *   Organization:  Lunarpulse
 *
 * =============================================================================
 */

#include <fplus/fplus.hpp>

double str_to_double (const std::string & str)
{
  double result;
  std::istringstream (str) >> result;
  return result;
}

const auto parse_and_product =
  fplus::fwd::compose (fplus::fwd::split (',', false),
		       fplus::fwd::transform (str_to_double),
		       fplus::fwd::product ());

int main ()
{
  const std::string input = "1,5,4,7,2,2,3.34";

  std::cout << parse_and_product (input) << std::endl;
  
  const auto result = fplus::fwd::apply(input
		  , fplus::fwd::split(',', false)
		  , fplus::fwd::transform(str_to_double)
		  , fplus::fwd::product()
		  );

  std::cout << result << std::endl;
}
