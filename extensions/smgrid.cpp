// -*- C++ -*-
/*
 * Simple MultimEdia LiTerator(SMELT)
 * by Chris Xiong 2015
 * Distortion grid implementation
 *
 * WARNING: This library is in development and interfaces would be very
 * unstable.
 *
 */
#include "smgrid.hpp"
#include <cstring>
SMELT *smGrid::sm=0;
smGrid::smGrid(int _cc,int _rc)
{
	sm=smGetInterface(SMELT_APILEVEL);
	cc=_cc;rc=_rc;cw=ch=.0;
	quad.tex=0;quad.blend=BLEND_ALPHABLEND;
	pos=new smVertex[cc*rc];
	for(int i=0;i<cc*rc;++i)
	{
		pos[i].x=pos[i].y=pos[i].z=.0;
		pos[i].tx=pos[i].ty=.0;
		pos[i].col=0xFFFFFFFF;
	}
}
smGrid::smGrid(const smGrid &copy)
{
	sm=smGetInterface(SMELT_APILEVEL);
	cc=copy.cc;rc=copy.rc;cw=copy.cw;ch=copy.ch;
	quad=copy.quad;tx=copy.tx;ty=copy.ty;w=copy.w;h=copy.h;
	pos=new smVertex[cc*rc];memcpy(pos,copy.pos,sizeof(smVertex)*cc*rc);
}
smGrid::~smGrid(){delete[] pos;sm->smRelease();}
smGrid& smGrid::operator =(const smGrid &copy)
{
	if(this!=&copy)
	{
		sm=smGetInterface(SMELT_APILEVEL);
		cc=copy.cc;rc=copy.rc;cw=copy.cw;ch=copy.ch;
		quad=copy.quad;tx=copy.tx;ty=copy.ty;w=copy.w;h=copy.h;
		delete[] pos;pos=new smVertex[cc*rc];
		memcpy(pos,copy.pos,sizeof(smVertex)*cc*rc);
	}
	return *this;
}
void smGrid::setTexture(SMTEX tex){quad.tex=tex;}
void smGrid::setTextureRect4f(float _x,float _y,float _w,float _h)
{
	float tw,th;
	tx=_x;ty=_y;w=_w;h=_h;
	if(quad.tex)
	{
		tw=(float)sm->smTextureGetWidth(quad.tex);
		th=(float)sm->smTextureGetHeight(quad.tex);
	}
	else tw=w,th=h;
	cw=w/(cc-1);ch=h/(rc-1);
	for(int i=0;i<rc;++i)
	for(int j=0;j<cc;++j)
	{
		pos[i*cc+j].tx=(tx+j*cw)/tw;
		pos[i*cc+j].ty=(ty+i*ch)/th;
		pos[i*cc+j].x=j*cw;
		pos[i*cc+j].y=i*ch;
	}
}
void smGrid::setTextureRectv(smTexRect rect){setTextureRect4f(rect.x,rect.y,rect.w,rect.h);}
void smGrid::setBlend(int blend){quad.blend=blend;}
void smGrid::setColor(int c,int r,DWORD col){if(c<cc&&r<rc)pos[r*cc+c].col=col;}
void smGrid::setPos(int c,int r,float x,float y,float z,int ref)
{
	if(c<cc&&r<rc)
	{
		if(ref==GRID_REFCENTER)x+=cw*(cc-1)/2,y+=ch*(rc-1)/2;
		if(ref==GRID_REFNODE)x+=c*cw,y+=r*ch;
		if(ref==GRID_REFCURRENT)x+=pos[r*cc+c].x,y+=pos[r*cc+c].y;
		pos[r*cc+c].x=x;
		pos[r*cc+c].y=y;
	}
}
void smGrid::clear(DWORD col)
{
	for(int i=0;i<rc;++i)
	for(int j=0;j<cc;++j)
	{
		pos[i*cc+j].x=j*cw;
		pos[i*cc+j].y=i*ch;
		pos[i*cc+j].z=.0;
		pos[i*cc+j].col=col;
	}
}
void smGrid::render(float x,float y)
{
	for(int i=0;i<rc-1;++i)
	for(int j=0;j<cc-1;++j)
	{
		int id=i*cc+j;
		for(int k=0;k<4;++k)
		{
			int sub=k<2?id+k:id+cc+3-k;
			quad.v[k].tx=pos[sub].tx;
			quad.v[k].ty=pos[sub].ty;
			quad.v[k].x=x+pos[sub].x;
			quad.v[k].y=y+pos[sub].y;
			quad.v[k].z=pos[sub].z;
			quad.v[k].col=pos[sub].col;
		}
		sm->smRenderQuad(&quad);
	}
}
