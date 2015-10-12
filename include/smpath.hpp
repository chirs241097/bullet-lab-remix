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
	virtual smvec2d getPointOnPath(double percentage);
	virtual double getPathLength();
	virtual ~smPathBase(){};
};
class smPathSegment:public smPathBase
{
private:
	smvec2d a,b;
public:
	smPathSegment(smvec2d _a,smvec2d _b);
	smvec2d getPointOnPath(double percentage);
	double getPathLength();
};
class smPathCircular:public smPathBase
{
private:
	smvec2d ctr;
	double a,b,r;
public:
	smPathCircular(smvec2d _ctr,double _a,double _b,double _r);
	smvec2d getPointOnPath(double percentage);
	double getPathLength();
};
class smPathCollection
{
private:
	smPathBase* paths[16];
public:
};
#endif
