#include "wrappers.h"

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
	return imageSource;
}



vector<complex<double> > fDSQPSKModulator(vector<int> bitsIn,
	vector<int> goldseq, int phi)
{
	vector<complex<double> > > out;
	return out;
}



vector<int> fGoldSeq(vector<int> mseq1, vector<int> mseq2, int shift)
{
	vector<int> out;
	return out;
}



vector<int> fMSeqGen(vector<int> coeffs)
{
	vector<int> out;
	return out;
}