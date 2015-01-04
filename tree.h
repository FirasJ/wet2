#ifndef TREE_H_
#define TREE_H_

//#include <stdlib.h>		//
#include <cassert>		// assert()
#include <exception>	// std::exception

/*
 * Class AVL Tree
 * a self-balancing Binary Search Tree (BST) where the difference between
 * heights of left and right subtrees cannot be more than one for all nodes.
 */
template<class T>
class Tree {
public:

	/* Exceptions thrown by the tree */
	class TreeIsEmpty: public std::exception {
	};
	class ElementNotFound: public std::exception {
	};
	class ElementAlreadyExists: public std::exception {
	};

	/* Empty constructor : initializes an empty new tree
	 * Time complexity : O(1)
	 */
	Tree();
	/*
	 *
	 */
	explicit Tree(int n);
	/* virtual destructor : clears the objects in the tree and deletes the data
	 * Time complexity : O(n)
	 */
	virtual ~Tree();
	/* allocates new memory, and inserts the object to the tree while
	 * making sure that height of the tree remains O(Log n)
	 * @throw ElementAlreadyExists
	 * Time complexity : O(log n)
	 */
	virtual void insert(const T& data);
	/* removes an object from the tree, if found, and makes sure the height of
	 * the tree remains O(log n)
	 * @throw TreeIsEmpty
	 * @throw ElementNotFound
	 * Time complexity : O(log n)
	 */
	virtual void remove(const T& data);
	/* returns the number of objects in the tree
	 * Time complexity : O(1)
	 */
	size_t size() const;
	/* A template method that calls the Function on all the objects of the tree
	 * using pre-order traversal
	 * Time complexity : O(n)
	 */
	template<class Function>
	void preOrder(Function& function) const;
	/* A template method that calls the Function on all the objects of the tree
	 * using post-order traversal
	 * Time complexity : O(n)
	 */
	template<class Function>
	void postOrder(Function& function) const;
	/* A template method that calls the Function on all the objects of the tree
	 * using in-order traversal
	 * Time complexity : O(n)
	 */
	template<class Function>
	void inOrder(Function& function) const;
	// An AVL Tree Node
	class Node;
	friend class Node;
	/* Searches for the passed @data in the tree and returns the Node that
	 * contains it, or the parent-to-be in case the data was inserted to
	 * the tree.
	 * @throw TreeIsEmpty
	 * Time complexity : O(log n)
	 */
	virtual Node* find(const T& data) const;
	/* returns the maximum data of the tree.
	 * @throw TreeIsEmpty
	 * Time complexity : O(log n)
	 */
	Node* getMax() const;
	/*
	 * Retuns the k-th element in the tree.
	 */
	const T& select(int k) const;
	Node* selectAux(Node* node, int k) const;
	/* deletes all the data stored in the tree.
	 * Time complexity : O(n)
	 */
	void clear(Node* node);

private:

	Node *_root; // stores a pointer to the root of the tree
	size_t _size; // contains the number of objects in the tree

	/* All non-recursive private functions are performed in time complexity of
	 * O(1) unless stated otherwise.
	 */

	// a recursive helping function that traverses through the tree in pre-order
	// and calls @Function on each object
	template<class Function>
	void subPreOrder(Node* node, Function& function) const;
	// a recursive helping function that traverses through the tree in post-order
	// and calls @Function on each object
	template<class Function>
	void subPostOrder(Node* node, Function& function) const;
	// a recursive helping function that traverses through the tree in in-order
	// and calls @Function on each object
	template<class Function>
	void subInOrder(Node* node, Function& function) const;
	/* A helping function that handles all the rotations needed in order to
	 * maintain a legal AVL tree.
	 * This function calls one of the 4 rotation methods.
	 * Each rotation is performed in time complexity of O(1).
	 */
	void rotate(Node* node);
	// An utility function to left rotate subtree rooted with @node
	void rotateLL(Node* node);
	// An utility function to right rotate subtree rooted with @node
	void rotateRR(Node* node);
	// An utility function to left-right rotate subtree rooted with @node
	void rotateLR(Node* node);
	// An utility function to right-left rotate subtree rooted with @node
	void rotateRL(Node* node);
	// A helping function to update the balance factor of @node.
	void updateBalanceFactor(Node* node);
	// A helping function to update the height of @node.
	void updateHeight(Node* node);
	// A helping function that updates the height and balance factor of all the
	// nodes starting from @leaf all the way up to the root.
	// Time complexity: O(n)
	//void update(Node* leaf);
	// A recursive utility function to find @data starting from @node
	Tree<T>::Node* findAux(Node* node, const T& data) const;
	// An utility function to remove a @node that has no more than one son
	// and maintain the correctness of the AVL tree
	// returns the parent of the node
	typename Tree<T>::Node* removeOneSon(Node* node);
	// A helping function to return a reference to the field of the parent
	// containing the node.
	Node*& parentSon(Node* node);
	// A helping function to return the following node of the passed @node.
	// Time complexity : O(log n)
	Node* getFollowing(Node* node);
	// An utility function that swaps the data between two given nodes
	void swapNodes(Node* node, Node* next);

	void fixSizes(Node* node, const T& data, int diff);
	void updateSize(Node* node);
};

template<class T>
class Tree<T>::Node {
public:
	friend class Tree<T> ;
	Node(const T& data) :
			_data(data), _left(0), _right(0), _parent(0), _height(0), _balanceFactor(
					0), _size(1) {
	}
	Node(const Node& node) :
			_data(node._data), _left(node._left), _right(node._right), _parent(
					node._parent), _height(node._height), _balanceFactor(
					node._balanceFactor), _size(node._size) {
	}
	const T& getData() {
		return _data;
	}
private:
	T _data;
	Node *_left, *_right, *_parent;
	int _height, _balanceFactor, _size;
	Node& operator=(const Node& node);
};

template<class T>
Tree<T>::Tree() :
		_root(0), _size(0) {
}

template<class T>
void Tree<T>::clear(Node* node) {
	if (!node)
		return;
	if (node->_left)
		clear(node->_left);
	if (node->_right)
		clear(node->_right);
	delete node;
	--_size;
}

template<class T>
Tree<T>::~Tree() {
	clear(_root);
}

template<class T>
void Tree<T>::insert(const T& data) {
	try {
		Node* parent = find(data);
		if (parent->_data == data) {
			throw ElementAlreadyExists();
		}
		Node* newNode = new Node(data);
		++_size;
		fixSizes(_root, data, +1);
		newNode->_parent = parent;
		if (data < parent->_data) {
			parent->_left = newNode;
		} else {
			parent->_right = newNode;
		}
		Node* tmpNode = newNode;
		while (tmpNode != _root) {
			Node* son = tmpNode;
			tmpNode = tmpNode->_parent;
			updateBalanceFactor(tmpNode);
			if (tmpNode->_height >= son->_height + 1)
				return;
			if (tmpNode->_height >= son->_height + 1)
				return;
			updateHeight(tmpNode);
			if (abs(tmpNode->_balanceFactor) > 1) {
				rotate(tmpNode);
				return;
			}
		}
	} catch (TreeIsEmpty& e) {
		Node* newNode = new Node(data);
		_root = newNode;
		++_size;
	}

}

template<class T>
typename Tree<T>::Node* Tree<T>::getMax() const {
	Node* max = _root;
	if (!max) {
		throw TreeIsEmpty();
	}
	while (max->_right) {
		max = max->_right;
	}
	return max;
}

template<class T>
inline size_t Tree<T>::size() const {
	return _size;
}

template<class T>
const T& Tree<T>::select(int k) const {
	if(size() == 0 || size() < k) {
		throw TreeIsEmpty();
	}
	return selectAux(_root, k)->_data;
}

template<class T>
typename Tree<T>::Node* Tree<T>::selectAux(Node* node, int k) const {
	int size=0;
	if(node->_left) {
		size = node->_left->_size;
	}
	if(size == k-1) {
		return node;
	} else if(size > k-1) {
		return selectAux(node->_left, k);
	} else { //if(size < k-1)
		return selectAux(node->_right, k-size-1);
	}
}

template<class T>
void Tree<T>::swapNodes(Node* node, Node* next) {
	T& t = node->_data;
	node->_data = next->_data;
	next->_data = t;
}

template<class T>
void Tree<T>::remove(const T& data) {
	Tree<T>::Node *node;
	node = find(data); // throws if empty
	if (node->_data != data) {
		throw ElementNotFound();
	}
	if (node->_left && node->_right) { // 2 sons
		Node* next = getFollowing(node);
		swapNodes(node, next);
		node = next;
	}

	Tree<T>::Node *parent = removeOneSon(node);

	while (parent != NULL) {
		updateHeight(parent);
		updateBalanceFactor(parent);
		updateSize(parent);
		if (abs(parent->_balanceFactor) > 1) {
			rotate(parent);
		}
		parent = parent->_parent;
	}
	--_size;
	delete node;
}

template<class T>
typename Tree<T>::Node*& Tree<T>::parentSon(Node* node) {
	assert(node);
	if (node->_parent)
		return (node->_parent->_left == node) ?
				node->_parent->_left : node->_parent->_right;
	return node->_parent;
}

template<class T>
typename Tree<T>::Node* Tree<T>::removeOneSon(Node* node) {
	assert(node);
	Node*& son = parentSon(node);
	fixSizes(_root, node->_data, -1);
	if (!node->_left && !node->_right) { // leaf node
		if (son) {
			son = NULL;
		} else {
			_root = NULL;
		}
	} else if (node->_left && !node->_right) { // only left son
		if (!son) {
			_root = node->_left;
			node->_left->_parent = NULL;
		} else {
			son = node->_left;
			node->_left->_parent = node->_parent;
		}
	} else { // only right son
		if (!son) {
			_root = node->_right;
			node->_right->_parent = NULL;
		} else {
			son = node->_right;
			node->_right->_parent = node->_parent;
		}
	}
	return node->_parent;
}

template<class T>
typename Tree<T>::Node* Tree<T>::getFollowing(Node* node) {
	assert(node && node->_right);
	Node* tmp = node->_right;
	while (tmp->_left) {
		tmp = tmp->_left;
	}
	return tmp;
}

template<class T>
typename Tree<T>::Node* Tree<T>::findAux(Node* node, const T& data) const {
	if (node->_data > data && node->_left) {
		return findAux(node->_left, data);
	}
	if (node->_data < data && node->_right) {
		return findAux(node->_right, data);
	}
	return node;
}

template<class T>
typename Tree<T>::Node* Tree<T>::find(const T& data) const {
	if (!_root)
		throw TreeIsEmpty();
	Node* node = findAux(_root, data);
	return node;
}

template<class T>
template<class Function>
void Tree<T>::preOrder(Function& function) const {
	subPreOrder(_root, function);
}

template<class T>
template<class Function>
void Tree<T>::postOrder(Function& function) const {
	subPostOrder(_root, function);
}

template<class T>
template<class Function>
void Tree<T>::inOrder(Function& function) const {
	subInOrder(_root, function);
}

template<class T>
template<class Function>
void Tree<T>::subPreOrder(Node* node, Function& function) const {
	if (node) {
		function(node->_data);
		if (node->_left)
			subPreOrder(node->_left, function);
		if (node->_right)
			subPreOrder(node->_right, function);
	}
}

template<class T>
template<class Function>
void Tree<T>::subPostOrder(Node* node, Function& function) const {
	if (node) {
		if (node->_left)
			subPostOrder(node->_left, function);
		if (node->_right)
			subPostOrder(node->_right, function);
		function(node->_data);
	}
}

template<class T>
template<class Function>
void Tree<T>::subInOrder(Node* node, Function& function) const {
	if (node) {
		if (node->_left)
			subInOrder(node->_left, function);
		function(node->_data);
		if (node->_right)
			subInOrder(node->_right, function);
	}
}

template<class T>
void Tree<T>::rotateLL(Node* node) {
	if (node->_parent) {
		(node->_parent->_left == node) ?
				node->_parent->_left = node->_left : node->_parent->_right =
						node->_left;
	} else {
		_root = node->_left;
	}
	node->_left->_parent = node->_parent;
	node->_parent = node->_left;
	Node* tmp = node->_left->_right;
	node->_left->_right = node;
	if (tmp)
		tmp->_parent = node;
	node->_left = tmp;

	updateHeight(node);
	updateHeight(node->_parent);

	updateBalanceFactor(node);
	updateBalanceFactor(node->_parent);

	updateSize(node);
	updateSize(node->_parent);
}

template<class T>
void Tree<T>::rotateRR(Node* node) {
	if (node->_parent) {
		(node->_parent->_left == node) ?
				node->_parent->_left = node->_right : node->_parent->_right =
						node->_right;
	} else {
		_root = node->_right;
	}
	node->_right->_parent = node->_parent;
	node->_parent = node->_right;
	Node* tmp = node->_right->_left;
	node->_right->_left = node;
	if (tmp)
		tmp->_parent = node;
	node->_right = tmp;

	updateHeight(node);
	updateHeight(node->_parent);

	updateBalanceFactor(node);
	updateBalanceFactor(node->_parent);

	updateSize(node);
	updateSize(node->_parent);
}

template<class T>
void Tree<T>::rotateLR(Node* node) {
	rotateRR(node->_left);
	rotateLL(node);
}

template<class T>
void Tree<T>::rotateRL(Node* node) {
	rotateLL(node->_right);
	rotateRR(node);
}

template<class T>
void Tree<T>::rotate(Node* node) {
	int left = node->_left ? node->_left->_balanceFactor : 0;
	int right = node->_right ? node->_right->_balanceFactor : 0;
	if (node->_balanceFactor == 2) {
		if (left >= 0) {
			rotateLL(node);
			return;
		} else {
			rotateLR(node);
			return;
		}
	} else {
		if (right <= 0) {
			rotateRR(node);
			return;
		} else {
			rotateRL(node);
			return;
		}
	}
}

template<class T>
void Tree<T>::updateBalanceFactor(Node* node) {
	if (!node)
		return;
	int right = node->_right ? node->_right->_height : -1;
	int left = node->_left ? node->_left->_height : -1;
	node->_balanceFactor = left - right;
}

template<class T>
void Tree<T>::updateHeight(Node* node) {
	if (!node)
		return;
	int right = node->_right ? node->_right->_height : -1;
	int left = node->_left ? node->_left->_height : -1;
	node->_height = 1 + (left > right ? left : right);
}
/*
template<class T>
void Tree<T>::update(Node* leaf) {
	Node* tmpNode = leaf;
	while (tmpNode) {
		updateHeight(tmpNode->_parent);
		tmpNode = tmpNode->_parent;
	}
	while (tmpNode) {
		updateBalanceFactor(tmpNode->_parent);
		tmpNode = tmpNode->_parent;
	}
}
*/
template<class T>
void Tree<T>::fixSizes(Node* node, const T& data, int diff) {
	if(node) {
		node->_size += diff;
	}
	if (node->_data > data && node->_left) {
		fixSizes(node->_left, data, diff);
	}
	if (node->_data < data && node->_right) {
		fixSizes(node->_right, data, diff);
	}
}

template<class T>
Tree<T>::Tree(int n) : _root(0), _size(n) {
	Node* ptrs = new Node[n];
	for(int i=0; i<n; i++) {
		Node* n = new Node(T());
		ptrs[i]=n;
	}
	_root = ptrs[0];
	for(int i=n-1; i>=0; i++) {
		// update fields: parent left right height bf size
		// parent
		Node* parent = ptrs[(i-1)/2];
		ptrs[i]->_parent = parent;
		// left & right
		if(i%2 == 0) {
			parent->_right = ptrs[i];
		} else {
			parent->_left = ptrs[i];
		}
		updateBalanceFactor(ptrs[i]);
		updateHeight(ptrs[i]);
		updateSize(ptrs[i]);
	}
	delete[] ptrs;
}

template<class T>
void Tree<T>::updateSize(Node* node) {
	if (!node)
		return;
	int right = node->_right ? node->_right->_size : 0;
	int left = node->_left ? node->_left->_size : 0;
	node->_size = 1 + left + right;
}

#endif /* TREE_H_ */
