/*
 * =============================================================================
 *
 *       Filename:  longpolygon.cpp
 *
 *    Description:  udemy functional programming with cpp
 *	section 2 lecture 
 *        Version:  1.0
 *        Created:  26/11/18 15:07:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Myoungki Jung (mj), myoungki.jung@gmail.com
 *   Organization:  Lunarpulse
 *
 * =====================================7========================================
 */

#include <fplus/fplus.hpp>

typedef std::pair < float, float > point;

float
point_distance (const point & p1, const point & p2)
{
  const float
    dx = p2.first - p1.first;
  const float
    dy = p2.second - p1.second;
  return std::sqrt (dx * dx + dy * dy);
}

int
main ()
{
  using namespace std;

  vector < point > polygon =
  {
    { 1, 2}, { 7, 3}, { 6, 5}, { 4, 4}, { 2, 9}};

  const auto edges = fplus::overlapping_pairs_cyclic (polygon);

  const auto result = fplus::maximum_on (
                [](const std::pair<point,point> &point_pair)->float{
                	return point_distance(point_pair.first, point_pair.second);
		}, edges);
  cout << fplus::show (result) <<": "<< point_distance( result.first, result.second)<< endl;
}

// Exercise:
//     Change the call to maximum_on
//     by using a lambda function
//     using point_distance internally,
//     so the code compiles and runs as intended.
//  const auto result = fplus::maximum_on(
//		  [](const std::pair<point, point>& edge) -> float
//		  {
//		  return point_distance(edge.first, edge.second);
//		  }, edges);
