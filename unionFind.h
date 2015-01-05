#ifndef UNIONFIND_H_
#define UNIONFIND_H_

template<class T>
class UnionFind {
public:

	class Node;

	UnionFind(int n);
	UnionFind(int n, T* data);
	UnionFind& operator=(const UnionFind& uf);
	T& Find(int x); // returns root
	T& get(int x) const; // returns elements[x]
	void Union(int x, int y);
	~UnionFind();

	class IndexOutOfBounds: public std::exception {
	};
private:
	int find(int x);

	int n;			// number of Nodes
	Node** elements;	// array of nodes
};

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
	int size;	// size of the Node, -1 if not parent.
	int parent;	// parent of the Node, -1 if current node is a parent.
	T& data;
};

template<class T>
UnionFind<T>::UnionFind(int n) :
		n(n), elements(new Node*[n]) {
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
	int xParent = find(x), yParent = find(y);
	if (xParent == yParent) { // x,y in same set
		return;
	}
	if (elements[xParent]->size > elements[yParent]->size) {
		elements[xParent]->size += elements[yParent]->size;
		elements[yParent]->size = -1;
		elements[yParent]->parent = xParent;
	} else {
		elements[yParent]->size += elements[xParent]->size;
		elements[xParent]->size = -1;
		elements[xParent]->parent = yParent;
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
			//nodes[i] = new Node(*elements[i]);
			nodes[i] = new Node(*elements[i]);
		}
	} catch (...) {
		delete[] nodes;
		throw;
	}
	for (int i = 0; i < n; i++) {
		delete elements[i];
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
