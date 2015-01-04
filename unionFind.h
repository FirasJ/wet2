#ifndef UNIONFIND_H_
#define UNIONFIND_H_

template<class T>
class UnionFind {
public:
	UnionFind(T* data, int n);
	T Find(int x);
	void Union(int x, int y);
	~UnionFind();

	class IndexOutOfBounds {
	};
private:
	struct Node {
		int size;	// size of the Node, -1 if not parent.
		int parent;	// parent of the Node, -1 if current node is a parent.
		T& data;
		Node(int size, int parent, T& data) : size(size), parent(parent), data(data) {}
	};
	int n;			// number of Nodes
	Node** elements;	// array of nodes
};

template<class T>
UnionFind<T>::UnionFind(T* data, int n) :
		n(n), elements(new Node*[n]) {
	for (int i = 0; i < n; i++) {
		Node* tmp = new Node(1, -1, data[i]);
		elements[i] = tmp;
	}
}

template<class T>
T UnionFind<T>::Find(int x) {
	if (x < 0 || x >= n) {
		throw IndexOutOfBounds();
	}
	if (elements[x]->parent == -1) {
		return x;
	} else {
		return elements[x]->parent = Find(elements[x]->parent);
	}
}

template<class T>
void UnionFind<T>::Union(int x, int y) {
	if (x < 0 || x >= n || y < 0 || y >= n) {
		throw IndexOutOfBounds();
	}
	int xParent = Find(x), yParent = Find(y);
	if(xParent == yParent) { // x,y in same set
		return;
	}
	if(elements[xParent]->size > elements[yParent]->size) {
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
UnionFind<T>::~UnionFind() {
	for(int i=0; i<n; i++) {
		delete elements[i];
	}
	delete[] elements;
}

#endif /* UNIONFIND_H_ */
