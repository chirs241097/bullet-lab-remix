// -*- C++ -*-
/*
 * Simple MultimEdia LiTerator(SMELT)
 * by Chris Xiong 2015
 * Internal header for SDL version
 *
 * WARNING: This library is in development and interfaces would be very
 * unstable.
 *
 */
#ifndef SMELT_INTERNAL_H
#define SMELT_INTERNAL_H

#include "../../include/smelt.hpp"
#include "smelt_config.hpp"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cstdarg>
#include <dirent.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
#include <ogg/ogg.h>
#include <vorbis/vorbisfile.h>
#ifdef WIN32
#include <windows.h>
#include <intrin.h>
#endif

#define GL_GLEXT_LEGACY 1
#include <GL/gl.h>
#include <GL/glext.h>

#define xstr(s) str(s)
#define str(s) #s
#define SLINE xstr(__LINE__)

#define GL_PROC(ext,fn,call,ret,params) typedef call ret (* _PFN_##fn) params;
#include "glimports.hpp"
#undef GL_PROC

class TOpenGLDevice
{
public:
	#define GL_PROC(ext,fn,call,ret,params) _PFN_##fn fn;
	#include "glimports.hpp"
	#undef GL_PROC
	GLenum TextureTarget;
	bool have_base_opengl;
	bool have_GL_ARB_texture_rectangle;
	bool have_GL_ARB_texture_non_power_of_two;
	bool have_GL_EXT_framebuffer_object;
	bool have_GL_EXT_texture_compression_s3tc;
	bool have_GL_ARB_vertex_buffer_object;
};

struct glTexture;
class TRenderTargetList
{
public:
	int w,h;
	SMTEX tex;
	GLuint depth,frame;
	TRenderTargetList *next;
};
class TTextureList
{
public:
	SMTEX tex;
	int w,h;
	TTextureList *next;
};
class TInputEventList
{
public:
	smInpEvent e;
	TInputEventList *next;
};

class SMELT_IMPL:public SMELT
{
public:
	virtual void smRelease();
	virtual bool smInit();
	virtual void smFinale();
	virtual void smMainLoop();
	virtual void smUpdateFunc(smHook func);
	virtual void smUnFocFunc(smHook func);
	virtual void smFocFunc(smHook func);
	virtual void smQuitFunc(smHook func);
	virtual void smWinTitle(const char* title);
	virtual bool smIsActive();
	virtual void smNoSuspend(bool para);
	virtual void smVidMode(int resX,int resY,bool _windowed);
	virtual void smLogFile(const char* path);
	virtual void smLog(const char* format,...);
	virtual void smScreenShot(const char* path);

	virtual void smSetFPS(int fps);
	virtual float smGetFPS();
	virtual float smGetDelta();
	virtual float smGetTime();

	virtual SMSFX smSFXLoad(const char *path);
	virtual SMSFX smSFXLoadFromMemory(const char *ptr,DWORD size);
	virtual SMCHN smSFXPlay(SMSFX fx,int vol=100,int pan=0,float pitch=1.,bool loop=0);
	virtual float smSFXGetLengthf(SMSFX fx);
	virtual DWORD smSFXGetLengthd(SMSFX fx);
	virtual void smSFXSetLoopPoint(SMSFX fx,DWORD l,DWORD r);
	virtual void smSFXFree(SMSFX fx);

	virtual void smChannelVol(SMCHN chn,int vol);
	virtual void smChannelPan(SMCHN chn,int pan);
	virtual void smChannelPitch(SMCHN chn,float pitch);
	virtual void smChannelPause(SMCHN chn);
	virtual void smChannelResume(SMCHN chn);
	virtual void smChannelStop(SMCHN chn);
	virtual void smChannelPauseAll();
	virtual void smChannelResumeAll();
	virtual void smChannelStopAll();
	virtual bool smChannelIsPlaying(SMCHN chn);
	virtual float smChannelGetPosf(SMCHN chn);
	virtual void smChannelSetPosf(SMCHN chn,float pos);
	virtual int smChannelGetPosd(SMCHN chn);
	virtual void smChannelSetPosd(SMCHN chn,int pos);

	virtual void smGetMouse2f(float *x,float *y);
	virtual void smSetMouse2f(float x,float y);
	virtual int smGetWheel();
	virtual bool smIsMouseOver();
	virtual int smGetKeyState(int key);
	virtual int smGetKey();
	virtual bool smGetInpEvent(smInpEvent *e);

	virtual bool smRenderBegin2D(bool ztest=0,SMTRG trg=0);
	virtual bool smRenderBegin3D(float fov,SMTRG trg=0);
	virtual bool smRenderEnd();
	virtual void sm3DCamera6f2v(float *pos,float *rot);
	virtual void sm2DCamera5f3v(float *pos,float *dpos,float *rot);
	virtual void smMultViewMatrix(float *mat);
	virtual void smClrscr(DWORD color);
	virtual void smRenderLinefd(float x1,float y1,float z1,float x2,float y2,float z2,DWORD color);
	virtual void smRenderLinefvd(float *p1,float *p2,DWORD color);
	virtual void smRenderTriangle(smTriangle *t);
	virtual void smRenderQuad(smQuad *q);
	virtual smVertex* smGetVertArray();
	virtual void smDrawVertArray(int prim,SMTEX texture,int blend,int _primcnt);

	virtual SMTRG smTargetCreate(int w,int h);
	virtual SMTEX smTargetTexture(SMTRG targ);
	virtual void smTargetFree(SMTRG targ);

	virtual SMTEX smTextureCreate(int w,int h);
	virtual SMTEX smTextureLoad(const char *path);
	virtual SMTEX smTextureLoadFromMemory(const char *ptr,DWORD size);
	virtual void smTextureFree(SMTEX tex);
	virtual int smTextureGetWidth(SMTEX tex,bool original=false);
	virtual int smTextureGetHeight(SMTEX tex,bool original=false);
	virtual DWORD* smTextureLock(SMTEX tex,int l,int t,int w,int h,bool ro=true);
	virtual void smTexutreUnlock(SMTEX tex);
//internal routines&variables...
	static SMELT_IMPL* getInterface();
	void focusChange(bool actif);

	void *hwnd;
	bool Active;
	char curError[256];

	bool (*pUpdateFunc)();
	bool (*pUnFocFunc)();
	bool (*pFocFunc)();
	bool (*pQuitFunc)();
	const char *Icon;
	char winTitle[256];
	int scrw,scrh;
	int dispw,disph;
	bool windowed,vsync;
	char logFile[256];
	int limfps;
	bool hideMouse,noSuspend;
	GLuint IndexBufferObject;

	TOpenGLDevice *pOpenGLDevice;
	smVertex *vertexArray;
	smVertex *vertexBuf;
	GLushort *indexBuf;
	SDL_GLContext glContext;
	TRenderTargetList *targets;
	TRenderTargetList *curTarget;
	TTextureList *textures;
	bool tdmode;
	int primcnt,primType,primBlend;
	SMTEX primTex;
	bool zbufenabled;
	bool checkGLExtension(const char *extlist,const char *ext);
	void unloadGLEntryPoints();
	bool loadGLEntryPoints();
	bool initOGL();
	void finiOGL();
	bool restOGL();
	bool confOGL();
	void batchOGL(bool endScene=false);
	void configTexture(glTexture *t,int w,int h,DWORD *px,bool compress=true);
	void bindTexture(glTexture *t);
	bool buildTarget(TRenderTargetList *pTarget,GLuint texid,int w,int h);
	SMTEX buildTexture(int w,int h,DWORD *px);
	void setBlend(int blend);
	void configProjectionMatrix2D(int w,int h);
	void configProjectionMatrix3D(int w,int h,float fov);
	void flipSDLSurface(int p,int h,void* px);
	DWORD* decodeImage(BYTE *data,const char *fn,DWORD size,int &w,int &h);

	void *pOpenALDevice;
	bool initOAL();
	void finiOAL();
	bool mute,lpp;
	int scnt;
	ALuint src[SRC_MAX];
	ALuint getSource();

	int posz,lkey;
	float posx,posy;
	SDL_Keymod keymods;
	bool mouseOver,captured;
	char keyz[256];
	bool keylst[256];
	TInputEventList *inpQueue;
	void initInput();
	void clearQueue();
	void buildEvent(int type,int k,int scan,int flags,int x,int y);
	bool procSDLEvent(const SDL_Event &e);
	int SDLKeyToSMKey(int sdlkey);

	float timeDelta,updateFPSDelay,fps,timeS;
	DWORD fixDelta,t0;
	int fcnt;
	DWORD dt;
private:
	SMELT_IMPL();
};
extern SMELT_IMPL *pSM;
#endif
