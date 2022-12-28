#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod = 1e9 + 7;

ll pow_(ll a, int n) {
	ll ans = 1;
	while(n) {
		if (n&1) ans = ans * a % mod;
		a = a * a % mod;
		n >>= 1;
	}
	return ans;
}

inline ll inv_(ll a) { return pow_(a, mod-2); }

void row_op(vector<vector<int>> & v, int n) {
	for (int i = 0; i < n; ++i) {
		if (!v[i][i]) {
			// swap rows
			int j=i+1; while(j<n && !v[j][i]) ++j;
			assert(j < n && "not invertible");
			swap(v[i], v[j]);
		}
		ll ii = inv_(v[i][i]);
		for (int j = i; j < v[i].size(); ++j) {
			// make the pivot = 1
			v[i][j] = v[i][j] * ii % mod;
		}
		for(int r = i + 1; r < n; ++r) {
			if (!v[r][i]) continue;
			ll coeff = v[r][i];
			// make each row's left to be 0
			for (int c = i; c < v[r].size(); ++c) {
			 	v[r][c] -= coeff * v[i][c] % mod;
			 	if (v[r][c] < 0) v[r][c] += mod;
			}
		}
	}
	// now make the matrix = 1
	for (int c = n - 1; c >= 0; --c) {
		for (int r = c - 1; r >= 0; --r) {
			// only iterate for index >= n because all
			// other will certainly be zero
			for (int cc = n ; cc < v[r].size(); ++cc) {
				v[r][cc] -= (ll)v[c][cc] * v[r][c] % mod;
				if (v[r][cc] < 0) v[r][cc] += mod;
			}
			v[r][c] = 0;
		}
	}
	// for (int i = 0; i < n; ++i) {
	// 	for (int j = 0; j < n; ++j) cerr << v[i][j] << " "; cerr << " | " << v[i][n] <<"\n";
	// }
}

void solve(int tc) {
	vector<vector<int> > v = {{1, 1, 1, 6}, {1, 2, 4, 15}, {1, 3, 9, 28}};
	row_op(v, 3);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int tc = 1; tc <= T; ++tc) {
		solve(tc);
	}
	return 0;
}