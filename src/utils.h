#pragma once

#include <fstream>
#include <cstdlib>
#include <cmath>
#include <complex>

using namespace std;

// help function to get file size. From stackoverflow.com.
std::ifstream::pos_type filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::in | std::ifstream::binary);
    in.seekg(0, std::ifstream::end);
    return in.tellg(); 
}

/* returns a complex random number whose real- and imag parts are
normally distributed */ 
complex<double> whiteGaussianNoise(double mean, double stdDev)
{
	/*
	this function uses the Box-Muller Method to produce
	two normal randoms by using to uniform randoms.
	The algorithm is described on
	http://www.dspguru.com/dsp/howtos/how-to-generate-white-gaussian-noise
	*/

	double u1;
	double u2;
	double v1, v2, s;
	do
	{
		u1 = rand();
		u1 /= RAND_MAX;

		u2 = rand();
		u2/= RAND_MAX;

		v1 = 2*u1 - 1;
		v2 = 2*u2 - 1;

		s =v1*v1 + v2*v2;
	} while (s>=1.0);

	return complex<double>(
		mean+stdDev*sqrt(-2*log(s)/s)*v1,
		mean+stdDev*sqrt(-2*log(s)/s)*v2);
}