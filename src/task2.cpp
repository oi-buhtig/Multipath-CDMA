#include "wrappers.h"
#include <iostream>
#include <time.h>
#include <fstream>
#include <cmath>
#include <cstdlib>

int main(void)
{
	cout << "Task 2\n";

	// initialize the random seed
	srand(time(NULL));

	// read source file
	double phi = 0.0;//1*19 + 2*19; // S is the nineteenth letter in the alphabet
	int fileSize;
	int garbage;
	vector<int> source = fImageSource("../data/im0.jpg", fileSize);
	vector<int> spam1 = fImageSource("../data/im1.jpg", garbage);
	vector<int> spam2 = fImageSource("../data/im2.jpg", garbage);

	// generate gold sequences
	vector<int> pol1(5, 1);
	vector<int> pol2(5, 1);
	pol1[1] = 0;
	pol1[2] = 0;
	pol2[2] = 0;
	pol2[3] = 0;
	vector<int> m1 = fMSeqGen(pol1);
	vector<int> m2 = fMSeqGen(pol2);
	vector<int> goldSeq = fGoldSeq(m1, m2, 2);

	// d >= 1 + (19+19) mod 12 -> d >= 3
	vector<int> goldSeqMAI1 = fGoldSeq(m1, m2, 6);
	vector<int> goldSeqMAI2 = fGoldSeq(m1, m2, 9);
	vector<int> pilotGoldSeq = fGoldSeq(m1, m2, 10);

	// perform the DS-QPSK modulation
	vector<vector<complex<double> > > channelIn;

	// since the signal s1 arrives via three paths, we push it times
	vector<complex<double> > s1 = fDSQPSKModulator(source, goldSeq, phi);
	for (int i = 0; i < 3; i++)
		channelIn.push_back(s1);

	/* since the receiver does not know, which bits are transmitted right
	the start, we send a pilot signal from the same transmitter with a
	different pn-code, sending only 1s. The estimator will then be able
	to estimate the complex betas.
	*/
	vector<complex<double> > pilotSignal(1, complex<double>(1.0,1.0));
	for (int i = 0; i < 3; i++)
		channelIn.push_back(s1);

	// push the MAI-signals
	channelIn.push_back(fDSQPSKModulator(spam1, goldSeqMAI1, phi));
	channelIn.push_back(fDSQPSKModulator(spam2, goldSeqMAI2, phi));

	// set up channel parameters
	vector<int> delay(8, 0);
	delay[3] = delay[0] = (19 + 19) % 4;
	delay[4] = delay[1] = 4 + (19 + 19) % 5;
	delay[5] = delay[2] = 9 + (19 + 19) % 6;
	delay[6] = 8;
	delay[7] = 11;

	vector<complex<double> > beta(8, complex<double>(0.9, 0.0));
	beta[4] = beta[1] = complex<double>(0.8*cos(-3.14159/6), 0.8*sin(-3.14159/6));
	beta[5] = beta[2] = complex<double>(0.7*cos(3.14159/4), 0.7*sin(3.14159/4));
	beta[6] = complex<double>(0.6, 0.0);
	beta[7] = complex<double>(0.5, 0.0);

	vector<struct DOAStruct> DOA;

	double SNR = 40.0;

	vector<vector<double> > array;

	return 0;
}