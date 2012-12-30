#include "wrappers.h"
#include <fstream>

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

}



struct fImageSourceStruct fImageSource(string filename, int P)
{
	struct fImageSourceStruct imageSource;

	ifstream file;
	file.open(filename);
	vector<char> fileContent;
	char * s = new char[1];

	// read file
	while (!file.eof())
	{
		file.read(s, 1);
		fileContent.push_back(*s);
	}

	// decompose into single bits
	int fileLength = fileContent.size();
	imageSource.bitsOut.resize(fileLength * 8);

	for (int i = 0; i < fileLength; i++)
	{
		int tmp = fileContent[i];
		for (int j = 0; j < 8; j++)
		{
			imageSource.bitsOut[i*8+j] = tmp & 1; //extract last bit
			tmp >> 1;
		}
	}

	/*
	Since it is not possible to read the x, y from pure RGB-data
	they're set to zero.
	*/
	imageSource.x = 0;
	imageSource.y = 0;
	delete s;
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