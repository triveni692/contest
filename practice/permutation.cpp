// Problem: https://atcoder.jp/contests/dp/tasks/dp_t
/*
	To solve this problem we'll use DP on permutations. The state is:
	
	dp[n, k] = Number of permutations p(n) that satisfies the criteria
	  		posed by the prefix of length 'n - 1' (of the given string, s).
	
	To find the recurrence, we'll fix the last number to 'k' and count
	the number of permutations of the first 'n - 1' numbers that satisfy
	the given criteria. 

	Please note that that after removal of 'k', the
	remaning n-1 numbers are not actually p(n-1) but one can map them
	with p(n-1) easily as follows:
	 
	 p(n)-{k}: [1, 2, .., k-1, k+1, ... n]
	 p(n-1):   [1, 2, .., k-1, k, ... n-1]
	
	The recurrence will be formed as follows, in two cases:-

	a) When s[n-1] is '<': 

		for 1 <= i < k: dp[n, k] += dp[n-1, i]

	b) When s[n-1] is '>':

		for k <= i < n: dp[n, k] += dp[n-1, i]

	Please note that in the second case, we're not going from k+1 because that would
	be correct for the original set of numbers, i.e., p(n)-{k}, but for the corres-
	ponding p(n-1), one can see that the it should be from k.

*/

#include <bits/stdc++.h>

using namespace std;

const int mod = 1000000007;

int dp[3010][3010];
char s[3010];

int solve(int n, int k) {
	// This is the obvious implementation, but is inefficient
	// This is O(n^3), but can be quickly improved by keeping
	// The cummulative sum of dp array.
	if (n == 1) return n == k;
	int& ans = dp[n][k];
	if (ans != -1) return ans;

	ans = 0;

	if (s[n-1] == '<') {
		for (int i = 1; i < k; ++i) {
			ans += solve(n-1, i);
			if (ans >= mod) ans -= mod;
		}
	}else {
		for (int i = k; i < n; ++i) {
			ans += solve(n-1, i);
			if (ans >= mod) ans -= mod;
		}
	}
	return ans;
}

int solve_fast(int N) {
	// Uses the cummulative/prefix sum of the dp[n] array.
	memset(dp, 0, sizeof (dp));
	dp[1][1] = 1;
	for (int n = 2; n <= N; ++n) {
		for (int k = 1; k <= n; ++k) {
			dp[n][k] = s[n-1] == '>' ? dp[n-1][n-1] - dp[n-1][k-1]: dp[n-1][k-1];

			dp[n][k] += dp[n][k-1]; // prefix sum part
		
			if (dp[n][k] >= mod) dp[n][k] -= mod;
			else if (dp[n][k] < 0) dp[n][k] += mod;
		}
	}
	return dp[N][N];
}

int main() {
	int n;
	scanf("%d %s", &n, s+1);
	/*
		Basic implementation executer.
		-------
		memset(dp, -1, sizeof (dp));
		int ans = 0;
		for (int k = 1; k <= n; ++k) {
			ans += solve(n, k);
			if (ans >= mod) ans -= mod;
		}
	*/
	printf("%d\n", solve_fast(n));
	return 0;
}

