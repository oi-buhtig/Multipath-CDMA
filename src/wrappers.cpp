#include "wrappers.h"
#include <fstream>
#include <cstdlib>
#include <iostream>

vector<int> fDSQPSKDemodulator(vector<int> symbolsIn,
	vector<int> GoldSeq, int phi)
{
	vector<int> out;
	return out;
}



struct fChannelEstimationStruct fChannelEstimation(
	vector<complex<double> > symbolsIn, vector<int>	goldseq)
{
	struct fChannelEstimationStruct channelEstimation;
	return channelEstimation;
}



vector<vector<complex<double> > > fChannel(vector<int> paths,
	vector<vector<complex<int> > > symbolsIn, vector<int> delay,
	vector<int> beta, vector<struct DOAStruct> DOA, double SNR,
	vector<vector<double> > array)
{
	vector<vector<complex<double> > > channel;
	return channel;
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
	vector<complex<double> > out;
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