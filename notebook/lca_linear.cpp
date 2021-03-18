/*
	Do O(nlogn) pre-processing and answer LCA in O(1)

	We first do a euler tour/walk of the tree. Then lca(u, v)
	is given by the node in the euler list which is located 
	most close to the root (smallest level from root). So,
	this is equivalent to answer minimum query in the range
	EulerArray[pos_in_euler[u] .... pos_in_euler[v]].

	Note: the size of the euler list will be 2*n - 1. 
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100000;

vector<int> tree[MAXN + 1];

bool vis[MAXN + 1];
int level[MAXN + 1];
int pos_in_euler[MAXN + 1];
int sparse_table[22][2 * MAXN + 2];
int log_2[2 * MAXN + 2];

void dfs(int u, int & t) {
	vis[u] = true;
	pos_in_euler[u] = t;
	sparse_table[0][t++] = u; // sparse_table[0][] is basically the euler list
	for (int c: tree[u]) if (!vis[c]) {
		level[c] = level[u] + 1;
		dfs(c, t);
		sparse_table[0][t++] = u;
	}
}

void build_sparse_table(int n) {
	// pre-processing O(nlogn) time. 
	for (int i = 0; (1 << i) < n; ++i) log_2[1<<i] = i;
	for (int i = 1; i < n; ++i) if (!log_2[i]) log_2[i] = log_2[i-1];

	for (int i = 0; i < 21; ++i) {
		for (int j = 0, j1 = (1<<i); j < n; ++j, ++j1) {
			sparse_table[i + 1][j] = sparse_table[i][j];
			if (j1 < n && level[sparse_table[i][j1]] < level[sparse_table[i][j]]) {
				sparse_table[i + 1][j] = sparse_table[i][j1];
			} 
		}
	}
}

int get_lca(int u, int v) {
	// O(1) per query
	if (pos_in_euler[u] > pos_in_euler[v]) swap(u, v);
	int idx = log_2[pos_in_euler[v] - pos_in_euler[u] + 1];
	const int & v1 = sparse_table[idx][pos_in_euler[u]];
	const int & v2 = sparse_table[idx][pos_in_euler[v] - (1 << idx) + 1];
	return level[v1] < level[v2] ? v1 : v2;
}

int get_dist(int u, int v) {
	// O(1) per query
	int lca = get_lca(u, v);
	return level[u] + level[v] - 2 * level[lca];
}

int main() {
	int n;
	cin >> n;
	for (int i = 1; i < n; ++i) {
		// nodes are 1 based.
		int u, v;
		cin >> u >> v;
		tree[u].push_back(v);
		tree[v].push_back(u);
	}

	int t = 0;
	dfs(1, t); assert(t == 2 * n - 1);
	build_sparse_table(t);

	int Q;
	cin >> Q;
	while(Q--) {
		int u, v;
		cin >> u >> v;
		cout << "Lca(" << u <<", "<<v <<") = " << get_lca(u, v) << "\n";
	}

	return 0;
}