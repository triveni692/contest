/*
Problem: Codechef QTREE7

user  : triveni
date  : 18/01/2016
time  : 15:44:43
*/

#include<iostream>
#include<cstdio>
#include<string>
#include<cassert>
#include<vector>
#include<stack>
#include<algorithm>
#include<queue>

using namespace std;

#define      pii               std::pair<int,int>
#define      vi                std::vector<int>
#define      mp(a,b)           make_pair(a,b)
#define      pb(a)             push_back(a)
#define      each(it,s)        for(auto it = s.begin(); it != s.end(); ++it)
#define      rep(i, n)         for(int i = 0; i < (n); ++i)
#define      fill(a)           memset(a, 0, sizeof (a))
#define      sortA(v)          sort(v.begin(), v.end())
#define      sortD(v)          sort(v.begin(), v.end(), greater<auto>())
#define      X                 first
#define      Y                 second

typedef int ll;

struct segtree{
	int tree[262145];
	int n;
	segtree(int n_, int val){
		n = n_;
		init(1, 1, n, val);
	}

	void init(int rt, int l, int r, int val){
		if(l == r) {tree[rt] = val; return ;}
		int mid = (l+r) / 2, lft = 2*rt, rgt = lft + 1;
		init(lft, l, mid, val);
		init(rgt, mid+1, r, val);
		tree[rt] = tree[lft] + tree[rgt];
	}

	void update(int id){
		return update(1, 1, n, id);
	}

	void update(int rt, int l, int r, int id){
		if(l==r) {
			tree[rt] ^= 1;
			return ;
		}
		int mid = (l+r) / 2, lft = 2*rt, rgt = lft + 1;
		if(mid >= id) update(lft, l, mid, id);
		else update(rgt, mid+1, r, id);
		tree[rt] = tree[lft] + tree[rgt];
	}

	int getSum(int rt, int l, int r, int i, int j){
		if(i<=l && r<=j) return tree[rt];
		int mid = (l+r) / 2, lft = 2*rt, rgt = lft + 1;
		int ans = 0;
		if(i <= mid) ans += getSum(lft, l, mid, i, j);
		if(mid+1 <= j) ans += getSum(rgt, mid+1, r, i, j);
		return ans;
	}

	int getLeft(int id){
		int tsum = 0;
		if(id < n) tsum = getSum(1, 1, n, id+1, n);
		if(tree[1] == id + tsum) return 0;
		return getIndex(1, 1, n, id, tsum);
	}

	int getIndex(int rt, int l, int r, int id, int sum){
		if(l == r) return l;
		int mid = (l+r) / 2, lft = 2*rt, rgt = lft + 1;
		if(id > r){
			if(tree[rgt] == r-mid) return getIndex(lft, l, mid, id, 0);
			else return getIndex(rgt, mid+1, r, id, 0);
		}
		if(id <= mid) return getIndex(lft, l, mid, id, sum - tree[rgt]);
		if(tree[rgt] == sum + id-mid) return getIndex(lft, l, mid, id, 0);
		return getIndex(rgt, mid+1, r, id, sum);
	}

};

ll bit[2][100100];

void bit_update(ll a[], int id, int val, int n){
	while(id <= n) {
		a[id] += val;
		id += (id & -id);
	}
}

void update(ll a[], int l, int r, int val, int n){
	bit_update(a, l, val, n);
	bit_update(a, r+1, -val, n);
}

ll query(ll a[], int id){
	ll sum = 0;
	while(id > 0){
		sum += a[id];
		id -= (id & -id);
	}
	return sum;
}

vector<int> tmp_graph[100100];
vector<int> graph[100100];
int col[100100];

int depth = 0;

int chainSt[100100];
int chainLen[100100];
int whereChain[100100];
int whichChain[100100];

vector<int> baseArray;

int sz[100100];
int par[100100];

/*void make_tree(int u){
  depth += 1;
  if(depth > 95555) assert(0);
  col[u] = 1;
  sz[u] = 1;
  for(int c : tmp_graph[u]) if(!col[c]) {
  graph[u].push_back(c);
  par[c] = u;
  make_tree(c);
  sz[u] += sz[c];
  }
  tmp_graph[u].clear();
  depth -= 1;
  }*/

void make_tree(int u){
	queue<int> Q;
	Q.push(u);
	col[u] = 1;
	while(!Q.empty()){
		u = Q.front();
		Q.pop();
		for(int c : tmp_graph[u]) if(!col[c]) {
			graph[u].push_back(c);
			par[c] = u;
			col[c] = 1;
			Q.push(c);
		}
	}
}
bool done[100100];
void cal_subsize(int u){
	stack <int> st;
	st.push(u);
	while(!st.empty()){
		u = st.top();
		if(!done[u]) {
			done[u] = 1;
			for(int c : graph[u]) if(!done[c]) st.push(c);
			continue;
		}
		st.pop();
		sz[u] = 1;
		for(int c : graph[u]) sz[u] += sz[c];
	}
}

int cnum=0;
void HLD(int u, int clen){
	whichChain[u] = cnum;
	whereChain[u] = clen;
	baseArray.push_back(u);
	clen += 1;

	int id = -1, mx = -1;
	for(int i = 0; i < graph[u].size(); ++i) {
		int c = graph[u][i];
		if(sz[c] > mx) mx = sz[c], id = i;
	}

	if(id == -1){
		chainLen[cnum] = clen;
		cnum += 1;
		return ;
	}

	HLD(graph[u][id], clen);

	for(int i = 0; i < graph[u].size(); ++i) if(i != id){
		chainSt[cnum] = baseArray.size();
		HLD(graph[u][i], 0);
	}

}

struct st
{
	int u;
	int clen;
	int pr;
};

void HLD2(int us, int clens)
{
	st init = {us, clens, 0};
	stack<st> mys;
	mys.push(init);
	while(!mys.empty())
	{
		st now=mys.top();
		mys.pop();
		if(now.pr==0)
		{
			int u=now.u;
			int clen=now.clen;
			whichChain[u] = cnum;
			whereChain[u] = clen;
			baseArray.push_back(u);
			clen += 1;
			int id = -1, mx = -1;
			for(int i = 0; i < graph[u].size(); ++i) {
				int c = graph[u][i];
				if(sz[c] > mx) mx = sz[c], id = i;
			}
			if(id == -1){
				chainLen[cnum] = clen;
				cnum += 1;
			}
			else
			{
				for(int i = 0; i < graph[u].size(); ++i) if(i != id){
					mys.push({graph[u][i], 0, 0});
					mys.push({u, clen, 2});
				}
				mys.push({graph[u][id], clen, 0});
			}
		}
		else
		{
			chainSt[cnum] = baseArray.size();
		}
	}
}


void test(){
	segtree sg(7, 1);
	while(1){
		int t, id;
		cin >> t >> id;
		if(t == 0) { // update
			sg.update(id);
		}
		else { // query
			cout << sg.getLeft(id) << "\n";
		}
	}
}

int main()
{
	// test();
	int n, Q;
	scanf("%d", &n);
	rep(i, n-1){
		int u, v;
		scanf("%d %d", &u, &v);
		--u, --v;
		tmp_graph[u].push_back(v);
		tmp_graph[v].push_back(u);
	}
	make_tree(0);
	cal_subsize(0);
	HLD2(0, 0);

	segtree sgW(n, 0);
	segtree sgB(n, 1);

	for(int i = 0; i < n; ++i){
		int u = baseArray[i];
		int s = sz[u];
		update(bit[1], i+1, i+1, s, n);
	}

	scanf("%d", &Q);
	while(Q--){
		int type, u;
		scanf("%d %d", &type, &u);
		u -= 1;
		int c = whichChain[u];
		int id = whereChain[u] + chainSt[c] + 1;

		if(type == 0){ // query
			bool cl = col[u];
			while(1){
				int idx = whereChain[u] + chainSt[whichChain[u]] + 1;
				int xx = 0;
				if(cl == 1) xx = sgB.getLeft(idx);
				else xx = sgW.getLeft(idx);
				int l = idx - xx;
				if(whereChain[u] + 1 <= l) {
					u = chainSt[whichChain[u]];
					u = baseArray[u];
					if(col[par[u]] != cl) break;
					else u = par[u];
				}
				else {
					u = idx - l;
					u = baseArray[u];
					break;
				}
				if(u == 0) break;
			}
			id = whereChain[u] + chainSt[whichChain[u]] + 1;
			int ans = query(bit[col[u]], id);
			printf("%d\n",ans);
		}
		else if(type == 1){
			if(col[u] == 1){ // black
				update(bit[1], id, id, -1, n);
				update(bit[0], id, id, +1, n);
				if(u == 0) {goto GG;}

				int v = par[u];
				int id1 = whereChain[v] + chainSt[whichChain[v]] + 1;
				if(col[v] == 1){
					update(bit[0], id1, id1, query(bit[0], id), n);
					int up = query(bit[1], id) + 1; up *= -1;
					while(1){
						int idx = whereChain[v] + chainSt[whichChain[v]] + 1;
						int xx = sgB.getLeft(idx);
						int l = idx - xx;
						if(whereChain[v] + 1 <= l) {
							update(bit[1], idx - whereChain[v], idx, up, n);
						}
						else {
							update(bit[1], idx - l + 1, idx, up, n);
							v = baseArray[idx-l];
							break;
						}
						v = chainSt[whichChain[v]];
						v = baseArray[v];
						if(whichChain[v] == 0) break;
						v = par[v];
					}
					if(v != 0) {
						v = par[v];
						int upid = chainSt[whichChain[v]] + whereChain[v] + 1;
						update(bit[1], upid, upid, up, n);
					}
				}
				else {
					int up = query(bit[0], id);
					update(bit[1], id1, id1, -query(bit[1], id) - 1, n);
					while(1){
						int idx = whereChain[v] + chainSt[whichChain[v]] + 1;
						int xx = sgW.getLeft(idx);
						int l = idx - xx;
						if(whereChain[v] + 1 <= l) {
							update(bit[0], idx - whereChain[v], idx, up, n);
						}
						else {
							update(bit[0], idx - l + 1, idx, up, n);
							v = baseArray[idx-l];
							break;
						}
						v = chainSt[whichChain[v]];
						v = baseArray[v];
						if(whichChain[v] == 0) break;
						v = par[v];
					}
					if(v != 0) {
						v = par[v];
						int upid = chainSt[whichChain[v]] + whereChain[v] + 1;
						update(bit[0], upid, upid, up, n);
					}
				}
			}
			else {
				update(bit[1], id, id, +1, n);
				update(bit[0], id, id, -1, n);

				if(u == 0) {goto GG;}
				int v = par[u];
				int id1 = whereChain[v] + chainSt[whichChain[v]] + 1;

				if(col[v] == 0){
					update(bit[1], id1, id1, query(bit[1], id), n);
					int up = query(bit[0], id) + 1; up *= -1;

					while(1){
						int idx = whereChain[v] + chainSt[whichChain[v]] + 1;
						int xx = sgW.getLeft(idx);
						int l = idx - xx;
						if(whereChain[v] + 1 <= l) {
							update(bit[0], idx - whereChain[v], idx, up, n);
						}
						else {
							update(bit[0], idx - l + 1, idx, up, n);
							v = baseArray[idx-l];
							break;
						}
						v = chainSt[whichChain[v]];
						v = baseArray[v];
						if(whichChain[v] == 0) break;
						v = par[v];
					}
					if(v != 0) {
						v = par[v];
						int upid = chainSt[whichChain[v]] + whereChain[v] + 1;
						update(bit[0], upid, upid, up, n);
					}
				}
				else {
					int up = query(bit[1], id);
					update(bit[0], id1, id1, -query(bit[0], id) - 1, n);

					while(1){
						int idx = whereChain[v] + chainSt[whichChain[v]] + 1;
						int xx = sgB.getLeft(idx);
						int l = idx - xx;
						if(whereChain[v] + 1 <= l) {
							update(bit[1], idx - whereChain[v], idx, up, n);
						}
						else {
							update(bit[1], idx - l + 1, idx, up, n);
							v = baseArray[idx-l];
							break;
						}
						v = chainSt[whichChain[v]];
						v = baseArray[v];
						if(whichChain[v] == 0) break;
						v = par[v];
					}
					if(v != 0) {
						v = par[v];
						int upid = chainSt[whichChain[v]] + whereChain[v] + 1;
						update(bit[1], upid, upid, up, n);
					}
				}
			}
GG:
			col[u] ^= 1;
			sgB.update(id);
			sgW.update(id);
		}
	}
	return 0;
}

