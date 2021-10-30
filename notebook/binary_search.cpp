#include <bits/stdc++.h>

using namespace std;

template <typename F>
int binary_search(int lo, int hi, F && func) {
	// seq: [.., true, true, true, |false|, false, ..]
	// ret: first occurence of false (i.e., blocked one)

	// func: returns true for 'lo = mid' assignment
	while(hi - lo > 1) {
		int mid = (lo + hi) / 2;
		if (func(mid)) lo = mid;
		else hi = mid;
	}
	if(func(hi)) return hi + 1;
	if(func(lo)) return lo + 1;
	return lo;
}

int main() {
	// Find floor(sqrt(n))
	for (int i = 0; i < 30000; ++i) {
		int sqrt_n = binary_search(0, i, [&](int mid) {
			return mid * mid <= i;
		}) - 1;

		assert(sqrt_n == (int)sqrt(i));
	}
	return 0;
}