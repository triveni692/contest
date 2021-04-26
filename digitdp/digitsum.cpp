#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod = 1000000007;

char N[100100];
int n, D;

ll dp[2][10010][101];

/*
 dp[0][idx][r]: Number of integers from 0 to N[idx ...] such that their 
 sum of digits produces remainder r modulo D.
 dp[1][idx][r]: Number of integers from 0 to [99...9] (n - idx 9's) such
 that the sum of digits produces remainder r modulo D. 
*/

ll solve(int idx, int r, int full_search) {
	// full_search indicates that we're allowed to use digits 0-9
	// everywhere without restriction. This is because the higher
	// significant digit has been set to a smaller value.
	if (idx == n) return (r == 0);

	ll & ans = dp[full_search][idx][r];

	if (ans != -1) return ans;

	ans = 0;

	int dig = !full_search ? N[idx] - '0' : 9;

	for (int d = 0; d < dig; ++d) {
		ans += solve(idx + 1, (r - d%D + D)%D, 1);
	}
	ans += solve(idx + 1, (r - dig%D + D)%D, full_search);
	ans %= mod;
	return ans;
}

int main() {
	scanf("%s %d", N, &D);
	n = strlen(N);
	
	// Initialize the dp with -1
	for (int i = 0; i < n; ++i) 
		for (int j = 0; j < D; ++j)
			for (int k = 0; k < 2; ++k)
				dp[k][i][j] = -1;

	ll ans = solve(0, 0, 0);

	// because 0 is always included in the answer, and we need to remove it
	ans = (ans + mod - 1) % mod;

	cout << ans << "\n";

	return 0;
}