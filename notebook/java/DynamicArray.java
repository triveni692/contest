package modules;

import java.util.*;

/**
 * Created by triveni on 26/9/17.
 */
public class DynamicArray<E> {
	private int size = 0;
	private Random rnd = new Random();
	private node head = null;
	private E lastRemoved = null;


	public DynamicArray() {}
	public DynamicArray(int n, E val) {head = init(n, 0, 0, Collections.nCopies(n, val)); size = n;}
	public DynamicArray(int n, List<E> vals) {head = init(n, 0, 0, vals); size = n;}
	public DynamicArray(int n, E [] vals) {head = init(n, 0, 0, Arrays.asList(vals)); size = n;}
	private DynamicArray(node root, int sz) {size = sz; head = root; lastRemoved = null;}

	public void clear(){size = 0; head = null;}
	public int size() {return size; }

	/**
	 * Add element anywhere in the array in O(log n)
	 * @param idxInModifiedArray 0-based index in the modified array.
	 * @param val
	 * @throws ArrayIndexOutOfBoundsException
	 */
	public void add(int idxInModifiedArray, E val) throws ArrayIndexOutOfBoundsException{
		if (idxInModifiedArray > size || idxInModifiedArray < 0) throw new ArrayIndexOutOfBoundsException();
		head = insert(head, idxInModifiedArray, new node(val, rnd.nextInt()));
		size += 1;
		return;
	}

	/**
	 * remove any element from the array in O(log n)
	 * @param idx 0-based index of the element to be removed
	 * @return the element that will be removed
	 * @throws ArrayIndexOutOfBoundsException
	 */
	public E remove(int idx) throws ArrayIndexOutOfBoundsException {
		if (!validIndex(idx)) throw new ArrayIndexOutOfBoundsException();
		head = erase(head, idx);
		size -= 1;
		return lastRemoved;
	}
	public E get(int idx) throws ArrayIndexOutOfBoundsException {
		if(!validIndex(idx)) throw new ArrayIndexOutOfBoundsException();
		return find(head, idx).val;
	}
	public void set(int idx, E val) throws ArrayIndexOutOfBoundsException {
		if (!validIndex(idx)) throw new ArrayIndexOutOfBoundsException();
		node nd = find(head, idx);
		nd.val = val;
	}

	/**
	 * append an element at the end of the array
	 * @param val value to be appended
	 */
	public void push(E val) {
		add(size, val);
	}

	/**
	 * Cut the array into two parts and destroy the current array
	 * @param len length of the first part to be cut. len > 0.
	 * @return pair of two array, first one will have {@code len} elements
	 * @throws ArrayIndexOutOfBoundsException
	 */
	public Pair<DynamicArray<E>, DynamicArray<E>> cut(int len) throws ArrayIndexOutOfBoundsException{
		if (!validIndex(len-1)) throw new ArrayIndexOutOfBoundsException();
		Pair<node, node> p = split(head, len);
		int len2 = size - len;
		clear();
		return new Pair<>(new DynamicArray<E>(p.X, len), new DynamicArray<E>(p.Y, len2));
	}

	/**
	 * join another array to the existing array at the end but the exiting ones destroy
	 * @param other the other dynamic array to be joined with the existing one.
	 * @return the new array created by joining the two
	 */
	public DynamicArray<E> join(DynamicArray<E> other) {
		head = merge(head, other.head);
		size += other.size;
		other.clear();
		return this;
	}

	private node init(int n, int binaryOffset, int heapOffset, List<E> vals) {
		if (n <= 0) return null;
		node root = new node(vals.get(binaryOffset + n/2), heapOffset + n);
		root.left = init(n/2, binaryOffset, heapOffset, vals);
		root.right = init(n - n/2 - 1, binaryOffset + n/2 + 1, heapOffset + n/2, vals);
		root.merge();
		return root;
	}

	private Pair<node, node> split(node root, int splitVal) {
		if (root == null) return new Pair<>(null, null);
		int v = size(root.left) + 1;
		Pair<node, node> p = null;
		if (v > splitVal) {
			p = split(root.left, splitVal);
			root.left = p.Y;
			root.merge();
			p.Y = root;
		}
		else {
			p = split(root.right, splitVal - v);
			root.right = p.X;
			root.merge();
			p.X = root;
		}
		return p;
	}
	private node merge(node a, node b) {
		if (a == null) return b;
		if (b == null) return a;
		if (a.pr > b.pr) {
			a.right = merge(a.right, b);
			a.merge();
			return a;
		}else {
			b.left = merge(a, b.left);
			b.merge();
			return b;
		}
	}
	private node insert(node root, int idx, node nd) {
		if (root == null) return nd;
		int valHere = 1 + size(root.left);
		if (root.pr < nd.pr) {
			Pair<node, node> p = split(root, idx);
			nd.left = p.X;
			nd.right = p.Y;
			root = nd;
		}
		else if (valHere > idx) {
			root.left = insert(root.left, idx, nd);
		}
		else {
			root.right = insert(root.right, idx - valHere, nd);
		}
		root.merge();
		return root;
	}
	private node erase(node root, int idx) {
		if (root == null) return null;
		int valHere = size(root.left);
		if (valHere == idx) {
			lastRemoved = root.val;
			return merge(root.left, root.right);
		}
		else if (idx < valHere) root.left = erase(root.left, idx);
		else root.right = erase(root.right, idx - valHere - 1);
		root.merge();
		return root;
	}
	private node find(node root, int idx) {
		int valHere = size(root.left);
		if (valHere == idx) return root;
		else if (valHere > idx) return find(root.left, idx);
		else return find(root.right, idx - valHere - 1);
	}

	private int size(node nd) {return nd == null ? 0 : nd.size;}
	private boolean validIndex(int idx) {return idx >= 0 && idx < size; }

	private class node {
		int pr;
		int size;
		node left, right;
		E val;
		node (E value, int priority) {
			this.pr = priority;
			this.val = value;
		}
		private void merge(){
			this.size = 1 + size(left) + size(right);
		}
	}
}

