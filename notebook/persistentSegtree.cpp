// This class takes as an argument an array of size N. 0-based index for the given array. 
// Example : A[] = {1,2,3,4,6}, call the constructor by (A, 5)
// It assumes that given elements will be unique and lie in the range [1, N].
// Method KthMinimum(l, r, k) return the kth minimum number in the given sub-array [l...r] in O(log N) time. l, r, k all are 1-based.
// Method RankingOfK(l, r, k) return the rank of k in the sub-array [l...r] in O(log N) time. l, r, k are all 1-based.
// This class does not cares about the validity of the query. It assumes that given query is valid. So be careful while using it.

#include <bits/stdc++.h>

using namespace std;

class PersistentSegmentTree
{
public:
	PersistentSegmentTree(int A[], int n){
		N = n;
		head = (node **)calloc(N+1, sizeof(node *));
		head[0] = create(1, N);
		for(int i = 0; i<N; ++i){
			head[i+1] = insert(1, N, A[i], head[i]);
		}
	}
	int KthMinimum(int l, int r, int k){
		return KthMinimum(head[l-1], head[r], k, 1, N);
	}

	int RankingOfK(int l, int r, int k){
		return RankingOfK(head[l-1], head[r], k, 1, N);
	}

	~PersistentSegmentTree(){
		free(head);
	}

private:
	struct node{
		int val;
		node * left;
		node * right;
	};
	int N;
	node ** head;

	node * make_node(int val){
		node * nd = (node *)calloc(1, sizeof(node));
		nd -> val = val;
		nd -> left = NULL;
		nd -> right = NULL;
		return nd;
	}

	node * create(int l, int r){
		node * nd = make_node(0);
		int m = (l+r) >> 1;
		if(l != r){
			nd -> left = create(l, m);
			nd -> right = create(m+1,r);
		}
		return nd;
	}

	node * insert(int l, int r, int v, node * n){
		node * nd = make_node(0);
		if(l == r){
			assert(l == v);
			nd -> val += 1;
			return nd;
		}
		int m = (l+r) >> 1;
		if(v <= m) nd -> left = insert(l, m, v, n->left), nd->right = n->right;
		else nd -> right = insert(m+1, r, v, n->right), nd->left = n->left;
		(nd -> val) = (nd -> left) -> val + (nd -> right) -> val;
		return nd;
	}

	int KthMinimum(node * l, node * r, int k, int i, int j){
		if(l->left == NULL and l->right == NULL){
			assert(r->left == r->right and r->left == NULL);
			assert(k==1 and i==j);
			return i;
		}
		int m = (i+j)>>1;
		int val = (r->left->val) - (l->left->val);
		if(val >= k) return KthMinimum(l->left, r->left, k, i, m);
		else return KthMinimum(l->right, r->right, k-val, m+1, j);
	}

	int RankingOfK(node * l, node * r, int k, int i, int j){
		if(l->left == NULL and l->right == NULL){
			assert(r->left == r->right and r->left == NULL);
			assert(k==i and i==j);
			return 1;
		}
		int m = (i+j)>>1;
		int val = (r->left->val) - (l->left->val);
		if(k <= m) return RankingOfK(l->left, r->left, k, i, m);
		else return RankingOfK(l->right, r->right, k, m+1, j) + val;
	}

};

int main()
{
	int n;
	int a[100];
	cin >> n;
	for(int i = 0; i < n; ++i)
		cin >> a[i];
	
	PersistentSegmentTree pst(a, n);
	int l, r, k;
	cin >> l >> r >> k;
	
	assert(1 <= l && l <= n);
	assert(1 <= r && r <= n);
	assert(l <= r);
	assert(1 <= k && k <= n);

	cout << pst.KthMinimum(l, r, k) << endl;

	cin >> l >> r >> k;
	
	assert(1 <= l && l <= n);
	assert(1 <= r && r <= n);
	assert(l <= r);
	
	cout << pst.RankingOfK(l, r, k) << endl;
	return 0;
}
