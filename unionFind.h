#ifndef UNIONFIND_H_
#define UNIONFIND_H_

/*
 * Class Union Find:
 * This class stores N unique elements and provides the following functionalities:
 * Find(x) : Given an index x, returns the set to which element[i] belongs.
 * get(x) : Given an index x, returns the element[i].
 * Union(x, y): Given two indices, merges the sets to which they belong to 1 set.
 * This class is implemented using UpTrees (as arrays), Union by size and path compression
 * Therefore, Find and Union takes O(log* n)
 */

template<class T>
class UnionFind {
public:
	/* Initializes an empty UnionFind class with size n
	 * Time Complexity: O(n)
	 */
	explicit UnionFind(int n);
	/* Initializes a UnionFind class with the array data and size n
	 * Time Complexity: O(n)
	 */
	UnionFind(int n, T* data);
	/* Operator assignement
	 * Time Complexity: O(n)
	 */
	UnionFind& operator=(const UnionFind& uf);
	/* Given an index x, returns the set to which element[x] belongs.
	 * Using UpTrees and path compression
	 * @throw IndexOutOfBounds
	 * Time Complexity: O(log n)
	 */
	T& Find(int x);
	/* Given an index x, returns the element[x]
	 * Time Complexity: O(1)
	 */
	T& get(int x) const;
	/* Given two roots, merges the sets of given roots.
	 * Using UpTrees and union by size.
	 * @throw IndexOutOfBounds
	 * Time Complexity: O(1)
	 */
	void Union(int x, int y);
	/* class Destructor
	 * Time complexity: O(n)
	 */
	~UnionFind();

	class Node;
	/* Exception thrown by UnionFind */
	class IndexOutOfBounds: public std::exception {
	};
	class IllegalUnion: public std::exception {
	};
private:
	/* Recursive aux function that returns the index of the UpTree root
	 * to which element[x] belongs.
	 */
	int find(int x);

	int n;			// number of Nodes (elements)
	Node** elements;	// array of nodes
};

/* Class Node
 * Implements a Node in the UpTree containing the data of each Node,
 * the parent of the Node (-1 if Node is a root)
 * and the size of the UpTree if Node is a root (-1 otherwise).
 */
template<class T>
class UnionFind<T>::Node {
public:
	Node(int size, int parent, T& data) :
			size(size), parent(parent), data(data) {
	}
	Node(const Node& n) :
			size(n.size), parent(n.parent), data(n.data) {
	}
	friend class UnionFind;
private:
	int size;	// size of the Node, -1 if not root.
	int parent;	// parent of the Node, -1 if current node is a parent.
	T& data;
};

template<class T>
UnionFind<T>::UnionFind(int n) :
		n(n), elements(new Node*[n]) {
	for (int i = 0; i < n; i++) {
		elements[i] = NULL;
	}
}

template<class T>
UnionFind<T>::UnionFind(int n, T* data) :
		n(n), elements(new Node*[n]) {
	for (int i = 0; i < n; i++) {
		elements[i] = new Node(1, -1, data[i]);
	}
}

template<class T>
T& UnionFind<T>::get(int x) const {
	return elements[x]->data;
}

template<class T>
int UnionFind<T>::find(int x) {
	if (x < 0 || x >= n) {
		throw IndexOutOfBounds();
	}
	if (elements[x]->parent == -1) {
		return x;
	} else {
		return elements[x]->parent = find(elements[x]->parent);
	}
}

template<class T>
T& UnionFind<T>::Find(int x) {
	return elements[find(x)]->data;
}

template<class T>
void UnionFind<T>::Union(int x, int y) {
	if (x < 0 || x >= n || y < 0 || y >= n) {
		throw IndexOutOfBounds();
	}
	if (elements[x]->parent != -1 || elements[x]->parent != -1) {
		throw IllegalUnion();
	}
	if (x == y) { // x,y in same set
		return;
	}
	if (elements[x]->size > elements[y]->size) {
		elements[x]->size += elements[y]->size;
		elements[y]->size = -1;
		elements[y]->parent = x;
	} else {
		elements[y]->size += elements[x]->size;
		elements[x]->size = -1;
		elements[x]->parent = y;
	}
}

template<class T>
UnionFind<T>& UnionFind<T>::operator =(const UnionFind& uf) {
	if (this == &uf) {
		return *this;
	}
	Node** nodes = new Node*[n];
	try {
		for (int i = 0; i < uf.n; i++) {
			nodes[i] = new Node(*(uf.elements[i]));
		}
	} catch (...) {
		for (int i = 0; i < uf.n; i++) {
			if (nodes[i] != NULL) {
				delete nodes[i];
			}
		}
		delete[] nodes;
		throw;
	}
	for (int i = 0; i < n; i++) {
		if (elements[i] != NULL) {
			delete elements[i];
		}

	}
	delete[] elements;
	elements = nodes;
	n = uf.n;
	return *this;
}

template<class T>
UnionFind<T>::~UnionFind() {
	for (int i = 0; i < n; i++) {
		delete elements[i];
	}
	delete[] elements;
}

#endif /* UNIONFIND_H_ */
