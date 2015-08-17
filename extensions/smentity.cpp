// -*- C++ -*-
/*
 * Simple MultimEdia LiTerator(SMELT)
 * by Chris Xiong 2015
 * Entity implementation
 *
 * WARNING: This library is in development and interfaces would be very
 * unstable.
 *
 */
#include "smentity.hpp"
#include "smmath.hpp"
#include <cstring>
#include <cstdio>
SMELT *smEntity2D::sm=NULL;
SMELT *smEntity3D::sm=NULL;

smEntity2D::smEntity2D(SMTEX tex,float _x,float _y,float _w,float _h)
{
	sm=smGetInterface(SMELT_APILEVEL);
	tx=_x;ty=_y;w=_w;h=_h;
	if(tex)
	{
		texw=sm->smTextureGetWidth(tex);
		texh=sm->smTextureGetHeight(tex);
	}else texw=texh=1.;
	ctrx=ctry=0;quad.tex=tex;
	quad.v[0].tx=_x/texw;quad.v[0].ty=_y/texh;
	quad.v[1].tx=(_x+_w)/texw;quad.v[1].ty=_y/texh;
	quad.v[2].tx=(_x+_w)/texw;quad.v[2].ty=(_y+_h)/texh;
	quad.v[3].tx=_x/texw;quad.v[3].ty=(_y+_h)/texh;
	for(int i=0;i<4;++i){quad.v[i].z=.5f;quad.v[i].col=0xFFFFFFFF;}
	quad.blend=BLEND_ALPHABLEND;
}
smEntity2D::smEntity2D(SMTEX tex,smTexRect rect)
{
	sm=smGetInterface(SMELT_APILEVEL);
	tx=rect.x;ty=rect.y;w=rect.w;h=rect.h;
	if(tex)
	{
		texw=sm->smTextureGetWidth(tex);
		texh=sm->smTextureGetHeight(tex);
	}else texw=texh=1.;
	ctrx=ctry=0;quad.tex=tex;
	quad.v[0].tx=rect.x/texw;quad.v[0].ty=rect.y/texh;
	quad.v[1].tx=(rect.x+rect.w)/texw;quad.v[1].ty=rect.y/texh;
	quad.v[2].tx=(rect.x+rect.w)/texw;quad.v[2].ty=(rect.y+rect.h)/texh;
	quad.v[3].tx=rect.x/texw;quad.v[3].ty=(rect.y+rect.h)/texh;
	for(int i=0;i<4;++i){quad.v[i].z=.5f;quad.v[i].col=0xFFFFFFFF;}
	quad.blend=BLEND_ALPHABLEND;
}
smEntity2D::smEntity2D(const smEntity2D &copy)
{
	memcpy(this,&copy,sizeof(smEntity2D));
	sm=smGetInterface(SMELT_APILEVEL);
}
void smEntity2D::render(float x,float y,float rot,float wsc,float hsc)
{
	if(hsc<EPS)hsc=wsc;
	float cx0=-ctrx*wsc,cy0=-ctry*hsc;
	float cx1=(w-ctrx)*wsc,cy1=(h-ctry)*hsc;
	float c=cosf(rot),s=sinf(rot);
	quad.v[0].x=cx0*c-cy0*s+x;quad.v[0].y=cx0*s+cy0*c+y;
	quad.v[1].x=cx1*c-cy0*s+x;quad.v[1].y=cx1*s+cy0*c+y;
	quad.v[2].x=cx1*c-cy1*s+x;quad.v[2].y=cx1*s+cy1*c+y;
	quad.v[3].x=cx0*c-cy1*s+x;quad.v[3].y=cx0*s+cy1*c+y;
	sm->smRenderQuad(&quad);
}
void smEntity2D::setTexture(SMTEX tex)
{
	float ntw,nth;
	if(tex)
	{
		ntw=sm->smTextureGetWidth(tex);
		nth=sm->smTextureGetHeight(tex);
	}else ntw=nth=1.;
	quad.tex=tex;
	if(ntw!=texw||nth!=texh)
	{
		float tx1=quad.v[0].tx*texw,ty1=quad.v[0].ty*texh;
		float tx2=quad.v[2].tx*texw,ty2=quad.v[2].ty*texh;
		texw=ntw;texh=nth;
		tx1/=texw;ty1/=texh;tx2/=texw;ty2/=texh;
		quad.v[0].tx=tx1;quad.v[0].ty=ty1;
		quad.v[1].tx=tx2;quad.v[1].ty=ty1;
		quad.v[2].tx=tx2;quad.v[2].ty=ty2;
		quad.v[3].tx=tx1;quad.v[3].ty=ty2;
	}
}
void smEntity2D::setTextureRect4f(float _x,float _y,float _w,float _h)
{
	tx=_x;ty=_y;w=_w;h=_h;
	quad.v[0].tx=_x/texw;quad.v[0].ty=_y/texh;
	quad.v[1].tx=(_x+_w)/texw;quad.v[1].ty=_y/texh;
	quad.v[2].tx=(_x+_w)/texw;quad.v[2].ty=(_y+_h)/texh;
	quad.v[3].tx=_x/texw;quad.v[3].ty=(_y+_h)/texh;
}
void smEntity2D::setTextureRectv(smTexRect rect){setTextureRect4f(rect.x,rect.y,rect.w,rect.h);}
void smEntity2D::setColor(DWORD col,int v)
{
	if(v>=0&&v<4)quad.v[v].col=col;
	else for(int i=0;i<4;++i)quad.v[i].col=col;
}
void smEntity2D::setZ(float z,int v)
{
	if(v>=0&&v<4)quad.v[v].z=z;
	else for(int i=0;i<4;++i)quad.v[i].z=z;
}
void smEntity2D::setBlend(int blend){quad.blend=blend;}
void smEntity2D::setCentre(float x,float y){ctrx=x;ctry=y;}

smEntity3D::smEntity3D(SMTEX tex,float _x,float _y,float _w,float _h)
{
	sm=smGetInterface(SMELT_APILEVEL);
	tx=_x;ty=_y;w=_w;h=_h;
	if(tex)
	{
		texw=sm->smTextureGetWidth(tex);
		texh=sm->smTextureGetHeight(tex);
	}else texw=texh=1.;
	ctrx=ctry=0;quad.tex=tex;
	quad.v[0].tx=_x/texw;quad.v[0].ty=_y/texh;
	quad.v[1].tx=(_x+_w)/texw;quad.v[1].ty=_y/texh;
	quad.v[2].tx=(_x+_w)/texw;quad.v[2].ty=(_y+_h)/texh;
	quad.v[3].tx=_x/texw;quad.v[3].ty=(_y+_h)/texh;
	for(int i=0;i<4;++i){quad.v[i].z=.5f;quad.v[i].col=0xFFFFFFFF;}
	quad.blend=BLEND_ALPHABLEND;
}
smEntity3D::smEntity3D(SMTEX tex,smTexRect rect)
{
	sm=smGetInterface(SMELT_APILEVEL);
	tx=rect.x;ty=rect.y;w=rect.w;h=rect.h;
	if(tex)
	{
		texw=sm->smTextureGetWidth(tex);
		texh=sm->smTextureGetHeight(tex);
	}else texw=texh=1.;
	ctrx=ctry=0;quad.tex=tex;
	quad.v[0].tx=rect.x/texw;quad.v[0].ty=rect.y/texh;
	quad.v[1].tx=(rect.x+rect.w)/texw;quad.v[1].ty=rect.y/texh;
	quad.v[2].tx=(rect.x+rect.w)/texw;quad.v[2].ty=(rect.y+rect.h)/texh;
	quad.v[3].tx=rect.x/texw;quad.v[3].ty=(rect.y+rect.h)/texh;
	for(int i=0;i<4;++i){quad.v[i].z=.5f;quad.v[i].col=0xFFFFFFFF;}
	quad.blend=BLEND_ALPHABLEND;
}
smEntity3D::smEntity3D(const smEntity3D &copy)
{
	memcpy(this,&copy,sizeof(smEntity3D));
	sm=smGetInterface(SMELT_APILEVEL);
}
void smEntity3D::render9f(float x,float y,float z,float ra,float rx,float ry,float rz,float wsc,float hsc)
{
	if(hsc<EPS)hsc=wsc;
	float cx0=-ctrx*wsc,cy0=-ctry*hsc;
	float cx1=(w-ctrx)*wsc,cy1=(h-ctry)*hsc;
	smvec3d a,r;smMatrix m;
	a=smvec3d(cx0,cy0,0);m.loadIdentity();m.rotate(ra,rx,ry,rz);r=m*a;
	quad.v[0].x=r.x;quad.v[0].y=r.y;quad.v[0].z=r.z;
	a=smvec3d(cx1,cy0,0);m.loadIdentity();m.rotate(ra,rx,ry,rz);r=m*a;
	quad.v[1].x=r.x;quad.v[1].y=r.y;quad.v[1].z=r.z;
	a=smvec3d(cx1,cy1,0);m.loadIdentity();m.rotate(ra,rx,ry,rz);r=m*a;
	quad.v[2].x=r.x;quad.v[2].y=r.y;quad.v[2].z=r.z;
	a=smvec3d(cx0,cy1,0);m.loadIdentity();m.rotate(ra,rx,ry,rz);r=m*a;
	quad.v[3].x=r.x;quad.v[3].y=r.y;quad.v[3].z=r.z;
	sm->smRenderQuad(&quad);
}
void smEntity3D::renderfv(float* pos,float* rot,float* scale)
{
	render9f(pos[0],pos[1],pos[2],rot[0],rot[1],rot[2],rot[3],scale[0],scale[1]);
}
void smEntity3D::setTexture(SMTEX tex)
{
	float ntw,nth;
	if(tex)
	{
		ntw=sm->smTextureGetWidth(tex);
		nth=sm->smTextureGetHeight(tex);
	}else ntw=nth=1.;
	quad.tex=tex;
	if(ntw!=texw||nth!=texh)
	{
		float tx1=quad.v[0].tx*texw,ty1=quad.v[0].ty*texh;
		float tx2=quad.v[2].tx*texw,ty2=quad.v[2].ty*texh;
		texw=ntw;texh=nth;
		tx1/=texw;ty1/=texh;tx2/=texw;ty2/=texh;
		quad.v[0].tx=tx1;quad.v[0].ty=ty1;
		quad.v[1].tx=tx2;quad.v[1].ty=ty1;
		quad.v[2].tx=tx2;quad.v[2].ty=ty2;
		quad.v[3].tx=tx1;quad.v[3].ty=ty2;
	}
}
void smEntity3D::setTextureRect4f(float _x,float _y,float _w,float _h)
{
	tx=_x;ty=_y;w=_w;h=_h;
	quad.v[0].tx=_x/texw;quad.v[0].ty=_y/texh;
	quad.v[1].tx=(_x+_w)/texw;quad.v[1].ty=_y/texh;
	quad.v[2].tx=(_x+_w)/texw;quad.v[2].ty=(_y+_h)/texh;
	quad.v[3].tx=_x/texw;quad.v[3].ty=(_y+_h)/texh;
}
void smEntity3D::setTextureRectv(smTexRect rect){setTextureRect4f(rect.x,rect.y,rect.w,rect.h);}
void smEntity3D::setColor(DWORD col,int v)
{
	if(v>=0&&v<4)quad.v[v].col=col;
	else for(int i=0;i<4;++i)quad.v[i].col=col;
}
void smEntity3D::setBlend(int blend){quad.blend=blend;}
void smEntity3D::setCentre(float x,float y){ctrx=x;ctry=y;}
