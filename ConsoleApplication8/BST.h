#include <iostream>
#include <algorithm>

using namespace std;

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
			string keyParts[2];
			BST::splitStringToArray(key, ' ', keyParts);

			assert(istringstream(keyParts[0]) >> id);
			data = keyParts[1];

			cout << "key: " << id << "; data: " << data << ";" << endl;

		}
	}*root;

	size_t size;

private:
	static void splitStringToArray(const string &str, char delimeter, string(&arr)[2])
	{
		stringstream ss;
		ss.str(str);
		string item;

		int i = 0;
		while (getline(ss, item, delimeter))
		{
			arr[i] = item;
			++i;
		}
	}

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
		return key < root->key ? search(root->left, key) : search(root->right, key);
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
			add(key < root->key ? root->left : root->right, key);
		}
	}

	bool remove(node*& root, const DataType& key)
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
				--size;
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
			--size;
			cout << "true" << endl;
			delete toDel;
			return true;
		}
		else
		{
			remove(key < root->key ? root->left : root->right, key);
		}
	}

	bool removeAll(node*& root, const int id)
	{
		if (!root) {
			cout << "false" << endl;
			return false;
		}

		if (root->id == id)
		{
			if (root->count > 1)
			{
				root->count--;
				--size;
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
			--size;
			cout << "true" << endl;
			delete toDel;
			return true;
		}
		else
		{
			removeAll(id < root->id ? root->left : root->right, id);
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
	BST() : root(nullptr), size(0){};

	~BST() { clear(root); }

	BST(const BST& tree)
		: root(copy(tree.root))
		, size(tree.size) {};

	BST& operator=(const BST& tree)
	{
		if (&tree != this)
		{
			clear(root);
			root = copy(tree.root);
			size = tree.size;
		}
		return *this;
	}

	bool search(const DataType& key) const { return search(root, key); }
	void add(const DataType& key) { add(root, key); ++size; }
	bool remove(const DataType& key) { return remove(root, key); }
	int removeAll(const int id) {
		bool continueRemoving = true;
		int removedElements = 0;
		while (continueRemoving)
		{
			continueRemoving = removeAll(root, id);
			if (continueRemoving)
			{
				++removedElements;
			}
		}

		return removedElements;
	}

	node* constructBalancedTree(std::string arr[10000], int min, int max)
	{
		if (min == max) return nullptr;

		int median = min + (max - min) / 2;

		return new node(arr[median], constructBalancedTree(arr, min, median), constructBalancedTree(arr, median + 1, max));
	}

	void makeTree(std::string arr[10000], int min, int max)
	{
		root = constructBalancedTree(arr, min, max);
	}

};