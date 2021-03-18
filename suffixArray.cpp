#include <bits/stdc++.h>

using namespace std;

#define  X first
#define  Y second

typedef pair<int, int> pii;

// 0-based suffix array. O(n log^2n). Use radix sort to make O(nlogn)
void getSA(string& s, vector<int>& sa){
	int n = s.length();
	vector<int> rank(n);
	vector<int> rr(256, 0);
	for(char c : s) rr[c] = 1;
	for(int i = 1; i < 256; ++i) rr[i] += rr[i-1];
	for(int i = 0; i < n; ++i) rank[i] = rr[s[i]]-1;
	vector<pii> tmpv(n);
	for(int jump = 0; (1<<jump) < n; ++jump){
		for(int i = 0; i < n; ++i){
			int sec = ((i+(1<<jump)) < n ? rank[i+(1<<jump)] : -1);
			tmpv[i] = {rank[i], sec};
		}
		sort(tmpv.begin(), tmpv.end());
		int sz = unique(tmpv.begin(), tmpv.end()) - tmpv.begin();
		for(int i = 0; i < n; ++i){
			int sec = ((i+(1<<jump)) < n ? rank[i+(1<<jump)] : -1);
			pii p = {rank[i], sec};
			rank[i] = lower_bound(tmpv.begin(), tmpv.begin() + sz, p) - tmpv.begin();
		}
	}
	sa.resize(n);
	for(int i = 0; i < n; ++i) sa[rank[i]] = i;
	return ;
}

// lcp[i] = lcp(s[i], s[i-1]). lcp[0] is not defined, but set as zero.
// O(n)
void getLCP(string& s, vector<int>& sa, vector<int>& lcp){
	int n = s.length(), k = 0;
	lcp.resize(n, 0);
	vector<int> pos(n);
	for(int i = 0; i < n; ++i) pos[sa[i]] = i;
	for(int i = 0; i < n; ++i, k ? --k : k) if(pos[i] < n-1){
		int j = sa[pos[i]+1];
		while(i + k < n && j + k < n && s[i+k] == s[j+k])
			++k;
		lcp[pos[i]+1] = k;
	}
	return ;
}

int main()
{
	string s;
	cin >> s;
	int n = s.length();
	vector<int> sa, lcp;
	getSA(s, sa);
	getLCP(s, sa, lcp);
	for(int i = 0; i < n; ++i){
		cout << sa[i] << " ";
	}
	cout << "\n";
	cerr << "- ";
	for(int i = 1; i < n; ++i){
		cerr << lcp[i] << " ";
	}
	cerr << "\n";
	for(int i = 0; i < n; ++i){
		cerr << s.substr(sa[i]) << "\n";
	}
	return 0;
}

