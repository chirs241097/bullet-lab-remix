// -*- C++ -*-
/*
 * Simple MultimEdia LiTerator(SMELT)
 * by Chris Xiong 2015
 * Path/Curve header & implementation
 *
 * WARNING: This library is in development and interfaces would be very
 * unstable.
 *
 */
#ifndef SMPATH_H
#define SMPATH_H
#include "smmath.hpp"
class smPathBase
{
public:
	virtual smvec2d getPointOnPath(double rt){return smvec2d(0,0);}
	virtual double getPathLength()//default lowres length calculator
	{
		double ret=0;
		for(int i=0;i<63;++i)
		ret+=(getPointOnPath(i/64.)-getPointOnPath((i+1)/64.)).l();
		return ret;
	}
	virtual ~smPathBase(){}
};
class smPathSegment:public smPathBase
{
private:
	smvec2d a,b;
public:
	smPathSegment(smvec2d _a,smvec2d _b);
	smvec2d getPointOnPath(double rt)override;
	double getPathLength()override;
};
class smPathCircular:public smPathBase
{
private:
	smvec2d ctr;
	double a,b,r;
public:
	smPathCircular(smvec2d _ctr,double _a,double _b,double _r);
	smvec2d getPointOnPath(double rt)override;
	double getPathLength()override;
};
class smPathCollection
{
private:
	smPathBase* paths[16];
	int cpaths;
public:
	int pushPath(smPathBase *p);
	smPathBase* getPath(int pid);
	smvec2d getPointOnCollection(double rt);
};
#endif
