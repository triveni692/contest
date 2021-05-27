#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
	int T;
	cin >> T;
	while (T--) {
		ll a, b;
		cin >> a >> b;
		if (1 == b) cout << "NO\n";
		else {
			cout << "YES\n" << a*b << " " << a << " " << a*(b+1)  << "\n";
		}
	}
	return 0;
}
