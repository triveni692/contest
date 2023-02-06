#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353;

inline int pow_(ll a, int n, int p=mod){
int r=1;while(n){if(n&1)r=r*a%p;n>>=1;a=a*a%p;}return r;}
inline int inv_(int a) {return pow_(a, mod-2, mod);}
inline int add(int a, int b){a+=b;if(a>=mod)a-=mod;return a;}
inline void adds(int& a, int b){a+=b;if(a>=mod)a-=mod;}
inline int mul(int a, int b){return a*1ll*b%mod;}
inline void muls(int& a, int b){a=a*1ll*b%mod;}
inline int sub(int a, int b){a-=b;if(a<0)a+=mod;return a;}

// IMP: if 3 is not a generator, please change this.
void ntt(int a[], int n, bool inv, int gen = 3) {
	for (int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		for (; j >= bit; bit >>= 1) j -= bit;
		j += bit;
		if (i < j) swap(a[i], a[j]);
	}
	vector<int> ws; int w = pow_(gen, (mod - 1) / n);
	if (inv) w = inv_(w);
	for (int h = 1; h < n; h <<= 1, muls(w, w)) {
		ws.push_back(w);
	}
	for (int len = 1; len < n; len <<= 1) {
		w = ws.back(); ws.pop_back();
		for (int i = 0, c = 1; i < n; i += (len<<1), c = 1) {
			for (int j = 0; j < len; j++, muls(c, w)) {
				int u = a[i+j], v = mul(a[i+j+len], c);
				a[i+j] = add(u, v), a[i+j+len] = sub(u, v);
			}
		}
	}
	if(inv) {
		int n_ = inv_(n);
		for(int i = 0; i < n; ++i) muls(a[i], n_);
	}
}
int main()
{
	
	return 0;
}
