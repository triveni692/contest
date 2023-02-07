#include <bits/stdc++.h>

using namespace std;

class Segtree {
public:
	struct node {
		int val, carry;
		void merge(node & left, node & right, int l, int r) {
			val = std::max(left.val, right.val);
			carry = 0;
		}

		void split(node & left, node & right, int l, int r) {
			int m = (l + r) >> 1;
			left.update(carry, l, m);
			right.update(carry, m+1, r);
			carry = 0;
		}

		void update(int v, int l, int r) {
			val += v;
			carry += v;
		}

		string print(int u, int l, int r) {
			string res;
			stringstream ss(res);
			ss << "(" << u << ":" << l << "_" << r << "|";
			// ss << val << ", " << carry;
			// ss << val << "," << carry;
			ss << ")";
			return ss.str();
		}
	};
	int n, iDel; // segtree size will be '2*n-1'
	vector<node> tree;
	Segtree(int n, int one_based): n(n), iDel(one_based) { tree.resize(2*n+1); }

	template<typename T>
	static T max(const T & a, const T & b) {
		return std::max<T>(a, b);
	}
	template<typename T>
	static T min(const T & a, const T & b) {
		return std::min<T>(a, b);
	}
	template<typename T>
	static T sum(const T & a, const T & b) {
		return a + b;
	}

	inline void subtree_info(int u, int l, int r, int & lt, int & rt, int & m) {
		m = ((l + r) >> 1);
		lt = u + 1;
		rt = u + ((m - l + 1) << 1);
	}

	void build(int u, int l, int r, const function<void(node &, int, int)> & f) {
		if(l == r) return f ? f(tree[u], l, r) : void();
		int lt, rt, m; subtree_info(u, l, r, lt, rt, m);
		build(lt, l, m, f);
		build(rt, m + 1, r, f);
		tree[u].merge(tree[lt], tree[rt], l, r);
	}

	vector<string> print_segtree(int u, int l, int r) {
		string res = tree[u].print(u, l, r);
		int c_sz = res.length();
		if (l == r) {
			return {res};
		}
		int lt, rt, m; subtree_info(u, l, r, lt, rt, m);
		vector<string> left  = print_segtree(lt, l, m);
		vector<string> right = print_segtree(rt, m+1, r);
		int l_sz = left[0].size(), r_sz = right[0].size();
		res = string(l_sz, ' ') + res;
		res += string(r_sz, ' ');
		vector<string> final_ans(1);
		for (int i = 0; i < left.size(); ++i) {
			string r = left[i] + string(c_sz, ' ');
			if (i < right.size()) {
				r += right[i];
			} else {
				r += string(r_sz, ' ');
			}
			final_ans.push_back(r);
		}
		int i = l_sz; while (i > 0 && final_ans[1][i] == ' ') --i;
		int j = l_sz; while (j < final_ans[1].size() && final_ans[1][j] == ' ') ++j;
		int c1 = 0, c2 = 0;
		while (i < final_ans[1].size() && res[i] == ' ') ++i, ++c1;
		while (j >= 0 && res[j] == ' ') --j, c2++;
		if (c2 > c1) {
			int del = (c2 - c1) / 2;
			res = string(del, ' ') + res;
			while(del > 0) res.pop_back(), --del;
		}
		else if (c1 > c2) {
			int del = (c1 - c2) / 2;
			res += string(del, ' ');
			reverse(res.begin(), res.end());
			while(del > 0) res.pop_back(), --del;
			reverse(res.begin(), res.end());
		}
		final_ans[0] = res;
		return final_ans;
	}

	void print() {
		vector<string> res = print_segtree(0, 0 + iDel, n-1 + iDel);
		int n = (int)res.size() - 2;
		for (auto & s: res) {
			cout << s << "\n";
			for (int i = 0; i < n; ++i) putchar(10);
			n -= 1;
		}
	}

	void range_update(int u, int l, int r, int i, int j, const function<void(node &, int, int)>& f) {
		if (i <= l && r <= j) {
			f(tree[u], l, r);
			return;
		}
		int m, lt, rt; subtree_info(u, l, r, lt, rt, m);
		tree[u].split(tree[lt], tree[rt], l, r);
		if (i <= m) range_update(lt, l, m, i, j, f);
		if (m+1 <= j) range_update(rt, m+1, r, i, j, f);
		tree[u].merge(tree[lt], tree[rt], l, r);
	}
	
	template<typename T>
	T range_query(int u, int l, int r, int i, int j, const function<T(node&,int,int)>& ret, const function<T(const T&, const T&, int, int)>& merger) {
		if (i <= l && r <= j) {
			return ret(tree[u], l, r);
		}
		int lt, rt, m; subtree_info(u, l, r, lt, rt, m);
		tree[u].split(tree[lt], tree[rt], l, r);
		if (i <= m && m+1 <= j) {
			return merger(
				range_query(lt, l, m, i, j, ret, merger),
				range_query(rt, m+1, r, i, j, ret, merger),
				l, r
			);
		}
		if (i <= m) return range_query(lt, l, m, i, j, ret, merger);
		else return range_query(rt, m+1, r, i, j, ret, merger);
	}

	int right_search(int u, int l, int r, int i, const function<bool(const node&)> & f) {
		if (r < i || !f(tree[u])) return n + iDel;
		if (l == r) return l;
		int lt, rt, m; subtree_info(u, l, r, lt, rt, m);
		tree[u].split(tree[lt], tree[rt], l, r);
		int res = right_search(lt, l, m, i, f);
		if (res < n) return res;
		return right_search(rt, m+1, r, i, f);
	}

	int left_search(int u, int l, int r, int i, const function<bool(const node&)> & f) {
		if (i < l || !f(tree[u])) return -1 + iDel;
		if (l == r) return l;
		int lt, rt, m; subtree_info(u, l, r, lt, rt, m);
		tree[u].split(tree[lt], tree[rt], l, r);
		int res = left_search(rt, m+1, r, i, f);
		if (res >= 0) return res;
		return left_search(lt, l, m, i, f);
	}

	void build(const function<void(node &, int, int)>& f = nullptr) {
		build(0, iDel, n-1 + iDel, f);
	}
	void update(int i, const function<void(node &, int, int)>& f) {
		assert(f && "f cannot be nullptr");
		assert(iDel <= i && i < n + iDel);
		range_update(0, iDel, n-1 + iDel, i, i, f);
	}
	void update(int i, int j, const function<void(node &, int, int)>& f) {
		assert(iDel <= i && i < n + iDel);
		assert(iDel <= j && j < n + iDel && i <= j);
		range_update(0, iDel, n-1 + iDel, i, j, f);
	}

	template<typename T>
	T query(int i, int j, const function<T(node&,int,int)> &ret, const function<T(const T&, const T&, int, int)>& merger) {
		assert(iDel <= i && i < n + iDel);
		assert(iDel <= j && j < n + iDel && i <= j);
		return range_query(0, iDel, n-1 + iDel, i, j, ret, merger);
	}

	template<typename T>
	T query(int i, int j, const function<T(node&,int,int)>& ret, const function<T(const T&, const T&)>& merger) {
		assert(iDel <= i && i < n + iDel);
		assert(iDel <= j && j < n + iDel);
		function<T(const T&, const T&, int, int)> func = nullptr;
		if (merger) func = [&](const T& x, const T& y, int l, int r) -> T{
			return merger(x, y);
		};
		return range_query(0, iDel, n-1 + iDel, i, j, ret, func);
	}

	node query(int i) {
		assert(iDel <= i && i < n + iDel);
		return range_query<node>(0, iDel, n-1 + iDel, i, i, [&](node& nd, int l, int r){
			return nd;
		}, nullptr);
	}

	node query(int i, int j) {
		assert(iDel <= i && i < n+iDel);
		assert(iDel <= j && j < n+iDel && i <= j);
		return query<node>(i, j, [&](node& nd, int l, int r){
			return nd;
		}, [&](node a, node b, int l, int r) {
			a.merge(a, b, l, r);
			return a;
		});
	}

	int right_search(int i, const function<bool(const node&)> &f) {
		assert(iDel <= i && i < n + iDel);
		return right_search(0, iDel, n-1 + iDel, i, f);
	}

	int left_search(int i, const function<bool(const node&)> &f) {
		assert(iDel <= i && i < n + iDel);
		return left_search(0, iDel, n-1 + iDel, i, f);
	}
};
using node = Segtree::node;

int main() {
	int n; cin >> n;
	vector<int> v(n); 
	for(int i = 0; i < n; ++i) cin >> v[i];
	Segtree sg(n, 0);
	sg.build([&](node & nd, int l, int r) {
		nd.val = v[l];
		nd.carry = 0;
	});
	int q; cin >> q;
	sg.print();
	while(q--) {
		string tp; cin >> tp;
		if (tp == "U") {
			int x, y, val; cin >> x >> y >> val;
			sg.update(x-1, y-1, [&](node & nd, ...) {
				nd.val += val;
				nd.carry += val;
			});
		}
		else {
			int x, y; cin >> x >> y;
			int ans = 0;
			if (x != y) ans = sg.query<int>(x-1, y-1, [&](node & nd, ...) {
				return nd.val;
			}, Segtree::max<int>);
			else ans = sg.query(x-1).val;
			cout << ans << "\n";
		}
		sg.print();
	}
	return 0;
}