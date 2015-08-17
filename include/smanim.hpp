// -*- C++ -*-
/*
 * Simple MultimEdia LiTerator(SMELT)
 * by Chris Xiong 2015
 * Animation header
 *
 * WARNING: This library is in development and interfaces would be very
 * unstable.
 *
 */
#ifndef SMANIM_H
#define SMANIM_H
#include "smelt.hpp"
#include "smentity.hpp"
#include "smdatapack.hpp"
#include <map>
#include <string>

class smTexInfo
{
public:
	smTexRect rect;
	char *name,*path;
	SMTEX tex;
};
class smAnmInfo
{
public:
	smTexInfo frames[256];
	int framedur[256],mode,fc;
	char* name;
};
class smAnmFile
{
private:
	static SMELT *sm;
	smDtpFileR anm;
	void parseMeta(const char* meta,DWORD size);
	std::map<std::string,smTexInfo> tm;
	std::map<std::string,smAnmInfo> am;
	std::map<std::string,SMTEX> xm;
public:
	bool loadAnmFromMemory(const char* ptr,DWORD size);
	void close();
	smTexInfo* getTextureInfo(const char* name);
	smAnmInfo* getAnimationInfo(const char* name);
};
class smAnimation2D:public smEntity2D
{
private:
	smAnmInfo ai;
	smAnimation2D();
	int cf,mf,r;
public:
	smAnimation2D(smAnmInfo a);
	void updateAnim(int f=1);
	void resetAnim();
};
class smAnimation3D:public smEntity3D
{
private:
	smAnmInfo ai;
	smAnimation3D();
	int cf,mf,r;
public:
	smAnimation3D(smAnmInfo a);
	void updateAnim(int f=1);
	void resetAnim();
};
#endif
