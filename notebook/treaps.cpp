/*
Problem: https://www.codechef.com/MARCH18A/problems/GCDCNT

  Beautiful Codes are MUCH better than 'Shorter' ones !
user  : triveni
date  : 23/02/2018
time  : 23:26:00
*/
#include <bits/stdc++.h>

using namespace std;

#define      pii               std::pair<int,int>
#define      vi                std::vector<int>
#define      sz(v)             (int)(v.size())
#define      mp(a,b)           make_pair(a,b)
#define      pb(a)             push_back(a)
#define      each(it,s)        for(auto it = s.begin(); it != s.end(); ++it)
#define      rep(i, n)         for(int i = 0; i < (n); ++i)
#define      all(v)            v.begin(), v.end()
#define      scan(n)           scanf("%d", &n)
#define      scan2(n, m)       scanf("%d%d", &n, &m)
#define      pin(n)            printf("%d\n",n)
#define      pis(n)            printf("%d ",n)
#define      pll(n)            printf("%lld\n", n)
#define      X                 first
#define      Y                 second

typedef long long ll;
ll mod = 1000000007;

inline int pow_(ll a, int n, int p=mod){
int r=1;while(n){if(n&1)r=r*a%p;n>>=1;a=a*a%p;}return r;}
inline int inv_(int a) {return pow_(a, mod-2, mod);}
inline int add(int a, int b){a+=b;if(a>=mod)a-=mod;return a;}
inline void adds(int& a, int b){a+=b;if(a>=mod)a-=mod;}
inline int mul(int a, int b){return a*1ll*b%mod;}
inline void muls(int& a, int b){a=a*1ll*b%mod;}
inline int sub(int a, int b){a-=b;if(a<0)a+=mod;return a;}

template <typename T>
struct order_set {
	struct node {
		int priority;
		size_t subSize;
		T val;
		node * left, * right;
	};
	typedef node * Treap;

	Treap head = NULL;

	inline size_t size() {
		return getSize(head);
	}
	
	inline size_t getSize(Treap t) {
		if (t != NULL) return t -> subSize;
		return 0;
	}

	inline void merge(Treap root) {
		root->subSize = getSize(root->right) + getSize(root->left) + 1;
	}

	inline Treap newNode(T val, int pr) {
		Treap t = (Treap) malloc(sizeof(node));
		t -> val = val;
		t -> priority = pr;
		t -> subSize = 1;
		t -> left = t -> right = NULL;
		return t;
	}

	Treap find(Treap root, T val) {
		if(root == NULL || root -> val == val) return root;
		if(root -> val > val) return find(root -> left, val);
		return find(root -> right, val);
	}

	pair<Treap, Treap> split(Treap root, T val) {
		if (root == NULL) return make_pair((Treap)NULL, (Treap)NULL);
		if (root->val > val) {
			auto p = split(root->left, val);
			root->left = p.Y;
			merge(root);
			return make_pair(p.X, root);
		}
		else {
			auto p = split(root->right, val);
			root->right = p.X;
			merge(root);
			return make_pair(root, p.Y);
		}
	}

	Treap merge(Treap a, Treap b) {
		if (a == NULL) return b;
		if (b == NULL) return a;
		if (a -> priority > b -> priority) {
			a -> right = merge(a -> right, b);
			merge(a);
			return a;
		}
		else {
			b -> left = merge(a, b->left);
			merge(b);
			return b;
		}
	}

	Treap insert(Treap root, T val, int pr) {
		if (root == NULL) {
			root = newNode(val, pr);
			return root;
		}
		if (root -> priority < pr) {
			Treap newNd = find(root, val);
			if(!newNd) {
				newNd = newNode(val, pr);
				pair<Treap, Treap> p = split(root, val);
				newNd -> left = p.X;
				newNd -> right = p.Y;
				merge(newNd);
			}
			return newNd;
		}
		if (root -> val < val) {
			root -> right = insert(root -> right, val, pr);
		}
		else root -> left = insert(root -> left, val, pr);
		merge(root);
		return root;
	}

	Treap remove(Treap root, T val) {
		if (root == NULL) return root;
		if (root -> val == val) return merge(root->left, root->right);
		else if (root -> val > val) root->left = remove(root->left, val);
		else root -> right = remove(root->right, val);
		merge(root);
		return root;
	}

	int countLeq(Treap root, T val) {
		if(!root) return 0;
		if(root->val > val) return countLeq(root->left, val);
		return getSize(root->left) + 1 + countLeq(root->right, val);
	}

	inline void insert(T val) {
		head = insert(head, val, rand());
	}
	inline void erase(T val) {
		head = remove(head, val);
	}
	inline int countLeq(T val) {
		return countLeq(head, val);
	}
};

vector<int> divs[100100];
order_set<int> idx[100100];
int inp[100100];
int mu[100100];

void init() {
	for (int i = 1; i < 100100; ++i) {
		for (int j = i; j < 100100; j += i){
			divs[j].pb(i);
		}
	}
	mu[1] = 1;
	for (int i = 2; i < 100100; ++i) {
		if(sz(divs[i]) == 2) mu[i] = -1;
		else {
			int p = divs[i][1]; // smallest prime divisor
			if((i / p) % p == 0) mu[i] = 0;
			else mu[i] = mu[i/p] * -1;
		}
	}
}
int count(order_set<int>& s, int l, int r) {
	int c = s.countLeq(r);
	c -= s.countLeq(l-1);
	return c;
}

int main()
{
	init();
	int n, q;
	scan(n);
	rep(i, n) {
		scan(inp[i]);
		for (int d : divs[inp[i]]) idx[d].insert(i);
	}
	scan(q);
	while(q--) {
		int t, l, r;
		scan(t);
		scan2(l, r);
		--l;
		if (t == 1) {
			for (int d : divs[inp[l]]) idx[d].erase(l);
			for (int d : divs[r]) idx[d].insert(l);
			inp[l] = r;
		}
		else {
			--r;
			int g; scan(g);
			int ans = 0;
			for (int d : divs[g]) if(mu[d]) {
				ans += mu[d] * count(idx[d], l, r);
			}
			pin(ans);
		}
	}
	return 0;
}

