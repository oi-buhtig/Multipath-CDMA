#pragma once

#include <vector>
#include <complex>

using namespace std;

vector<int> fDSQPSKDemodulator(vector<complex<double> > symbolsIn,
	vector<int> GoldSeq, int phi);


struct fChannelEstimationStruct
{
	vector<int> delay_estimate;
	vector<int> DOA_estimate;
	vector<int> beta_estimate;
};

struct fChannelEstimationStruct fChannelEstimation(
	vector<complex<double> > symbolsIn, vector<int>	goldseq);


struct DOAStruct
{
	int azimuth;
	int elevation;
};

vector<vector<complex<double> > > fChannel(vector<int> paths,
	vector<vector<complex<double> > > symbolsIn, vector<int> delay,
	vector<complex<double> > beta, vector<struct DOAStruct> DOA, double SNR,
	vector<vector<double> > array);

void fImageSink(vector<int> bitsIn, int Q, int x, int y);

struct fImageSourceStruct
{
	vector<int> bitsOut;
	int x;
	int y;
};

struct fImageSourceStruct fImageSource(string filename, int P);

vector<complex<double> > fDSQPSKModulator(vector<int> bitsIn,
	vector<int> goldseq, int phi);

vector<int> fGoldSeq(vector<int> mseq1, vector<int> mseq2, int shift);

vector<int> fMSeqGen(vector<int> coeffs);