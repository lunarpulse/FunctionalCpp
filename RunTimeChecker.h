/*
 * =============================================================================
 *
 *       Filename:  RunTimeChecker.h
 *
 *    Description:  a library composed of timing tools
 *
 *        Version:  1.0
 *        Created:  29/11/18 18:12:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Myoungki Jung (mj), myoungki.jung@gmail.com
 *   Organization:  Lunarpulse
 *
 * =============================================================================
 */

#include <chrono>

class Timer{
	public: Timer(): beg_(clock::now()){}
		void reset(){beg_= clock::now();};
		double elasped() const{
			return std::chrono::duration_cast<second>
				(clock::now() - beg_).count();
		}
	private:
		typedef std::chrono::high_resolution_clock clock;
		typedef std::chrono::duration<double, std::ratio<1>> second;
		std::chrono::time_point<clock> beg_;

};
