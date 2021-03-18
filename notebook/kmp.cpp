#include <bits/stdc++.h>

using namespace std;

vector<int> getPiTable(string& str){
	int n = str.length();
	vector<int> T(n+1, 0);
	T[0] = -1;
	T[1] = 0;
	int j = 0;
	for(int i=2;i<=n;++i){
		if(str[i-1] == str[j]) T[i] = ++j;
		else if(j > 0) --i, j = T[j];
		else T[i] = j;
	}
	return T;
}

vector<int> KMP(string& text, string& pattern){
	int N = text.length();
	int n = pattern.length();
	vector<int> T = getPiTable(pattern);
	vector<int> matches;
	for(int i=0, j=0;i<N;++i){
		if(pattern[j] != text[i] and j > 0) j = T[j], i-= 1;
		else if(pattern[j] == text[i]){
			j += 1;
			if(j == n) matches.push_back(i + 1 - n);
		}
	}
	return matches;
}

int main()
{
	string text, pattern;
	cin >> text;
	vector<int> ans;
	while(1){
		cin >> pattern;
		ans = KMP(text, pattern);
		for(int i=0;i<ans.size();++i){
			cout << ans[i] << " ";
		}
		cout << endl;
	}
	return 0;
}

