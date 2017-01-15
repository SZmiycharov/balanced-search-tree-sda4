#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <cstdlib>
#include <string>
#include <algorithm>

void splitStringToArray(const std::string &str, char delimeter, std::string(&arr)[3])
{
	std::stringstream ss;
	ss.str(str);
	std::string item;

	int i = 0;
	while (getline(ss, item, delimeter))
	{
		arr[i] = item;
		++i;
	}
}

bool is_not_digit(char c)
{
	return !isdigit(c);
}

bool numericFirstStringCompare(const std::string s1, const std::string s2)
{
	if (s1 == "" || s2 == "")
	{
		if (s1 == "" && s2 == "") return true;
		else return false;
	}

	std::string::const_iterator it1 = s1.begin(), it2 = s2.begin();

	if (isdigit(s1[0]) && isdigit(s2[0])) {
		int n1, n2;
		std::stringstream ss(s1);
		ss >> n1;
		ss.clear();
		ss.str(s2);
		ss >> n2;

		if (n1 != n2) return n1 < n2;


		it1 = find_if(s1.begin(), s1.end(), is_not_digit);
		it2 = find_if(s2.begin(), s2.end(), is_not_digit);
	}

	return std::lexicographical_compare(it1, s1.end(), it2, s2.end());
}