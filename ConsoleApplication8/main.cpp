// newTryHWSDA4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <cstdlib>
#include <string>

#include "BST.h"

using namespace std;

void splitStringToArray(const string &str, char delimeter, string(&command)[3])
{
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

void populateArrayFromFile(char* fileName, string(&allCommands)[10000], int &arrSize)
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
			//dataString = "test";


			cout << "key: *" << key << "* dataSize: *" << dataSize << "* datastring: *";

			dataString[dataSize] = '\0';
			cout << "add successful!" << endl;
			allCommands[arrSize] = to_string(key) + " " + dataString;
			++arrSize;
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
void handleCommand(string line, BST<T> &tree)
{
	string key;
	string data;
	string command[3];

	splitStringToArray(line, ' ', command);

	command[0][command[0].length()] = '\0';
	command[1][command[1].length()] = '\0';
	command[2][command[2].length()] = '\0';

	cout << command[0] << endl;

	key = command[1];
	data = command[2];

	key = key + " " + data;

	data[data.length()] = '\0';

	for (int i = 0; i < data.length(); i++)
	{
		cout << "dataIII: " << data[i];
	}
	cout << endl << endl;


	cout << "data length: " << data.length();

	cout << "command 0 length: " << command[0].length() << endl;

	command[0][command[0].length()] = '\0';


	if (command[0] == "àdd")
	{
		cout << "ADDING" << endl;
		cout << "key: " << key << "data: *" << data << "*" << endl;
		tree.add(key);
	}
	else if (command[0] == "remove")
	{
		cout << "REMOVE!" << endl;
		for (int i = 0; i < key.length(); i++)
		{
			cout << key[i];
		}
		cout << "*" << endl << endl;
		tree.remove(key);
	}
	else if (command[0] == "removeall")
	{
		cout << "REMOVEALL" << endl;
		tree.removeAll(key);
	}
	else if (command[0] == "search")
	{
		cout << "SEARCH" << endl;
		tree.search(key);
	}
	else
	{
		cout << "Unknown command! excepted commands are: add, remove, removall, search" << endl;
	}

	command[0] = '\0';
}

void quickSort(string(&arr)[10000], int left, int right) {
	int i = left, j = right;
	string tmp;
	string pivot = arr[(left + right) / 2];

	/* partition */
	while (i <= j) {
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	};

	/* recursion */
	if (left < j)
		quickSort(arr, left, j);
	if (i < right)
		quickSort(arr, i, right);
}

int main(int argc, char* argv[])
{
	//	D:\Users\Desktop\test.bin

	string allCommands[10000];
	//validateCmdParams(argc, argv);
	char* fileName = argv[1];
	int arrSize = 0;

	populateArrayFromFile("D:\\Users\\Desktop\\test.bin", allCommands, arrSize);

	cout << "arr elements before sort:\n";
	for (int i = 0; i < arrSize; i++)
	{
		cout << allCommands[i] << "*" << endl;
	}
	cout << "END\n";

	quickSort(allCommands, 0, arrSize - 1);

	for (int i = 0; i < arrSize; i++)
	{
		cout << allCommands[i] << "*" << endl;
	}

	BST<string> tree;


	tree.makeTree(allCommands, 0, arrSize);

	string line;

	while (getline(cin, line))
	{
		handleCommand(line, tree);
	}


	system("pause");
	return 0;
}