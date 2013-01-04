#include <iostream>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include "wrappers.h"

using namespace std;

int main(void)
{
	cout << "Task 1\n";

	// initialize the random seed
	srand(time(NULL));



	// task-1a, system simulation starts here
	// read source file
	double phi = 0.0;//1*19 + 2*19; // S is the nineteenth letter in the alphabet
	int fileSize;
	int garbage;
	vector<int> source = fImageSource("../data/t0.txt", fileSize);
	vector<int> spam1 = fImageSource("../data/t1.txt", garbage);
	vector<int> spam2 = fImageSource("../data/t2.txt", garbage);

	/*vector<int> source = fImageSource("../data/im0.jpg", fileSize);
	vector<int> spam1 = fImageSource("../data/im1.jpg", garbage);
	vector<int> spam2 = fImageSource("../data/im2.jpg", garbage);*/

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

	// perform the DS-QPSK modulation
	vector<vector<complex<double> > > channelIn;
	channelIn.push_back(fDSQPSKModulator(source, goldSeq, phi));
	channelIn.push_back(fDSQPSKModulator(spam1, goldSeqMAI1, phi));
	channelIn.push_back(fDSQPSKModulator(spam2, goldSeqMAI2, phi));

	// set up channel parameters
	vector<int> delay;
	delay.push_back(5);
	delay.push_back(8);
	delay.push_back(11);

	complex<double> beta1(0.9, 0.0);
	complex<double> beta2(0.6, 0.0);
	complex<double> beta3(0.5, 0.0);
	vector<complex<double> > beta;
	beta.push_back(beta1);
	beta.push_back(beta2);
	beta.push_back(beta3);

	vector<struct DOAStruct> DOA;
	struct DOAStruct sourceDOA;
	sourceDOA.azimuth = 3.14159/9; // 20 degrees
	sourceDOA.elevation = 0.0;
	DOA.push_back(sourceDOA);

	struct DOAStruct spam1DOA;
	spam1DOA.azimuth = 3.14159/18*7; // 70 degrees
	spam1DOA.elevation = 0.0;
	DOA.push_back(spam1DOA);

	struct DOAStruct spam2DOA;
	spam2DOA.azimuth = 3.14159/3*2; // 120 degrees
	spam2DOA.elevation = 0.0;
	DOA.push_back(spam2DOA);
	
	double SNR = 40.0;
	
	vector<vector<double> > array(5, vector<double>(3,0.0));
	for (int i = 0; i < 5; i++)
	{
		array[i][0] = -cos(3.14159/6) + i*0.5*cos(3.14159/6);
		array[i][1] = -sin(3.14159/6) + i*0.5*sin(3.14159/6);
	}

//dbg
for (int i = 0; i < 3; i++)
	array[0][i] = 0.0;

	// apply signals to the channel
	vector<vector<complex<double> > > channelOut = fChannel(
		channelIn, delay, beta, DOA, SNR, array);

	// point T^_1, system simulation up to the receivers input is completed
	// channel output will therefore be stored in a file ("channelOut.txt")
	ofstream file;
	file.open("channelOut.txt");
	for (int i = 0; i < channelOut.size(); i++)
	{
		file << "SIGNAL VECTOR " << i << endl;
		for (int j = 0; j < channelOut[i].size(); j++)
		{
			file << channelOut[i][j] << endl;
		}
	}



	// task-1b, receiver starts here
	// estimate channel parameters
	struct fChannelEstimationStruct est = fChannelEstimation(channelOut, goldSeq, 1);

	// demodulate signal
	vector<int> sinkBits = fDSQPSKDemodulator(channelOut, est, goldSeq, phi);

	// save file
	fImageSink(sinkBits, "out.txt", fileSize);
	return 0;
}