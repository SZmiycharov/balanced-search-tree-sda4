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

#include <assert.h>
#include <exception>
#include <stdlib.h>
#include <string>

template <typename T>
class Node
{
public:
	int key;
	T data;
	int subTreeHeight;
	Node<T>* leftChild;
	Node<T>* rightChild;
	Node(int key, T data);

	friend bool operator< (const Node<T> &c1, const Node<T> &c2)
	{
		if (c1.key == c2.key) return c1.data < d2.data;

		return c1.key < c2.key;
	}

	friend bool operator> (const Node<T> &c1, const Node<T> &c2)
	{
		if (c1.key == c2.key) return c1.data > d2.data;

		return c1.key > c2.key;
	}

	friend bool operator== (const Node &c1, const Node &c2)
	{
		return (c1.key == c2.key) && (c1.data == c2.data);
	}
};

template <typename T>
class AVLTree{
public:
	AVLTree();
	Node<T>* add(Node<T>* el, int key);
	bool remove(Node<T>* el, int key, std::string data);
	int search(Node<T>* el, int key, std::string data);
	int removeAll(Node<T>* el, int key);

private:
	int subTreeHeight(Node<T>* el);
	int balanceFactor(Node<T>* el);
	void fixHeight(Node<T>* el);
	Node<T>* rotateRight(Node<T>* el);
	Node<T>* rotateLeft(Node<T>* el);
	Node<T>* balance(Node<T>* el);
	Node<T>* findMin(Node<T>* el);
	Node<T>* removeMin(Node<T>* el);
	Node<T>* root;
};

template <typename T>
Node<T>::Node(int key, T data)
{ 
	key = key; 
	data = data;
	leftChild = rightChild = 0; 
	subTreeHeight = 1; 
}

template <typename T>
AVLTree<T>::AVLTree()
{
	root = new Node<T>(0, "data");
}

template <typename T>
int AVLTree<T>::subTreeHeight(Node<T>* el)
{
	return el ? el->subTreeHeight : 0;
}

template <typename T>
int AVLTree<T>::balanceFactor(Node<T>* el)
{
	return subTreeHeight(el->rightChild) - subTreeHeight(el->leftChild);
}

template <typename T>
void AVLTree<T>::fixHeight(Node<T>* el)
{
	int heightLeftSubTree = subTreeHeight(el->leftChild);
	int heightRightSubTree = subTreeHeight(el->rightChild);
	el->subTreeHeight = (heightLeftSubTree>heightRightSubTree ? heightLeftSubTree : heightRightSubTree) + 1;
}

template <typename T>
Node<T>* AVLTree<T>::rotateRight(Node<T>* el)
{
	Node<T>* q = el->leftChild;
	el->leftChild = q->rightChild;
	q->rightChild = el;
	fixHeight(el);
	fixHeight(q);
	return q;
}

template <typename T>
Node<T>* AVLTree<T>::rotateLeft(Node<T>* el)
{
	Node<T>* p = el->rightChild;
	el->rightChild = p->leftChild;
	p->leftChild = el;
	fixHeight(el);
	fixHeight(p);
	return p;
}

template <typename T>
Node<T>* AVLTree<T>::balance(Node<T>* el)
{
	fixHeight(el);

	assert(balanceFactor(el) == -2 || balanceFactor(el) == 2);

	if (balanceFactor(el) == 2)
	{
		if (balanceFactor(el->rightChild) < 0)
			el->rightChild = rotateRight(el->rightChild);
		return rotateLeft(el);
	}
	else if (balanceFactor(el) == -2)
	{
		if (balanceFactor(el->leftChild) > 0)
			el->leftChild = rotateLeft(el->leftChild);
		return rotateRight(el);
	}

	return el;
}

template <typename T>
Node<T>* AVLTree<T>::add(Node<T>* p, int k)
{
	if (k < p->key)
		p->leftChild = add(p->leftChild, k);
	else
		p->rightChild = add(p->rightChild, k);

	return balance(p);
}

template <typename T>
Node<T>* AVLTree<T>::findMin(Node<T>* el)
{
	return el->leftChild ? findMin(el->leftChild) : el;
}

template <typename T>
Node<T>* AVLTree<T>::removeMin(Node<T>* el)
{
	if (el->leftChild == 0)
	{
		return el->rightChild;
	}
	el->leftChild = removeMin(el->leftChild);
	return balance(el);
}

template <typename T>
bool AVLTree<T>::remove(Node<T>* el, int key, std::string data)
{
	if (!el) return 0;
	if (key < el->key)
		el->leftChild = remove(el->leftChild, key);
	else if (key > el->key)
		el->rightChild = remove(el->rightChild, key);
	else //  key == el->key 
	{
		Node<T>* q = el->leftChild;
		Node<T>* r = el->rightChild;
		delete el;
		if (!r) return q;
		Node<T>* min = findMin(r);
		min->rightChild = removeMin(r);
		min->leftChild = q;
		return balance(min);
	}
	return balance(el);
}

template <typename T>
int AVLTree<T>::search(Node<T>* el, int key, std::string data)
{
	return 5;
}
