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
	vector<complex<double> > channelIn = fDSQPSKModulator(is.bitsOut, blub, 0);

	cout << endl << endl;

	vector<int> paths(1, 1);
	vector<vector<complex<double> > > totChannelIn;
	totChannelIn.push_back(channelIn);

	vector<int> delay(1,0);
	complex<double> beta0(1.0, 0.0);
	vector<complex<double> > beta(1, beta0);

	vector<struct DOAStruct> DOA;
	double SNR = 40.0;
	vector<vector<double> > array;

	cout << "size= " << totChannelIn[0].size() << endl;
	for (int i = 0; i < totChannelIn[0].size(); i++)
		cout << "no " << i << totChannelIn[0][i] << ", " << endl;

	vector<vector<complex<double> > > channelOut = fChannel(
		paths, totChannelIn, delay, beta, DOA, SNR, array);


	cout << endl << endl;
	for (int i = 0; i < channelOut[0].size(); i++)
		cout << "no " << i << channelOut[0][i] << ", " << endl;
	cout << endl << endl;

	vector<int> res = fDSQPSKDemodulator(channelOut[0], blub, 0);

 	fImageSink(res, 80, 0, 0);
	return 0;
}