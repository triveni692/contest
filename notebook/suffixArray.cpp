#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

// 0-based suffix array. O(nlogn) using radix sort
class SuffixArray {
	int n, *r=0, *s=0, *c=0, *ts=0;
	void init(const char str[]) {
		r = new int[n]; c = new int [max(256,n)]; // can be optimized
		s = new int[n]; ts = new int [n];
		memset(c, 0, 1<<10);
		for (int i = 0; i < n; ++i) c[str[i]]++;
		for (int i = 1; i < 256; ++i) c[i] += c[i-1];
		for (int i = 0; i < n; ++i) s[--c[str[i]]] = i;
		for (int i = 0; i < n; ++i) {
			r[s[i]] = (i && str[s[i]] == str[s[i-1]]) ? r[s[i-1]]: i;
		}
	}
	void build_sa(const char str[]) {
		init(str);
		for (int k = 1; k < n; k <<= 1) {
			memset(c, 0, n<<2);
			for (int i = n - k, j = 0; i < n; ++i) ts[j++] = i;
			for (int i = 0, j = k; i < n; ++i) {
				if (s[i] >= k) ts[j++] = s[i] - k;
				c[r[i]]++;
			}
			
			for (int i = 1; i < n; ++i) c[i] += c[i-1];
			for (int i = n-1; i >= 0; --i) {
				s[--c[r[ts[i]]]] = ts[i];
			}
			
			for (int i = 0; i < n; ++i) c[i] = s[i]+k < n ? r[s[i]+k]: -1;
			bool was_ok = false;
			for (int i = 0, p = 0; i < n; ++i) {
				bool ok = (i && c[i] == c[i-1] && p == r[s[i]]);
				p = r[s[i]]; r[s[i]] = (ok ? r[s[i-1]] : i);
				was_ok |= ok;
			}
			if(!was_ok) break;
		}
		delete [] c, delete [] ts;
	}

public:
	SuffixArray(string & str) { n = str.length(); build_sa(str.data()); }
	SuffixArray(const char str[], int n) : n(n) { build_sa(str); }
	
	~SuffixArray() {
		delete [] r, delete [] s;
	}

	// O(n): lcp[i] = lcp(s[i], s[i-1]). lcp[0] is not defined
	void get_lcp(const char str[], int lcp []) {
		assert(s && "suffix array not built!");
		lcp[0] = 0;
		for(int i = 0, k = 0; i < n; ++i, k && --k) if(r[i] < n-1){
			int j = s[r[i]+1];
			while(i+k < n && j+k < n && str[i+k] == str[j+k])
				++k;
			lcp[r[i]+1] = k;
		}
	}
	void get_lcp(string & str, vector<int> & lcp) {
		lcp.resize(n);
		get_lcp(str.data(), lcp.data());
	}
	vector<int> get_lcp(string & str) {
		vector<int> lcp(n);
		get_lcp(str.data(), lcp.data());
		return lcp;
	}

	// one can use this one like:
	// vector<int> v(n); sa.get_sa(v.data());
	void get_sa(int a[]) {
		memcpy(a, s, n<<2);
	}
	void get_sa(vector<int> & v) {
		v.resize(n);
		get_sa(v.data());
	}
	vector<int> get_sa() {
		return vector<int> (s, s + n);
	}
};

int main()
{
	int n = 1e6;
	string s; 
	for (int i = 0; i < n; ++i) s += char(rand()%26+'a');
	cin >> s; n = s.length();
	vector<int> sa, lcp;
	SuffixArray sf(s);
	sf.get_sa(sa);
	sf.get_lcp(s, lcp);
	for (int i = 0; i < n; ++i) {
		cout << sa[i] << " ";
	}
	cout <<"\n---\n";
	cerr << "- ";
	for(int i = 1; i < n; ++i){
		cerr << lcp[i] << " ";
	}
	cout <<"\n";
	for(int i = 0; i < n; ++i){
		cerr << s.substr(sa[i]) << "\n";
	}
	return 0;
}

