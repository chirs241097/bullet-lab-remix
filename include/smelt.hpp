// -*- C++ -*-
/*
 * Simple MultimEdia LiTerator(SMELT)
 * by Chris Xiong 2015
 * api level 3
 * Public header
 *
 * WARNING: This library is in development and interfaces would be very
 * unstable.
 * This library is developed for the BLR series games.
 *
 * This file is part of the SMELT library.
 *
 *  SMELT is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  SMELT is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef SMELT_H
#define SMELT_H

#include <stddef.h>
#include <stdint.h>

#define SMELT_APILEVEL 3

typedef uint32_t DWORD;
typedef uint16_t WORD;
typedef uint8_t BYTE;

#define PI 3.14159265358979323846f

//Handles
typedef size_t SMTEX;//Texture Handle
typedef size_t SMTRG;//Target Handle
typedef size_t SMSFX;//SoundFX Handle
typedef size_t SMCHN;//Channel Handle

//Color Marcos
#define RGBA(r,g,b,a)	((DWORD(a)<<24)+(DWORD(r)<<16)+(DWORD(g)<<8)+DWORD(b))
#define ARGB(a,r,g,b)	((DWORD(a)<<24)+(DWORD(r)<<16)+(DWORD(g)<<8)+DWORD(b))
#define GETA(col)		((col)>>24)
#define GETR(col)		(((col)>>16)&0xFF)
#define GETG(col)		(((col)>>8)&0xFF)
#define GETB(col)		((col)&0xFF)
#define SETA(col,a)		(((col)&0x00FFFFFF)+(DWORD(a)<<24))
#define SETR(col,r)		(((col)&0xFF00FFFF)+(DWORD(r)<<16))
#define SETG(col,g)		(((col)&0xFFFF00FF)+(DWORD(g)<<8))
#define SETB(col,b)		(((col)&0xFFFFFF00)+DWORD(b))

//Blend Modes
#define	  BLEND_COLORADD 0x1
#define	  BLEND_COLORMUL 0x0
#define	  BLEND_COLORINV 0x8
#define	  BLEND_ALPHABLEND 0x2
#define	  BLEND_ALPHAADD 0x0
#define	  BLEND_ZWRITE 0x4
#define	  BLEND_NOZWRITE 0x0

typedef bool (*smHook)();

#define FPS_FREE 0
#define FPS_VSYNC -1

#define PRIM_LINES		2
#define PRIM_TRIANGLES	3
#define PRIM_QUADS		4

struct smTexRect
{
	smTexRect(){x=y=w=h=.0;}
	smTexRect(float _x,float _y,float _w,float _h){x=_x;y=_y;w=_w;h=_h;}
	float x,y,w,h;
};

struct smVertex
{
	float x,y,z;//Position. Z can be used for depth testing in 2D Mode.
	DWORD col;//Color.
	float tx,ty;//Texture coords.
};

struct smTriangle
{
	smVertex v[3];
	SMTEX tex;
	int blend;
};

struct smQuad
{
	smVertex v[4];
	SMTEX tex;
	int blend;
};

struct smInpEvent
{
	int type,flag;
	int sccode,chcode;
	int wheel,x,y;
	//TODO: add joystick
};

class SMELT
{
public:
	SMELT(){}
	virtual ~SMELT(){}
	virtual void smRelease()=0;
	virtual bool smInit()=0;
	virtual void smFinale()=0;
	virtual void smMainLoop()=0;
	virtual void smUpdateFunc(smHook func)=0;
	virtual void smUnFocFunc(smHook func)=0;
	virtual void smFocFunc(smHook func)=0;
	virtual void smQuitFunc(smHook func)=0;
	virtual void smWinTitle(const char* title)=0;
	virtual bool smIsActive()=0;
	virtual void smNoSuspend(bool para)=0;
	virtual void smVidMode(int resX,int resY,bool _windowed)=0;
	virtual void smLogFile(const char* path)=0;
	virtual void smLog(const char* format,...)=0;
	virtual void smScreenShot(const char* path)=0;

	virtual void smSetFPS(int fps)=0;
	virtual float smGetFPS()=0;
	virtual float smGetDelta()=0;
	virtual float smGetTime()=0;

	virtual SMSFX smSFXLoad(const char *path)=0;
	virtual SMSFX smSFXLoadFromMemory(const char *ptr,DWORD size)=0;
	virtual SMCHN smSFXPlay(SMSFX fx,int vol=100,int pan=0,float pitch=1.,bool loop=0)=0;
	virtual float smSFXGetLengthf(SMSFX fx)=0;
	virtual DWORD smSFXGetLengthd(SMSFX fx)=0;
	virtual void smSFXSetLoopPoint(SMSFX fx,DWORD l,DWORD r)=0;
	virtual void smSFXFree(SMSFX fx)=0;

	virtual void smChannelVol(SMCHN chn,int vol)=0;
	virtual void smChannelPan(SMCHN chn,int pan)=0;
	virtual void smChannelPitch(SMCHN chn,float pitch)=0;
	virtual void smChannelPause(SMCHN chn)=0;
	virtual void smChannelResume(SMCHN chn)=0;
	virtual void smChannelStop(SMCHN chn)=0;
	virtual void smChannelPauseAll()=0;
	virtual void smChannelResumeAll()=0;
	virtual void smChannelStopAll()=0;
	virtual bool smChannelIsPlaying(SMCHN chn)=0;
	virtual float smChannelGetPosf(SMCHN chn)=0;
	virtual void smChannelSetPosf(SMCHN chn,float pos)=0;
	virtual int smChannelGetPosd(SMCHN chn)=0;
	virtual void smChannelSetPosd(SMCHN chn,int pos)=0;

	virtual void smGetMouse2f(float *x,float *y)=0;
	virtual void smSetMouse2f(float x,float y)=0;
	virtual int smGetWheel()=0;
	virtual bool smIsMouseOver()=0;
	virtual int smGetKeyState(int key)=0;
	virtual int smGetKey()=0;
	virtual bool smGetInpEvent(smInpEvent *e)=0;

	virtual bool smRenderBegin2D(bool ztest=0,SMTRG trg=0)=0;
	virtual bool smRenderBegin3D(float fov,SMTRG trg=0)=0;
	virtual bool smRenderEnd()=0;
	virtual void sm3DCamera6f2v(float *pos,float *rot)=0;
	virtual void sm2DCamera5f3v(float *pos,float *dpos,float *rot)=0;
	virtual void smMultViewMatrix(float *mat)=0;
	virtual void smClrscr(DWORD color)=0;
	virtual void smRenderLinefd(float x1,float y1,float z1,float x2,float y2,float z2,DWORD color)=0;
	virtual void smRenderLinefvd(float *p1,float *p2,DWORD color)=0;
	virtual void smRenderTriangle(smTriangle *t)=0;
	virtual void smRenderQuad(smQuad *q)=0;
	virtual smVertex* smGetVertArray()=0;
	virtual void smDrawVertArray(int prim,SMTEX texture,int blend,int _primcnt)=0;

	virtual SMTRG smTargetCreate(int w,int h)=0;
	virtual SMTEX smTargetTexture(SMTRG targ)=0;
	virtual void smTargetFree(SMTRG targ)=0;

	virtual SMTEX smTextureCreate(int w,int h)=0;
	virtual SMTEX smTextureLoad(const char *path)=0;
	virtual SMTEX smTextureLoadFromMemory(const char *ptr,DWORD size)=0;
	virtual void smTextureFree(SMTEX tex)=0;
	virtual int smTextureGetWidth(SMTEX tex,bool original=false)=0;
	virtual int smTextureGetHeight(SMTEX tex,bool original=false)=0;
	virtual DWORD* smTextureLock(SMTEX tex,int l,int t,int w,int h,bool ro=true)=0;
	virtual void smTexutreUnlock(SMTEX tex)=0;
};

SMELT* smGetInterface(int apilevel);

//event types
#define INPUT_KEYDOWN		1
#define INPUT_KEYUP			2
#define INPUT_MBUTTONDOWN	3
#define INPUT_MBUTTONUP		4
#define INPUT_MOUSEMOVE		5
#define INPUT_MOUSEWHEEL	6

//key mods/flags
#define SMINP_SHIFT			0x1
#define SMINP_CTRL			0x2
#define SMINP_ALT			0x4
#define SMINP_CAPSLOCK		0x8
#define SMINP_SCROLLLOCK	0x10
#define SMINP_NUMLOCK		0x20
#define SMINP_REPEAT		0x40

//key codes
#define SMK_LBUTTON	0x01
#define SMK_RBUTTON	0x02
#define SMK_MBUTTON	0x04

#define SMK_ESCAPE		0x1B
#define SMK_BACKSPACE	0x08
#define SMK_TAB			0x09
#define SMK_ENTER		0x0D
#define SMK_SPACE		0x20

#define SMK_SHIFT		0x10
#define SMK_CTRL		0x11
#define SMK_ALT			0x12

#define SMK_LWIN		0x5B
#define SMK_RWIN		0x5C
#define SMK_APPS		0x5D

#define SMK_PAUSE		0x13
#define SMK_CAPSLOCK	0x14
#define SMK_NUMLOCK		0x90
#define SMK_SCROLLLOCK	0x91

#define SMK_PGUP		0x21
#define SMK_PGDN		0x22
#define SMK_HOME		0x24
#define SMK_END			0x23
#define SMK_INSERT		0x2D
#define SMK_DELETE		0x2E

#define SMK_LEFT		0x25
#define SMK_UP			0x26
#define SMK_RIGHT		0x27
#define SMK_DOWN		0x28

#define SMK_0			0x30
#define SMK_1			0x31
#define SMK_2			0x32
#define SMK_3			0x33
#define SMK_4			0x34
#define SMK_5			0x35
#define SMK_6			0x36
#define SMK_7			0x37
#define SMK_8			0x38
#define SMK_9			0x39

#define SMK_A			0x41
#define SMK_B			0x42
#define SMK_C			0x43
#define SMK_D			0x44
#define SMK_E			0x45
#define SMK_F			0x46
#define SMK_G			0x47
#define SMK_H			0x48
#define SMK_I			0x49
#define SMK_J			0x4A
#define SMK_K			0x4B
#define SMK_L			0x4C
#define SMK_M			0x4D
#define SMK_N			0x4E
#define SMK_O			0x4F
#define SMK_P			0x50
#define SMK_Q			0x51
#define SMK_R			0x52
#define SMK_S			0x53
#define SMK_T			0x54
#define SMK_U			0x55
#define SMK_V			0x56
#define SMK_W			0x57
#define SMK_X			0x58
#define SMK_Y			0x59
#define SMK_Z			0x5A

#define SMK_GRAVE		0xC0
#define SMK_MINUS		0xBD
#define SMK_EQUALS		0xBB
#define SMK_BACKSLASH	0xDC
#define SMK_LBRACKET	0xDB
#define SMK_RBRACKET	0xDD
#define SMK_SEMICOLON	0xBA
#define SMK_APOSTROPHE	0xDE
#define SMK_COMMA		0xBC
#define SMK_PERIOD		0xBE
#define SMK_SLASH		0xBF

#define SMK_NUMPAD0	0x60
#define SMK_NUMPAD1	0x61
#define SMK_NUMPAD2	0x62
#define SMK_NUMPAD3	0x63
#define SMK_NUMPAD4	0x64
#define SMK_NUMPAD5	0x65
#define SMK_NUMPAD6	0x66
#define SMK_NUMPAD7	0x67
#define SMK_NUMPAD8	0x68
#define SMK_NUMPAD9	0x69

#define SMK_MULTIPLY	0x6A
#define SMK_DIVIDE		0x6F
#define SMK_ADD			0x6B
#define SMK_SUBTRACT	0x6D
#define SMK_DECIMAL		0x6E

#define SMK_F1		0x70
#define SMK_F2		0x71
#define SMK_F3		0x72
#define SMK_F4		0x73
#define SMK_F5		0x74
#define SMK_F6		0x75
#define SMK_F7		0x76
#define SMK_F8		0x77
#define SMK_F9		0x78
#define SMK_F10		0x79
#define SMK_F11		0x7A
#define SMK_F12		0x7B

#define SMKST_NONE		0
#define SMKST_HIT		1
#define SMKST_KEEP		2
#define SMKST_RELEASE	3

#endif
