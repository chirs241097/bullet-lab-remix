// -*- C++ -*-
/*
 * Simple MultimEdia LiTerator(SMELT)
 * by Chris Xiong 2015
 * Distortion grid header
 *
 * WARNING: This library is in development and interfaces would be very
 * unstable.
 *
 */
#ifndef SMGRID_H
#define SMGRID_H
#include "smelt.hpp"

#define GRID_REFNODE 0
#define GRID_REFTOPLEFT 1
#define GRID_REFCENTER 2
#define GRID_REFCURRENT 3

class smGrid
{
private:
	smGrid();
	static SMELT *sm;
	smVertex *pos;
	int cc,rc;
	float cw,ch;
	float tx,ty,w,h;
	smQuad quad;
public:
	smGrid(int _cc,int _rc);
	smGrid(const smGrid &copy);
	~smGrid();
	smGrid& operator =(const smGrid &copy);
	void render(float x,float y);
	void clear(DWORD color=0xFFFFFFFF);
	void setTexture(SMTEX tex);
	void setTextureRect4f(float _x,float _y,float _w,float _h);
	void setTextureRectv(smTexRect rect);
	void setBlend(int blend);
	void setColor(int c,int r,DWORD col);
	void setPos(int c,int r,float x,float y,float z,int ref);
};
#endif
