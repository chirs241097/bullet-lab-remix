// -*- C++ -*-
/*
 * Simple MultimEdia LiTerator(SMELT)
 * by Chris Xiong 2015
 * Random engine header & implementation
 *
 * WARNING: This library is in development and interfaces would be very
 * unstable.
 *
 */
class smRandomEngine
{
private:
	unsigned int cseed;
public:
	void setSeed(unsigned int seed){cseed=seed;}
	int nextInt(int min,int max)
	{
		if (min>max){int t=min;min=max;max=t;}
		cseed*=214013;cseed+=2531011;
		return min+(cseed^cseed>>15)%(max-min+1);
	}
	double nextDouble(double min,double max)
	{
		if (min>max){double t=min;min=max;max=t;}
		cseed*=214013;cseed+=2531011;
		return min+(cseed>>16)*(1.0f/65535.0f)*(max-min);
	}
};
