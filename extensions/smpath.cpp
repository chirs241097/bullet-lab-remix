#include <cmath>
#include "smpath.hpp"
smPathSegment::smPathSegment(smvec2d _a,smvec2d _b){a=_a,b=_b;}
smvec2d smPathSegment::getPointOnPath(double rt)
{return a+rt*(b-a);}
double smPathSegment::getPathLength()
{return (a-b).l();}
smPathCircular::smPathCircular(smvec2d _ctr,double _a,double _b,double _r)
{ctr=_ctr,a=_a,b=_b,r=_r;}
smvec2d smPathCircular::getPointOnPath(double rt)
{return smvec2d(ctr.x+r*cos(a+rt*(b-a)),ctr.y+r*sin(a+rt*(b-a)));}
double smPathCircular::getPathLength()
{return fabs(a-b)*r;}
int smPathCollection::pushPath(smPathBase *p){paths[cpaths++]=p;return cpaths-1;}
smPathBase* smPathCollection::getPath(int pid){return paths[pid];}
smvec2d smPathCollection::getPointOnCollection(double rt)
{
	double l=0.,tl=0.;
	int i;
	for(i=0;i<cpaths;++i)l+=paths[i]->getPathLength();
	for(i=0;i<cpaths;++i)
	{
		if(tl+paths[i]->getPathLength()>=l*rt)break;
		tl+=paths[i]->getPathLength();
	}
	return paths[i]->getPointOnPath(rt-tl/l);
}
