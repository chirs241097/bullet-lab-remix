// -*- C++ -*-
/*
 * Simple MultimEdia LiTerator(SMELT)
 * by Chris Xiong 2015
 * Color system header & implementation
 *
 * WARNING: This library is in development and interfaces would be very
 * unstable.
 *
 */
#ifndef SMCOLOR_H
#define SMCOLOR_H
#include "smelt.hpp"
#include "smmath.hpp"
#define clmp(a) a=a>1?1:a<0?0:a
class smColorRGBA
{
public:
	float r,g,b,a;
	smColorRGBA(){r=g=b=a=.0;}
	smColorRGBA(DWORD col){setHWColor(col);}
	smColorRGBA(float _r,float _g,float _b,float _a){r=_r;g=_g;b=_b;a=_a;}
	void clamp(){clmp(r);clmp(g);clmp(b);clmp(a);}
	friend smColorRGBA operator +(smColorRGBA a,smColorRGBA b){return smColorRGBA(a.r+b.r,a.g+b.g,a.b+b.b,a.a+b.a);}
	friend smColorRGBA operator -(smColorRGBA a,smColorRGBA b){return smColorRGBA(a.r-b.r,a.g-b.g,a.b-b.b,a.a-b.a);}
	friend smColorRGBA operator *(smColorRGBA a,smColorRGBA b){return smColorRGBA(a.r*b.r,a.g*b.g,a.b*b.b,a.a*b.a);}
	friend smColorRGBA operator *(smColorRGBA a,float b){return smColorRGBA(b*a.r,b*a.g,b*a.b,b*a.a);}
	friend smColorRGBA operator /(smColorRGBA a,float b){return smColorRGBA(a.r/b,a.g/b,a.b/b,a.a/b);}
	void setHWColor(DWORD col){a=GETA(col)/255.;r=GETR(col)/255.;g=GETG(col)/255.;b=GETB(col)/255.;}
	DWORD getHWColor(){clamp();return RGBA(r,g,b,a);}
};
class smColorHSVA
{
public:
	float h,s,v,a;
	smColorHSVA(){h=s=v=a=.0;}
	smColorHSVA(DWORD col){setHWColor(col);}
	smColorHSVA(float _h,float _s,float _v,float _a){h=_h;s=_s;v=_v;a=_a;}
	void clamp(){clmp(h);clmp(s);clmp(v);clmp(a);}
	friend smColorHSVA operator +(smColorHSVA a,smColorHSVA b){return smColorHSVA(a.h+b.h,a.s+b.s,a.v+b.v,a.a+b.a);}
	friend smColorHSVA operator -(smColorHSVA a,smColorHSVA b){return smColorHSVA(a.h-b.h,a.s-b.s,a.v-b.v,a.a-b.a);}
	friend smColorHSVA operator *(smColorHSVA a,smColorHSVA b){return smColorHSVA(a.h*b.h,a.s*b.s,a.v*b.v,a.a*b.a);}
	friend smColorHSVA operator *(smColorHSVA a,float b){return smColorHSVA(b*a.h,b*a.s,b*a.v,b*a.a);}
	friend smColorHSVA operator /(smColorHSVA a,float b){return smColorHSVA(a.h/b,a.s/b,a.v/b,a.a/b);}
	void setHWColor(DWORD col)
	{
		float r,g,b,dr,dg,db;
		float minv,maxv,dv;
		a=GETA(col)/255.;r=GETR(col)/255.;
		g=GETG(col)/255.;b=GETB(col)/255.;
		minv=min(min(r,g),b);maxv=max(max(r,g),b);
		dv=maxv-minv;v=maxv;
		if(dv<EPS)h=s=.0;
		else
		{
			s=dv/maxv;
			dr=(((maxv-r)/6)+dv/2)/dv;
			dg=(((maxv-g)/6)+dv/2)/dv;
			db=(((maxv-b)/6)+dv/2)/dv;
			if(maxv==r)h=db-dg;
			else if(maxv==g)h=(1./3.)+dr-db;
			else if(maxv==b)h=(2./3.)+dg-dr;
		}
		clamp();
	}
	DWORD getHWColor()
	{
		clamp();
		float r,g,b;
		float xh,i,p1,p2,p3;
		if(s<EPS)r=g=b=v;
		else
		{
			xh=h*6;
			if(fabsf(xh-6)<EPS)xh=0;
			i=floorf(xh);
			p1=v*(1-s);
			p2=v*(1-s*(xh-i));
			p3=v*(1-s*(1-(xh-i)));
			if(i==0)r=v,g=p3,b=p1;
			else if(i==1)r=p2,g=v,b=p1;
			else if(i==2)r=p1,g=v,b=p3;
			else if(i==3)r=p1,g=p2,b=v;
			else if(i==4)r=p3,g=p1,b=v;
			else r=v,g=p1,b=p2;
		}
		return RGBA(DWORD(r*255.0f),DWORD(g*255.0f),DWORD(b*255.0f),DWORD(a*255.0f));
	}
};
#endif
