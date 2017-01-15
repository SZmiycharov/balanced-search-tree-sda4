/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Stanislav Zmiycharov
* @idnumber 61883
* @task 4
* @compiler VC
*
*/

#include "Node.h"

template <class T>
class BST
{
private:
	node<T>* copyFrom(node<T>* root);
	node<T>* extractMin(node<T>*& root);
	void clear(node<T>* root);
	void addHelper(node<T>*& root, const T& key);
	bool searchHelper(const node<T>* root, const T& key) const;
	bool removeByKeyHelper(node<T>*& root, const T& key);
	bool removeByID(node<T>*& root, const int id);

	node<T>* root;

public:
	BST();
	~BST();
	BST(const BST& other);
	BST<T>& operator=(const BST& other);

	node<T>* sortedArrayToNodes(std::string arr[10000], int min, int max);
	void constructPerfectlyBalancedTree(std::string arr[10000], int min, int max);
	void add(const T& key);
	bool search(const T& key) const;
	bool removeByKey(const T& key);
	int removeAllByID(const int id);
};

template <typename T>
BST<T>::BST()
{
	node<T>* root = nullptr;
}

template <typename T>
BST<T>::~BST() 
{ 
	clear(root); 
}

template <typename T>
BST<T>::BST(const BST& other)
{
	root(copyFrom(tree.other));
}

template <typename T>
BST<T>& BST<T>::operator=(const BST& other)
{
	if (&other != this)
	{
		clear(root);
		root = copyFrom(other.root);
	}
	return *this;
}

template <typename T>
node<T>* BST<T>::sortedArrayToNodes(std::string arr[10000], int min, int max)
{
	if (min == max) return nullptr;

	int median = min + (max - min) / 2;

	return new node<T>(arr[median], sortedArrayToNodes(arr, min, median), sortedArrayToNodes(arr, median + 1, max));
}

template <typename T>
void BST<T>::constructPerfectlyBalancedTree(std::string arr[10000], int min, int max)
{
	root = sortedArrayToNodes(arr, min, max);
}

template <typename T>
void BST<T>::add(const T& key)
{
	addHelper(root, key);
}

template <typename T>
bool BST<T>::search(const T& key) const
{
	return searchHelper(root, key);
}

template <typename T>
bool BST<T>::removeByKey(const T& key)
{
	return removeByKeyHelper(root, key);
}

template <typename T>
int BST<T>::removeAllByID(const int id) 
{
	int removedElements = 0;
	bool removedEl = false;

	while (true)
	{
		removedEl = removeByID(root, id);
		if (removedEl) ++removedElements;
		else break;
	}

	return removedElements;
}

template <typename T>
node<T>* BST<T>::copyFrom(node<T>* root)
{
	return root ?
		new node(root->key, copyFrom(root->left), copyFrom(root->right)) :
		root;
}

template <typename T>
node<T>* BST<T>::extractMin(node<T>*& root)
{
	if (root->left)
		return extractMin(root->left);

	node<T>* n = root;
	root = root->right;
	return n;
}

template <typename T>
void BST<T>::clear(node<T>* root)
{
	if (root)
	{
		clear(root->left);
		clear(root->right);
		delete root;
	}
}

template <typename T>
void BST<T>::addHelper(node<T>*& root, const T& key)
{
	if (!root)
	{
		root = new node<T>(key);
	}
	else if (root->key == key)
	{
		root->count++;
	}
	else
	{
		addHelper(numericFirstStringCompare(key, root->key) ? root->left : root->right, key);
	}
}

template <typename T>
bool BST<T>::searchHelper(const node<T>* root, const T& key) const
{
	if (!root) {
		cout << "false" << endl;
		return false;
	}
	if (root->key == key) {
		cout << "true" << endl;
		return true;
	}
	return numericFirstStringCompare(key, root->key) ? searchHelper(root->left, key) : searchHelper(root->right, key);
}

template <typename T>
bool BST<T>::removeByKeyHelper(node<T>*& root, const T& key)
{
	if (!root) {
		cout << "false" << endl;
		return false;
	}

	if (root->key == key)
	{
		if (root->count > 1)
		{
			root->count--;
			cout << "true" << endl;
			return true;
		}

		node<T>* toDel = root;
		if (!root->left)
		{
			root = root->right;
		}
		else if (!root->right)
		{
			root = root->left;
		}
		else
		{
			node<T>* mR = extractMin(root->right);
			mR->left = root->left;
			mR->right = root->right;
			root = mR;
		}
		cout << "true" << endl;
		delete toDel;
		return true;
	}
	else
	{
		removeByKeyHelper(numericFirstStringCompare(key, root->key) ? root->left : root->right, key);
	}
}

template <typename T>
bool BST<T>::removeByID(node<T>*& root, const int id)
{
	if (!root) {
		return false;
	}

	if (root->id == id)
	{
		if (root->count > 1)
		{
			root->count--;
			return true;
		}

		node<T>* toDel = root;
		if (!root->left)
		{
			root = root->right;
		}
		else if (!root->right)
		{
			root = root->left;
		}
		else
		{
			node<T>* mR = extractMin(root->right);
			mR->left = root->left;
			mR->right = root->right;
			root = mR;
		}
		delete toDel;
		return true;
	}
	else
	{
		removeByID(id < root->id ? root->left : root->right, id);
	}
}

















