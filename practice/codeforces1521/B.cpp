#include <bits/stdc++.h>

using namespace std;

int a[100100];

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) scanf("%d", a + i);
		int idx = min_element(a, a + n) - a;
		printf("%d\n", n-1);
		for (int i = 0; i < n; ++i) if (i != idx) {
			printf("%d %d %d %d\n", idx+1, i+1, a[idx], a[idx] + abs(i - idx));
		}
	}
	return 0;
}
