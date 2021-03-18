#include <bits/stdc++.h>

using namespace std;

/*
1.	This class impliments Edmond-Karp Maximum Flow algorithm in a directed graph
2.	Nodes are 0 based, hence the edges must be 0 based
3.	Edges can be added using the AddEdge method which takes 3 argummnets:
		(from, to, capacity) in order
4.	Initialize the class with N, denoting the number of nodes
5.	'getMaxFlow' method returns the maximum flow in the network which takes 2 arguments:
		(source, destination) in order 
6.	'getFlowValues' method returns the actual flow across the edges
7.	Complexity : O(N * M ^ 2) but practically very fast
*/

// tested
class EdmondKarp
{
public:
	EdmondKarp(int n)
	{
		N 	= n;
		INF = 2000000000;
		AdjacencyMatrix.resize(N);
		flowMatrix.resize(N);
		List.resize(N);
		for(int i = 0; i < N; ++i)
		{
			AdjacencyMatrix[i].resize(N,0);
			flowMatrix[i].resize(N,0);
		}

		return ;
	}

	~EdmondKarp()
	{
		for(int i = 0; i < N; ++i)
		{
			AdjacencyMatrix[i].clear();
			flowMatrix[i].clear();
			List[i].clear();
		}

		AdjacencyMatrix.clear();
		flowMatrix.clear();
		List.clear();

		return;
	}

	void AddEdge(int from, int to, int cap)
	{
		AdjacencyMatrix[from][to] = cap;
		List[from].push_back(to);
		List[to].push_back(from);
	}

	int getMaxFlow(int s, int d)
	{
		initFlowMatrix();
		int maxFlow = 0, pathCapacity;
		while(pathCapacity = augmentingPath(s,d))
		{
			maxFlow += pathCapacity;
		}
		return maxFlow;
	}

	// Note : this method must be called just after the getMaxFlow method
	vector<vector<int> > getFlowValues()
	{
		vector<vector<int> > ans(N);
		for(int i=0;i<N;++i)
		{
			ans[i].resize(N);
			for(int j=0;j<N;++j)
			{
				if(AdjacencyMatrix[i][j] > 0)
				{
					ans[i][j] = flowMatrix[j][i];
					assert(ans[i][j] <= AdjacencyMatrix[i][j]);
				}
			}
		}
		return ans;
	}

private:
	int N, INF;
	vector<vector<int> > AdjacencyMatrix;
	vector<vector<int> > flowMatrix;
	vector<vector<int> > List;
	void initFlowMatrix()
	{
		for(int i=0;i<N;++i)
			for(int j=0;j<N;++j)
				flowMatrix[i][j] = AdjacencyMatrix[i][j];
		return ;
	}
	int augmentingPath(int s, int d)
	{
		vector<int> from(N, -1);
		vector<bool> vis(N, 0);
		queue<int> Q;
		Q.push(s);
		vis[s] = 1;
		while(!Q.empty())
		{
			int v = Q.front();
			Q.pop();
			for(int i=0;i<List[v].size();++i)
			{
				int c = List[v][i];
				if(vis[c] || flowMatrix[v][c] == 0) continue;
				from[c] = v;
				if(c == d)
				{
					while(!Q.empty()) Q.pop();
					break;
				}
				Q.push(c);
				vis[c] = true;
			}
		}
		int where = d, flow = INF;
		while(from[where] != -1)
		{
			int prev = from[where];
			flow = min(flow, flowMatrix[prev][where]);
			where = prev;
		}
		where = d;
		while(from[where] != -1)
		{
			int prev = from[where];
			flowMatrix[prev][where] -= flow;
			flowMatrix[where][prev] += flow;
			where = prev;
		}
		if(flow == INF) flow = 0;
		from.clear(); vis.clear();
		return flow;
	}
};

int main()
{
	int N, M;
	cin >> N >> M;
	EdmondKarp E(N);
	for(int i=0;i<M;++i)
	{
		int x, y, w;
		cin >> x >> y >> w;
		E.AddEdge(x, y, w);
	}
	
	while(1){
		cerr << "\n";
		int s, d;
		cin >> s >> d;
		cout << E.getMaxFlow(s,d) << "\n";
		vector<vector<int> > tmp = E.getFlowValues();
		for(int i=0;i<tmp.size();++i, putchar(10))
			for(int j=0;j<tmp[i].size();++j)
				cout << tmp[i][j] << " ";
	}
	
	return 0;
}
