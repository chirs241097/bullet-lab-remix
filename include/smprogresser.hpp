// -*- C++ -*-
/*
 * Simple MultimEdia LiTerator(SMELT)
 * by Chris Xiong 2015
 * Progresser header & implementation
 *
 * WARNING: This library is in development and interfaces would be very
 * unstable.
 *
 */
#include "smmath.hpp"
class smProgresserLinear
{
private:
	double a,b,val;
	double elapsed,lim;
	bool done;
public:
	void init(double _a,double _b,double _lim){a=_a;b=_b;lim=_lim;}
	void launch(){elapsed=.0;val=a;done=false;}
	void update(double delta)
	{
		if(elapsed+delta>=lim)return(void)(val=b,elapsed=lim,done=true);
		elapsed+=delta;val=(b-a)*(elapsed/lim)+a;
	}
	bool isDone(){return done;}
	double getValue(){return val;}
	double getPercentage(){return elapsed/lim;}
	double getDelta(){return val-a;}
	double getElapsed(){return elapsed;}
};
class smProgresserCurve
{
private:
	double a,b,val;int cpara;
	double elapsed,lim;
	bool done;
	double transformFunc(double x)
	{
		if(cpara>=64)return sqrt(1-sqr(x-1));
		if(cpara>0)
		{
			double ctrx=(1+sqrt(2*sqr(64-cpara)-1))/2;double ctry=1-ctrx;
			return sqrt(sqr(64-cpara)-sqr(x-ctrx))+ctry;
		}
		if(cpara==0)return x;
		if(cpara<=-64)return -sqrt(1-sqr(x))+1;
		if(cpara<0)
		{
			double ctrx=(1-sqrt(2*sqr(64+cpara)-1))/2;double ctry=1-ctrx;
			return -sqrt(sqr(64+cpara)-sqr(x-ctrx))+ctry;
		}
		return NAN;
	}
public:
	void init(double _a,double _b,double _lim,int _cp){a=_a;b=_b;lim=_lim;cpara=_cp;}
	void launch(){elapsed=.0;val=a;done=false;}
	void update(double delta)
	{
		if(elapsed+delta>=lim)return(void)(val=b,elapsed=lim,done=true);
		elapsed+=delta;val=(b-a)*transformFunc(elapsed/lim)+a;
	}
	bool isDone(){return done;}
	double getValue(){return val;}
	double getPercentage(){return elapsed/lim;}
	double getDelta(){return val-a;}
	double getElapsed(){return elapsed;}
};
