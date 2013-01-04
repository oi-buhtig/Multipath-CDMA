#include <iostream>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include "wrappers.h"

using namespace std;

vector<vector<complex<double> > > readMatrixFromFile(const char * filename);

int main(int argc, char const *argv[])
{
	// initialization
	if (argc < 2)
	{
		cout << "Not enough arguments provided.\n" << endl;
		return 0;
	}

	// random seed
	srand(time(NULL));
	cout << "Task 4\n";



	// read our matrix from the CSV-file
	vector<vector<complex<double> > > Xmatrix = readMatrixFromFile("../data/Xmatrix.txt");
	
	int phase_shift = 31;
	double phi_mod = 1.326450231515690/360*2*3.14159;

	vector<int> pol1(6, 1);
	vector<int> pol2(6, 1);
	pol1[1] = 0;
	pol1[2] = 0;
	pol1[4] = 0;
	pol2[1] = 0;
	vector<int> m1 = fMSeqGen(pol1);
	vector<int> m2 = fMSeqGen(pol2);
	vector<int> goldSeq = fGoldSeq(m1, m2, phase_shift);

	for (int i = 0; i < goldSeq.size(); i++)
		cout << (1+goldSeq[i])/2;
	cout << endl;

	//struct fChannelEstimationStruct est = fChannelEstimation(Xmatrix, goldSeq, 3);
	struct fChannelEstimationStruct est;
	est.delay_estimate.resize(3, 0);
	est.beta_estimate.resize(3);
	est.beta_estimate[0] = complex<double>(0.406414213735189,0.520782224541765);
	est.beta_estimate[1] = complex<double>(0.283242719038962,0.446950570456580);
	est.beta_estimate[2] = complex<double>(0.444941299571734,0.292659103891727);

	vector<int> sinkBits = fDSQPSKDemodulator(Xmatrix, est, goldSeq, phi_mod);
	fImageSinkNoPilot(sinkBits, argv[1]);

	return 0;
}



vector<vector<complex<double> > > readMatrixFromFile(const char * filename)
{
	/*
	This function reads a complex matrix from CSV-formatted file.
	*/
	ifstream file;
	file.open(filename);
	string line;
	vector<vector<complex<double> > > out;
	int pos, posI, posPlus, posMinus, lastposI;

	while(!file.eof())
	{
		getline(file, line);
		vector<complex<double> > tmp;
		lastposI = -2;
		
		while(true)
		{
			posPlus = line.find("+", lastposI+3);
			posMinus = line.find("-", lastposI+3);

			/*cout << "line" << line;
			cout << "plusp = " << posPlus << endl;
			cout << "minusp = " << posMinus << endl;*/

			if (posPlus != string::npos && posMinus != string::npos)
				pos = posPlus < posMinus ? posPlus : posMinus;
			else if (posPlus == string::npos && posMinus != string::npos)
				pos = posMinus;
			else if (posPlus != string::npos && posMinus == string::npos)
				pos = posPlus;
			else if (posPlus == string::npos && posMinus == string::npos)
				break;

			posI = line.find("i", pos);

			tmp.push_back(
				complex<double>(
				atof((char *)line.substr(lastposI+2, pos-lastposI+2).c_str()),
				atof((char *)line.substr(pos, posI-pos).c_str()))
				);

			lastposI = posI;
		}
		out.push_back(tmp);
	}
	out.resize(out.size()-1);
	return out;
}