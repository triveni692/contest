package modules;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by triveni on 23/7/17.
 */
public class DinicFlow {
	int n, src, snk;
	final int inf = 1000000007;
	int [] dist;
	int [] now;
	public ArrayList<Integer>[] adj;
	public ArrayList<DinicFlow.edge> edges;

	public DinicFlow(int n_) {
		n = n_;
		dist = new int[n];
		now = new int[n];
		adj = new ArrayList[n];
		for(int i = 0; i < n; ++i)
			adj[i] = new ArrayList<Integer> ();
		edges = new ArrayList<DinicFlow.edge>(2 * n);
	}

	public void addEdge(int from, int to, int cap) {
		adj[from].add(edges.size());
		edges.add(new DinicFlow.edge(from, to, 0, cap));
		adj[to].add(edges.size());
		edges.add(new DinicFlow.edge(to, from, 0, 0));
	}

	private boolean bfs() {
		for (int i = 0; i < n; ++i) {
			dist[i] = inf;
			now[i] = adj[i].size() - 1;
		}
		List Q = new ArrayList<Integer> (n);
		Q.add(src);
		dist[src] = 0;
		int sid = 0;
		while(sid < Q.size()) {
			int v = (int)Q.get(sid++);
			for(Object w_ : adj[v]) {
				int w = (int)w_;
				DinicFlow.edge e = edges.get(w);
				if(dist[e.to] > dist[v] + 1 && e.cap - e.flow > 0){
					dist[e.to] = dist[v] + 1;
					Q.add(e.to);
				}
			}
		}
//		for(int i = 0; i < n; ++i) System.out.print(dist[i] + " ");
//		System.out.println();
		Q.clear();
		return dist[snk] != inf;
	}

	private int dfs(int u, int flow) {
		if(u == snk || flow == 0)
			return flow;
		for(;now[u] >= 0; --now[u]) {
			DinicFlow.edge e = edges.get((int)adj[u].get(now[u]));
			if(dist[e.to] == dist[u] + 1 && e.cap > e.flow){
				int fl = dfs(e.to, Math.min(flow, e.cap - e.flow));
				if(fl > 0) {
					e.flow += fl;
					edges.get(((int)adj[u].get(now[u]))^1).flow -= fl;
					return fl;
				}
			}
		}
		return 0;
	}

	public int getMaxFlow(int source, int sink) {
		src = source;
		snk = sink;
		int totFlow = 0;
		while(bfs()) {
			while(true) {
				int f = dfs(src, inf);
				totFlow += f;
				if(f == 0)break;
			}
		}
		return totFlow;
	}

	public class edge{
		public int from, to;
		public int flow, cap;

		public edge(int from_, int to_, int flow_, int cap_){
			from = from_;
			to = to_;
			flow = flow_;
			cap = cap_;
		}
	}
}

