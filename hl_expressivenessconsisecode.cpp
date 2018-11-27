/*
 * =============================================================================
 *
 *       Filename:  hl_expressivenessconsisecode.cpp
 *
 *    Description:  high level expressiveness and consize code 
 *    Section 2 lecture 9
 *
 *        Version:  1.0
 *        Created:  26/11/18 16:26:04
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

float
point_distance (const point & p1, const point & p2)
{
  const float dx = p2.first - p1.first;
  const float dy = p2.second - p1.second;
  return std::sqrt (dx * dx + dy * dy);
}

int
main ()
{
  using namespace std;

  vector < point > polygon = { { 1, 2}, { 7, 3}, { 6, 5}, { 4, 4}, { 2, 9}};

  const auto edge_length =[](const std::pair < point, point > &point_pair)->float {
    const float
      dx = point_pair.second.first - point_pair.first.first;
    const float
      dy = point_pair.second.second - point_pair.second.second;
    return
    std::sqrt (dx * dx + dy * dy);
  };

  const auto get_edges =[](auto polygon) {
    return fplus::overlapping_pairs_cyclic (polygon);
  };
  const auto result = fplus::maximum_on (edge_length, get_edges (polygon));

  cout << fplus::show (result) << endl;
}

// Exercise:
//     Implement edge_length and get_edges
//     so the improved code from above works.
