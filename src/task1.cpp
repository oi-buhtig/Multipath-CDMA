#include <iostream>
#include "wrappers.h"

using namespace std;

int main(void)
{
	cout << "Task 1\n";

	struct fImageSourceStruct is = fImageSource("testfile.txt", 80);

	vector<int> poly(4,0);
	poly[0] = 1;
	poly[2] = 1;
	poly[3] = 1;
	vector<int> blub = fMSeqGen(poly);
	vector<complex<double> > signal = fDSQPSKModulator(is.bitsOut, blub, 5);

	for ( int i = 0; i < signal.size(); i++)
		cout << signal[i] << endl;

	cout << endl << endl;

 	fImageSink(is.bitsOut, 80, 0, 0);
	return 0;
}