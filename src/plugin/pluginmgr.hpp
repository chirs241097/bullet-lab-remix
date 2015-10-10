#ifndef PLUGINMGR_H
#define PLUGINMGR_H
class pluginManager
{
private:
	char fn[256][256];
	int fcnt;
	char pluginFolder[256];
public:
	pluginManager();
	void scanPlugin();
	void loadPlugin(const char* filename);
};
#endif

