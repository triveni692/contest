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

/* 
  Following function mutates the vectors, if you don't
  want them to be mutated, don't pass by ref (remove the '&').
  Method signature should look like:

vector<pt> multiply(vector<pt> a, vector<pt> b)
*/
vector<pt> multiply(vector<pt> & a, vector<pt> & b) {
	int n = a.size(); // degree of a is 'n-1'
	int m = b.size(); // degree of b is 'm-1'

	// Since the degree of the resultant polynomial will be n + m - 2,
	// we need to initialize both the arrays by the nearest power of 2
	// which is greater than or equal to n + m - 1.

	int nn = 1;
	while (nn < n + m - 1) nn <<= 1;

	a.resize(nn);
	b.resize(nn);
	DFT(a, false);
	DFT(b, false);
	for (int i = 0; i < nn; ++i) {
		a[i] *= b[i];
	}
	DFT(a, true);
	return a;
}

/* Tested : Ok */
int main()
{
	int n, m;
	vector<pt> a, b;

	cin >> n; // degree of polynomial a is 'n - 1'
	a.resize(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	cin >> m;
	b.resize(m);
	for (int i = 0; i < m; ++i) {
		cin >> b[i];
	}

	a = multiply(a, b);

	cout << "With leading zeroes:\n";
	
	for(int i = 0; i < a.size(); ++i) {
		cout << a[i].real() << " ";
	}
	cout << "\n";

	// One may ignore the highesr degree coefficients 
	// which are zero by chosing a suitable epsilon.

	cout << "After removing the leading zeroes:\n";

	const double eps = 1e-9;

	int nn = a.size() - 1; // degree of the result
	while (nn > 0) {
		if (abs(a[nn].real()) < eps) nn -= 1;
		else break;
	}
	for (int i = 0; i <= nn; ++i) {
		cout << a[i].real() << " ";
	}
	cout << "\n";

	
	/*
	Performance test
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

	vector <int> ans = f.multiply(a, b);
	*/

	return 0;
}

