#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

// AKNOWLEDGEMENT : Most of the code below has been taken from ACRush's (Tiancheng Lou) solution to problem : http://www.codechef.com/MARCH14/problems/SSTORY/
// This class takes as argument a char array of length N. Example : str[] = "banana", suffixArray mySA(str, N).
// As soon as constructor is called, it build the suffix array, SA and POS array. To get the suffix array call : getSuffixArray(int A[]).
// The indices will be 1 based , meaning array should be acessed from A[1] to A[N] (not from 0 to N-1). To get POS array, call : getPosArray(int A[]).
// This also returns 1 based indices, same convention as getSuffixArray method. To get LCP, call method getLCPArray(int A[]).
// LCP array should be acessed from 1 based index as well, i.e., a[1] to A[N]. 
// A[i] contains longest common prefix of suffixes starting at index i-1 and index i (indices are 1 based).
// No care has been taken while constructing this class. Care must be taken while calling any of the functions.
// Given string is first copied in the class so string can be modified outside the class safely.

/*               NOTE : ALWAYS PASS ARRAYS WITH SIZE ATLEAST (N + 1), because indices are filled from index 1.                  */

class suffixArray
{
public:
	suffixArray(char ss[], int n){
		N = n;
		POS = (int *)calloc(N+1, sizeof(int));
		SA  = (int *)calloc(N+1, sizeof(int));
		LCP = (int *)calloc(N+1, sizeof(int));
		str = (char *)calloc(N+1, sizeof(char));
		for(int i=0;i<=n;++i) str[i] = ss[i];
		SuffixArray(N, str, SA, POS);
	}
	~suffixArray(){
		free(POS);
		free(SA);
		free(LCP);
		free(str);
	}

	void getSuffixArray(int a[]){
		for(int i=1;i<=N;++i)
			a[i] = SA[i-1]+1;
		return ;
	}

	void getPosArray(int a[]){
		for(int i=1;i<=N;++i)
			a[i] = POS[i-1]+1;
		return ;
	}

	void getLCPArray(int a[]){
		buildLCP();
		for(int i=2;i<=N;++i)
			a[i] = LCP[i-2];
		a[1] = 0;
		return ;
	}

private:
	int * POS, * SA, *LCP , N;
	char * str;

	inline bool leq(int a1,int a2,int b1,int b2)
	{
		return (a1<b1 || a1==b1 && a2<=b2);
	}
	inline bool leq(int a1,int a2,int a3,int b1,int b2,int b3)
	{
		return (a1<b1 || a1==b1 && leq(a2,a3,b2,b3)); 
	}
	void RadixPass(int *a,int *b,int *r,int n,int K) 
	{
		int *cnt=new int[K+1];
		memset(cnt,0,(K+1)*sizeof(int));
		for (int i=0;i<n;i++) cnt[r[a[i]]]++;
		for (int i=1;i<=K;i++) cnt[i]+=cnt[i-1];
		for (int i=n-1;i>=0;i--) b[--cnt[r[a[i]]]]=a[i];
		delete[] cnt;
	}
	void GetSuffixArray(int *s,int *SA,int n,int K)
	{
		if (n<=8)
		{
			bool c[8][8];
			for (int i=n-1;i>=0;i--) for (int j=i+1;j<n;j++)
			{
				if (s[i]==s[j]) c[i][j]=(j+1<n && c[i+1][j+1]);
				else c[i][j]=(s[i]<s[j]);
				c[j][i]=!c[i][j];
			}
			for (int i=0;i<n;i++) SA[i]=i;
			for (int i=0;i<n;i++) for (int j=i+1;j<n;j++) if (c[SA[j]][SA[i]]) swap(SA[i],SA[j]);
			return;
		}
		int n0=(n+2)/3,n1=(n+1)/3,n2=n/3,n02=n0+n2;
		int *s12=new int[n02+3];
		s12[n02]=s12[n02+1]=s12[n02+2]=0; 
		int *SA12=new int[n02+3];
		SA12[n02]=SA12[n02+1]=SA12[n02+2]=0;
		int *s0=new int[n0];
		int *SA0=new int[n0];
		for (int i=0,j=0;i<n+(n0-n1);i++) if (i%3!=0) s12[j++]=i;
		RadixPass(s12,SA12,s+2,n02,K);
		RadixPass(SA12,s12,s+1,n02,K);  
		RadixPass(s12,SA12,s,n02,K);
		int name=0,c0=-1,c1=-1,c2=-1;
		for (int i=0;i<n02;i++)
		{
			if (s[SA12[i]]!=c0 || s[SA12[i]+1]!=c1 || s[SA12[i]+2]!=c2)
				name++,c0=s[SA12[i]],c1=s[SA12[i]+1],c2=s[SA12[i]+2];
			if (SA12[i]%3==1)
				s12[SA12[i]/3]=name;
			else 
				s12[SA12[i]/3+n0]=name;
		}
		if (name<n02)
		{
			GetSuffixArray(s12,SA12,n02,name);
			for (int i=0;i<n02;i++) s12[SA12[i]]=i+1;
		}
		else
		{
			for (int i=0;i<n02;i++) SA12[s12[i]-1]=i; 
		}
		for (int i=0,j=0;i<n02;i++) if (SA12[i]<n0) s0[j++]=3*SA12[i];
		RadixPass(s0,SA0,s,n0,K);
		for (int p=0,t=n0-n1,k=0;k<n;k++)
		{
			int i=(SA12[t]<n0?SA12[t]*3+1:(SA12[t]-n0)*3+2);
			int j=SA0[p];
			if (SA12[t]<n0?leq(s[i],s12[SA12[t]+n0],s[j],s12[j/3]):
				           leq(s[i],s[i+1],s12[SA12[t]-n0+1],s[j],s[j+1],s12[j/3+n0]))
			{
				SA[k]=i;
				if ((++t)==n02) for (k++;p<n0;p++,k++) SA[k]=SA0[p];
			}
			else
			{ 
				SA[k]=j;
				if ((++p)==n0) for (k++;t<n02;t++,k++) SA[k]=(SA12[t]<n0?SA12[t]*3+1:(SA12[t]-n0)*3+2); 
			}
		}
		delete[] s12;
		delete[] SA12;
		delete[] s0;
		delete[] SA0;
	}
	void SuffixArray(int n,char *s,int *SA,int *Rank)
	{
		int *A=new int[n+3];
		for (int i=0;i<n;i++) A[i]=(int)((unsigned char)s[i]);
		A[n]=A[n+1]=A[n+2]=0;
		GetSuffixArray(A,SA,n,256);
		for (int i=0;i<n;i++) Rank[SA[i]]=i;
	}
	void SuffixArray(int n,int *s,int *SA,int *Rank)
	{
		int maxs=0;
		for (int i=0;i<n;i++) if (s[i]>maxs) maxs=s[i];
		maxs++;
		int *A=new int[n+3];
		A[n]=A[n+1]=A[n+2]=0;
		if (maxs<(1<<16))
		{
			for (int i=0;i<n;i++) A[i]=s[i];
			GetSuffixArray(A,SA,n,maxs);
		}
		else
		{
			int *C=new int[1<<16];
			int *t=new int[n];
			memset(C,0,(1<<16)*sizeof(int));
			for (int i=0;i<n;i++) C[s[i]&65535]++;
			for (int i=1;i<(1<<16);i++) C[i]+=C[i-1];
			for (int i=n-1;i>=0;i--) A[--C[s[i]&65535]]=i;
			memset(C,0,(1<<16)*sizeof(int));
			for (int i=0;i<n;i++) C[s[i]>>16]++;
			for (int i=1;i<(1<<16);i++) C[i]+=C[i-1];
			for (int i=n-1;i>=0;i--) t[--C[s[A[i]]>>16]]=A[i];
			for (int d=0,i=0;i<n;i++) A[t[i]]=(i>0 && s[t[i]]!=s[t[i-1]])?(++d):d;
			GetSuffixArray(A,SA,n,n);
			delete[] C;
			delete[] t;
		}
		for (int i=0;i<n;i++) Rank[SA[i]]=i;
	}
	void PrepareD(int *s,int *SA,int *Rank,int *D,int n)
	{
		for (int k=0,i=0;i<n;i++)
			if (Rank[i]==n-1)
				D[n-1]=k=0;
			else
			{
				if (k>0) k--;
				int t=SA[Rank[i]+1];
				for (;i+k<n && i+k<n && s[i+k]==s[t+k];k++);
				D[Rank[i]]=k;
			}
	}
	void PrepareD(char *s,int *SA,int *Rank,int *D,int n)
	{
		for (int k=0,i=0;i<n;i++)
			if (Rank[i]==n-1)
				D[n-1]=k=0;
			else
			{
				if (k>0) k--;
				int t=SA[Rank[i]+1];
				for (;i+k<n && i+k<n && s[i+k]==s[t+k];k++);
				D[Rank[i]]=k;
			}
	}

	void buildLCP(){
		int k = 0;
		for(int i=0;i<N;++i) if(POS[i] != N-1){
			// POS[i] actually gives the 0 based successor of current suffix in the suffix array, hence 
			// SA[POS[i]] - 1 should give the actual index of the successor in the actual string str
			for(int j = SA[POS[i]+1] ; str[j + k] == str[i + k] ; )
				k = k + 1;
			LCP[POS[i]] = k;
			if(k > 0) k = k - 1;
		}
		POS[N-1] = 0; // for no other reason than safety :D
		return ;
	}

};

int SA[1000001], POS[1000001], LCP[1000001];
LL distinctSubStr[1000001];
char str[1000001], ss[100];

int main()
{
	int N;
	LL l, r;
	scanf("%s",str);
	N = strlen(str);

	suffixArray sa(str, N);
	sa.getSuffixArray(SA);
	sa.getPosArray(POS);
	sa.getLCPArray(LCP);

	for(int i = 1; i <= N; ++i) cerr << SA[i] << " "; cerr << "\n";
	for(int i = 1; i <= N; ++i) cerr << LCP[i] << " "; cerr << "\n";
	for(int i = 1; i <= N; ++i) cerr << POS[i] << " "; cerr << "\n";

	return 0;
}

