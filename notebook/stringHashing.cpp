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

typedef long long ll;

inline int pow_(long long a, int n, int p){
int r=1;while(n){if(n&1)r=r*a%p;n>>=1;a=a*a%p;}return r;}

template<const int Base, const int Modulo>
class Hashing {
public:
	Hashing(string& str) : n(str.length()) {
		ipow.resize(n);
		hash.resize(n);
		
		ipow[0] = 1;
		hash[0] = str[0];

		ll inv = pow_(Base, Modulo - 2, Modulo);
		ll prv = 1;

		for(int i = 1; i < n; ++i) {
			prv = prv * Base % Modulo;
			ipow[i] = ipow[i-1] * inv % Modulo;
			hash[i] = hash[i-1] + prv * str[i] % Modulo;
			if(hash[i] >= Modulo) hash[i] -= Modulo;
		}
	}
	int get_hash(int s = 0, int e = -1) {
		if (e == -1) e += n; 
		ll ans = hash[e];
		if(s > 0) {
			ans = ans - hash[s-1];
			if(ans < 0) ans += Modulo;
			ans = ans * ipow[s] % Modulo;
		}
		return ans;
	}
private:
	typedef long long ll;
	vector<int> ipow, hash;
	int n;
};

/* Tested : Ok. */
int main()
{
	string str;
	cin >> str;
	unordered_set <string> uset;
	set <ll> st;
	Hashing<256,(int)1e9+7> hs(str);
	for(int i = 0; i < str.length(); ++i)
		for(int l = 1; i + l <= str.length(); ++l)
		{
			uset.insert(str.substr(i, l));
			st.insert(hs.get_hash(i, i+l-1));
		}
	cerr << st.size() << " " << uset.size() << endl;
	assert(st.size() == uset.size());
	return 0;
}

