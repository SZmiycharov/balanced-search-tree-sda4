// newTryHWSDA4.cpp : Defines the entry point for the console application.
//


#include "BST.h"

using namespace std;

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
			dataString[dataSize] = '\0';
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
void handleCommand(std::string line, BST<T> &tree)
{
	int id;
	std::string data;
	std::string command[3];

	splitStringToArray(line, ' ', command);

	//make sure all strings are terminated
	command[0][command[0].length()] = '\0';
	command[1][command[1].length()] = '\0';
	command[2][command[2].length()] = '\0';

	if (command[0] != "add" && command[0] != "remove" && command[0] != "removeall" && command[0] != "search")
	{
		cout << "Unknown command! Accepted commands are: add, remove, removeall, search!" << endl;
		return;
	}

	assert(istringstream(command[1]) >> id);
	data = command[2];

	std::string key = to_string(id) + " " + data;

	data[data.length()] = '\0';

	if (command[0] == "add")
	{
		tree.add(key);
	}
	else if (command[0] == "remove")
	{
		tree.removeByKey(key);
	}
	else if (command[0] == "removeall")
	{
		bool removed = false;
		int deletedElements = 0;
		cout << tree.removeAllByID(id) << endl;
	}
	else if (command[0] == "search")
	{
		tree.search(key);
	}
	
	command[0] = '\0';
}

void quickSort(std::string(&arr)[10000], int left, int right) {
	int i = left, j = right;
	std::string tmp;
	std::string pivot = arr[(left + right) / 2];

	while (i <= j) 
	{
		while (arr[i] < pivot) i++;
		while (arr[j] > pivot) j--;

		if (i <= j) 
		{
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	}

	if (left < j)
		quickSort(arr, left, j);
	if (i < right)
		quickSort(arr, i, right);
}

int main(int argc, char* argv[])
{
	//	D:\Users\Desktop\test.bin
	//make sure we are given file from cmd to read entries from
	validateCmdParams(argc, argv);

	std::string allCommands[10000];
	
	char* fileName = argv[1];
	int arrSize = 0;

	//get all entries from file and populate array with keys (id + ' ' + data)
	populateArrayFromFile(fileName, allCommands, arrSize);

	//sort entry elements to be ready for insertion in tree
	quickSort(allCommands, 0, arrSize - 1);

	BST<std::string> tree;
	tree.constructPerfectlyBalancedTree(allCommands, 0, arrSize);

	std::string line;

	while (getline(cin, line))
	{
		handleCommand(line, tree);
	}

	system("pause");
	return 0;
}