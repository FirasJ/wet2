#include "hashTable.h"
#include "tree.h"
#include "unionFind.h"

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

void print(double x) {
	std::cout << x << " ";
}

int UFmain() {

	int a[] = { 0, 1, 2, 3, 4, 5 };
	UnionFind<int> uf(6, a);
	for (int i = 0; i < 6; i++) {
		cout << i << "belongs to " << uf.Find(i) << endl;
	}
	uf.Union(0, 5);
	uf.Union(1, 4);
	uf.Union(2, 3);
	for (int i = 0; i < 6; i++) {
		cout << i << "belongs to " << uf.Find(i) << endl;
	}
	uf.Union(0, 1);
	uf.Union(2, 3);
	uf.Union(3, 0);
	for (int i = 0; i < 6; i++) {
		cout << i << "belongs to " << uf.Find(i) << endl;
	}

	return 0;
}
int hashMain() {
	cout << "hi" << endl;
	HashTable<int> table;
	for (int i = 0; i < 10; ++i) {
		//cout << i << endl;
		table.insert(i);
	}
	if (table.find(1)) {
		cout << "SUCCESS" << endl;
	}
	if (!table.find(10)) {
		cout << "SUCCESS" << endl;
	}
	for (int i = 0; i < 10; ++i) {
		//cout << i*100 << endl;
		table.remove(i);
	}
	cout << "bye" << endl;
	return 0;
}

int treeMain() {
	Tree<double> tree;
//	int x[10];
	for (int i = 0; i < 10; ++i) {
		//std::cin >> x[i];
		//tree.insert(x[i]);
		tree.insert(i);
		tree.inOrder(print);
		std::cout << std::endl;
	}
	for (int i = 0; i < 10; ++i) {
//		tree.remove(x[i]);
		tree.remove(i);
		tree.inOrder(print);
		std::cout << std::endl;
		//std::cout << tree.find(i)->getData() << std::endl;
	}
	//tree.preOrder(print);
	//tree.inOrder(print);
	return 0;
}
