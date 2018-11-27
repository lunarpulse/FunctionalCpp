/*
 * =============================================================================
 *
 *       Filename:  monad.cpp
 *
 *    Description:  monad exercise cli input a text and calculate median of the int array.
 *
 *        Version:  1.0
 *        Created:  27/11/18 14:48:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Myoungki Jung (mj), myoungki.jung@gmail.com
 *   Organization:  Lunarpulse
 *
 * =============================================================================
 */


#include <fplus/fplus.hpp>

using namespace fplus;
using namespace std;

typedef vector < int >Ints;
typedef vector < string > Strings;

result < string, string > get_input_filepath (const Strings & args)
{
  assert (args.size () > 0);
  if (args.size () != 2)
    return error < string, string > ("Usage: " + args[0] + " FILEPATH");
  else
    return ok < string, string > (args[1]);
}

result < string, string > read_file (const string & filepath)
{
  const auto maybe_content = read_text_file_maybe (filepath) ();
  const auto trimmed = lift_maybe (trim_whitespace < string >, maybe_content);
  return from_maybe (string ("Unable to open ") + filepath, trimmed);
}

result < Ints, string > parse_content (const string & content)
{
  const auto maybe_values = fwd::apply (content, fwd::split (',', false),
					fwd::transform (read_value < int >));
  if (all_by (is_just < int >, maybe_values))
      return ok < Ints, string > (justs (maybe_values));
  else
    return error < Ints, string > ("Can not parse file.");
}

result < int, string >
calc_median (const vector < int >&xs)
{
  if (is_not_empty (xs))
    return ok < int, string > (median (xs));
  return error < int, string > ("Need at least one value.");
}

string
show_median (int value)
{
  return "The median is " + show (value);
}

string
show_error (const string & error)
{
  return "ERROR: " + error;
}

/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  conventional_chain
 *  Description:  
 * =============================================================================
 */
void
conventional_chain (vector < string > arguments, const string & error_msg)
{
  const auto input_fp = get_input_filepath (arguments);
  if (is_ok (input_fp))
    {
      const auto content = read_file (input_fp.unsafe_get_ok ());
      if (is_ok (content))
	{
	  const auto values = parse_content (content.unsafe_get_ok ());
	  if (is_ok (values))
	    {
	      const auto res = calc_median (values.unsafe_get_ok ());
	      const auto output = lift_result (show_median, res);
	      cout << ok_with_default (error_msg, output) << endl;

	    }
	  else
	    {
	      cout << error_msg << endl;
	    }

	}
      else
	{
	  cout << error_msg << endl;
	}


    }
  else
    {
      cout << error_msg << endl;
    }

}				/* -----  end of function conventional_chain  ----- */

/* 
 * ===  FUNCTION  ==============================================================
 *         Name: compose_result_chain
 *  Description:  
 * =============================================================================
 */
void
compose_result_chain (vector < string > arguments)
{
  const auto res = fwd::apply (arguments,
			       compose_result (get_input_filepath,
					       read_file,
					       parse_content,
					       calc_median));
  const auto output = unify_result (show_median, show_error, res);
  cout << output << endl;
}

/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  and_then
 *  Description:  
 * =============================================================================
 */
template < typename Res, typename F, typename A >
  maybe < Res > and_then (F f, const maybe < A > &m)
{
  if (is_just (m))
    return f (unsafe_get_just (m));
  else
    return nothing < Res > ();
}				/* -----  end of function and_then  ----- */

// Exercise:
 //     Let's rewrite our command line tool
 //     using Result instead of Maybe,
 //     so it provides meaningful error messages
 //     to the user in case of failure.
 //     Implement the and_then part of the result
 //     monad on your own.
template < typename Res, typename Error,
  typename F, typename A >
  result < Res, Error > my_and_then_result (F f, const result < A, Error > &r)
{
  if (is_ok (r))
    return f (unsafe_get_ok (r));
  else
    return error < Res, Error > (r.unsafe_get_error ());
}

/* 
 * ===  FUNCTION  ==============================================================
 *         Name: my_result_and_then_chain
 *  Description:  
 * =============================================================================
 */
void
my_result_and_then_chain (vector < string > arguments)
{
//      const auto input_fp = get_input_filepath (arguments);
//      const auto content = and_then<string>( read_file ,input_fp);
//      const auto values = and_then<Ints>( parse_content,content);
//      const auto res = and_then<Ints>( calc_median ,values);
//      const auto output = lift(show_median, res);
//      cout << ok_with_default (error_msg, output) << endl;

  const auto input_filepath = get_input_filepath (arguments);
  const auto file_content =
    my_and_then_result < string > (read_file, input_filepath);

  const auto values =
    my_and_then_result < Ints > (parse_content, file_content);

  const auto res = my_and_then_result < int >(calc_median, values);

  const auto output = unify_result (show_median, show_error, res);
  cout << output << endl;
}


int
main (int argc, char *argv[])
{
  const Strings arguments (argv, argv + argc);

  // conventional chain test
  const string error_msg = "An error occured.";
  conventional_chain (arguments, error_msg);

  compose_result_chain (arguments);

  my_result_and_then_chain (arguments);
}
