#include "wrappers.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

vector<int> fDSQPSKDemodulator(vector<complex<double> > symbolsIn,
	vector<int> GoldSeq, int phi)
{
	vector<int> out;
	int outLength = 2 * symbolsIn.size() / GoldSeq.size();
	out.resize(outLength);

	for (int i = 0; i < outLength/2; i++)
	{
		// compute the average real and imaginary part
		complex<double> sum(0.0,0.0);
		for (int k = 0; k < GoldSeq.size(); k++)
		{
			complex<double> pmVal(GoldSeq[k],0.0);
			sum += symbolsIn[i*GoldSeq.size()+k] * pmVal;
		}
		double evenAv = sum.real() / GoldSeq.size();
		double oddAv = sum.imag() / GoldSeq.size();

		// decide for the one with the lowest distance
		if ((evenAv-1.0)*(evenAv-1.0) < (evenAv+1.0)*(evenAv+1.0))
			out[2*i] = 1;
		else
			out[2*i] = 0;

		if ((oddAv-1.0)*(oddAv-1.0) < (oddAv+1.0)*(oddAv+1.0))
			out[2*i+1] = 1;
		else
			out[2*i+1] = 0;
	}

	return out;
}



struct fChannelEstimationStruct fChannelEstimation(
	vector<complex<double> > symbolsIn, vector<int>	goldseq)
{
	struct fChannelEstimationStruct channelEstimation;
	return channelEstimation;
}



vector<vector<complex<double> > > fChannel(vector<int> paths,
	vector<vector<complex<double> > > symbolsIn, vector<int> delay,
	vector<complex<double> > beta, vector<struct DOAStruct> DOA, double SNR,
	vector<vector<double> > array)
{
  	// make random generator engine
  	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  	std::default_random_engine generator (seed);
	
	double stdDev = 1.0; // to be adjusted
	normal_distribution<double> derGauss(0.0, stdDev);

	vector<vector<complex<double> > > out;

	// find length of longest message
	int longestMsg = 0;
	for (int i = 0; i < symbolsIn.size(); i++)
		if (symbolsIn[i].size() > longestMsg) longestMsg = symbolsIn[i].size();

	// find maximum delay
	int maxDelay = 0;
	for (int i = 0; i < delay.size(); i++)
		if (delay[i] > maxDelay) maxDelay = delay[i];

	// for now, we'll be operating with one output
	int outLength = longestMsg;
	int nInputs = symbolsIn.size(); // number of inputs
	out.resize(1);
	out[0].resize(outLength);

	for (int i = 0; i < outLength; i++)
	{
		out[0][i] = complex<double>(0.0,0.0);
		for (int k = 0; k < nInputs; i++)
		{
			out[0][i] += beta[k]*symbolsIn[k][(i+delay[k]) % outLength];
		}
		double noise;
		noise = derGauss(generator);
		complex<double> cNoise(noise, 0.0);
		out[0][i] += cNoise;
	}

	return out;
}



void fImageSink(vector<int> bitsIn, int Q, int x, int y)
{
	ofstream file;
	char * filename = "out.txt"; // name under which file will be stored
	int fileSize = Q/8;
	char * buffer = new char[fileSize];
	for (int i = 0; i < fileSize; i++)
	{
		char tmp = 0;
		for (int j = 0; j < 7; j++)
		{
			tmp += bitsIn[i*8+j];
			tmp = tmp << 1;
		}
		tmp += bitsIn[i*8+7];
		buffer[i] = tmp;
	}

	file.open(filename);
	file.write(buffer, fileSize);
	file.close();
}



struct fImageSourceStruct fImageSource(string filename, int P)
{
	struct fImageSourceStruct imageSource;

	ifstream file;
	file.open((char *)filename.c_str());
	int bufferSize = P/8;
	char * buffer = new char[bufferSize];
	int i = 0;
	// read file
	while (!file.eof())
	{
		file >> buffer[i++];
		if (i >= bufferSize) break;
	}

	file.close();

	for (; i < bufferSize; i++)
		buffer[i] = 0;

	// decompose into single bits
	imageSource.bitsOut.resize(P);
	for (int i = 0; i < bufferSize; i++)
	{
		char tmp = buffer[i];
		cout << tmp << endl;
		for (int j = 0; j < 8; j++)
		{
			if (tmp & (1 << (7-j))) imageSource.bitsOut[i*8+j] = 1;
			else imageSource.bitsOut[i*8+j] = 0;
			//imageSource.bitsOut[i*8+j] = tmp & 1; //extract last bit
			//tmp = tmp >> 1;
		}
	}

	// padd with zeros
	if (P > 8*bufferSize)
		for (int i = 8*bufferSize; i < P; i++)
			imageSource.bitsOut[i] = 0;

	/*
	Since it is not possible to read the x, y from pure RGB-data,
	they're set to zero.
	*/
	imageSource.x = 0;
	imageSource.y = 0;
	return imageSource;
}



vector<complex<double> > fDSQPSKModulator(vector<int> bitsIn,
	vector<int> goldseq, int phi)
{
	// imaginary unit
	complex<double> j(0.0,1.0);

	int inLength = bitsIn.size();
	vector<complex<double> > tmp(inLength/2 + inLength%2, 0);

	int outLength = tmp.size() * goldseq.size();
	vector<complex<double> > out(outLength, 0);

	// create new bit vector
	// move odd bits to imaginary part, even bits to real part
	for (int i = 0; i < inLength; i++)
	{
		if (!bitsIn[i]) bitsIn[i] = -1;
		complex<double> bit(bitsIn[i],0.0);
		if (i%2) tmp[i/2] += j*bit;
		else tmp[i/2] += bit;
	}

	complex<double> phase(cos(phi*2*3.14159/360),sin(phi*2*3.14159/360));

	// spread with pn-code and multiply with exp(j*phi)
	for (int i = 0; i < outLength; i++)
	{
		complex<double> pnVal(goldseq[i%goldseq.size()], 0.0);
		out[i] = phase * tmp[i/goldseq.size()] * pnVal;
	}
	return out;
}



vector<int> fGoldSeq(vector<int> mseq1, vector<int> mseq2, int shift)
{
	vector<int> out;
	int N_c = mseq1.size();
	out.resize(N_c);

	for(int i = 0; i < N_c; i++)
		out[i] = (mseq1[i] + mseq2[(i+shift) % N_c]) % 2;
	return out;
}



vector<int> fMSeqGen(vector<int> coeffs)
{
	vector<int> out;
	int m = coeffs.size() - 1;

	// Compute N_c = 2^m - 1
	int N_c = 1;
	for (int i = 0;  i < m; i++)
		N_c *= 2;
	N_c--;

	out.resize(N_c);

	// init shift registers with 1s
	vector<int> shiftRegs;
	shiftRegs.resize(m);
	for (int i = 0; i < m; i++)
		shiftRegs[i] = 1;

	int adderOut;

	// enter the loop
	for (int i = 0; i < N_c; i++)
	{
		out[i] = 1-2*shiftRegs[m-1];
		adderOut = 0;
		for (int j = m-1; j > 0; j--)
		{
			if (coeffs[j+1]) adderOut += shiftRegs[j];
			shiftRegs[j] = shiftRegs[j-1];
		}
		adderOut %= 2;
		shiftRegs[0] = adderOut;
	}

	return out;
}