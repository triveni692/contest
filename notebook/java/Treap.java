package modules;

import java.util.ArrayList;
import java.util.Random;

/**
 * Created by triveni on 23/9/17.
 */
public class Treap<K extends Comparable<K>, V> {
	private int size = 0;
	private BinaryNode rootNode = null;
	private Random random = new Random();

	public int size() {
		return size;
	}

	public boolean isEmpty() {
		return rootNode == null || size == 0;
	}

	public boolean containsKey(K key) {
		return find(rootNode, key) != null;
	}

	public V get(K key) {
		BinaryNode val = find(rootNode, key);
		return  val == null ? null : val.val;
	}

	public boolean put(K key, V val) {
		int lastN = size();
		rootNode = insert(rootNode, new BinaryNode(key, val));
		return size > lastN;
	}

	public boolean remove(K key) {
		int lastN = size();
		rootNode = delete(rootNode, key);
		return size < lastN;
	}

	public void clear() {
		size = 0;
		rootNode = null;
	}

	public ArrayList<K> keySet() {
		ArrayList<K> keys = new ArrayList<K>(size);
		getKeyArray(rootNode, keys);
		return keys;
	}

	private BinaryNode insert(BinaryNode root, BinaryNode newNode) {
		if (root == null || root.bstKey.equals(newNode.bstKey)) {
			if (root == null) {
				size += 1;
				root = newNode;
			}
			else root.val = newNode.val;
		}

		else if (newNode.heapKey > root.heapKey) {
			BinaryNode nd = find(root, newNode.bstKey);
			if (nd != null) {
				 nd.val = newNode.val;
			}
			else{
				Pair<BinaryNode, BinaryNode> treaps = split(root, newNode.bstKey);
				newNode.left = treaps.X;
				newNode.right = treaps.Y;
				root = newNode;
				size += 1;
			}
		}
		else {
			if (newNode.bstKey.compareTo(root.bstKey) > 0) {
				root.right = insert(root.right, newNode);
			}
			else root.left = insert(root.left, newNode);
		}
		return root;
	}

	private BinaryNode delete(BinaryNode root, K key) {
		if (root == null) return root;
		int c = root.bstKey.compareTo(key);
		if (c == 0) {
			size -= 1;
			return merge(root.left, root.right);
		}
		else if (c < 0) {
			root.right = delete(root.right, key);
		}
		else root.left = delete(root.left, key);
		return root;
	}
	private BinaryNode find(BinaryNode root, K key) {
		if (root == null) return null;
		int c = root.bstKey.compareTo(key);
		if (c == 0) return root;
		if (c < 0) return find(root.right, key);
		else return find(root.left, key);
	}

	private Pair<BinaryNode, BinaryNode> split(BinaryNode root, K key) {
		if (root == null) return new Pair<>(null, null);
		if (root.bstKey.compareTo(key) > 0) {
			Pair<BinaryNode, BinaryNode> p = split(root.left, key);
			root.left = p.Y;
			return new Pair<>(p.X, root);
		}
		else {
			Pair<BinaryNode, BinaryNode> p = split(root.right, key);
			root.right = p.X;
			return new Pair<>(root, p.Y);
		}
	}
	private BinaryNode merge(BinaryNode root1, BinaryNode root2) {
		if (root1 == null) return root2;
		if (root2 == null) return root1;
		if (root1.heapKey <= root2.heapKey) {
			root2.left = merge(root1, root2.left);
			return root2;
		}
		else{
			root1.right = merge(root1.right, root2);
			return root1;
		}
	}

	private void getKeyArray(BinaryNode root, ArrayList<K> ar) {
		if (root == null) return;
		getKeyArray(root.left, ar);
		ar.add(root.bstKey);
		getKeyArray(root.right, ar);
	}

	private class BinaryNode {
		int heapKey;
		K bstKey;
		V val;
		BinaryNode left;
		BinaryNode right;
		BinaryNode (K key, V val) {
			this.heapKey = random.nextInt();
			this.bstKey = key;
			this.val = val;
			this.left = null;
			this.right = null;
		}
	}
}

