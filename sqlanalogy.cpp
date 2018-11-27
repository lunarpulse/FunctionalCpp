/*
 * =============================================================================
 *
 *       Filename:  sqlanalogy.cpp
 *
 *    Description:  functional programming 
 *    section 2.12
 *
 *        Version:  1.0
 *        Created:  26/11/18 23:12:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Myoungki Jung (mj), myoungki.jung@gmail.com
 *   Organization:  Lunarpulse
 *
 * =============================================================================
 */

#include <fplus/fplus.hpp>

struct user
{
  std::string name;
  std::string country;
  std::size_t visits;
};

std::string get_country (const user & u)
{
  return u.country;
}

std::size_t get_visits (const user & u)
{
  return u.visits;
}

int
main ()
{
	using namespace fplus;
	using namespace std;
  const std::vector < user > users = {
    {"Nicole", "GER", 2},
    {"Justin", "USA", 1},
    {"Rachel", "USA", 5},
    {"Robert", "USA", 6},
    {"Stefan", "GER", 4}
  };

  const auto visit_sum=[](const std::vector <user> &xs)->std::size_t{
	  return fwd::apply(xs,
			  fwd::transform(get_visits),
			  fwd::sum()
			  );
  };

  const auto result_log = fwd::apply(users,
		  fwd::sort_on(get_country),
		  fwd::group_globally_on_labeled(get_country),
		  fwd::transform(fwd::transform_snd(visit_sum))
		  );
  
  cout << show_cont (result_log) << endl;

  const auto result = fwd::apply(users,
		  fwd::group_globally_on_labeled(get_country),
		  fwd::transform(fwd::transform_snd(visit_sum))
		  );
  
  cout << show_cont (result) << endl;
  const auto sum_cube =	[](const auto &xs){
	  return fwd::apply(xs,
			  fwd::transform(get_visits),
			  fwd::sum(),
			  fwd::cube(),
			  fwd::square()
			  );
  };
  const auto result_test = fwd::apply(
		  users,
		  fwd::group_globally_on_labeled(get_country),
		  fwd::transform(
			  fwd::transform_snd(sum_cube)
			  )
		  );

  cout << show_cont (result_test) << endl;

}
// SELECT country, SUM(visits)
//   FROM users
//     GROUP BY country;

// Exercise:
//     Implement the task solved by the SQL query above
//     in C++ using the following fplus functions:
//     - group_globally_on_labeled
//     - transform_snd
//     - mean
//     Look them up in the API search,
//     and understand the type signatures.

// Bonus Exercise:
//     The run-time complexity of your algorithm will be O(n^2),
//     due to using group_globally_on_labeled.
//     But Strings form a partially ordered set.
//     See if you can get down to O(n*log(n))
//     by using sort and group_on_labeled.
