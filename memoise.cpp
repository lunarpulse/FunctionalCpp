/*
 * =============================================================================
 *
 *       Filename:  momoise.cpp
 *
 *    Description:  memoise with dictionary
 *
 *        Version:  1.0
 *        Created:  27/11/18 13:02:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Myoungki Jung (mj), myoungki.jung@gmail.com
 *   Organization:  Lunarpulse
 *
 * =============================================================================
 */


#include	<stdlib.h>
#include <iostream> 
#include <functional>
#include <unordered_map>
template <typename F>
std::function<int(int)> memoise(F f)
{
	std::unordered_map<int,int> storage;
	return [f, storage](int x )mutable-> int
	{
		const auto it = storage.find(x);
		if(it==storage.end())
			return storage.insert(std::make_pair(x,f(x))).first->second;
		else
			return it->second;
	};
}

int costly_function(int x)
{
	return 42+x;
}

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

	const auto c_f_memoised = memoise(costly_function);
	cout<<c_f_memoised(11)<<endl;
	cout<<c_f_memoised(11)<<endl;
	cout<<c_f_memoised(12)<<endl;
	cout<<c_f_memoised(51)<<endl;
	cout<<c_f_memoised(11)<<endl;
	cout<<c_f_memoised(21)<<endl;
	cout<<c_f_memoised(51)<<endl;

	return EXIT_SUCCESS;
}				/* ----------  end of function main  -------- */
