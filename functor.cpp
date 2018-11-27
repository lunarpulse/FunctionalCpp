/*
 * =============================================================================
 *
 *       Filename:  functor.cpp
 *
 *    Description:  functional programming with cpp
 *    section 3. 19
 *
 *        Version:  1.0
 *        Created:  27/11/18 13:43:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Myoungki Jung (mj), myoungki.jung@gmail.com
 *   Organization:  Lunarpulse
 *
 * =============================================================================
 */
#include <fplus/fplus.hpp>
// Exercise:
//     write lift_dict as a function template on your own
//     and test it with the following code.
// lift_dict : ((a -> b), Map key a) -> Map key b
/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  lift_dict
 *  Description:  
 * =============================================================================
 */
template < typename ValOut, typename F, typename Key, typename ValIn >
  std::map < Key, ValOut > lift_dict (F f, const std::map < Key,
				      ValIn > &dict)
{
  std::map < Key, ValOut > result;
for (const auto & key_val:dict)
    {
      result[key_val.first] = f (key_val.second);
    }
  return result;
}				/* -----  end of function lift_dict  ----- */

template < typename ValOut, typename F, typename H, typename Key, typename ValIn >
  std::map < Key, ValOut > lift_dict_secondary (F f, H h, const std::map < Key,
				      ValIn > &dict)
{
  std::map < Key, ValOut > result;
for (const auto & key_val:dict)
    {
      result[key_val.first] =h( f (key_val.second));
    }
  return result;
}

template < typename F, typename A, typename B >
  fplus::maybe < B > maybe_lift (F f, const fplus::maybe < A > &m)
{
  if (fplus::is_just (m))
    return fplus::just < B > (f (fplus::unsafe_get_just (m)));
  else
    return fplus::nothing < B > ();
}

int
main ()
{
  using namespace fplus;
  std::map < int, double >dict = { {2, 1.41}, {3, 1.73}, {4, 2.0} };
  auto dict_squared = lift_dict < double >(square < double >, dict);
  auto dict_cubed= lift_dict < double >(cube< double >, dict);
  auto dict_shown = lift_dict < std::string > (show < double >, dict);
  std::cout << show_cont (dict_squared) << std::endl;
  std::cout << show_cont (dict_shown) << std::endl;
  auto dict_squared_cubed= lift_dict_secondary < double >(cube< double >, square<double>, dict);
  std::cout << show_cont (dict_squared_cubed) << std::endl;
  std::cout << show_cont (dict_cubed) << std::endl;
}
