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

void writeToFile(int key, int dataSize, char* data, char* fileName)
{
	std::fstream writeFile;

	writeFile.open(fileName, std::fstream::binary | std::fstream::app);

	if (writeFile.is_open())
	{
		writeFile.write((char*)&key, sizeof(key));
		writeFile.write((char*)&dataSize, sizeof(dataSize));
		writeFile.write(data, sizeof(char)*dataSize);
	}
	else
	{
		cout << "FAIL!!" << endl;
	}

	writeFile.close();
}

template <typename T>
void readFromFile(char* fileName, AVLTree<T> &tree)
{
	std::fstream readFile;

	int key;
	int dataSize;

	readFile.open(fileName, std::ios_base::binary | std::ios_base::in);
	if (readFile.is_open())
	{
		while (readFile.read((char*)&key, 4))
		{
			readFile.read((char*)&dataSize, 4);

			char* dataString = new char[dataSize];
			readFile.read(dataString, dataSize);

			cout << "key: " << key << " dataSize: " << dataSize << " datastring: ";
			for (int i = 0; i < dataSize; i++)
			{
				cout << dataString[i];
			}
			cout << endl;

			tree.add(key);
		}
	}
	else
	{
		cerr << "Unable to open file " << fileName << "\n";
		exit(EXIT_FAILURE);
	}
}

void validateCmdParams(int argc, char* argv[])
{
	if (argc != 2)
	{
		cerr << "Usage: " << argv[0] << " <fileName>" << "\n";
		system("pause");
		exit(EXIT_FAILURE);
	}
}

template <typename T>
void handleCommand(string line, AVLTree<T> &tree)
{
	int key;
	string data;
	string command[3];

	splitStringToArray(line, ' ', command);
	//cout << command[0] << endl;
		
	assert(istringstream(command[1]) >> key);
	data = command[2];

	if (command[0] == "àdd")
	{
		tree.add(key);
	}
	else if (command[0] == "remove")
	{
		tree.remove(key);
	}
	else if (command[0] == "removeall")
	{
		tree.removeAll(key);
	}
	else if (command[0] == "search")
	{
		tree.search(key);
	}

	command[0] = '\0';
}

int main(int argc, char* argv[])
{
	//
	//test.bin contains keys: 1, 2, 5, 3, 4, 6
	//

	validateCmdParams(argc, argv);

	char* fileName = argv[1];

	string line;
	AVLTree<int> tree;

	readFromFile(fileName, tree);

	tree.remove(5);
	tree.remove(2);
	tree.remove(2);

	while (getline(cin, line))
	{
		handleCommand(line, tree);
	}

	system("pause");
	return 0;
}

