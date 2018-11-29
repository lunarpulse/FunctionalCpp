/*
 * =============================================================================
 *
 *       Filename:  async.cpp
 *
 *    Description:  async from cppreference.com
 *    Run        : clang++ -O3 -g -std=c++14 -lpthread async.cpp -o async && ./async
 *        Version:  1.0
 *        Created:  29/11/18 15:21:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Myoungki Jung (mj), myoungki.jung@gmail.com
 *   Organization:  Lunarpulse
 *
 * =============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>

template < typename RandomIt > int
parallel_sum (RandomIt beg, RandomIt end)
{
  auto len = end - beg;
  if (len < 1000)
    return std::accumulate (beg, end, 0);

  RandomIt bmid = beg + len / 4;
  RandomIt mid = bmid + len / 4;
  RandomIt fmid = mid + len / 4;
  auto handle1 = std::async (std::launch::async,
			     parallel_sum < RandomIt >, bmid, mid);
  auto handle2 = std::async (std::launch::async,
			     parallel_sum < RandomIt >, mid, fmid);
  auto handle3 = std::async (std::launch::async,
			     parallel_sum < RandomIt >, fmid, end);
  int sum = parallel_sum (beg, bmid);
  return sum + handle1.get () + handle2.get () + handle3.get ();
}

int
main ()
{
  std::vector < int >v (10000, 1);
  std::cout << "The sum is " << parallel_sum (v.begin (), v.end ()) << '\n';
}
