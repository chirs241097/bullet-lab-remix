// -*- C++ -*-
/*
 * Simple MultimEdia LiTerator(SMELT)
 * by Chris Xiong 2015
 * Entity header
 *
 * WARNING: This library is in development and interfaces would be very
 * unstable.
 *
 */
#ifndef SMENTITY_H
#define SMENTITY_H
#include "smelt.hpp"
class smEntity2D
{
private:
	smEntity2D();
	static SMELT *sm;
	smQuad quad;
	float tx,ty,w,h,texw,texh;
	float ctrx,ctry;
public:
	smEntity2D(SMTEX tex,float _x,float _y,float _w,float _h);
	smEntity2D(SMTEX tex,smTexRect rect);
	smEntity2D(const smEntity2D &copy);
	~smEntity2D(){sm->smRelease();}
	void render(float x,float y,float rot=0,float wsc=1.,float hsc=0.);

	void setTexture(SMTEX tex);
	void setTextureRect4f(float _x,float _y,float _w,float _h);
	void setTextureRectv(smTexRect rect);
	void setColor(DWORD col,int v=-1);
	void setZ(float z,int v=-1);
	void setBlend(int blend);
	void setCentre(float x,float y);
	float _w(){return w;}
	float _h(){return h;}
};

class smEntity3D
{
private:
	smEntity3D();
	static SMELT *sm;
	smQuad quad;
	float tx,ty,w,h,texw,texh;
	float ctrx,ctry;
public:
	smEntity3D(SMTEX tex,float _x,float _y,float _w,float _h);
	smEntity3D(SMTEX tex,smTexRect rect);
	smEntity3D(const smEntity3D &copy);
	~smEntity3D(){sm->smRelease();}
	void render9f(float x,float y,float z,float ra=.0,float rx=.0,float ry=.0,float rz=.0,float wsc=1.,float hsc=0.);
	void renderfv(float* pos,float* rot,float* scale);

	void setTexture(SMTEX tex);
	void setTextureRect4f(float _x,float _y,float _w,float _h);
	void setTextureRectv(smTexRect rect);
	void setColor(DWORD col,int v=-1);
	void setBlend(int blend);
	void setCentre(float x,float y);
	float _w(){return w;}
	float _h(){return h;}
};
#endif
