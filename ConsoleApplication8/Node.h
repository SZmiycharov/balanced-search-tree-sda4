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

template <typename T>
class Node 
{
public:
	T key;
	int balance;
	Node *leftChild, *rightChild, *parent;

	Node(T k, Node *p);
	~Node();
};

template <typename T>
Node<T>::Node(T k, Node *p)
{
	key = k;
	balance = 0;
	parent = p;
	leftChild = NULL;
	rightChild = NULL;
}

template <typename T>
Node<T>::~Node()
{
	delete leftChild;
	delete rightChild;
}