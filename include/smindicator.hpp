// -*- C++ -*-
/*
 * Simple MultimEdia LiTerator(SMELT)
 * by Chris Xiong 2015
 * Indicator header & implementation
 *
 * WARNING: This library is in development and interfaces would be very
 * unstable.
 *
 */
#ifndef SMINDICATOR_H
#define SMINDICATOR_H
#include "smelt.hpp"
#include "smmath.hpp"
#include "smcolor.hpp"
#include "smentity.hpp"
#include "smgrid.hpp"
class indicatorCircular
{
private:
	smGrid *circle;
	float value,radius,thickness;
	DWORD color;
	BYTE alpha;
public:
	void init(float r,float thkns,BYTE a,SMTEX tex,smTexRect tr)
	{
		circle=new smGrid(1025,3);
		circle->setTexture(tex);
		circle->setTextureRectv(tr);
		radius=r;thickness=thkns;alpha=a;color=0;
		for(int i=0;i<=1024;++i)
		{
			float tang,tx,ty;
			tang=(float)i/1024.*PI*2-PI/2;
			tx=-cos(tang)*radius;ty=sin(tang)*radius;
			circle->setPos(i,2,tx,ty,0.5,GRID_REFTOPLEFT);
			tx=-cos(tang)*(radius-thickness);ty=sin(tang)*(radius-thickness);
			circle->setPos(i,1,tx,ty,0.5,GRID_REFTOPLEFT);
			tx=-cos(tang)*(radius-2*thickness);ty=sin(tang)*(radius-2*thickness);
			circle->setPos(i,0,tx,ty,0.5,GRID_REFTOPLEFT);
		}
	}
	void overrideColor(DWORD col){color=col;}
	void setAlpha(BYTE a){alpha=a;}
	void setValue(float v)
	{
		value=v;
		for(int i=0;i<=1024;++i)
		{
			int tr=(int)((1.0f-value)*255);
			int tg=(int)(value*255);
			DWORD tcolor=ARGB(alpha,tr,tg,0);
			smColorHSVA *tc=new smColorHSVA(tcolor);
			if(tc->v<0.85)tc->v=0.85;
			tcolor=color?SETA(color,alpha):SETA(tc->getHWColor(),alpha);
			delete tc;
			if((float)i/1024.<=value)
			{
				circle->setColor(i,2,tcolor);
				circle->setColor(i,1,SETA(0x00FFFFFF,alpha));
				circle->setColor(i,0,tcolor);
			}
			else
			{
				circle->setColor(i,2,0);
				circle->setColor(i,1,0);
				circle->setColor(i,0,0);
			}
		}
	}
	void render(float x,float y){circle->render(x,y);}
	void deinit(){delete circle;circle=NULL;}
};
class indicatorLinear
{
private:
	smEntity2D *upper,*lower;
	float value,maxlength,thickness;
	DWORD color;smTexRect trect;
	BYTE alpha;
public:
	void init(float ml,float thkns,BYTE a,SMTEX tex,smTexRect tr)
	{
		upper=new smEntity2D(tex,tr.x,tr.y,tr.w,tr.h/2);
		lower=new smEntity2D(tex,tr.x,tr.y+tr.h/2,tr.w,tr.h/2);
		maxlength=ml;thickness=thkns;alpha=a;color=0;trect=tr;
	}
	void overrideColor(DWORD col){color=col;}
	void setAlpha(BYTE a){alpha=a;}
	void setValue(float v)
	{
		value=v;
		int tr=(int)((1.0f-value)*255);
		int tg=(int)(value*255);
		DWORD tcolor=ARGB(alpha,tr,tg,0);
		smColorHSVA *tc=new smColorHSVA(tcolor);
		if(tc->v<0.85)tc->v=0.85;
		tcolor=color?SETA(color,alpha):SETA(tc->getHWColor(),alpha);
		delete tc;
		upper->setColor(tcolor,0);upper->setColor(tcolor,1);
		upper->setColor(0,2);upper->setColor(0,3);
		lower->setColor(0,0);lower->setColor(0,1);
		lower->setColor(tcolor,2);lower->setColor(tcolor,3);
	}
	void render(float x,float y)
	{
		upper->render(x,y,0,value*maxlength/trect.w,thickness/trect.h/2);
		lower->render(x,y+thickness/2,0,value*maxlength/trect.w,thickness/trect.h/2);
	}
	void deinit(){delete upper;delete lower;upper=lower=NULL;}
};
#endif
