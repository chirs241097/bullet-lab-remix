//Chrisoft Bullet Lab Remix HGE
//Chrisoft Game Helper header
//Copyright Chrisoft 2014
//libcgh version 0005
//Last full compatible version 0002
//^Modify that when big change is made^
#include <hge.h>
#include <hgefont.h>
#include <hgedistort.h>
#include <hgecolor.h>
#include <math.h>
#ifndef libcgh_H
#define libcgh_H
#define pi 3.1415926535
#define sqr(x) ((x)*(x))
//static const char* LIBCGH_H_FN="libcgh.h";

struct vector2d
{
	double x,y;
	vector2d(double _x,double _y){x=_x;y=_y;}
	vector2d(){x=y=0;}
	void ToUnitCircle()
	{
		double l=sqrt(sqr(x)+sqr(y));
		x/=l;y/=l;
	}
	void Swap(){double t=x;x=y;y=t;}
	void rotate(double rad){double tx=x*cos(rad)+y*sin(rad),ty=y*cos(rad)-x*sin(rad);x=tx,y=ty;}
	friend vector2d operator -(vector2d a,vector2d b)
	{
		return vector2d(a.x-b.x,a.y-b.y);
	}
	friend vector2d operator +(vector2d a,vector2d b)
	{
		return vector2d(a.x+b.x,a.y+b.y);
	}
	friend double operator |(vector2d a,vector2d b)//dot product
	{
		return a.x*b.x+a.y*b.y;
	}
	friend double operator *(vector2d a,vector2d b)//length of cross product
	{
		return a.x*b.y-b.x*a.y;
	}
	friend vector2d operator *(double a,vector2d b)
	{
		return vector2d(b.x*a,b.y*a);
	}
};
inline vector2d ToUnitCircle(vector2d input)
{
	vector2d res=input;
	res.x=res.x/sqrt(sqr(input.x)+sqr(input.y));
	res.y=res.y/sqrt(sqr(input.x)+sqr(input.y));
	return res;
}
inline double GetDist(const vector2d a,const vector2d b)
{
	return sqrtf((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
inline double GetDistSeg(const vector2d a,const vector2d b,const vector2d c)
{
	double l2=GetDist(a,b)*GetDist(a,b);
	if (l2==0.0)return GetDist(c,a);
	double t=((c-a)|(b-a))/l2;
	if (t<0)return GetDist(c,a);
	else if (t>1)return GetDist(c,b);
	vector2d projection=a+t*(b-a);
	return GetDist(c,projection);
}
inline double normalizerad(double a)
{
	while (a<0)a+=2*pi;
	while (a>2*pi)a-=2*pi;
	return a;
}
struct TextureRect
{
	double x,y,w,h;
	TextureRect(){}
	TextureRect(double _x,double _y,double _w,double _h){x=_x,y=_y,w=_w,h=_h;}
};
class CircleIndicator
{
private:
	hgeDistortionMesh *circle;
	double value,radius,thk;
	DWORD ccolour;
	bool gradient;
	BYTE alpha;
public:
	void Init(double _r,double _thk,BYTE _a,bool _gr,HTEXTURE _Texture,TextureRect _TR,DWORD _cc=0);
	void SetAlpha(BYTE _alpha);
	void SetValue(double _value);
	void Render(double x,double y);
};
class LinearProgresser
{
private:
	double a,b,val;
	double Elapsed,Limit;
public:
	void Init(double _a,double _b,double _Lim);
	void Launch();
	void Update(double DT);
	double GetA();
	double GetB();
	double GetValue();
	double GetPercentage();
	double GetDelta();
	double GetElapsed();
};
class HangUpText
{
private:
	hgeFont *TFont;
	vector2d Position;
	double Elapsed,Limit,dlim,delta;
	BYTE alim,alpha;
	char Text[255];
	LinearProgresser Progresser,Progalpha;
	bool done;
public:
	bool Active();
	void Init(const char *Font,const char *_Text,double _tlim,double _alim,double _dlim,DWORD _color=0x00FFFFFF);
	void Launch(vector2d pos);
	void Process(double DT);
};
#endif
