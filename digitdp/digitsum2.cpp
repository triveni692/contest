// Problem: https://www.spoj.com/problems/PR003004/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

char num[100];
int n;

ll dp[2][17];
ll pow10[17];
ll num_eq[17];

/*
 We need to find the sum of digits from '00000' to '54327' for example.
 So we iterate from the most significant bit to the least significant bit.
 The above range can be broken into 2 parts -
  1. from '00000' to '49999':
  	In this case, the contribution comes from two parts - 
   		a. The most significant digit
   		  - For each value 'd' for the most significant bit, the sum
   			contributed is d * 10^(k-1). In this example, #digits, k = 5. 
   			We need to iterate for 0 <= d < dig[i]. In this example, 0 <= d < 5.
   			So, overall, sum contributed is = 10^k-1 * dig[i] * (dig[i]-1) / 2

   		b. The rest of the digits
   		  - For each choice of the most significant bit, the sum contributed
   		  	can be found separately for these simpler cases [0000 - 9999]. So,
   		  	the overall contribution is = dig[i] * 45k * 10^k-1. Here k = 4.
   		  	NOTE: the mentioned formula can also be done in a DP way.
  
  2. from '50000' to '54327'
  	In this case again the sum will be contributed because of two parts -
  		a. The most significant digit
  		  - Contribution = dig[i] * (int(dig[i + 1, ...]) + 1). In this example,
  		  	it is equal to 5 * (4327 + 1).

  		b. Rest of it
  		  - Contribution can be found out recursively for the remaining suffix
  		  	after the removal of the most significant digit.
*/

ll solve(int idx, int full_search) {
	// full_search indicates that we're allowed to use digits 0-9
	// everywhere without restriction. This is because the higher
	// significant digit has been set to a smaller value.
	if (idx == n) return 0;

	ll & ans = dp[full_search][idx];

	if (ans != -1) return ans;

	ll dig = !full_search ? num[idx] - '0' : 9;

	// Case I: contribution by most significant digit
	ans = dig * (dig - 1) / 2 * pow10[idx + 1];

	// Case I: contribution because of the other digits
	ans += dig * solve(idx + 1, 1);

	// Case II: Contribution by the most significant digit
	ans += dig * (!full_search ? num_eq[idx + 1] + 1: pow10[idx + 1]);

	// Case II: Contribution because of the rest
	ans += solve(idx + 1, full_search);

	return ans;
}

ll solve(ll a) {
	sprintf(num, "%lld", a);
	n = strlen(num);

	pow10[n] = 1;
	for (int i = n - 1; i >= 0; --i) 
		pow10[i] = pow10[i + 1] * 10;

	num_eq[n] = 0;
	for (int i = n - 1; i >= 0; --i)
		num_eq[i] = num_eq[i + 1] + pow10[i + 1] * (num[i] - '0');

	memset(dp, -1, sizeof(dp));
	return solve(0, 0);
}

int main() {

	int T;
	scanf("%d", &T);
	while(T--) {
		ll a, b;
		scanf("%lld %lld", &a, &b);

		ll ans = solve(b);
		if (a > 0) ans -= solve(a - 1);

		printf("%lld\n", ans);

	}
	return 0;
}