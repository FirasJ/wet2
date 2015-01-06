#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "tree.h"

/* Class HashTable
 * This data structure maps keys to values using a Modulo as the hash function
 * dynamic allocation for the array, Chain Hashing technique along with and
 * AVL Trees as the chains in each slot (bucket).
 */
template<class T>
class HashTable {
public:
	/* Exceptions thrown by the Hash Table */
	class ElementAlreadyExists: public std::exception {
	};
	class ElementNotFound: public std::exception {
	};
	class TableIsEmpty: public std::exception {
	};

	/* Empty constructor : initializes an empty new hash table
	 * Time complexity : O(1)
	 */
	HashTable();
	/* Destructor: clears the objects in the table and deletes the data
	 * Time complexity : O(n)
	 */
	~HashTable();
	/* Inserts a new item with @data to the hash table.
	 * @throw ElementAlreadyExists
	 * Time Complexity: O(1) amortized in average.
	 */
	void insert(const T& data);
	/* Removes an element from the Hash Table.
	 * @throw ElementNotFound
	 * @throw TableIsEmpty
	 * Time Complexity: O(1) amortized in average.
	 */
	void remove(const T& data);
	/* Returns a pointer to the data if found in the table, NULL otherwise.
	 * Time Complexity: O(1) in average, O(log n) in worst case.
	 */
	T* find(const T& data) const;
	/* Returns the number of elements in the Hash Table
	 * Time Complexity: O(1)
	 */
	size_t size() const;

private:

	size_t _size, _tableSize;
	Tree<T> **_table;

	void initializeTable(Tree<T>* _table[], int size);
	void deleteTable(Tree<T>* _table[], int size);
	template<class HashFunction>
	int hash(const T& data, HashFunction& hashFucntion) const ;
	void realocateTable(size_t newSize);
	class InsertToNewTable;
	class Modulo;

};

template<class T>
class HashTable<T>::Modulo {
public:
	Modulo(int mod) :
			_mod(mod) {
	}
	int operator()(const T& data) {
		return data % _mod;
	}
private:
	int _mod;
};

template<class T>
HashTable<T>::HashTable() :
		_size(0), _tableSize(2), _table(new Tree<T>*[_tableSize]) {
	initializeTable(_table, _tableSize);
}

template<class T>
void HashTable<T>::initializeTable(Tree<T>* table[], int size) {
	for (int i = 0; i < size; ++i) {
		table[i] = new Tree<T>();
	}
}

template<class T>
void HashTable<T>::deleteTable(Tree<T>* table[], int size) {
	for (int i = 0; i < size; ++i) {
		delete table[i];
	}
	delete[] table;
}

template<class T>
HashTable<T>::~HashTable() {
	deleteTable(_table, _tableSize);
}

template<class T>
void HashTable<T>::insert(const T& data) {
	try {
		HashTable<T>::Modulo modulo(_tableSize);
		_table[hash(data, modulo)]->insert(data);
		_size++;
		if (_size == _tableSize) {
			realocateTable(_tableSize * 2);
		}
	} catch (typename Tree<T>::ElementAlreadyExists &e) {
		throw ElementAlreadyExists();
	}
}

template<class T>
void HashTable<T>::remove(const T& data) {
	try {
		HashTable<T>::Modulo modulo(_tableSize);
		_table[this->hash(data, modulo)]->remove(data);
		_size--;
		if (_size == _tableSize / 4) {
			realocateTable(_tableSize / 2);
		}
	} catch (typename Tree<T>::ElementNotFound &e) {
		throw ElementNotFound();
	} catch (typename Tree<T>::TreeIsEmpty &e) {
		throw TableIsEmpty();
	}
}

template<class T>
T* HashTable<T>::find(const T& data) const {
	HashTable<T>::Modulo modulo(_tableSize);
	Tree<T> *tree = _table[this->hash(data, modulo)];
	try {
		if (tree->find(data)->getData() == data) {
			return &(tree->find(data)->getData());
		}
	} catch (typename Tree<T>::TreeIsEmpty &e) {
		return NULL;
	}
	return NULL;
}

template<class T>
size_t HashTable<T>::size() const {
	return _size;
}

template<class T>
template<class HashFunction>
int HashTable<T>::hash(const T& data, HashFunction& hashFucntion) const {
	return hashFucntion(data);
}

template<class T>
void HashTable<T>::realocateTable(size_t newSize) {
	Tree<T>** newTable = new Tree<T>*[newSize];
	initializeTable(newTable, newSize);
	Tree<T>** oldTable = _table;
	size_t oldSize = _tableSize;
	_table = newTable;
	_tableSize = newSize;
	for (unsigned int i = 0; i < oldSize; ++i) {
		InsertToNewTable insertFunc(this);
		oldTable[i]->inOrder(insertFunc);
	}
	deleteTable(oldTable, oldSize);
}

template<class T>
class HashTable<T>::InsertToNewTable {
public:
	InsertToNewTable(HashTable<T>* hashTable) :
			_hashTable(hashTable) {
	}
	void operator()(const T& data) {
		_hashTable->insert(data);
	}
private:
	HashTable<T>* _hashTable;
};

#endif /* HASHTABLE_H_ */
