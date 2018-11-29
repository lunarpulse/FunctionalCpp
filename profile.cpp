/*
 * =============================================================================
 *
 *       Filename:  profile.cpp
 *
 *    Description:  testing profiling 
 *
 *        Version:  1.0
 *        Created:  29/11/18 13:31:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Myoungki Jung (mj), myoungki.jung@gmail.com
 *   Organization:  Lunarpulse
 *
 * =============================================================================
 */

#include	<stdlib.h>
#include <set>
#include <iostream>
#include <vector>
#include <algorithm>
#include "RunTimeChecker.h"

/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  main
 *  Description:  
 * =============================================================================
 */
	int
main ( int argc, char *argv[] )
{
	using namespace std;
	vector<int> v = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38};

	Timer stopwatch;
        const int upperLimit = 2000000;	
	for ( int i = 0 ; i< upperLimit ; ++i )
	{
		find(begin(v), end(v), 25);
	}
	cout<<"vector: "<< stopwatch.elasped() << " s" << endl;
        
	set<int> s = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38};

	stopwatch.reset();
	for ( int i = 0 ; i< upperLimit ; ++i )
	{
		find(begin(s), end(s), 25);
	}
	cout<<"set: "<< stopwatch.elasped() << " s" << endl;
	return EXIT_SUCCESS;
}				/* ----------  end of function main  -------- */
