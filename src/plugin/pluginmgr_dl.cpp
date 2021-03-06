#include <dlfcn.h>
#include <dirent.h>
#include <cstring>
#include "pluginmgr.hpp"
pluginManager::pluginManager()
{
	strcpy(pluginFolder,"./plugins");
}
void pluginManager::scanPlugin()
{
	DIR *dir;
	struct dirent *file;
	if((dir=opendir(pluginFolder)))
	{
		while((file=readdir(dir)))
		//puts(file->d_name);
		if(strcmp(file->d_name+strlen(file->d_name)-3,".so")==0)
			strcpy(fn[fcnt++],file->d_name);
		closedir(dir);
	}
	for(int i=0;i<fcnt;++i)
	{
		void* hso=dlopen(fn[i],RTLD_LAZY);
		if(!hso)continue;
		void* hndi=dlsym(hso,"getPluginInterface");
		if(!hndi)continue;
	}
}
