#include <iostream>
#include <fstream>
#include "utils.h"

using namespace std;

int main(int argc, char const *argv[])
{
	// initialize
	if (argc < 2)
	{
		cout << "No argument provided.\n";
		return 0;
	}

	int fileSize = filesize(argv[1]);
	char * buffer = new char[fileSize];

	ifstream inFile;
	inFile.open(argv[1]);
	inFile.read(buffer, fileSize);
	inFile.close();

	stringstream strHeader;
	strHeader << argv[1];
	strHeader << ".header";

	stringstream strData;
	strData << argv[1];
	strData << ".data";

	ofstream outFileHeader;
	outFileHeader.open((char*)strHeader.str().c_str());
	outFileHeader.write(buffer, 54);
	outFileHeader.close();

	ofstream outFileData;
	outFileData.open((char*)strData.str().c_str());
	outFileData.write(buffer+54, fileSize-54);
	outFileData.close();

	return 0;
}