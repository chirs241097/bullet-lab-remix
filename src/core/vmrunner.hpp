#ifndef VMRUNNER_H
#define VMRUNNER_H
#include <cstring>
#include "smelt.hpp"
#include "smrandom.hpp"
#include "scriptshared.hpp"
const Idata ione=Idata(0,1),izero=Idata(0,0);
const Idata rone=Idata(1,1),rzero=Idata(1,0);
template<class memb>
class callStack//a queue, in fact.
{
private:
	int l,r;
	memb data[16];
public:
	callStack(){clear();}
	void clear(){l=0;r=-1;}
	int size(){return r-l+1;}
	bool empty(){return size()==0;}
	void push(memb a){memcpy(data+(++r),&a,sizeof(a));if(r>15)throw;}
	memb pop(){if(l<=r+1)return data[l++];else throw;}
	memb front(){return data[l];}
	memb back(){return data[r];}
};
typedef struct _fncEntry{int hash,pos;}fncEntry;
class blrScriptVM
{
private:
	Idata ir[101],ia[10000];
	Idata rr[103],ra[10000];
	SInst inst[65537];
	int ic,fncnt,pinst;
	fncEntry fncent[8];
	const unsigned char *sbyte,*cbyte;
	DWORD fsize;
	void readPara(SPara *para);
	int mgetc();
	Idata& fetchData(SPara para,bool forcerw=false);
public:
	smRandomEngine* re;
	blrScriptVM(){ic=fncnt=pinst=0;}
	int loadLSBFromMemory(const char* ptr,DWORD size);
	int getInstCount();
	void vmRunFunction(const char *fncnym);
	void vmSetRetValf(float v);
	void vmSetRetVald(int v);
	void vmInit(unsigned int seed);
	void vmDeinit();
};
extern blrScriptVM *vm;
extern callStack<Idata> callStk;
#endif
