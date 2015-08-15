// -*- C++ -*-
/*
 * Simple MultimEdia LiTerator(SMELT)
 * by Chris Xiong 2015
 * Truetype font support header
 *
 * WARNING: This library is in development and interfaces would be very
 * unstable.
 * This library is developed for the BLR series games.
 */
#ifndef SMTTFONT_H
#define SMTTFONT_H
#include "smelt.hpp"
#include <cwchar>
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H

#ifndef ALIGN_LEFT
#define ALIGN_LEFT 0
#define ALIGN_RIGHT 1
#define ALIGN_CENTER 2
#endif

class smTTChar
{
private:
	smQuad quad;
	int rw,rh,_w,_h,xofs,yofs;
	static SMELT *sm;
public:
	float w(){return (float)_w;}
	float h(){return (float)_h;}
	void free();
	bool setChar(wchar_t c,FT_Face ttface);
	void render(float x,float y,DWORD col);
};

class smTTFont
{
protected:
	FT_Library ftlib;
	FT_Face ttface;
private:
	wchar_t buf[1024];
	std::map<wchar_t,smTTChar> chars;
	float w,h;
public:
	bool loadTTF(const char* path,int pt);
	bool loadTTFFromMemory(char* ptr,DWORD size,int pt);
	void releaseTTF();
	float getWidth(){return w;}
	float getHeight(){return h;}
	void updateString(const wchar_t *format,...);
	void render(float x,float y,DWORD col,int align);
	DWORD getCacheSize();
	void clearCache();
};
#endif
