#include "vmrunner.hpp"
#include "coreshared.hpp"
#include <cstdlib>
unsigned getHash(const char *s)
{
	unsigned r=5381;char c;
	while((c=(*s++)))r=((r<<5)+r)+c;
	return r;
}
Idata& blrScriptVM::fetchData(SPara para,bool forcerw)
{
	static Idata cret;
	switch (para.type)
	{
		case 0:
			if(forcerw)throw;
			cret.i()=para.data.i;cret.type=0;
			return cret;
		case 1:
			if(forcerw)throw;
			cret.r()=para.data.r;cret.type=1;
			return cret;
		case 2:
			return ir[para.data.i];
		case 3:
			return rr[para.data.i];
		case 4:
			return ia[para.data.i];
		case 5:
			return ra[para.data.i];
		case 6:
			return ia[ir[para.data.i].i()];
		case 7:
			return ra[ir[para.data.i].i()];
		default:
			throw;
	}
}
int blrScriptVM::mgetc()
{
	if(cbyte-sbyte<fsize)
	{++cbyte;return (int)*(cbyte-1);}
	else return -1;
}
void blrScriptVM::readPara(SPara *para)
{
	para->type=mgetc();
	para->data.d=0;
	int l=0;
	switch(para->type)
	{
		case 1: l=8;break;
		case 0: case 4: case 5: l=4;break;
		case 2: case 3: case 6: case 7: l=1;break;
		default: break;
	}
	for(int i=0;i<l;++i)
	{
		para->data.d<<=8LL;
		para->data.d|=(unsigned long long)mgetc();
	}
}
int blrScriptVM::loadLSBFromMemory(const char *ptr,DWORD size)
{
	cbyte=sbyte=ptr;fsize=size;
	int ibyt=0,infunc=0;
	while(~(ibyt=mgetc()))
	{
		++ic;inst[ic].id=ibyt;
		switch(inst[ic].id)
		{
			case 0xFF: case 0x02:
			{
				int nl=mgetc();
				if(nl==-1)return 1;
				if(inst[ic].id==0xFF){if(infunc)return 1;else infunc=1;}
				if(inst[ic].id==0x02)if(!infunc)return 1;
				inst[ic].para1.fnc=(char*)calloc(sizeof(char),nl+1);
				inst[ic].para1.type=8;
				for(int i=0;i<nl;++i)inst[ic].para1.fnc[i]=mgetc();
				if(inst[ic].id==0xFF)
				{
					fncent[fncnt].pos=ic;
					fncent[fncnt++].hash=getHash(inst[ic].para1.fnc);
				}
			}
			break;
			case 0x00: break;
			case 0xFE:
				if(!infunc)return 1;
				infunc=0;
			break;
			case 0x0F:
				if(!infunc)return 1;
			break;
			case 0x01: case 0x0C: case 0x0D:
			case 0x0E: case 0x11: case 0x12:
			case 0x13: case 0x14: case 0x15:
			case 0x16: case 0x21:
				if(!infunc)return 1;
				readPara(&inst[ic].para1);
			break;
			case 0x03: case 0x04: case 0x05:
			case 0x06: case 0x07: case 0x08:
			case 0x09: case 0x0A: case 0x0B:
			case 0x22: case 0x23:
				if(!infunc)return 1;
				readPara(&inst[ic].para1);
				readPara(&inst[ic].para2);
			break;
		}
	}
	return 0;
}
int blrScriptVM::getInstCount(){return pinst;}
void blrScriptVM::runFunction(const char *fncnym)
{
	int nymhash=getHash(fncnym),cur=0;pinst=0;
	for(int i=0;i<fncnt;++i)if(nymhash==fncent[i].hash){cur=fncent[i].pos;break;}
	while(inst[cur].id!=0xFE)
	{
		int jmp=0;++pinst;
		//printf("@offset %d, instId 0x%x\n",cur,inst[cur].id);
		rr[100].r()=0.01667;
		//printf("r00: %f, r01: %f\n",rr[0].r(),rr[1].r());
		switch(inst[cur].id)
		{
			case 0x00:
				//no-op
			break;
			case 0xFF:
				//no-op
			break;
			case 0x01:
				callStk.push(fetchData(inst[cur].para1));
			break;
			case 0x02:
				//callFnc(inst[cur].para1.fnc);
				//callstk.clear();
				//printf("stubbed call %s\n",inst[cur].para1.fnc);
			break;
			case 0x03:
				fetchData(inst[cur].para1,true)=fetchData(inst[cur].para2);
			break;
			case 0x04:
				fetchData(inst[cur].para1,true)+=fetchData(inst[cur].para2);
			break;
			case 0x05:
				fetchData(inst[cur].para1,true)-=fetchData(inst[cur].para2);
			break;
			case 0x06:
				fetchData(inst[cur].para1,true)*=fetchData(inst[cur].para2);
			break;
			case 0x07:
				fetchData(inst[cur].para1,true)/=fetchData(inst[cur].para2);
			break;
			case 0x08:
				fetchData(inst[cur].para1,true)%=fetchData(inst[cur].para2);
			break;
			case 0x09:
				fetchData(inst[cur].para1,true)&=fetchData(inst[cur].para2);
			break;
			case 0x0A:
				fetchData(inst[cur].para1,true)|=fetchData(inst[cur].para2);
			break;
			case 0x0B:
				fetchData(inst[cur].para1,true)^=fetchData(inst[cur].para2);
			break;
			case 0x0C:
				fetchData(inst[cur].para1,true)=~fetchData(inst[cur].para1,true);
			break;
			case 0x0D:
				++fetchData(inst[cur].para1,true);
			break;
			case 0x0E:
				--fetchData(inst[cur].para1,true);
			break;
			case 0x0F:
				callStk.clear();
			break;
			case 0x11:
				switch (fetchData(inst[cur].para1,true).type)
				{
					case 0:
					fetchData(inst[cur].para1,true)=
					fetchData(inst[cur].para1,true).ltz()?ione:izero;
					break;
					case 1:
					fetchData(inst[cur].para1,true)=
					fetchData(inst[cur].para1,true).ltz()?rone:rzero;
					break;
				}
			break;
			case 0x12:
				switch (fetchData(inst[cur].para1,true).type)
				{
					case 0:
					fetchData(inst[cur].para1,true)=
					fetchData(inst[cur].para1,true).elz()?ione:izero;
					break;
					case 1:
					fetchData(inst[cur].para1,true)=
					fetchData(inst[cur].para1,true).elz()?rone:rzero;
					break;
				}
			break;
			case 0x13:
				switch (fetchData(inst[cur].para1,true).type)
				{
					case 0:
					fetchData(inst[cur].para1,true)=
					fetchData(inst[cur].para1,true).gtz()?ione:izero;
					break;
					case 1:
					fetchData(inst[cur].para1,true)=
					fetchData(inst[cur].para1,true).gtz()?rone:rzero;
					break;
				}
			break;
			case 0x14:
				switch (fetchData(inst[cur].para1,true).type)
				{
					case 0:
					fetchData(inst[cur].para1,true)=
					fetchData(inst[cur].para1,true).egz()?ione:izero;
					break;
					case 1:
					fetchData(inst[cur].para1,true)=
					fetchData(inst[cur].para1,true).egz()?rone:rzero;
					break;
				}
			break;
			case 0x15:
				switch (fetchData(inst[cur].para1,true).type)
				{
					case 0:
					fetchData(inst[cur].para1,true)=
					fetchData(inst[cur].para1,true).eqz()?ione:izero;
					break;
					case 1:
					fetchData(inst[cur].para1,true)=
					fetchData(inst[cur].para1,true).eqz()?rone:rzero;
					break;
				}
			break;
			case 0x16:
				switch (fetchData(inst[cur].para1,true).type)
				{
					case 0:
					fetchData(inst[cur].para1,true)=
					fetchData(inst[cur].para1,true).nez()?ione:izero;
					break;
					case 1:
					fetchData(inst[cur].para1,true)=
					fetchData(inst[cur].para1,true).nez()?rone:rzero;
					break;
				}
			break;
			case 0x21:
				cur=fetchData(inst[cur].para1).i();
				jmp=1;
			break;
			case 0x22:
				if(fetchData(inst[cur].para1).eqz())
					cur=fetchData(inst[cur].para2).i(),jmp=1;
			break;
			case 0x23:
				if(fetchData(inst[cur].para1).nez())
					cur=fetchData(inst[cur].para2).i(),jmp=1;
			break;
		}
		if(!jmp)++cur;
	}
}
void blrScriptVM::vmInit()
{
}
void blrScriptVM::vmDeinit()
{
}
