/*********************************************
* Author:		Marc Penalosa
* Filename:		hashTable.h
* Date Created:	2/17/26
*********************************************/

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
using std::vector;
#include <list>
using std::list;
using std::pair;
#include <iterator>
#include "exception.h"

/*****************************************************************
* Class: HashTable
* 
* Purpose:
*		Creates a Hash Table ADT using a vector of lists of pairs
* 
* Manager Functions:
*		HashTable()
*			sets m_hash to nullptr. delegates the rest to default by the STLs
*		HashTable(int size, int(*hash)(K key) = nullptr)
*			creates a vector<list<pair<K, V>>> with the given size
*			defaults the m_hash to nullptr if a pointer is not optionally given as a second parameter
*		HashTable(const HashTable& copy)
*		HashTable(HashTable&& copy) noexcept
*		HashTable& operator=(const HashTable& rhs)
*		HashTable& operator=(HashTable&& rhs) noexcept
*		~HashTable()
* 
* Public Methods:
*		void setHash(int (*hash)(K key))
*		int getSize() const
*		void Insert(K key, V value)
*			inserts a pair into the table
*		V operator[](K key)
*			finds the pair with the given key in the table and return that pair's value
*		const V operator[](K key) const
*			const version of function above
*		void Delete(K key)
*			finds the pair with the given key in the table and deletes it
*		void Traverse(void (*visit)(V value))
*			traverses through the entire table and uses a visit function pointer to
*			manipulate a copy of every pair's value
*		void Traverse(void (*visit)(V value)) const
*			const version of function above
*		void Resize(int size)
*			resizes the table. if there's data, it keeps all the data and recalculates the buckets
*			based on the new size
* 
* Private Methods:
*		void Rehash()
*			rehashes the table
*****************************************************************/
template<typename K, typename V>
class HashTable
{
public:
	HashTable();
	HashTable(int size, int(*hash)(K key) = nullptr);
	HashTable(const HashTable& copy);
	HashTable(HashTable&& copy) noexcept;
	HashTable& operator=(const HashTable& rhs);
	HashTable& operator=(HashTable && rhs) noexcept;
	~HashTable();

	void setHash(int (*hash)(K key)); // store the function pointer in a data member
	int getSize() const;
	void Insert(K key, V value);
	V operator[](K key);
	const V operator[](K key) const;
	void Delete(K key);
	void Traverse(void (*visit)(V value));
	void Traverse(void (*visit)(V value)) const;
	void Resize(int size);
private:
	vector<list<pair<K, V>>> m_table;
	int(*m_hash)(K key);

	void Rehash();
};

template<typename K, typename V>
HashTable<K, V>::HashTable() : m_hash(nullptr)
{
}

template<typename K, typename V>
HashTable<K, V>::HashTable(int size, int(*hash)(K key)) : m_table(vector<list<pair<K, V>>>(size)), m_hash(hash)
{
}

template<typename K, typename V>
HashTable<K, V>::HashTable(const HashTable& copy) : m_table(copy.m_table), m_hash(copy.m_hash)
{
}

template<typename K, typename V>
HashTable<K, V>::HashTable(HashTable&& copy) noexcept : m_table(std::move(copy.m_table)), m_hash(std::move(copy.m_hash))
{
	// delegate rhs vector reset to the stl
	copy.m_hash = nullptr;
}

template<typename K, typename V>
HashTable<K, V>& HashTable<K, V>::operator=(const HashTable& rhs)
{
	if (this != &rhs)
	{
		m_table = rhs.m_table;
		m_hash = rhs.m_hash;
	}

	return *this;
}

template<typename K, typename V>
HashTable<K, V>& HashTable<K, V>::operator=(HashTable&& rhs) noexcept
{
	if (this != &rhs)
	{
		m_table = std::move(rhs.m_table);
		m_hash = std::move(rhs.m_hash);

		// delegate rhs vector reset to stl
		rhs.m_hash = nullptr;
	}

	return *this;
}

template<typename K, typename V>
HashTable<K, V>::~HashTable()
{
	m_hash = nullptr;
}

template<typename K, typename V>
void HashTable<K, V>::setHash(int(*hash)(K key))
{
	// rehash only if pointer changes
	if (m_hash != hash)
	{
		m_hash = hash;
		Rehash();
	}
}

template<typename K, typename V>
int HashTable<K, V>::getSize() const
{
	return m_table.size();
}

/*
* Purpose:
*		inserts a pair into the table
*		if the key already exists, insertion is ignored
* Precondition:
*		hash pointer must be set
*		table's size must be bigger than zero
* Postcondition:
*		a pair is inserted into the table
*/
template<typename K, typename V>
void HashTable<K, V>::Insert(K key, V value)
{
	if (m_table.size() == 0)
		throw Exception("table size is zero");
	if (m_hash == nullptr)
		throw Exception("hash not set");

	int bucket = m_hash(key) % m_table.size();
	if (bucket < 0)
		throw Exception("bucket value is negative");
	
	// check for double insertions
	bool alreadyExists = false;
	for (typename list<pair<K, V>>::iterator i = m_table[bucket].begin(); i != m_table[bucket].end(); i++)
	{
		if (i->first == key)
		{
			alreadyExists = true;
		}
	}
	// only insert if it's a new node
	if (!alreadyExists)
		m_table[bucket].push_back(pair<K, V>(key, value));
}

/*
* Purpose:
*		finds a pair with the given key and return that pair's value
* Precondition:
*		hash pointer must be set
*		table's size must be bigger than zero
*		key must exist
* Postcondition:
*		returns a copy of the pair's value
*/
template<typename K, typename V>
V HashTable<K, V>::operator[](K key)
{
	if (m_table.size() == 0)
		throw Exception("hash table size of zero");
	if (m_hash == nullptr)
		throw Exception("hash function not set");

	int bucket = m_hash(key) % m_table.size();
	if (bucket < 0)
		throw Exception("bucket value is negative");

	V result = V();
	bool found = false;

	// with the given bucket, iterate over the list of pairs
	for (typename list<pair<K, V>>::iterator i = m_table[bucket].begin(); i != m_table[bucket].end() && !found; i++)
	{
		// if the key matches the pair's key, copy its paired value
		if (key == i->first)
		{
			result = i->second;
			found = true;
		}
	}

	if (found == false)
		throw Exception("key not found");

	return result;
}

/*
* Const version of above function
*/
template<typename K, typename V>
const V HashTable<K, V>::operator[](K key) const
{
	if (m_table.size() == 0)
		throw Exception("hash table size of zero");
	if (m_hash == nullptr)
		throw Exception("hash function not set");

	int bucket = m_hash(key) % m_table.size();
	if (bucket < 0)
		throw Exception("bucket value is negative");

	V result = V();
	bool found = false;

	// with the given bucket, iterate over the list of pairs
	for (typename list<pair<K, V>>::const_iterator i = m_table[bucket].begin(); i != m_table[bucket].end() && !found; i++)
	{
		// if the key matches the pair's key, copy its paired value
		if (key == i->first)
		{
			result = i->second;
			found = true;
		}
	}

	if (found == false)
		throw Exception("key not found");

	return result;
}

/*
* Purpose:
*		deletes a pair with the given key
* Precondition:
*		table size must be bigger than zero
*		hash pointer must set
*		key must exist
* Postcondition:
*		deletes a pair with the given key
*/
template<typename K, typename V>
void HashTable<K, V>::Delete(K key)
{
	if (m_table.size() == 0)
		throw Exception("hash table size of zero");
	if (m_hash == nullptr)
		throw Exception("hash function not set");

	int bucket = m_hash(key) % m_table.size();
	if (bucket < 0)
		throw Exception("bucket value is negative");
	if (m_table[bucket].size() == 0)
		throw Exception("key not found");
	
	// this variable will save the iterator location to be erased
	// list.remove needed a == operator overload
	typename list<pair<K, V>>::iterator pairToDelete = m_table[bucket].begin();

	bool found = false;

	// iterator over list of pairs
	for (typename list<pair<K, V>>::iterator i = m_table[bucket].begin(); !found && i != m_table[bucket].end(); i++)
	{
		if (key == i->first)
		{
			// save the location
			pairToDelete = i;
			found = true;
		}
	}
	// throw if key is not found
	if (found == false)
		throw Exception("key not found");

	m_table[bucket].erase(pairToDelete);
}

/*
* Purpose:
*		traverses the table and uses the visit function to manipulate a copy of each pair's value
* Precondition:
*		visit function must not be nullptr
* Postcondition:
*		a copy of each pair's value are exposed
*/
template<typename K, typename V>
void HashTable<K, V>::Traverse(void(*visit)(V value))
{
	// traverse each bucket
	for (int i = 0; i < m_table.size(); i++)
	{
		// if the bucket isn't empty
		if (m_table[i].size() != 0)
		{
			// visit every pair in the list
			for (typename list<pair<K, V>>::iterator j = m_table[i].begin(); j != m_table[i].end(); j++)
				visit(j->second);
		}
	}
}

/*
* Const version of function above
*/
template<typename K, typename V>
void HashTable<K, V>::Traverse(void(*visit)(V value)) const
{
	// traverse each bucket
	for (int i = 0; i < m_table.size(); i++)
	{
		// if the bucket isn't empty
		if (m_table[i].size() != 0)
		{
			// visit every pair in the list
			for (typename list<pair<K, V>>::const_iterator j = m_table[i].begin(); j != m_table[i].end(); j++)
				visit(j->second);
		}
	}
}

/*
* Purpose:
*		resizes the table with the given size
* Precondition:
*		size must be non-negative
*		hash pointer must be set
* Postcondition:
*		the table is resized
*		if a non-zero size is given, data is kept and rehashed
*/
template<typename K, typename V>
void HashTable<K, V>::Resize(int size)
{
	if (size < 0)
		throw Exception("allocating negative length");
	if (m_hash == nullptr)
		throw Exception("hash function not set");

	if (size == 0)
	{
		m_table.clear();
	}
	else if (m_table.size() == 0)
	{
		m_table.resize(size);
	}
	else
	{
		// save current data
		vector<list<pair<K, V>>> temp = m_table;

		int bucket = 0;

		// clear and resize
		m_table.clear();
		m_table.resize(size);

		// traverse through the saved data
		for (int i = 0; i < temp.size(); i++)
		{
			// if the bucket isn't empty
			if (temp[i].size() != 0)
			{
				// copy everything back to a new bucket
				for (typename list<pair<K, V>>::iterator j = temp[i].begin(); j != temp[i].end(); j++)
				{
					bucket = m_hash(j->first) % m_table.size();
					if (bucket < 0)
						throw Exception("negative index");
					m_table[bucket].push_back(*j);
				}
			}
		}
	}
}

/*
* Purpose:
*		rehashes the table
* Precondition:
*		hash pointer must be set
* Postcondition:
*		table is rehashed
*/
template<typename K, typename V>
void HashTable<K, V>::Rehash()
{
	if (m_hash == nullptr)
		throw Exception("hash function not set");

	if (m_table.size() != 0)
	{
		vector<list<pair<K, V>>> temp = m_table;
		int bucket;

		// reset the vector, then resize because clear resizes to 0
		m_table.clear();
		m_table.resize(temp.size());

		// traverse through the old vector
		for (int i = 0; i < temp.size(); i++)
		{
			// if the bucket isn't empty
			if (temp[i].size() != 0)
			{
				// insert all of its contents back in the new bucket
				for (typename list<pair<K, V>>::iterator j = temp[i].begin(); j != temp[i].end(); j++)
				{
					// use temp pairs to reorder the data back into new buckets
					bucket = m_hash(j->first) % m_table.size();
					if (bucket < 0)
						throw Exception("bucket value is negative");
					m_table[bucket].push_back(*j);
				}
			}
		}
	}
}

#endif // !HASH_TABLE_H