/*
  Kosaraju's O(n + m) time, two pass algo
  Tested on : spoj BOTTOM
*/
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 100000;

vector<int> List[MAXN];
vector<int> rev_List[MAXN];

void dfs(int u, int& cur_t, vector<bool>& vis, vector<int>& tm){
	vis[u] = 1;
	for(int c : rev_List[u]) if(!vis[c]) {
		dfs(c, cur_t, vis, tm);
	}
	tm[cur_t++] = u;
}

void dfs2(int u, int comp_num, vector<int>& v){
	v[u] = comp_num;
	for(int c : List[u]) if(v[c] == -1){
		dfs2(c, comp_num, v);
	}
	return ;
}

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	for(int i = 0; i < m; ++i){
		int u, v; // 0-based nodes. directed edge from u to v
		scanf("%d %d", &u, &v);
		List[u].push_back(v);
		rev_List[v].push_back(u);
	}
	vector<bool> vis(n, 0); 
	vector<int> tm(n, -1); // tm[t] = node which was last-visited at time = t
	vector<int> which_comp(n, -1); 
	// which_comp[i] = connected component number where node i belongs to
	// connected component number is  defined as the node with minimum index
	// in that particular connected component
	int cur_t = 0;
	for(int i = 0; i < n; ++i) if(!vis[i]) {
		dfs(i, cur_t, vis, tm);
	}
	for (int i = n-1; i >= 0; --i) if(which_comp[tm[i]] == -1){
		dfs2(tm[i], tm[i], which_comp);
	}
	for(int i = 0; i < n; ++i){
		cout << which_comp[i] << " ";
	}
	cout << "\n";
	return 0;
}

