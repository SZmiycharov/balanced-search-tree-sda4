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

using namespace std;

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



	system("pause");
	return 0;
}

