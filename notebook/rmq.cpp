// This class takes as an argument an array of size N. 0-based index for the given array. 
// Example : A[] = {1,2,3,4,6}, call the constructor by (A, 5)
// Method findMin(l, r) return the minimum element in the range [l...r] in O(1) time after preprocessing time of O(N log N).
// l and r are 1-based index. Memory used is O(NlogN) as well.
// this class doesn't checks the validity of the inputs. Be careful why using this class

#include <bits/stdc++.h>

using namespace std;

class RMQ
{
public:
	RMQ(int A[], int n){
		RMQ::init();
		H = ceil(log2(n));
		N = n;
		M.resize(N+1);
		for(int i=0;i<=N;++i)
			M[i].resize(H+1);

		for(int i=0;i<=H;++i){
			int jump = ((1<<i)>>1);
			for(int j=1;j<=N;++j)
			{
				if(i == 0) M[j][i] = A[j-1];
				else if(j+jump <= N) M[j][i] = min(M[j][i-1], M[j+jump][i-1]);
				else  M[j][i] = M[j][i-1];
			}
		}
	}

	~RMQ(){
		for(int i=0;i<=N;++i) M[i].clear();
		M.clear();
	}

	int findMin(int l, int r){
		if(l>r) return 0;
		int d = A[r-l+1];
		r = r - (1<<d) + 1;
		return min(M[l][d], M[r][d]);
	}

private:
	int H, N;
	vector<vector<int> > M;
	int A[2000001];

	void init(){
		memset(A, -1, sizeof A);
		for(int i=0; (1<<i)<=2000000; ++i){
			A[(1<<i)] = i;
		}
		for(int i=1;i<=2000000;++i){
			if(A[i] != -1) continue;
			A[i] = A[i-1];
		}
		return;
	}
	
};

int main()
{
	int a[100];
	int n;
	cin >> n;
	for(int i = 0; i < n; ++i) cin >> a[i];
	RMQ rmq(a, n);
	while(1){
		int l, r;
		cin >> l >> r;
		assert(1 <= l && l <= n);
		assert(1 <= r && r <= n);
		assert(l <= r);
		cout << rmq.findMin(l, r) << endl;
	}
	return 0;
}
