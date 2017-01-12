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
template <class T>
class AVLTree 
{
public:
	AVLTree();
	~AVLTree();
	bool add(T key);
	void remove(const T key);

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

template <class T>
AVLTree<T>::AVLTree()
{
	root = NULL;
}

template <class T>
AVLTree<T>::~AVLTree() 
{
	delete root;
}

template <class T>
bool AVLTree<T>::add(T key)
{
	if (root == NULL)
	{
		root = new Node<T>(key, NULL);
	}
	else
	{
		Node<T> *n = root;
		Node<T> *parent;

		while (true)
		{
			if (n->key == key) return false;

			parent = n;

			bool goLeft = n->key > key;
			n = goLeft ? n->leftChild : n->rightChild;

			if (n == NULL)
			{
				if (goLeft)
				{
					parent->leftChild = new Node<T>(key, parent);
				}
				else
				{
					parent->rightChild = new Node<T>(key, parent);
				}

				rebalance(parent);
				break;
			}
		}
	}

	return true;
}

template <class T>
void AVLTree<T>::remove(const T delKey)
{
	if (root == NULL) return;

	Node<T> *n = root;
	Node<T> *parent = root;
	Node<T> *delNode = NULL;
	Node<T> *child = root;

	while (child != NULL)
	{
		parent = n;
		n = child;
		child = delKey >= n->key ? n->rightChild : n->leftChild;
		if (delKey == n->key) delNode = n;
	}

	if (delNode != NULL)
	{
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
}

template <class T>
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

template <class T>
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

template <class T>
Node<T>* AVLTree<T>::rotateLeftThenRight(Node<T> *n)
{
	n->leftChild = rotateLeft(n->leftChild);
	return rotateRight(n);
}

template <class T>
Node<T>* AVLTree<T>::rotateRightThenLeft(Node<T> *n)
{
	n->rightChild = rotateRight(n->rightChild);
	return rotateLeft(n);
}

template <class T>
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

template <class T>
int AVLTree<T>::height(Node<T> *n) 
{
	if (n == NULL) return -1;

	return height(n->leftChild) >= height(n->rightChild) ? 
		height(n->leftChild) + 1 : height(n->rightChild) + 1;
}

template <class T>
void AVLTree<T>::setBalance(Node<T> *n) {
	n->balance = height(n->rightChild) - height(n->leftChild);
}







