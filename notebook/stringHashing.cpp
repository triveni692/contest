/*
 Class : Hashing (Rabin - Karp - Technique)
 @Input : a string str
 @Indexing : 0-based everywhere
 @Query : 
 	1. Method : getHash() return Hash value of the string
 	2. Method : getHash(int l) return hash value of the string str[l...end]
 	3. Method : getHash(int l, int r) returns hash value of str[l...r]
 @Space : O(n)
 @Time : O(n) preprocessing, O(1) per query
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

class Hashing
{
public:
	const LL BASE = 256, mod = 1e9+7;
	LL * ipow, * hash;
	int n;
	Hashing(string& str)
	{
		n = str.length();
		ipow = new LL[n];
		hash = new LL[n];
		
		ipow[0] = 1;
		hash[0] = str[0];

		LL inv = pow_(BASE, mod - 2, mod);
		LL prv = 1;

		for(int i = 1; i < n; ++i)
		{
			prv = prv * BASE % mod;
			ipow[i] = ipow[i-1] * inv % mod;
			hash[i] = hash[i-1] + prv * str[i] % mod;
			if(hash[i] >= mod) hash[i] -= mod;
		}
	}
	~Hashing()
	{
		delete ipow;
		delete hash;
	}

	LL getHash(int s = 0, int e = -1)
	{
		if (e == -1) e = n-1;
		LL ans = hash[e];
		if(s > 0)
		{
			ans = ans - hash[s-1];
			if(ans < 0) ans += mod;
			ans = ans * ipow[s] % mod;
		}
		return ans;
	}

	LL pow_(LL a, LL b, LL mod)
	{
		LL ans = 1;
		while(b)
		{
			if(b & 1) ans = ans * a % mod;
			b >>= 1;
			a = a * a % mod;
		}
		return ans;
	}
};

/* Tested : Ok. */
int main()
{
	string str;
	cin >> str;
	unordered_set <string> uset;
	set <LL> st;
	Hashing hs(str);
	for(int i = 0; i < str.length(); ++i)
		for(int l = 1; i + l <= str.length(); ++l)
		{
			uset.insert(str.substr(i, l));
			st.insert(hs.getHash(i, i+l-1));
		}
	cerr << st.size() << " " << uset.size() << endl;
	assert(st.size() == uset.size());
	return 0;
}

