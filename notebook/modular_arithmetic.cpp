/*
	Most commonly used modular arithmatic functions
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod = (int)1e9 + 7;

ll pow_(ll a, int n) {
	ll ans = 1;
	while(n) {
		if (n&1) ans = ans * a % mod;
		n >>= 1;
		a = a * a % mod;
	}
	return ans;
}

ll mod_inv(int a) {
	return pow_(a, mod - 2);
}

void mod_inverse_all(int n) {
	// computes modular inverse of all numbers from 1 to n
	// in linear time without using mod pow
	vector<int> inv(n + 1);
	
	inv[1] = 1;
	for(int i = 2; i <= n; ++i)
    	inv[i] = mod - (mod/i) * inv[mod%i] % mod;
}

int main() {

	return 0;
}