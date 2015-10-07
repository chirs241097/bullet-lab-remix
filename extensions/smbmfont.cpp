// -*- C++ -*-
/*
 * Simple MultimEdia LiTerator(SMELT)
 * by Chris Xiong 2015
 * Bitmap font support implementation
 *
 * WARNING: This library is in development and interfaces would be very
 * unstable.
 * This library is developed for the BLR series games.
 */
#include "smbmfont.hpp"
#include <cstdio>
#include <cstring>
#include <cstdarg>

SMELT *smBMFont::sm=NULL;
SMELT *smBMFontw::sm=NULL;

void smBMFont::parseMeta(const char* meta,DWORD size)
{
	const char* cp=meta;
	char line[65];
	int cc,cod,pa,pb;smTexRect rct;
	while(cp-meta<=size)
	{
		cc=0;
		for(;*(cp+cc)!='\n'&&cp+cc-meta<=size;++cc);
		strncpy(line,cp,cc);if(line[cc]=='\n')line[cc]='\0';
		cp+=cc+1;
		char* tp=strchr(line,',');
		if(tp)*tp='\0';else continue;
		sscanf(tp+1,"%d,%f,%f,%f,%f,%d,%d",&cod,&rct.x,&rct.y,&rct.w,&rct.h,&pb,&pa);
		if(cod>=0&&cod<256)
		{
			if(xm.find(std::string(line))==xm.end())
			{
				char* texct=anm.getFilePtr(line);
				DWORD texsz=anm.getFileSize(line);
				xm[std::string(line)]=sm->smTextureLoadFromMemory(texct,texsz);
				anm.releaseFilePtr(line);
			}
			chars[cod]=new smEntity2D(xm[std::string(line)],rct);
			pdb[cod]=pb;pda[cod]=pa;if(hadv<rct.h)hadv=(float)rct.h;
		}
	}
}
bool smBMFont::loadAnmFromMemory(const char* ptr,DWORD size)
{
	sm=smGetInterface(SMELT_APILEVEL);
	anm.openDtpFromMemory(ptr,size);hadv=0;
	xm.clear();memset(chars,0,sizeof(chars));
	char* mptr=anm.getFilePtr("content.meta");
	DWORD msez=anm.getFileSize("content.meta");
	parseMeta(mptr,msez);
	anm.releaseFilePtr("content.meta");
	setBlend(BLEND_ALPHABLEND);
	setColor(0xFFFFFFFF);
	return true;
}
void smBMFont::close()
{
	anm.closeDtp();
	for(int i=0;i<256;++i)if(chars[i]){delete chars[i];chars[i]=NULL;}
	for(std::map<std::string,SMTEX>::iterator i=xm.begin();i!=xm.end();++i)
	sm->smTextureFree(i->second);
	xm.clear();
	sm->smRelease();
}
void smBMFont::render(float x,float y,float z,int align,float *rw,const char* text)
{
	float width=0,cw=0,ofs=x;
	const char* t=text;
	while(*t)
	{
		cw=0;
		for(;*t&&*t!='\n';++t)
		{
			if(chars[(int)*t])
			cw+=chars[(int)*t]->_w()+pdb[(int)*t]+pda[(int)*t];
		}
		if(cw>width)width=cw;
		while(*t=='\n')++t;
	}
	width*=sc;
	if(rw)*rw=width;
	if(align==ALIGN_CENTER)ofs-=width/2.;
	if(align==ALIGN_RIGHT)ofs-=width;
	while(*text)
	{
		if(*text=='\n')
		{
			y+=hadv*sc;ofs=x;
			if(align==ALIGN_CENTER)ofs-=width/2.;
			if(align==ALIGN_RIGHT)ofs-=width;
		}
		else
		{
			if(chars[(int)*text])
			{
				ofs+=pdb[(int)*text]*sc;
				chars[(int)*text]->setZ(z);
				chars[(int)*text]->setColor(color);
				chars[(int)*text]->setBlend(b);
				chars[(int)*text]->render(ofs,y,0,sc);
				ofs+=(chars[(int)*text]->_w()+pda[(int)*text])*sc;
			}
		}
		++text;
	}
}
void smBMFont::printf(float x,float y,float z,int align,float *rw,const char* format,...)
{
	char buf[1024];
	va_list vl;
	va_start(vl,format);
	vsnprintf(buf,sizeof(buf)-1,format,vl);
	va_end(vl);
	buf[sizeof(buf)-1]='\0';
	render(x,y,z,align,rw,buf);
}

void smBMFontw::parseMeta(char* meta,DWORD size)
{
	char* cp=meta;
	char line[65];
	int cc,cod,pa,pb;smTexRect rct;
	while(cp-meta<=size)
	{
		cc=0;
		for(;*(cp+cc)!='\n'&&cp+cc-meta<=size;++cc);
		strncpy(line,cp,cc);if(line[cc]=='\n')line[cc]='\0';
		cp+=cc+1;
		char* tp=strchr(line,',');
		if(tp)*tp='\0';else continue;
		sscanf(tp+1,"%d,%f,%f,%f,%f,%d,%d",&cod,&rct.x,&rct.y,&rct.w,&rct.h,&pb,&pa);
		if(cod>=WCHAR_MIN&&cod<=WCHAR_MAX)
		{
			if(xm.find(std::string(line))==xm.end())
			{
				char* texct=anm.getFilePtr(line);
				DWORD texsz=anm.getFileSize(line);
				xm[std::string(line)]=sm->smTextureLoadFromMemory(texct,texsz);
				anm.releaseFilePtr(line);
			}
			chars[cod]=new smEntity2D(xm.find(std::string(line))->second,rct);
			pdb[cod]=pb;pda[cod]=pa;if(hadv<rct.h)hadv=(float)rct.h;
		}
	}
}
bool smBMFontw::loadAnmFromMemory(char* ptr,DWORD size)
{
	sm=smGetInterface(SMELT_APILEVEL);
	anm.openDtpFromMemory(ptr,size);hadv=0;
	xm.clear();chars.clear();pdb.clear();pda.clear();
	char* mptr=anm.getFilePtr("content.meta");
	DWORD msez=anm.getFileSize("content.meta");
	parseMeta(mptr,msez);
	anm.releaseFilePtr("content.meta");
	return true;
}
void smBMFontw::close()
{
	anm.closeDtp();
	for(std::map<wchar_t,smEntity2D*>::iterator i=chars.begin();i!=chars.end();++i)if(i->second){delete i->second;i->second=NULL;}
	for(std::map<std::string,SMTEX>::iterator i=xm.begin();i!=xm.end();++i)
	sm->smTextureFree(i->second);
	xm.clear();chars.clear();pdb.clear();pda.clear();
	sm->smRelease();
}
void smBMFontw::render(float x,float y,float z,int align,float *rw,const wchar_t* text)
{
	float width=0,cw=0,ofs=x;
	const wchar_t* t=text;
	while(*t)
	{
		cw=0;
		for(;*t&&*t!='\n';++t)
		{
			if(chars[*t])
			cw+=chars[*t]->_w()+pdb[*t]+pda[*t];
		}
		if(cw>width)width=cw;
		while(*t=='\n')++t;
	}
	width*=sc;
	if(rw)*rw=width;
	if(align==ALIGN_CENTER)ofs-=width/2.;
	if(align==ALIGN_RIGHT)ofs-=width;
	while(*text)
	{
		if(*text=='\n')
		{
			y+=hadv*sc;ofs=x;
			if(align==ALIGN_CENTER)ofs-=width/2.;
			if(align==ALIGN_RIGHT)ofs-=width;
		}
		else
		{
			if(chars[*text])
			{
				ofs+=pdb[*text]*sc;
				chars[*text]->setZ(z);
				chars[*text]->setColor(color);
				chars[*text]->setBlend(b);
				chars[*text]->render(ofs,y,0,sc);
				ofs+=(chars[*text]->_w()+pda[*text])*sc;
			}
		}
		++text;
	}
}
void smBMFontw::printf(float x,float y,float z,int align,float *rw,const wchar_t* format,...)
{
	wchar_t buf[1024];
	va_list vl;
	va_start(vl,format);
	vswprintf(buf,sizeof(buf)-1,format,vl);
	va_end(vl);
	buf[sizeof(buf)-1]='\0';
	render(x,y,z,align,rw,buf);
}
