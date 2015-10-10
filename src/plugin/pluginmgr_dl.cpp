#include <dlfcn.h>
#include <dirent.h>
#include "pluginmgr.hpp"
pluginManager::pluginManager()
{
	pluginFolder="./plugins";
}
void pluginManager::scanPlugin()
{
	DIR *dir;
	struct dirent *file;
	if(dir=opendir(pluginFolder))
	{
		while(file=readdir(dir))
		//puts(file->d_name);
		if(strcmp(file->d_name+strlen(file->d_name)-3,".so")==0)
			strcpy(fn[fcnt++],file->d_name);
		closedir(dir);
	}
}
