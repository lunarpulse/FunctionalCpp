/*
 * =============================================================================
 *
 *       Filename:  forward_application.cpp
 *
 *    Description:  functional programming with CPP
 *    section 2.11
 *
 *        Version:  1.0
 *        Created:  26/11/18 21:20:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Myoungki Jung (mj), myoungki.jung@gmail.com
 *   Organization:  Lunarpulse
 *
 * =============================================================================
 */

#include <fplus/fplus.hpp>

typedef
std::pair < float, float >
  point;
typedef
  std::pair <
  point,
  point >
  edge;
typedef
  std::vector <
  point >
  points;

float
point_distance (const point & p1, const point & p2)
{
  const float
    dx = p2.first - p1.first;
  const float
    dy = p2.second - p1.second;
  return std::sqrt (dx * dx + dy * dy);
}

float
edge_length (const edge & e)
{
  return point_distance (e.first, e.second);
}

std::vector < edge > get_edges (const points & polygon)
{
  return fplus::overlapping_pairs_cyclic (polygon);
}

const auto str_to_int = fplus::read_value_unsafe < int >;

int
main ()
{
  using namespace
    std;
  using namespace
    fplus;

  const
    std::string
    input = "1,5,4,7,4,2,2,3";

  const auto
    parts = split (',', false, input);
  const auto
    nums = transform (str_to_int, parts);
  const auto
    result_product = product (nums);

  cout << result_product << endl;

  const auto
    result_product_nested = product (transform (str_to_int,
						split (',', false, input)));

  cout << result_product_nested << endl;

  //result = input
  // |> split(',',false)
  // |> transform(str_to_int)
  // |> product
  const auto
    result_product_fa =
    fwd::apply (input, fwd::split (',', false), fwd::transform (str_to_int),
		fwd::product ());

  cout << result_product_fa << endl;


  vector < point > polygon =
  {
    {
    1, 2},
    {
    7, 3},
    {
    6, 5},
    {
    4, 4},
    {
    2, 9}
  };

  // const auto result = fplus::maximum_on (edge_length,
  //                                      get_edges (polygon));

  const auto
    result = fwd::apply (polygon, get_edges, fwd::maximum_on (edge_length));

  cout << show (result) << endl;

  vector < int >
  iv = { 23, 12, 43, 5, 2, 34, 23, 2, 16, 8, 9, 18 };
 int i = 9;
  const auto result_complex = fwd::apply (iv,
			  fwd::standardize(),
			  fwd::unique(),
			  fwd::sum(),
			  fwd::square(),
			  fwd::max_2 (30),
			  fwd::cube (),
			  fwd::min_2 (10000000),
			  fwd::abs (),
			  fwd::abs_diff(65535)
			  );
  cout << show (result_complex) << endl;
}

// Exercise 1:
//     Rewrite the the longest-edge code
//     in forward-application style.

// Exercise 2:
//     Invent a quite long chain of function applications,
//     at least 5 functions,
//     and implement its application to an input value
//     in all three styles:
//         1) Assign intermediate values to variables.
//         2) Nested function calls
//         3) Foward-application style
//     Compare all three versions and contemplate
//     the readability of all of them.
