#include "../../include/smdatapack.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
int main(int argc,char** argv)
{
	if(argc<3)
	return printf("usage: %s <r/w> <anmfilename> [filetoread1/filetowrite1] ...\n",argv[0]),1;
	if(argv[1][0]=='w')
	{
		smDtpFileW file;
		for(int i=3;i<argc;++i)
		{
			char* rp=argv[i];
			if(*rp=='.'&&*(rp+1)=='/')rp+=2;
			if(!file.addFile(rp,argv[i]))
			printf("error adding file: %s\n",argv[i]);
		}
		char *wn=new char[strlen(argv[2])+10];
		strcat(wn,".writing");
		file.writeDtp(wn);
		char comm[256];
		sprintf(comm,"zcat %s > %s",wn,argv[2]);
		if(system(comm))
		puts("Error while trying decompressing the file, you may have to decompress it yourself.");
		else{sprintf(comm,"rm %s",wn);system(comm);}
		delete wn;
	}
	if(argv[1][0]=='r')
	{
		smDtpFileR file;
		FILE *pFile;DWORD size,rsize;char *buff;
		pFile=fopen(argv[2],"rb");
		if(!pFile)return 0;
		fseek(pFile,0,SEEK_END);size=ftell(pFile);rewind(pFile);
		buff=(char*)malloc(sizeof(char)*size);
		if(!buff)return 0;
		rsize=fread(buff,1,size,pFile);
		if(rsize!=size)return 0;
		file.openDtpFromMemory(buff,size);
		if(argc==3)
		{
			for(char* c=file.getFirstFile();c;c=file.getNextFile(c))
			{
				puts(c);
				char *ptr=file.getFilePtr(c);
				if(!ptr)printf("error\n");else
				printf("size:%lu, first bytes:%c%c%c\n",file.getFileSize(c),*ptr,*(ptr+1),*(ptr+2));
				file.releaseFilePtr(c);
			}
		}
		else
		for(int i=3;i<argc;++i)
		{
			char *ptr=file.getFilePtr(argv[i]);
			printf("size:%lu, first bytes:%c%c%c\n",file.getFileSize(argv[i]),*ptr,*(ptr+1),*(ptr+2));
			file.releaseFilePtr(argv[i]);
		}
		file.closeDtp();
		free(buff);
		fclose(pFile);
	}
}
