#include <bits/stdc++.h>

using namespace std;

template<typename T>
class SparseTable {
private:
	int n, k;
	vector<vector<T> > data;
	function<bool(T,T)> cmp = [&](T x, T y) {return x < y; };
public:
	SparseTable() {}
	template<class Iterator>
	SparseTable(Iterator beg, Iterator end, function<bool(T, T)> func = nullptr) {
		n = end - beg;
		k = (31 - __builtin_clz(n));
		data.resize(k + 1, vector<T>(n));
		int i = 0;
		while(beg < end) {
			data[0][i++] = *(beg++);
		}

		if (func != nullptr) cmp = func;

		for (int j = 0; j < k; ++j) {
			for (int i = 0; i < n; ++i) {
				data[j + 1][i] = data[j][i];
				int nextIndex = i + (1 << j);
				if (nextIndex < n && cmp(data[j][nextIndex], data[j][i])) {
					data[j + 1][i] = data[j][nextIndex];
				}
			}
		}
	}
	T get_min(int l, int r) {
		assert(0 <= l && l <= r && r < n && "use 0-based index");
		int kk = (31 - __builtin_clz(r - l + 1));
		T ans = data[kk][l];
		int nextIndex = r - (1 << kk) + 1;
		if (cmp(data[kk][nextIndex], data[kk][l])) {
			ans = data[kk][nextIndex];
		}
		return ans;
	}
	~SparseTable() {
		for (auto & v: data) v.clear();
		data.clear();
	}
};
// using rmq = SparseTable<int>;

int main() {
	int n;
	cin >> n;
	vector<string> v(n);
	for (int i = 0; i < n; ++i) {
		cin >> v[i];
	}
	SparseTable<string> s(v.begin(), v.end(), [&](string a, string b){return a > b;});
	while(1) {
		int l, r; cin >> l >> r;
		--l, --r;
		cout << s.get_min(l, r) << "\n";
	}
	return 0;
}