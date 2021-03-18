package modules;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * This class works completely with 0-based index. Suppose the tree provided has N nodes. Then they
 * should be numbered from 0 through N-1. Certain attempt has been made to check valid argument for
 * each methods, however, methods should be called with only valid arguments. First method to call
 * after creating an instance of HLD is  'hld'. Check each method for more description.
 *
 * Created on 12/7/17.
 *
 * @author triveni
 */

public class HLD {
	private List<List<Integer> > adjList = null;
	private int treeSize, rootNode, pathCnt, tmpVisCnt;
	private int [] whichPath;
	private int [] subSize;
	private int [] whereInPath;
	private int [] headOfPath;
	private int [] nodeAtIndex;
	// headOfPath[nd] : smallest index `idx` in the array among all element belonging to same chain
	// as `nd`.

	public void hld(List<List<Integer>> adjList, int rootNode) {
		this.adjList = Collections.unmodifiableList(adjList);
		this.rootNode = rootNode;
		init();
	}

	/** @return 0-based chain number to which `node` belongs */
	public int whichPath(int node) {
		return node < treeSize ? whichPath[node] : -1;
	}

	/** @return 0-based position of `node` in its chain */
	public int whereInPath(int node) {
		return node < treeSize ? whereInPath[node] : -1;
	}

	/** @return 0-based postion of `node` in the array */
	public int whereInArray(int node) {
		if (node >= treeSize) return -1;
		return whereInPath[node] + headOfPath[whichPath[node]];
	}

	/** @return node number which is located at index `index` in the array */
	public int nodeAtArray(int index) {
		if (index >= treeSize) return -1;
		return nodeAtIndex[index];
	}

	/**
	 * @return path disjoint ranges in the array for path from u -> anc in the tree. includeAncestor = true means, the path
	 * includes the `anc` as well, otherwise it does not.
	 */
	public List<Pair<Integer, Integer>> getPathToAncestor(int u, int anc, boolean includeAncestor, LCA myLca) {
		if(myLca == null || u >= treeSize || anc >= treeSize) return null;
		List<Pair<Integer, Integer>> ans = new ArrayList<Pair<Integer, Integer>>();
		while (u != rootNode && whichPath(u) != whichPath(anc)) {
			int pathHead = headOfPath[whichPath(u)];
			ans.add(new Pair<>(pathHead, pathHead + whereInPath[u]));
			u = myLca.getParent(nodeAtArray(pathHead), 0);
		}
		if (whichPath[u] != whichPath[anc]) anc = u;
		if (!includeAncestor && u == anc) return ans;
		int pathStart = whereInArray(anc);
		ans.add(new Pair<>(pathStart + (includeAncestor ? 0 : 1), whereInArray(u)));
		return ans;
	}

	/**@return  path disjoint ranges of the array for path u -> v in the tree */
	public List<Pair<Integer, Integer> > getPath(int u, int v, LCA myLca) {
		int l = myLca.getLCA(u, v);
		if (l == -1) return  null;
		List<Pair<Integer, Integer>> ans = getPathToAncestor(u, l, true, myLca);
		List<Pair<Integer, Integer>> ans1 = getPathToAncestor(v, l, false, myLca);
		if(ans != null && ans1 != null) {
			for (Pair<Integer, Integer> p : ans1) {
				ans.add(p);
			}
			return ans;
		}
		return null;
	}

	private void init() {
		treeSize = adjList.size();
		pathCnt = tmpVisCnt = 0;
		if(whichPath == null || treeSize != whichPath.length) {
			whichPath = new int [treeSize];
			whereInPath = new int [treeSize];
			headOfPath = new int [treeSize];
			subSize = new int [treeSize];
			nodeAtIndex = new int[treeSize];
		}
		computeSubtreeSize(rootNode, -1);
		headOfPath[pathCnt] = 0;
		hld(rootNode, -1, 0);
		for (int i = 0; i < treeSize; ++i) {
			nodeAtIndex[whereInArray(i)] = i;
		}
	}

	private void computeSubtreeSize(int r, int p) {
		subSize[r] = 1;
		if(adjList.get(r) != null) for (int c : adjList.get(r)) if (p != c) {
			computeSubtreeSize(c, r);
			subSize[r] += subSize[c];
		}
	}

	private void hld(int r, int p, int pathPos) {
		whichPath[r] = pathCnt;
		whereInPath[r] = pathPos;
		tmpVisCnt += 1;
		int heavyNode = -1, heavyEdgeWeight = 0;
		if(adjList.get(r) != null) for (int c : adjList.get(r)) if (c != p) {
			if (subSize[c] > heavyEdgeWeight) {
				heavyNode = c;
				heavyEdgeWeight = subSize[c];
			}
		}
		if(heavyNode == -1) {
			pathCnt += 1;
			return;
		}
		hld(heavyNode, r, pathPos + 1);
		for (int c : adjList.get(r)) if (c != p && c != heavyNode) {
			headOfPath[pathCnt] = tmpVisCnt;
			hld(c, r, 0);
		}
	}
}

