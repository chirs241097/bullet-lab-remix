// -*- C++ -*-
/*
 * Simple MultimEdia LiTerator(SMELT)
 * by Chris Xiong 2015
 * DaTaPack format support implementation
 *
 * WARNING: This library is in development and interfaces would be very
 * unstable.
 * This library is developed for the BLR series games.
 */
#include "smdatapack.hpp"
#include <cstdio>
#include <cstring>
inline int gzgch(gzFile f){return gzgetc(f);}
inline DWORD gzgetDWORD(gzFile f)
{return ((gzgch(f)<<24)|(gzgch(f)<<16)|(gzgch(f)<<8)|gzgch(f))&0xFFFFFFFF;}
inline DWORD gch(const char *&cp){return (DWORD)((*(cp++))&0xFF);}
inline DWORD mmgetDWORD(const char *&cp){return ((gch(cp)<<24)|(gch(cp)<<16)|(gch(cp)<<8)|(gch(cp)))&0xFFFFFFFF;}
#define gzputDWORD(f,a) gzputc(f,a>>24);gzputc(f,(a>>16)&0xFF);gzputc(f,(a>>8)&0xFF);gzputc(f,a&0xFF);
bool smDtpFileR::openDtp(const char* path)
{
	file=gzopen(path,"r");
	if(!file)return false;enmemory=false;msize=0;
	if(gzgetc(file)!='D')return false;
	if(gzgetc(file)!='T')return false;
	if(gzgetc(file)!='P')return false;
	fcnt=gzgetc(file);
	for(int i=0;i<fcnt;++i)
	{
		int pl=gzgetc(file);
		smFileInfo f;
		f.path=new char[pl+1];f.data=NULL;
		for(int j=0;j<pl;++j)f.path[j]=gzgetc(file);
		f.path[pl]='\0';
		f.size=gzgetDWORD(file);
		f.offset=gzgetDWORD(file);
		f.crc=gzgetDWORD(file);
		m[std::string(f.path)]=f;
	}
	return true;
}
bool smDtpFileR::openDtpFromMemory(const char* ptr,DWORD size)
{
	enmemory=true;msize=size;
	if(!ptr||size<4)return false;
	if(ptr[0]!='D'||ptr[1]!='T'||ptr[2]!='P')return false;
	cp=ptr+3;bp=ptr;
	fcnt=*(cp++);
	for(int i=0;i<fcnt;++i)
	{
		int pl=*(cp++);
		smFileInfo f;
		f.path=new char[pl+1];f.data=NULL;
		for(int j=0;j<pl;++j)f.path[j]=*(cp++);
		f.path[pl]='\0';
		f.size=mmgetDWORD(cp);
		f.offset=mmgetDWORD(cp);
		f.crc=mmgetDWORD(cp);
		m[std::string(f.path)]=f;
	}
	return true;
}
void smDtpFileR::closeDtp()
{
	for(std::map<std::string,smFileInfo>::iterator i=m.begin();i!=m.end();++i)
	{
		delete[] i->second.path;i->second.path=NULL;
		if(i->second.data){delete[] i->second.data;i->second.data=NULL;}
		i->second.size=i->second.offset=i->second.crc=0;
	}
	fcnt=0;
	m.clear();if(!enmemory){gzclose(file);file=0;}
}
char* smDtpFileR::getFirstFile(){return m.begin()->second.path;}
char* smDtpFileR::getLastFile(){return (--m.end())->second.path;}
char* smDtpFileR::getNextFile(const char* path)
{
	std::map<std::string,smFileInfo>::iterator i=m.find(std::string(path));
	if(i==m.end()||(++i)==m.end())return NULL;
	return i->second.path;
}
char* smDtpFileR::getPrevFile(const char* path)
{
	std::map<std::string,smFileInfo>::iterator i=m.find(std::string(path));
	if(i==m.end()||i==m.begin())return NULL;--i;
	return i->second.path;
}
char* smDtpFileR::getFilePtr(const char* path)
{
	std::string fns(path);
	if(m.find(fns)==m.end()){printf("error: file not found in the archive.\n");return NULL;}
	if(m.at(fns).data)return m.at(fns).data;
	else
	{
		if(!m.at(fns).size){printf("error: empty file.\n");return NULL;}
		if(!enmemory)
		gzseek(file,m[fns].offset,SEEK_SET);
		else
		cp=bp+m[fns].offset;
		m[fns].data=new char[m[fns].size];
		if(!enmemory)
		{
			int r=gzread(file,m[fns].data,m[fns].size);
			if((unsigned)r<m[fns].size){delete[] m[fns].data;printf("error: file size mismatch.\n");return m[fns].data=NULL;}
		}
		else
		{
			if((cp-bp)+m[fns].size>msize){delete[] m[fns].data;printf("error: file size mismatch.\n");return m[fns].data=NULL;}
			memcpy(m[fns].data,cp,m[fns].size);
		}
		DWORD crc=crc32(0,(Bytef*)m[fns].data,m[fns].size);
		if(crc!=m[fns].crc)
		{delete[] m[fns].data;printf("error: crc mismatch.\n");return m[fns].data=NULL;}
		return m[fns].data;
	}
}
void smDtpFileR::releaseFilePtr(const char* path)
{
	std::string fns(path);
	if(m.find(fns)==m.end()){printf("error: file not found in the archive.\n");return;}
	if(m[fns].data)
	{
		delete[] m[fns].data;
		m[fns].data=NULL;
	}
}
DWORD smDtpFileR::getFileSize(const char* path)
{if(m.find(std::string(path))==m.end()){printf("error: file not found in the archive.\n");return 0;}return m[std::string(path)].size;}

smDtpFileW::smDtpFileW(){fcnt=0;}
bool smDtpFileW::addFile(const char* path,const char* realpath)
{
	FILE *pFile;DWORD size,rsize;
	pFile=fopen(realpath,"rb");
	if(!pFile)return false;
	fseek(pFile,0,SEEK_END);size=ftell(pFile);rewind(pFile);
	if(!size)return false;files[fcnt].data=NULL;
	files[fcnt].data=new char[size];
	if(!files[fcnt].data)return false;
	files[fcnt].path=new char[strlen(path)+1];
	strcpy(files[fcnt].path,path);
	rsize=fread(files[fcnt].data,1,size,pFile);
	if(rsize!=size)
	{
		delete[] files[fcnt].data;files[fcnt].data=NULL;
		delete[] files[fcnt].path;files[fcnt].path=NULL;
		return false;
	}
	files[fcnt].size=size;
	files[fcnt].crc=crc32(0,(Bytef*)files[fcnt].data,files[fcnt].size);
	++fcnt;
	fclose(pFile);
	return true;
}
bool smDtpFileW::writeDtp(const char* path)
{
	gzFile file=gzopen(path,"w");
	gzputs(file,"DTP");gzputc(file,fcnt);
	int metasize=4;
	for(int i=0;i<fcnt;++i)metasize+=strlen(files[i].path)+1+4+4+4;
	files[0].offset=metasize;
	for(int i=1;i<fcnt;++i)files[i].offset=files[i-1].offset+files[i-1].size;
	for(int i=0;i<fcnt;++i)
	{
		gzputc(file,strlen(files[i].path));
		gzputs(file,files[i].path);
		gzputDWORD(file,files[i].size);
		gzputDWORD(file,files[i].offset);
		gzputDWORD(file,files[i].crc);
	}
	for(int i=0;i<fcnt;++i)gzwrite(file,(voidpc)files[i].data,files[i].size);
	gzclose(file);
	for(int i=0;i<fcnt;++i)
	{
		files[i].size=files[i].offset=files[i].crc=0;
		delete[] files[i].data;files[i].data=NULL;
		delete[] files[i].path;files[i].path=NULL;
	}
	fcnt=0;
	return true;
}
