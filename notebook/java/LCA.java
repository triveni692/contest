package modules;

import java.util.Collections;
import java.util.HashMap;
import java.util.List;

/**
 * This class works completely with 0-based indexing. Tree nodes are numbered from 0 through N-1.
 *
 * Created on 12/7/17.
 * @author triveni
 */
public class LCA {
	private List<List<Integer>> adjList;
	private int rootNode, treeSize, parHeight;
	private int [][] par;
	private int [] level;
	private HashMap<Integer, Integer> log2Map;

	public void lca(List<List<Integer>> adjList, int rootNode) {
		this.adjList = Collections.unmodifiableList(adjList);
		this.rootNode = rootNode;
		init();
	}

	public int getLCA(int u, int v) {
		if (u < 0 || v < 0 || u >= treeSize || v >= treeSize) return -1;
		if (level[u] > level[v]) return getLCA(v, u);
		int diff = level[v] - level[u];
		while (diff > 0) {
			int p = (diff & -diff);
			v = par[v][log2Map.get(p)];
			diff -= p;
		}
		if (u == v) return  u;
		for (int i = parHeight-1; i >= 0; --i) {
			if (par[u][i] != par[v][i]) {
				u = par[u][i];
				v = par[v][i];
			}
		}
		return par[u][0];
	}

	/**
	 * @param u
	 * @param atHeight
	 * @return ancestor of u at height 2^atHeight from node u
	 */
	public int getParent(int u, int atHeight) {
		atHeight = Math.min(atHeight, parHeight - 1);
		return par[u][atHeight];
	}

	public int getLevel(int u) {
		return level[u];
	}

	public int getDistance(int u, int v) {
		int l = getLCA(u, v);
		return  level[u] + level[v] - 2 * level[l];
	}

	private void init() {
		treeSize = adjList.size();
		log2Map = new HashMap<Integer, Integer>();
		parHeight = 0; log2Map.put(1, 0);
		while ((1 << parHeight) < treeSize ) {
			parHeight += 1;
			log2Map.put((1<<parHeight), parHeight);
		}
		parHeight = Math.max(parHeight, 1);

		if(par == null || par.length != treeSize) {
			par = new int[treeSize][parHeight];
			level = new int[treeSize];
		}
		level[rootNode] = 0;
		dfs(rootNode, rootNode);
	}

	private void dfs(int r, int p) {
		par[r][0] = p;
		for (int i = 1; i < parHeight; ++i) {
			par[r][i] = par[par[r][i-1]][i-1];
		}
		if(adjList.get(r) != null) for (int c : adjList.get(r)) if (c != p) {
			level[c] = level[r] + 1;
			dfs(c, r);
		}
	}
}

