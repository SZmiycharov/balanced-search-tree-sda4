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

#include "HelperFunctions.h"

template <typename T>
struct node
{
	T key;
	int id;
	std::string data;
	node *left, *right;
	int count;

	node(const T& k, node* l = nullptr, node* r = nullptr, int c = 1);
};

template <typename T>
node<T>::node(const T& k, node* l = nullptr, node* r = nullptr, int c = 1)
{
	key = k;
	left = l;
	right = r;
	count = c;

	std::string keyParts[3];
	splitStringToArray(key, ' ', keyParts);

	assert(istringstream(keyParts[0]) >> id);
	data = keyParts[1];
}