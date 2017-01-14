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
	int key;
	int balance;
	int count;
	T data;
	Node *leftChild, *rightChild, *parent;

	Node(int k, Node *p, T d);
	~Node();
};

template <typename T>
Node<T>::Node(int k, Node *p, T d)
{
	key = k;
	balance = 0;
	parent = p;
	data = d;
	leftChild = NULL;
	rightChild = NULL;
	count = 1;
}

template <typename T>
Node<T>::~Node()
{
	delete leftChild;
	delete rightChild;
}