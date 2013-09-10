#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <iomanip>
#include <bitset>

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

bitset<65536> notPrime(0);
int primes[7000];
int nprimes = 0;

void init()
{
	for(int i=2;i<257;)
 	{
		for(int j=i+i;j<65536;j+=i)
 			notPrime[j] = 1;
		
		i++;
		while( notPrime[i] == 1 && i < 257 ) i++;
 	}
	
	for(int i=2;i<65536;i++)
	{
		if( notPrime[i] == 0 )
		{
			primes[nprimes++] = i;
		}
	}
}

void factorize(int64_t n, int facs[], int cnt[], int& nfacs)
{
	nfacs = 0;
	for(int i=0;i<nprimes;i++)
	{
		int p = primes[i];
		
		if( p * p > n ) break;
		
		cnt[nfacs] = 0;
		while( n % p == 0 )
		{
			cnt[nfacs]++;
			n /= p;
		}
		
		if( cnt[nfacs] > 0 )
		{
			facs[nfacs++] = p;
		}
	}
	
	if( n > 1 )
	{
		cnt[nfacs] = 1;
		facs[nfacs++] = n;
	}
}

int solve(int64_t n)
{
	int64_t m = (n * (n+1)) >> 1;
	
	int nfacs;
	int facs[128];
	int cnt[128];
	
	factorize(m, facs, cnt, nfacs);
		
	int res = 1;
	for(int i=0;i<nfacs;i++)
	{
		res *= (cnt[i] + 1);
	}
	
	if( res > 500 )
		cout << m << " : " << res << endl;
	
	return res;
}

int main()
{	
	init();
	int64_t n = 1;
	while( true )
	{
		int k = solve( n );
		if( k > 500 )
		{
			break;
		}
		n++;
	}
    return 0;
}
