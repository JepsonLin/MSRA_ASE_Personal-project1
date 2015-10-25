#include <iostream>
//#include "stdio.h"
//#include<cstdio>
#include "math.h"
#include <algorithm>
#define Pi acos(-1.0)
using namespace std;

struct complex 
{
	double re, im;
	complex(double r = 0.0, double i = 0.0)
	{
		re = r, im = i;
	} 

	complex operator +(complex o)
	{
		return complex(re + o.re, im + o.im);
	}
	complex operator -(complex o)
	{
		return complex(re - o.re, im - o.im);
	}
	complex operator *(complex o)
	{
		return complex(re*o.re - im*o.im, re*o.im + im*o.re);
	}
};

void BRC(complex *y, unsigned long long len)
{
	unsigned long long i, j, k;
	for (i = 1, j = len / 2; i<len - 1; i++)
	{
		if (i<j)swap(y[i], y[j]);
		k = len / 2;
		while (j >= k)
		{
			j -= k; k = k / 2;
		}
		if (j<k)j += k;
	}
}

//on=1is FFT, on=-1 is IFFT
void FFT(complex *y, unsigned long long len, double on)
{
	unsigned long long i, j, k, h;
	complex u, t;
	BRC(y, len);
	for (h = 2; h <= len; h <<= 1)
	{
		
		complex wn(cos(on * 2 * Pi / h), sin(on * 2 * Pi / h));
		for (j = 0; j<len; j += h)
		{
			
			complex w(1, 0);
			for (k = j; k<j + h / 2; k++)
			{
				u = y[k];
				t = w*y[k + h / 2];
				y[k] = u + t;
				y[k + h / 2] = u - t;
				w = w*wn;
			}
		}
	}
	if (on == -1)
	for (i = 0; i<len; i++) 
		y[i].re /= len;
}

 long long Substract(char *p1, char *p2, unsigned long long len1, unsigned long long len2)
{
	unsigned long long i;
	if (len1<len2)
		return -1;
	if (len1 == len2)
	{
		for (i = len1 ; i >= 1; --i)
		{
			if (p1[i-1]<p2[i-1])    //p1<p2
				return -1;
			else if (p1[i-1]>p2[i-1]) //p1>p2
				break;
		}
	}
	for (i = 0; i<len2; ++i)
	{
		p1[i] -= p2[i];
		if (p1[i]<0)
		{
			p1[i] += 10;
			--p1[i + 1];
		}
	}
	while (i<len1&&p1[i] < 0)
	{
		p1[i] += 10;
		--p1[i + 1];
		i++;
	}
	for (i = len1; i >= 1; --i)
	if (p1[i-1])    
		return i ;
	return 0;   
}
 void Show(char *s,unsigned long long size)
 {
	 bool sign = 0;
	 if (s == NULL)
	 {
		 cout << "NULL Number!" << endl;
	 }
	 else
	 {
		 if (sign)
			 cout << '-';
		 if (size > 1)
		 {
			 if (s[size - 1] != 0)
				 cout << (char)(s[size - 1] + '0');
			 for (unsigned long long i = size - 1; i > 0; i--)
				 cout << (char)(s[i - 1] + '0');
		 }
		 else
			 cout << (char)(s[0] + '0');
	 }
 }