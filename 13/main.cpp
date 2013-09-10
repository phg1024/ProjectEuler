#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct BigInt
{
	typedef int64_t digit_t;
	static const unsigned int base = 100000000;
	static const unsigned int w = 8;
	
    static const size_t PRECISION = 400;
    BigInt():
        L(1)
    {
        memset(data, 0, sizeof(digit_t)*PRECISION);
    }

    BigInt(int num)
    {
        memset(data, 0, sizeof(digit_t)*PRECISION);

		L = 0;
		while( num )
		{
			data[L++] = num % base;
			num /= base;
		}
    }

    BigInt(const BigInt& other):
        L(other.L)
    {
        memset(data, 0, sizeof(digit_t)*PRECISION);
        memcpy(data, other.data, sizeof(digit_t)*other.L);
    }

    BigInt& operator=(const BigInt& other)
    {
        if( this != &other )
        {
            memset(data, 0, sizeof(digit_t)*PRECISION);
            L = other.L;
            memcpy(data, other.data, sizeof(digit_t)*other.L);
        }
        return (*this);
    }

    const digit_t& operator()(size_t pos) const
    {
        return data[pos];
    }

    digit_t& operator()(size_t pos)
    {
        return data[pos];
    }

    void leftShift(size_t n)
    {
        for(int i=L-1;i>=0;i--)
            data[i+n] = data[i];

        for(int i=n-1;i>=0;i--)
            data[i] = 0;

        L += n;
    }

    void rightShift(size_t n)
    {
        for(int i=0;i<L-n;i++)
            data[i] = data[i+n];
        L -= n;
    }

    void zero_justify();

    BigInt operator+(const BigInt& rhs) const;
    BigInt operator+(int rhs) const;
    BigInt operator-(const BigInt& rhs) const;
    BigInt operator-(int rhs) const;
    BigInt operator*(const BigInt& rhs) const;
    BigInt operator*(int rhs) const;
	BigInt operator^(int n) const;

    bool operator<(const BigInt& rhs) const;
    bool operator<=(const BigInt& rhs) const;
    bool operator>(const BigInt& rhs) const;
    bool operator>=(const BigInt& rhs) const;
    bool operator==(const BigInt& rhs) const;

    friend ostream& operator<<(ostream& os, const BigInt& num);
    friend istream& operator>>(istream& is, const BigInt& num);

    size_t L;
    digit_t data[PRECISION];
};

BigInt BigInt::operator+(const BigInt& rhs) const
{
    BigInt v = (*this);

    size_t maxL = max(v.L, rhs.L);

    v.L = maxL;

    for(size_t i=0;i<maxL;i++)
    {
        v(i) += rhs(i);
        if( v(i) >= base )
        {
            v(i) -= base;
            v(i+1)++;
        }
    }

    if( v(v.L) != 0 ) v.L++;

    return v;
}

BigInt BigInt::operator+(int rhs) const
{
    BigInt r(rhs);
    return (*this) + r;
}

BigInt BigInt::operator-(const BigInt& rhs) const
{
	// assumes (*this) > rhs
    BigInt v = (*this);

    // do the normal subtraction
    size_t maxL = max(v.L, rhs.L);
    for(int i=0;i<maxL;i++)
    {
        v(i) -= rhs(i);
        if( v(i) < 0 )
        {
            v(i) += base;
            v(i+1)--;
        }
    }

    v.L = maxL;

    // remove leading zeros
    v.zero_justify();
            
    return v;
}

BigInt BigInt::operator-(int rhs) const
{
    BigInt r(rhs);
    return (*this) - r;
}

BigInt BigInt::operator*(const BigInt& rhs) const
{
    BigInt res(0);
	res.L = rhs.L + L;
    for(size_t i=0;i<rhs.L;i++)
    {
        digit_t digit = rhs(i);
        for(size_t j=0;j<L;j++)
        {
			res(i+j) += digit * data[j];
			res(i+j+1) += res(i+j) / base;
			res(i+j) %= base;
        }
    }

    res.zero_justify();

    return res;
}

BigInt BigInt::operator*(int rhs) const
{
    return (*this) * BigInt(rhs);
}

BigInt BigInt::operator^(int n) const
{
	if( n == 0 ) return BigInt(1);
	
	if( n == 1 )
		return (*this);
	
	int m = n / 2;
	int k = n - m * 2;
	
	BigInt v = (*this)^m;
	BigInt vm = (*this)^k;
	return v * v * vm;	
}

void BigInt::zero_justify()
{
    for(int i=L-1;i>=0;i--)
    {
        if( data[i] != 0 ) break;
        L--;
    }

    if( L == 0 )
    {
        L = 1;
    } 
}

bool BigInt::operator<(const BigInt& rhs) const
{
    return rhs > (*this);
}

bool BigInt::operator<=(const BigInt& rhs) const
{
    return (*this) < rhs || (*this) == rhs;
}

bool BigInt::operator>(const BigInt& rhs) const
{
        if( L > rhs.L )
        {
            return true;
        }
        else if( L < rhs.L )
        {
            return false;
        }
        else
        {
            for(int i=L-1;i>=0;i--)
            {
                if( data[i] != rhs(i) )
                {
                    if( data[i] > rhs(i) )
                        return true;
                    else
						return false;
                }
            }

            return false;
        }
}

bool BigInt::operator>=(const BigInt& rhs) const
{
    return ((*this) > rhs) || ((*this) == rhs);
}

bool BigInt::operator==(const BigInt& rhs) const
{
    if( L != rhs.L ) return false;

    for(size_t i=0;i<L;i++)
        if( data[i] != rhs(i) ) return false;
    return true;
}

istream& operator>>(istream& is, BigInt& num)
{
	string buf;
	getline(is, buf);

	std::reverse(buf.begin(), buf.end());

	num.L = ceil(buf.size() / (double)BigInt::w);

	for(int i=0;i<num.L;i++)
	{
		int val = 0;
		int offset = i * BigInt::w;
		for(int j=offset + BigInt::w - 1;j>=offset;j--)
		{
			if( j >= buf.size() ) continue;
			val = val * 10 + (buf[j] - '0');
		}
		num(i) = val;
	}

	return is;
}

ostream& operator<<(ostream& os, const BigInt& num)
{
	os << num(num.L-1);
    for(int i=num.L-2;i>=0;i--)
        os << setw(BigInt::w) << setfill('0') << num(i);

    return os;
}

int main()
{
    int ncases = 100;
	BigInt sum(0);
    for(int i=0;i<ncases;i++)
    {
        BigInt n;
        cin >> n;
		sum = sum + n;
    }
	
	cout << sum << endl;
    return 0;
}
