#include <bits/stdc++.h>

using namespace std;

/*
	1. Dinic's Implimentation of Max-Flow. typeDefine `fType` = int/long long. 
	2. Usage : 
		a) initiate with number of nodes
		b) all the nodes are 0 based
		c) use the method `addedge` to add edges to the network
	3. Method `getFlow()` gives the maximum flow from `src` to `snk`
	4. To get the actual flow values, iterate over `vector<edge>edges`,
	   for any edge with e.cap > 0, get the actual flow value as e.flow.
	5. Time Complexity : Complexity O(n^2*m).

	Code tested on SPOJ : FASTFLOW 
*/
typedef int fType;

struct edge{
	int from, to;
	fType flow, cap;
};

struct DinicFlow{
	vector <edge> edges;
	vector <int> dist, now;
	vector <vector <int> > adj;
	int n, src, snk;
	const int inf = 1e9+7;

	DinicFlow() {}

	DinicFlow(int nn) {
		n = nn;
		dist.resize(n);
		now.resize(n);
		adj.resize(n);
	}

	void addEdge(int from, int to, int cap){
		adj[from].push_back(edges.size());
		edges.push_back({from, to, 0, cap});
		adj[to].push_back(edges.size());
		edges.push_back({to, from, 0, 0});
	}

	bool bfs(){
		for(int i = 0; i < n; ++i) {
			dist[i] = inf; 
			now[i] = (int)adj[i].size() - 1;
		}
		queue <int> Q;
		Q.push(src), dist[src] = 0;
		while(!Q.empty()){
			int v = Q.front(); Q.pop();
			for(int w : adj[v]) {
				edge & e = edges[w];
				if(dist[e.to] > dist[v] + 1 && e.cap - e.flow > 0){
					dist[e.to] = dist[v] + 1;
					Q.push(e.to);
				}
			}
		}
		return dist[snk] != inf;
	}

	fType dfs(int u, fType flow){
		if(u == snk || !flow) return flow;
		for(int & w = now[u]; w >= 0; --w){
			edge & e = edges[adj[u][w]];
			if(dist[e.to] == dist[u] + 1 && e.cap > e.flow){
				fType fl = dfs(e.to, min(flow, e.cap - e.flow));
				if(fl > 0){
					e.flow += fl;
					edges[adj[u][w] ^ 1].flow -= fl;
					return fl;
				}
			}
		}
		return 0;
	}

	fType getFlow(int source, int sink){
		src = source, snk = sink;
		fType totFlow = 0;
		fType flowLimit = std::numeric_limits<fType>::max() >> 2;
		while(bfs()){
			while(fType f = dfs(src, flowLimit)){
				totFlow += f;
			}
		}
		return totFlow;
	}
};

int main()
{
	DinicFlow df;
	df.getFlow(0,0);
	return 0;
}

