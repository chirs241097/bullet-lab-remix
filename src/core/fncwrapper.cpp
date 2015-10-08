#include "vmrunner.hpp"
#include "fncmodules.hpp"
#define bindFuncr(fs,fn) if(getHash(fnc)==getHash(fs))vm->vmSetRetValf(fn().r())
#define bindFunci(fs,fn) if(getHash(fnc)==getHash(fs))vm->vmSetRetVald(fn().i())
#define bindFuncv(fs,fn) if(getHash(fnc)==getHash(fs))fn()
extern unsigned getHash(const char *s);
void callFnc(const char* fnc)
{
	bindFunci("randi",randi);bindFuncr("randr",randr);
	bindFunci("createBullet",createBullet);
	bindFuncv("setBulletPropf",setBulletPropf);
	bindFuncv("setBulletPropi",setBulletPropi);
	bindFuncr("sin",vmsin);bindFuncr("cos",vmcos);
	bindFuncr("tan",vmtan);bindFuncr("sqrt",vmsqrt);
	bindFuncr("absf",vmabsf);bindFunci("absd",vmabsd);
	bindFuncr("asin",vmasin);bindFuncr("acos",vmacos);
	bindFuncr("atan",vmatan);bindFuncr("atan2",vmatan2);
	bindFuncr("log",vmlog);bindFuncr("ceil",vmceil);
	bindFuncr("floor",vmfloor);bindFuncr("trunc",vmtrunc);
	bindFuncr("round",vmround);
	if(callStk.empty())callStk.clear();
}
