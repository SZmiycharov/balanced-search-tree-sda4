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

#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <cstdlib>
#include <string>
#include "AVLTree.h"

using namespace std;

void splitStringToArray(const string &str, char delimeter, string(&command)[3]) {
	stringstream ss;
	ss.str(str);
	string item;

	int i = 0;
	while (getline(ss, item, delimeter)) 
	{
		command[i] = item;
		++i;
	}
}

template <typename T>
void handleAddCommand(int key, string data, AVLTree<T> &tree)
{
	int key;
	assert(istringstream(command[1]) >> key);
	string data = command[2];

	tree.add(key, data);
}

template <typename T>
void handleRemoveCommand(int key, string data, AVLTree<T> &tree)
{
	int key;
	assert(istringstream(command[1]) >> key);
	string data = command[2];

	tree.remove(key, data);
}

template <typename T>
void handleRemoveAllCommand(int key, AVLTree<T> &tree)
{
	tree.removeAll(key);
}

template <typename T>
void handleSearchCommand(int key, string data, AVLTree<T> &tree)
{


}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cerr << "Usage: " << argv[0] << " <fileName>" << "\n";
		system("pause");
		exit(EXIT_FAILURE);
	}

	char* fileName = argv[1];

	ifstream fileCommands(fileName);

	if (fileCommands.is_open())
	{
		string data;
		int key;

		while (fileCommands >> key >> data)
		{
			cout << key << " " << data << endl;
		}


		fileCommands.close();
	}
	else
	{
		cerr << "Unable to open file " << fileName << "\n";
		exit(EXIT_FAILURE);
	}

	string command[3];
	string line;
	int key;
	string data;
	AVLTree<string> tree;

	while (getline(cin, line))
	{
		splitStringToArray(line, ' ', command);
		cout << command[0] << endl;
		
		assert(istringstream(command[1]) >> key);
		data = command[2];
		Node<string>* el;

		if (command[0] == "àdd")
		{
			//tree.add(el, 1);
		}
		else if (command[0] == "remove")
		{
			//tree.remove(key, data);
		}
		else if (command[0] == "removeall")
		{
			//tree.removeAll(key);
		}
		else if (command[0] == "search")
		{
			//tree.search(key, data);
		}

		command[0] = '\0';
	}


	system("pause");
	return 0;
}

