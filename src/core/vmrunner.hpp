#ifndef VMRUNNER_H
#define VMRUNNER_H
#include <cstring>
#include "smelt.hpp"
#include "smrandom.hpp"
#include "scriptshared.hpp"
const Idata ione=Idata(0,1),izero=Idata(0,0);
const Idata rone=Idata(1,1),rzero=Idata(1,0);
template<class memb>
class callStack
{
private:
	int t;
	memb data[16];
public:
	callStack(){clear();}
	void clear(){t=-1;}
	int size(){return t+1;}
	bool empty(){return size()==0;}
	void push(memb a){memcpy(data+(++t),&a,sizeof(a));if(t>15)throw;}
	memb pop(){if(~t)return data[t--];else throw;}
	memb top(){if(~t)return data[t];else throw;}
};
typedef struct _fncEntry{int hash,pos;}fncEntry;
class blrScriptVM
{
private:
	Idata ir[101],ia[10000];
	Idata rr[103],ra[10000];
	SInst inst[65537];
	int ic,fncnt,pinst,lops,lppos[8],lpjmp[8];
	fncEntry fncent[8];
	const unsigned char *sbyte,*cbyte;
	DWORD fsize;
	void readPara(SPara *para);
	int mgetc();
	Idata& fetchData(SPara para,bool forcerw=false);
public:
	smRandomEngine* re;
	blrScriptVM(){ic=fncnt=pinst=lops=0;}
	int loadLSBFromMemory(const char* ptr,DWORD size);
	int getInstCount();
	void vmRunFunction(const char *fncnym);
	void vmSetRetValf(double v);
	void vmSetRetVald(int v);
	void vmInit(unsigned int seed);
	void vmDeinit();
};
extern blrScriptVM *vm;
extern callStack<Idata> callStk;
#endif
