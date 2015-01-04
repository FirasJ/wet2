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

int main() {
	cout << "hi" << endl;
	HashTable<int> table;
	for(int i = 0; i < 10; ++i) {
		//cout << i << endl;
		table.insert(i);
	}
	if(table.find(1)) {
		cout << "SUCCESS" << endl;
	}
	if(!table.find(10)) {
		cout << "SUCCESS" << endl;
	}
	for(int i = 0; i < 10; ++i) {
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
