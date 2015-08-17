// -*- C++ -*-
/*
 * Simple MultimEdia LiTerator(SMELT)
 * by Chris Xiong 2015
 * Bitmap font support header
 *
 * WARNING: This library is in development and interfaces would be very
 * unstable.
 *
 */
 #ifndef SMBMFONT_H
#define SMBMFONT_H
#include "smanim.hpp"
#include <cwchar>
#ifndef ALIGN_LEFT
#define ALIGN_LEFT 0
#define ALIGN_RIGHT 1
#define ALIGN_CENTER 2
#endif
class smBMFont
{
private:
	static SMELT *sm;
	smDtpFileR anm;
	float sc,hadv;
	smEntity2D* chars[256];
	int pdb[256],pda[256],b;
	DWORD color;
	std::map<std::string,SMTEX> xm;
	void parseMeta(const char* meta,DWORD size);
public:
	bool loadAnmFromMemory(const char* ptr,DWORD size);
	void close();
	void render(float x,float y,float z,int align,float *rw,const char* text);
	void printf(float x,float y,float z,int align,float *rw,const char* format,...);
	void setColor(DWORD col){color=col;}
	void setBlend(int blend){b=blend;}
	void setScale(float scale){sc=scale;}
};
class smBMFontw
{
private:
	static SMELT *sm;
	smDtpFileR anm;
	float sc,hadv;
	int b;
	DWORD color;
	std::map<std::string,SMTEX> xm;
	std::map<wchar_t,smEntity2D*> chars;
	std::map<wchar_t,int> pdb,pda;
	void parseMeta(char* meta,DWORD size);
public:
	bool loadAnmFromMemory(char* ptr,DWORD size);
	void close();
	void render(float x,float y,float z,int align,float *rw,const wchar_t* text);
	void printf(float x,float y,float z,int align,float *rw,const wchar_t* format,...);
	void setColor(DWORD col){color=col;}
	void setBlend(int blend){b=blend;}
	void setScale(float scale){sc=scale;}
};
#endif
