/*
This tool takes a windows bitmap header and the corresponding RGB-data,
each in form of a file, and merges them to a valid windows bitmap file.
*/

#include <iostream>
#include "utils.h"
#include <fstream>

using namespace std;

int main(int argc, char const *argv[])
{
	// initialize
	if (argc < 4)
	{
		cout << "Not enough arguments provided.\n";
		return 0;
	}

	int fileSize = filesize(argv[3]) + 54;
	char * buffer = new char[fileSize];

	ifstream inHeader;
	inHeader.open(argv[2]);
	inHeader.read(buffer, 54);
	inHeader.close();

	ifstream inData;
	inData.open(argv[3]);
	inData.read(buffer+54, fileSize-54);
	inData.close();

	ofstream out;
	out.open(argv[1]);
	out.write(buffer, fileSize);
	out.close();

	return 0;
}