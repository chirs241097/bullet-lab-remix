// -*- C++ -*-
/*
 * Simple MultimEdia LiTerator(SMELT)
 * by Chris Xiong 2015
 * DaTaPack format support header
 *
 * WARNING: This library is in development and interfaces would be very
 * unstable.
 *
 */
#ifndef SMDTP_H
#define SMDTP_H
#include "smelt.hpp"
#include <cstdlib>
#include <zlib.h>
#include <string>
#include <map>
class smFileInfo
{
public:
	char *path,*data;
	DWORD size,offset,crc;
};
class smDtpFileR
{
private:
	int fcnt;
	gzFile file;
	std::map<std::string,smFileInfo> m;

	bool enmemory;
	DWORD msize;
	const char *cp,*bp;
public:
	bool openDtp(const char* path);
	bool openDtpFromMemory(const char* ptr,DWORD size);
	void closeDtp();
	char* getFirstFile();
	char* getLastFile();
	char* getNextFile(const char* path);
	char* getPrevFile(const char* path);
	char* getFilePtr(const char* path);
	void releaseFilePtr(const char* path);
	DWORD getFileSize(const char* path);
};
class smDtpFileW
{
private:
	smFileInfo files[256];
	int fcnt;
public:
	smDtpFileW();
	bool addFile(const char* path,const char* realpath);
	bool writeDtp(const char* path);
};
#endif
