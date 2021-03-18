/*
 Class : FFT (compute DFT using FFT algorithm)
 @Input : two polynomials vector<type> a, b.
 @Query : 
 	1. Method : DFT(vector <pt> v, bool inv) fill v with its DFT. inv = 1 means inverse DFT
 	2. Method : doit(vector <pt> a, b, res) multiply a and b and fill into res
 	3. Method : multiply(vector<int> a, b) returns a vector<int> (length is perfect power of 2),
 				containing multiplication of polynomials a and b
 @Space : O(n)
 @Time : O(n log(n))
 @Performance : n = 40000 => 1 second.
 @Rating : Slow.
*/

#include <bits/stdc++.h>

using namespace std;

typedef complex <double> pt;

void DFT(vector <pt>& a, bool inv)
{
	int n = a.size();
	for (int i = 1, j = 0; i < n; i++)
	{
		int bit = n >> 1;
		for (; j >= bit; bit >>= 1) j -= bit;
		j += bit;
		if (i < j) swap(a[i], a[j]);
	}
	for (int len = 2; len <= n; len <<= 1)
	{
		double ang = 2 * M_PI / len * (inv ? -1 : 1);
		pt wlen(cos(ang), sin(ang));
		for (int i = 0; i < n; i += len)
		{
			pt w(1);
			for (int j = 0; j < len/2; j++, w *= wlen)
			{
				pt u = a[i+j], v = a[i+j+len/2] * w;
				a[i+j] = u + v, a[i+j+len/2] = u - v;
			}
		}
	}
	if(inv) for(int i = 0; i < a.size(); ++i) {
		a[i] /= (double)a.size();
	}
}

/* Tested : Ok */
int main()
{
	int n, m;
	vector<pt> a, b;
	n = m = 40000;

	a.resize(n);
	b.resize(m);

	for(int i = 0; i < n; ++i)
	{
		a[i] = rand() % 100000007;
	}

	for(int i = 0; i < m; ++i)
	{
		b[i] = rand() % 10000007;
	}

//	vector <int> ans = f.multiply(a, b);

	return 0;
}

