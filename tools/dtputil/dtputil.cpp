#include "../../include/smdatapack.hpp"
#include <cstdio>
int main(int argc,char** argv)
{
	if(argc<3)
	return printf("usage: %s <r/w> <dtpfilename> [filetoread1/filetowrite1] ...\n",argv[0]),1;
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
		file.writeDtp(argv[2]);
	}
	if(argv[1][0]=='r')
	{
		smDtpFileR file;
		file.openDtp(argv[2]);
		if(argc==3)
		{
			for(char* c=file.getFirstFile();c;c=file.getNextFile(c))
			{
				puts(c);
				char *ptr=file.getFilePtr(c);
				if(!ptr)printf("error\n");else
				printf("size:%u, CRC: 0x%08X\n",file.getFileSize(c),file.getFileCRC(c));
				file.releaseFilePtr(c);
			}
		}
		else
		for(int i=3;i<argc;++i)
		{
			char *ptr=file.getFilePtr(argv[i]);
			if(!ptr)printf("error\n");else
			printf("size:%u, CRC: 0x%08X\n",file.getFileSize(argv[i]),file.getFileCRC(argv[i]));
			file.releaseFilePtr(argv[i]);
		}
		file.closeDtp();
	}
}
