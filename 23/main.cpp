#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

const int MAXN = 28124;
bool flag[MAXN];
int anumber[MAXN];
int anumbercount;

bool isAbundant(int64_t val)
{
    // 1 is deficient
    if( val == 1 ) return false;

    int64_t sum = 1;
    int bound = floor(sqrt(val));

    for(int i=2;i<=bound;i++)
    {
        if( val % i == 0 )
        {
            int64_t q = val / i;
			if( q != i )
				sum += (i+q);
			else
				sum += i;
        }
    }
    return (sum - val) > 0;
}

void init()
{
	anumbercount = 0;
	flag[0] = false;
	for(int i=1;i<MAXN;i++)
	{
		if( isAbundant( i ) )
		{
			flag[i] = true;
			anumber[anumbercount++] = i;
		}
		else
			flag[i] = false;
	}
}

int main()
{
	init();
	
	int64_t sum = 0;
	for(int i=1;i<MAXN;i++)
	{
		bool passed = true;
		for(int j=0;j<anumbercount;j++)
		{
			if( anumber[j] > i ) break;
			int r = i - anumber[j];
			if( flag[r] )
			{
				passed = false;
			}
		}
		if( passed ) sum += i;
	}
	
	cout << sum << endl;
	
    return 0;
}
