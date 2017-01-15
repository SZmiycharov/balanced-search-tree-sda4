#include "HelperFunctions.h"

template <class DataType>
class BST
{
private:
	struct node
	{
		DataType key;
		int id;
		std::string data;
		node *left, *right;
		int count;

		//node constructor + root declaration
		node(const DataType& key, node* left = nullptr, node* right = nullptr, int count = 1)
			: key(key), left(left), right(right), count(count)
		{
			std::string keyParts[3];
			splitStringToArray(key, ' ', keyParts);

			assert(istringstream(keyParts[0]) >> id);
			data = keyParts[1];
		}
	}*root;


private:
	void clear(node* root)
	{
		if (root)
		{
			clear(root->left);
			clear(root->right);
			delete root;
		}
	}

	node* copy(node* root)
	{
		return root ?
			new node(root->key, copy(root->left), copy(root->right)) :
			root;
	}

	bool search(const node* root, const DataType& key) const
	{
		if (!root) {
			cout << "false" << endl;
			return false;
		}
		if (root->key == key) {
			cout << "true" << endl;
			return true;
		}
		return numericFirstStringCompare(key, root->key) ? search(root->left, key) : search(root->right, key);
	}

	void add(node*& root, const DataType& key)
	{
		if (!root)
		{
			root = new node(key);
		}
		else if (root->key == key)
		{
			root->count++;
		}
		else
		{
			add(numericFirstStringCompare(key, root->key) ? root->left : root->right, key);
		}
	}

	bool removeByKey(node*& root, const DataType& key)
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

			node* toDel = root;
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
				node* mR = extractMin(root->right);
				mR->left = root->left;
				mR->right = root->right;
				root = mR;
			}
			cout << "true" << endl;
			delete toDel;
			toDel = 0;
			return true;
		}
		else
		{
			removeByKey(numericFirstStringCompare(key, root->key) ? root->left : root->right, key);
		}
	}

	bool removeByID(node*& root, const int id)
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

			node* toDel = root;
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
				node* mR = extractMin(root->right);
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

	node* extractMin(node*& root)
	{
		if (root->left)
			return extractMin(root->left);

		node* n = root;
		root = root->right;
		return n;
	}

public:
	BST() : root(nullptr){};

	~BST() { clear(root); }

	BST(const BST& tree)
		: root(copy(tree.root)) {};

	BST& operator=(const BST& tree)
	{
		if (&tree != this)
		{
			clear(root);
			root = copy(tree.root);
		}
		return *this;
	}

	bool search(const DataType& key) const { return search(root, key); }
	void add(const DataType& key) { add(root, key); }
	bool removeByKey(const DataType& key) { return removeByKey(root, key); }
	int removeAllByID(const int id) {
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

	node* sortedArrayToNodes(std::string arr[10000], int min, int max)
	{
		if (min == max) return nullptr;

		int median = min + (max - min) / 2;

		return new node(arr[median], sortedArrayToNodes(arr, min, median), sortedArrayToNodes(arr, median + 1, max));
	}

	void constructPerfectlyBalancedTree(std::string arr[10000], int min, int max)
	{
		root = sortedArrayToNodes(arr, min, max);
	}

};

