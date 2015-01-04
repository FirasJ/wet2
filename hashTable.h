#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "tree.h"

template<class T>
class HashTable {
public:

	class ElementAlreadyExists: public std::exception {
	};
	class ElementNotFound: public std::exception {
	};
	class TableIsEmpty: public std::exception {
	};

	HashTable();
	~HashTable();
	void insert(const T& data);
	void remove(const T& data);
	bool find(const T& data) const;
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

};

class Modulo {
public:
	Modulo(int mod) :
			_mod(mod) {
	}
	int operator()(int number) {
		return number % _mod;
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
		Modulo modulo(_tableSize);
		_table[this->hash(data, modulo)]->insert(data);
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
		Modulo modulo(_tableSize);
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
bool HashTable<T>::find(const T& data) const {
	Modulo modulo(_tableSize);
	Tree<T> *tree = _table[this->hash(data, modulo)];
	try {
		if (tree->find(data)->getData() == data) {
			return true;
		}
	} catch (typename Tree<T>::TreeIsEmpty &e) {
		return false;
	}
	return false;
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
