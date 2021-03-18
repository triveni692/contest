#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100000;

vector<int> tree[MAXN + 1];

bool vis[MAXN + 1]; // if a node has been chosen as a centroid
int par[MAXN + 1]; // Parent in the centroid tree
int sz[MAXN + 1]; // size of subtree

void cent_dfs(int u, int p = -1) {
	// Used for initialization of the subtree sizes
	sz[u] = 1;
	for (int c: tree[u]) if (c != p && !vis[c]) {
		cent_dfs(c, u);
		sz[u] += sz[c];
	}
}

int get_center(int u, int s, int p = -1) {
	// s: size of the tree under consideration
	for(int c: tree[u]) if (c != p && !vis[c]) {
		if (sz[c] * 2 > s) return get_center(c, s, u);
	}
	return u;
}

void centroid_decompose(int u, int p = -1) {
	cent_dfs(u);
	int cent = get_center(u, sz[u]);
	par[cent] = p;

	// 'cent' node has been chosen as a centroid and
	// should now be removed from the original tree.
	// vis[cent] marks the same, i.e., removed from the tree
	vis[cent] = true;

	for (int c: tree[cent]) if (!vis[c]) {
		centroid_decompose(c, cent);
	}
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

	centroid_decompose(1);

	for (int i = 1; i <= n; ++i) {
		cout << "Parent of node " << i << " in the centroid tree is " << par[i] << "\n";
	}

	return 0;
}