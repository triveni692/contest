#include <bits/stdc++.h>

using namespace std;

typedef int fType;
typedef int cType;

const fType INF = (int)1e9;

struct edge {
    int u, v;
    fType flow; // it contains remaining flow capacity in the edge
    cType cost;
    edge() {}
    edge(int u, int v, fType f, cType c) : u(u), v(v), flow(f), cost(c) {}
};

struct MinCostMaxFlow {
    int N;
    vector < vector <int> > G;
    vector <edge> E;
    int numEdges;
    vector <int> found, dad;
    vector <cType> dist;

    MinCostMaxFlow(int N): 
     N(N), G(N), found(N), dist(N), dad(N), numEdges(0) {}
  
    void addEdge(int from, int to, fType capacity, cType cost) {
        // cerr << "from : " << from << " to : " << to << " capacity : " << capacity << " cost : " << cost << "\n";
        G[from].push_back(numEdges++);
        E.push_back(edge(from, to, capacity, cost));
        G[to].push_back(numEdges++);
        E.push_back(edge(to, from, 0, cType(-1) * cost));
    }
  
    bool spfa(int s, int t) {
        fill(dad.begin(), dad.end(), -1);
        fill(dist.begin(), dist.end(), INF);
        fill(found.begin(), found.end(), 0);
        queue<int> Q;
        dist[s] = 0;
        Q.push(s);
        found[s] = true;
        
        while(!Q.empty()) {
          int u = Q.front(); Q.pop();
          // cerr<<"u : "<<u<<"\n";
          if(u == t) continue;
          for (int i =0; i < G[u].size(); ++i) {
            edge &pres = E[G[u][i]];
            int v = pres.v;
            if(pres.flow <= 0) continue;
            if(dist[u] + pres.cost < dist[v]){
                dad[v] = G[u][i];
                dist[v] = dist[u] + pres.cost;
                if(!found[v]) Q.push(v), found[v] = true;
            }
          }
          found[u] = false;
        }
        return (dad[t] != -1);
    }
 
    fType dfs(int s,int t) {
        fType flow = INF;
        for(int i = dad[t]; i != -1; i = dad[E[i].u]) {
            if(E[i].flow < flow) flow = E[i].flow;
        }
        for(int i = dad[t]; i != -1; i = dad[E[i].u]) {
            E[i].flow -= flow;
            E[i^1].flow += flow;
        }
        return flow;
    }

    pair <fType, cType> getMaxFlow(int s, int t) {
        // cerr<<" s: "<<s<<" t : "<<t<<"\n";
        fType totflow = 0;
        cType totcost = 0;
        while(spfa(s,t)) {
            fType amt = dfs(s,t);
            // cerr<<" amt : "<<amt<<"\n";
            totflow += amt;
            totcost += dist[t] * (cType)amt;
        }
        return make_pair(totflow, totcost);
    }
};

const int MAX_N = 25;

int friday[MAX_N][MAX_N];
int saturday[MAX_N][MAX_N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    srand(time(NULL));
    clock_t start = clock();
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> friday[i][j];

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> saturday[i][j];

    vector <int> masks;
    for (int mask = (1 << n) - 1; mask >= 0; --mask)
        if (__builtin_popcount(mask) == n / 2)
            masks.push_back(mask);
    for (int iter = 0; iter < 10; ++iter)
        random_shuffle(masks.begin(), masks.end());
    int ans = 0;
    for (int mask : masks) {
        if (clock() < 1.9 * CLOCKS_PER_SEC)  {
            MinCostMaxFlow mcmf(n + n + 2);
            int src = n + n;
            int snk = src + 1;
            for (int i = 0; i < n; ++i)
                mcmf.addEdge(src, i, 1, 0);
            for (int i = 0; i < n; ++i)
                mcmf.addEdge(n + i, snk, 1, 0);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (mask >> j & 1) {
                        mcmf.addEdge(i, n + j, 1, -friday[i][j]);
                    } else {
                        mcmf.addEdge(i, n + j, 1, -saturday[i][j]);
                    }
                }
            }
            pair <fType, cType> flow = mcmf.getMaxFlow(src, snk);
            ans = max(ans, -flow.second);
        }
    }
    cout << ans << "\n";

    return 0;
}

