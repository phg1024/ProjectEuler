// next_permutation example
#include <iostream>     // std::cout
#include <algorithm>    // std::next_permutation, std::sort
#include <iterator>
using namespace std;

int main () {
	int myints[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	int cnt = 1;	
	const int N = 1000000;
  	do 
  	{
		std::next_permutation(myints,myints+10);
  	} while ( (++cnt) < N );

	std::copy(myints, myints+10, ostream_iterator<int>(cout, ","));

  	return 0;
}