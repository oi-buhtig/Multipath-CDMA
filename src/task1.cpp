#include <iostream>
#include "wrappers.h"

using namespace std;

int main(void)
{
	cout << "Task 1\n";

	// read source file
	vector<int> source = fImageSource("le.jpg");

	// generate gold sequence
	vector<int> pol1(5, 1);
	vector<int> pol2(5, 1);
	pol1[1] = 0;
	pol1[2] = 0;
	pol2[2] = 0;
	pol2[3] = 0;
	vector<int> goldSeq = fGoldSeq(fMSeqGen(pol1), fMSeqGen(pol2), 0);

	// perform the DS-QPSK modulation
	vector<complex<double> > channelIn1 = fDSQPSKModulator(source, goldSeq, 0.0);

	// apply signal to channel
	vector<int> paths(1, 1);
	vector<int> delay(1, 0);
	complex<double> beta0(1.0, 0.0);
	vector<complex<double> > beta(1, beta0);
	vector<struct DOAStruct> DOA;
	double SNR = 40.0;
	vector<vector<double> > array;
	vector<vector<complex<double> > > totChannelIn(1, channelIn1);
	vector<vector<complex<double> > > channelOut = fChannel(
		paths, totChannelIn, delay, beta, DOA, SNR, array);

	// estimate channel parameters
	struct fChannelEstimationStruct est = fChannelEstimation(channelOut, goldSeq);

	// demodulate signal
	vector<int> sinkBits = fDSQPSKDemodulator(channelOut, est, goldSeq, 0.0);

	// save file
	fImageSink(sinkBits, "out.jpg");
	return 0;
}