#include <cmath>
#include "smpath.hpp"
smPathSegment::smPathSegment(smvec2d _a,smvec2d _b){a=_a,b=_b;}
smvec2d smPathSegment::getPointOnPath(double percentage)
{return a+percentage*(b-a);}
double smPathSegment::getPathLength()
{return (a-b).l();}
smPathCircular::smPathCircular(smvec2d _ctr,double _a,double _b,double _r)
{ctr=_ctr,a=_a,b=_b,r=_r;}
smvec2d smPathCircular::getPointOnPath(double percentage)
{return smvec2d(ctr.x+r*cos(a+percentage*(b-a)),ctr.y+r*sin(a+percentage*(b-a)));}
double smPathCircular::getPathLength()
{return fabs(a-b)*r;}
