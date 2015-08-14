// -*- C++ -*-
/*
 * Simple MultimEdia LiTerator(SMELT)
 * by Chris Xiong 2015
 * api level 1
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
#include "smgrid.hpp"
class indicatorCircular
{
private:
	smGrid *circle;
	double value,radius,thickness;
	DWORD color;
	BYTE alpha;
public:
	void init(double r,double thkns,BYTE a,SMTEX tex,smTexRect tr)
	{
		circle=new smGrid(1025,3);
		circle->setTexture(tex);
		circle->setTextureRectv(tr);
		radius=r;thickness=thkns;alpha=a;color=0;
		for(int i=0;i<=1024;++i)
		{
			double tang,tx,ty;
			tang=(double)i/1024.*PI*2-PI/2;
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
	void setValue(double v)
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
			if((double)i/1024.<=value)
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
#endif
