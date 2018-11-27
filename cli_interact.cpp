/*
 * =============================================================================
 *
 *       Filename:  cli_interact.cpp
 *
 *    Description:  functional programming in Cpp
 *
 *        Version:  1.0
 *        Created:  27/11/18 00:30:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Myoungki Jung (mj), myoungki.jung@gmail.com
 *   Organization:  Lunarpulse
 *
 * =============================================================================
 */

#include <fplus/fplus.hpp>
#include <iostream>

//cmd_line_interact:(String->String)->()
template < typename F > void
cmd_line_interact (F f)
{
  std::cout << f (std::string (std::istreambuf_iterator <
			       char >(std::cin.rdbuf ()),
			       std::istreambuf_iterator <
			       char >())) << std::endl;
}

const auto sort_n =fplus::fwd::compose (
			  fplus::fwd::split_lines (false),
			  fplus::fwd::sort (),
			  fplus::fwd::join (std::string ("\n"))
			  );
 
int
main ()
{
  using namespace fplus;
  cmd_line_interact(fwd::to_lower_case());
  cmd_line_interact(sort_n);

  // 1:
  cmd_line_interact (fwd::to_upper_case ());

  // 2:
  cmd_line_interact (fwd::compose (
			  fwd::split_lines (false),
			  fwd::sort (),
			  fwd::join (std::string ("\n"))
			  )
		  );
}
