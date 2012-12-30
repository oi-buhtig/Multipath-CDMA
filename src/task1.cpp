#include <iostream>
#include "wrappers.h"

using namespace std;

int main(void)
{
	cout << "Task 1\n";

	struct fImageSourceStruct is = fImageSource("testfile.txt", 80);

	cout << endl << endl;

 	fImageSink(is.bitsOut, 80, 0, 0);
	return 0;
}