#include <bits/stdc++.h>

using namespace std;

const int UNSOLVED = -1;

int dp[100][100];
char a[100];
char b[100];

int solve(int m, int n) {
	if (m == 0 || n == 0) return 0;
	int & ans = dp[m][n];
	if (ans == UNSOLVED) {
		ans = max(solve(m, n - 1), solve(m - 1, n));
		if (a[m] == b[n]) {
			ans = max(ans, solve(m - 1, n - 1) + 1);
		}
	}
	return ans;
}

void print_lcs(int m, int n) {
	if (m == 0 || n == 0) return ;

	if (dp[m - 1][n] == dp[m][n]) return print_lcs(m - 1, n);
	else if (dp[m][n - 1] == dp[m][n]) return print_lcs(m, n - 1);
	else {
		assert(a[m] == b[n]);
		assert(dp[m - 1][n - 1] + 1 == dp[m][n]);
		print_lcs(m - 1, n - 1);
		cout << a[m];
	}
}

int main() {
	int m, n;
	scanf("%d%d", &m, &n);
	scanf("%s%s", a + 1, b + 1);

	memset(dp, UNSOLVED, sizeof dp);

	int ans = solve(m, n);
	cout << ans << "\n";

	print_lcs(m, n);
	cout <<  "\n";

	return 0;
}