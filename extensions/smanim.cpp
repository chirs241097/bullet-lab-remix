// -*- C++ -*-
/*
 * Simple MultimEdia LiTerator(SMELT)
 * by Chris Xiong 2015
 * api level 1
 * Animation implementation
 *
 * WARNING: This library is in development and interfaces would be very
 * unstable.
 * This library is developed for the BLR series games.
 */
#include "smanim.hpp"
#include <cstdio>
#include <cstring>
#define METAWARN printf("metafile warning at line %d",lc)
void smAnmFile::parseMeta(char* meta,DWORD size)
{
	char* cp=meta;
	bool inAnim=false;
	int lc=0;
	smAnmInfo cur;
	while(cp-meta<=size)
	{
		int cc=0;
		for(;*(cp+cc)!='\n';++cc);
		char line[65];
		strncpy(cp,line,cc);line[cc-1]='\0';
		cp+=cc+1;++lc;
		if(inAnim&&line[0]!='F'&&line[0]!='E'){METAWARN;continue;}
		if(line[0]=='E')
		{
			if(!inAnim)METAWARN;
			else{inAnim=false;am[std::string(cur.name)]=cur;}
		}
		if(line[0]=='A')
		{
			if(inAnim)METAWARN;
			else
			{
				inAnim=true;
				int cn=0;while(line[cn+2]!=',')++cn;
				cur.name=new char[cn];strncpy(cur.name,line+2,cn);
				cur.name[cn-1]='\0';cur.mode=0;cur.fc=0;
				if(!strcmp(line+3+cn,"loop"))cur.mode=1;
				if(!strcmp(line+3+cn,"bidi"))cur.mode=2;
			}
		}
		if(line[0]=='F')
		{
			if(!inAnim)METAWARN;
			else
			{
				int cn=0;while(line[cn+2]!=',')++cn;
				cur.frames[cur.fc].path=new char[cn];
				cur.frames[cur.fc].name=NULL;
				strncpy(cur.frames[cur.fc].path,line+2,cn);
				cur.frames[cur.fc].path[cn-1]='\0';
				sscanf(line+3+cn,"%d,%d,%d,%d,%d",&cur.frames[cur.fc].rect.x,
				&cur.frames[cur.fc].rect.y,&cur.frames[cur.fc].rect.w,&cur.frames[cur.fc].rect.h,
				&cur.framedur[cur.fc]);
				if(xm.find(std::string(cur.frames[cur.fc].path))!=xm.end())
				cur.frames[cur.fc].tex=xm[std::string(cur.frames[cur.fc].path)];
				else
				{
					char *texct=anm.getFilePtr(cur.frames[cur.fc].path);
					DWORD texsz=anm.getFileSize(cur.frames[cur.fc].path);
					cur.frames[cur.fc].tex=xm[std::string(cur.frames[cur.fc].path)]
					=sm->smTextureLoadFromMemory(texct,texsz);
					anm.releaseFilePtr(cur.frames[cur.fc].path);
				}
				++cur.fc;
			}
		}
		if(line[0]=='S')
		{
			smTexInfo t;
			int cn=0;while(line[cn+2]!=',')++cn;
			t.name=new char[cn];strncpy(t.name,line+2,cn);
			t.name[cn-1]='\0';
			int cn2=0;while(line[cn+3+cn2]!=',')++cn2;
			t.path=new char[cn2];strncpy(t.path,line+3+cn,cn2);
			t.path[cn2-1]='\0';
			sscanf(line+4+cn+cn2,"%d,%d,%d,%d",&t.rect.x,&t.rect.y,&t.rect.w,&t.rect.h);
			tm[std::string(t.name)]=t;
			if(xm.find(std::string(t.path))!=xm.end())
			t.tex=xm[std::string(t.path)];
			else
			{
				char *texct=anm.getFilePtr(t.path);
				DWORD texsz=anm.getFileSize(t.path);
				t.tex=xm[std::string(t.path)]
				=sm->smTextureLoadFromMemory(texct,texsz);
				anm.releaseFilePtr(t.path);
			}
		}
		if(line[0]=='I')
		{
			char* mptr=anm.getFilePtr(line+2);
			DWORD msez=anm.getFileSize(line+2);
			parseMeta(mptr,msez);
			anm.releaseFilePtr(line+2);
		}
	}
}
bool smAnmFile::loadAnmFromMemory(char* ptr,DWORD size)
{
	sm=smGetInterface(SMELT_APILEVEL);
	anm.openDtpFromMemory(ptr,size);
	xm.clear();tm.clear();am.clear();
	char* mptr=anm.getFilePtr("content.meta");
	DWORD msez=anm.getFileSize("content.meta");
	parseMeta(mptr,msez);
	anm.releaseFilePtr("content.meta");
}
void smAnmFile::close()
{
	anm.closeDtp();
	for(std::map<std::string,smTexInfo>::iterator i=tm.begin();i!=tm.end();++i)
	{delete i->second.name;delete i->second.path;}
	tm.clear();
	for(std::map<std::string,smAnmInfo>::iterator i=am.begin();i!=am.end();++i)
	{
		delete i->second.name;
		for(int j=0;j<i->second.fc;++j)
		delete i->second.frames[j].path;
	}
	am.clear();
	for(std::map<std::string,SMTEX>::iterator i=xm.begin();i!=xm.end();++i)
	sm->smTextureFree(i->second);
	xm.clear();
	sm->smRelease();
}
smTexInfo* smAnmFile::getTextureInfo(const char* name)
{return &tm.at(name);}
smAnmInfo* smAnmFile::getAnimationInfo(const char* name)
{return &am.at(name);}

smAnimation2D::smAnimation2D(smAnmInfo a):smEntity2D(a.frames[0].tex,a.frames[0].rect)
{
	ai=a;cf=mf=r=0;
	for(int i=0;i<ai.fc;++i)mf+=ai.framedur[i];
}
void smAnimation2D::updateAnim(int f)
{
	if(ai.mode==0){cf+=f;if(cf>mf)cf=mf;}
	if(ai.mode==1){cf+=f;if(cf>mf)cf-=mf;}
	if(ai.mode==2)
	{
		if(r){cf-=f;if(cf<0)r=0,cf=-cf;}
		else{cf+=f;if(cf>mf)r=1,cf=2*mf-cf;}
	}
	int l=0,r=ai.framedur[0],ff=0;
	for(int i=0;i<ai.fc;++i)
	{
		if(cf>l&&cf<=r){ff=i;break;}
		l+=ai.framedur[i];r+=ai.framedur[i+1];
	}
	setTexture(ai.frames[ff].tex);
	setTextureRectv(ai.frames[ff].rect);
}
void smAnimation2D::resetAnim()
{
	cf=mf=r=0;
	setTexture(ai.frames[0].tex);
	setTextureRectv(ai.frames[0].rect);
}

smAnimation3D::smAnimation3D(smAnmInfo a):smEntity3D(a.frames[0].tex,a.frames[0].rect)
{
	ai=a;cf=mf=r=0;
	for(int i=0;i<ai.fc;++i)mf+=ai.framedur[i];
}
void smAnimation3D::updateAnim(int f)
{
	if(ai.mode==0){cf+=f;if(cf>mf)cf=mf;}
	if(ai.mode==1){cf+=f;if(cf>mf)cf-=mf;}
	if(ai.mode==2)
	{
		if(r){cf-=f;if(cf<0)r=0,cf=-cf;}
		else{cf+=f;if(cf>mf)r=1,cf=2*mf-cf;}
	}
	int l=0,r=ai.framedur[0],ff=0;
	for(int i=0;i<ai.fc;++i)
	{
		if(cf>l&&cf<=r){ff=i;break;}
		l+=ai.framedur[i];r+=ai.framedur[i+1];
	}
	setTexture(ai.frames[ff].tex);
	setTextureRectv(ai.frames[ff].rect);
}
void smAnimation3D::resetAnim()
{
	cf=mf=r=0;
	setTexture(ai.frames[0].tex);
	setTextureRectv(ai.frames[0].rect);
}
