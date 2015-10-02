#include "smdatapack.hpp"
#include "smbmfont.hpp"
smDtpFileR blrdtp;
smBMFont lcdfont;
smAnmFile ssanm;
void resourcesLoad()
{
	blrdtp.openDtp("blr3.dtp");
	lcdfont.loadAnmFromMemory(blrdtp.getFilePtr("lcdfont.anm"),blrdtp.getFileSize("lcdfont.anm"));
	lcdfont.setScale(0.6);
	ssanm.loadAnmFromMemory(blrdtp.getFilePtr("ss.anm"),blrdtp.getFileSize("ss.anm"));
}
void resourcesUnload()
{
	blrdtp.closeDtp();
	lcdfont.close();
	ssanm.close();
}
