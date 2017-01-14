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

#include <algorithm>
#include <iostream>

#include "Node.h"

/* AVL tree */
template <typename T>
class AVLTree 
{
public:
	AVLTree();
	~AVLTree();
	void add(const int key, T data);
	void remove(const int key, T data);
	int removeAll(const int key);
	void search(const int key, T data);

private:
	Node<T> *root;

	Node<T>* rotateLeft(Node<T> *a);
	Node<T>* rotateRight(Node<T> *a);
	Node<T>* rotateLeftThenRight(Node<T> *n);
	Node<T>* rotateRightThenLeft(Node<T> *n);
	void rebalance(Node<T> *n);
	int height(Node<T> *n);
	void setBalance(Node<T> *n);
};

template <typename T>
AVLTree<T>::AVLTree()
{
	root = NULL;
}

template <typename T>
AVLTree<T>::~AVLTree() 
{
	delete root;
}

template <typename T>
void AVLTree<T>::add(const int key, T data)
{
	if (root == NULL)
	{
		root = new Node<T>(key, NULL, data);
	}
	else if (root->key == key && root->data == data)
	{
		root->count++;
		return;
	}
	else
	{
		Node<T> *n = root;
		Node<T> *parent;

		while (true)
		{
			parent = n;

			bool goLeft = n->key > key || (n->key == key && n->data > data);
			n = goLeft ? n->leftChild : n->rightChild;

			
			if (n != NULL && n->key == key && n->data == data)
			{
				n->count++;
				return;
			}

			if (n == NULL)
			{
				if (goLeft)
				{
					parent->leftChild = new Node<T>(key, parent, data);
				}
				else
				{
					parent->rightChild = new Node<T>(key, parent, data);
				}

				rebalance(parent);
				break;
			}
		}
	}

}

template <typename T>
void AVLTree<T>::remove(const int delKey, T data)
{
	if (root == NULL)
	{
		cout << "false" << endl;
		return;
	}

	Node<T> *n = root;
	Node<T> *parent = root;
	Node<T> *delNode = NULL;
	Node<T> *child = root;

	while (child != NULL)
	{
		parent = n;
		n = child;
		child = (delKey >= n->key && data >= n->data) ? n->rightChild : n->leftChild;
		if (delKey == n->key && data == n->data)
		{
			delNode = n;
			if (n->count > 1)
			{
				n->count--;
				cout << "true" << endl;
				return;
			}

			break;
		}
	}

	if (delNode != NULL)
	{
		cout << "true" << endl;
		delNode->key = n->key;

		child = n->leftChild != NULL ? n->leftChild : n->rightChild;

		if (root->key == delKey && root->data == data)
		{
			root = child;
		}
		else
		{
			if (parent->leftChild == n)
			{
				parent->leftChild = child;
			}
			else
			{
				parent->rightChild = child;
			}

			rebalance(parent);
		}
	}
	else
	{
		cout << "false" << endl;
	}
}

template <typename T>
int AVLTree<T>::removeAll(const int delKey)
{
	int nodesRemoved = 0;

	if (root == NULL)
	{
		return nodesRemoved;
	}

	Node<T> *n = root;
	Node<T> *parent = root;
	Node<T> *delNode = NULL;
	Node<T> *child = root;
	bool toContinue = true;

	while (toContinue)
	{
		toContinue = false;
		while (child != NULL)
		{
			parent = n;
			n = child;
			child = delKey >= n->key ? n->rightChild : n->leftChild;
			if (delKey == n->key)
			{
				delNode = n;
				break;
			}
		}

		if (delNode != NULL)
		{
			toContinue = true;
			nodesRemoved += delNode->count;
			cout << "delnode key: " << delNode->key << "; data: " << delNode->data << "; count : " << delNode->count << endl;
			delNode->key = n->key;

			child = n->leftChild != NULL ? n->leftChild : n->rightChild;

			if (root->key == delKey)
			{
				root = child;
			}
			else
			{
				if (parent->leftChild == n)
				{
					parent->leftChild = child;
				}
				else
				{
					parent->rightChild = child;
				}

				rebalance(parent);
			}
		}
		else
		{
			return nodesRemoved;
		}

		n = root;
		parent = root;
		delNode = NULL;
		child = root;
	}

	return nodesRemoved;
}

template <typename T>
void AVLTree<T>::search(const int key, T data)
{
	if (root == NULL)
	{
		cout << "false" << endl;
		return;
	}

	Node<T> *n = root;
	Node<T> *parent = root;
	Node<T> *child = root;

	while (child != NULL)
	{
		parent = n;
		n = child;
		child = key > n->key ? n->rightChild : n->leftChild;
		if (key == n->key && data == n->data)
		{
			cout << "true" << endl;
			return;
		}
	}

	cout << "false" << endl;
}


template <typename T>
Node<T>* AVLTree<T>::rotateLeft(Node<T> *a)
{
	Node<T> *b = a->rightChild;
	b->parent = a->parent;
	a->rightChild = b->leftChild;

	if (a->rightChild != NULL)
	{
		a->rightChild->parent = a;
	}

	b->leftChild = a;
	a->parent = b;

	if (b->parent != NULL)
	{
		if (b->parent->rightChild == a)
		{
			b->parent->rightChild = b;
		}
		else
		{
			b->parent->leftChild = b;
		}
	}

	setBalance(a);
	setBalance(b);
	return b;
}

template <typename T>
Node<T>* AVLTree<T>::rotateRight(Node<T> *a)
{
	Node<T> *b = a->leftChild;
	b->parent = a->parent;
	a->leftChild = b->rightChild;

	if (a->leftChild != NULL)
	{
		a->leftChild->parent = a;
	}

	b->rightChild = a;
	a->parent = b;

	if (b->parent != NULL) {
		if (b->parent->rightChild == a)
		{
			b->parent->rightChild = b;
		}
		else
		{
			b->parent->leftChild = b;
		}
	}

	setBalance(a);
	setBalance(b);
	return b;
}

template <typename T>
Node<T>* AVLTree<T>::rotateLeftThenRight(Node<T> *n)
{
	n->leftChild = rotateLeft(n->leftChild);
	return rotateRight(n);
}

template <typename T>
Node<T>* AVLTree<T>::rotateRightThenLeft(Node<T> *n)
{
	n->rightChild = rotateRight(n->rightChild);
	return rotateLeft(n);
}

template <typename T>
void AVLTree<T>::rebalance(Node<T> *n) 
{
	setBalance(n);

	if (n->balance == -2) 
	{
		if (height(n->leftChild->leftChild) >= height(n->leftChild->rightChild))
		{
			n = rotateRight(n);
		}
		else
		{
			n = rotateLeftThenRight(n);
		}
	}
	else if (n->balance == 2) 
	{
		if (height(n->rightChild->rightChild) >= height(n->rightChild->leftChild))
		{
			n = rotateLeft(n);
		}
		else
		{
			n = rotateRightThenLeft(n);
		}	
	}

	if (n->parent != NULL) 
	{
		rebalance(n->parent);
	}
	else 
	{
		root = n;
	}
}

template <typename T>
int AVLTree<T>::height(Node<T> *n) 
{
	if (n == NULL) return -1;

	return height(n->leftChild) >= height(n->rightChild) ? 
		height(n->leftChild) + 1 : height(n->rightChild) + 1;
}

template <typename T>
void AVLTree<T>::setBalance(Node<T> *n) 
{
	n->balance = height(n->rightChild) - height(n->leftChild);
}







