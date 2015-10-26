/*
 * Extra coding style for parser.cpp...
 * 1. write C-like C++ code...(e.g. typedef struct _x{...}x; instead of
 * struct x{...};
 * 2. DO NOT USE STL!
 * 3. if you don't like the rules above, you can ignore them though...
 */
//parser: primitive version.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdarg>
#include "scriptshared.hpp"
/*
 * SPara...
 * type=-1: Invalid Parameter
 * type=0 : integer, data.i
 * type=1 : real, data.r
 * type=2 : int register, #data.i
 * type=3 : real register, #data.i
 * type=4 : int array member, const subs, #data.i
 * type=5 : real array member, const subs, #data.i
 * type=6 : int array member, register subs, #[intreg]data.i
 * type=7 : real array member, register subs, #[intreg]data.i
 * type=8 : function name
 */
SInst result[65537];
int infunc,lc,lops,lppos[8];
char line[256],fst[16];
void error(const char *szFormat,...)
{
	va_list ap;
	va_start(ap,szFormat);
	vfprintf(stderr,szFormat,ap);
	va_end(ap);
	fprintf(stderr,"\n");
	exit(1);
}
int hexBit(char b)
{
	if(b>='0'&&b<='9')return b-'0';
	if(b>='a'&&b<='f')return b-'a'+10;
	if(b>='A'&&b<='F')return b-'A'+10;
	return -1;
}
Udata parseNumber(char *l,char *r,int mode)//0:real, 1:int, 2:linenum
{
	int i=0,m=1,absln=1;double d=0,mlt=0.1;Udata res;
	char *c=l;res.d=0LL;
	if(*c=='x')
	{
		++c;
		for(;~hexBit(*c)&&c!=r;++c)i*=16,i+=hexBit(*c);
		if(c!=r){res.r=nan("");return res;}
		res.i=m*i;return res;
	}
	if(*c=='+')m=1,++c,absln=0;
	if(*c=='-')m=-1,++c,absln=0;
	for(;*c>='0'&&*c<='9'&&c!=r;++c)i*=10,i+=*c-'0';
	if(c==r)
	{mode==2?res.i=(absln?m*i:lc+m*i):mode==1?res.i=m*i:res.r=(double)m*i;return res;}
	if(*c!='.'||mode!=0){res.r=nan("");return res;}
	++c;
	for(;*c>='0'&&*c<='9'&&c!=r;++c)d+=(*c-'0')*mlt,mlt*=0.1;
	if(c!=r){res.r=nan("");return res;}
	res.r=d+i;return res;
}
int parsePara(char *cont,char *contr,SPara *para,int mode)
/* mode:
 * 0:all(excluding function name)
 * 1:register only
 * 2:constant only
 * 3:integer only
 * 4:integer register only
 * 5:real only				<-shouldn't this accept all?...
 * 6:real register only
 * 7:function name
 * 8:line number
 */
{
	para->type=-1;
	if(mode==6)
	{
		para->fnc=(char*)calloc(16,sizeof(char));
		strcpy(para->fnc,cont);
		para->type=8;
		return 0;
	}
	if(cont[0]=='r')
	{
		if(mode==2||mode==3||mode==4)return 1;//reject if...
		if(cont[1]=='[')//r[number], r[ixx]
		{
			char *c=&cont[2];
			while(*c!=']'&&c!=contr)++c;
			if(*c!=']')return 1;//brace mismatch
			if(cont[2]=='i')
			{
				Udata d=parseNumber(&cont[3],c,1);
				if(isnan(d.r))return 1;
				if(d.i<0||d.i>99)return 1;
				para->type=7;para->data=d;
				return 0;
			}
			Udata d=parseNumber(&cont[2],c,1);
			if(isnan(d.r))return 1;
			if(d.i<0||d.i>9999)return 1;
			para->type=5;para->data=d;
			return 0;
		}
		if(strlen(cont)==3)
		{
			if(cont[1]=='d'&&cont[2]=='t')
			{para->type=3;para->data.i=100;return 0;}
			if(cont[1]=='a'&&cont[2]=='t')
			{para->type=3;para->data.i=101;return 0;}
			if(cont[1]=='r'&&cont[2]=='t')
			{para->type=3;para->data.i=102;return 0;}
		}
		Udata d=parseNumber(&cont[1],contr,1);
		if(isnan(d.r))return 1;
		if(d.i<0||d.i>99)return 1;
		para->type=3;para->data=d;
		return 0;
	}
	if(cont[0]=='i')
	{
		if(mode==2/*||mode==5||mode==6*/)return 1;//reject if...
		if(cont[1]=='[')//i[number], i[ixx]
		{
			char *c=&cont[2];
			while(*c!=']'&&c!=contr)++c;
			if(*c!=']')return 1;//brace mismatch
			if(cont[2]=='i')
			{
				Udata d=parseNumber(&cont[3],c,1);
				if(isnan(d.r))return 1;
				if(d.i<0||d.i>99)return 1;
				para->type=6;para->data=d;
				return 0;
			}
			Udata d=parseNumber(&cont[2],c,1);
			if(isnan(d.r))return 1;
			if(d.i<0||d.i>9999)return 1;
			para->type=4;para->data=d;
			return 0;
		}
		if(strlen(cont)==3)
		{
			if(cont[1]=='r'&&cont[2]=='t')
			{para->type=2;para->data.i=100;return 0;}
		}
		Udata d=parseNumber(&cont[1],contr,1);
		if(isnan(d.r))return 1;
		if(d.i<0||d.i>99)return 1;
		para->type=2;para->data=d;
		return 0;
	}
	if(mode==1||mode==4||mode==6)return 1;
	Udata tryi=mode==8?parseNumber(cont,contr,2):parseNumber(cont,contr,1);
	Udata tryr=parseNumber(cont,contr,0);
	if(isnan(tryr.r))return 1;
	if(isnan(tryi.r)&&mode==3)return 1;
	if(!isnan(tryi.r))return para->type=0,para->data=tryi,0;
	if(!isnan(tryr.r))return para->type=1,para->data=tryr,0;
	return 1;
}
int parseInstruction(char *line,SInst *inst)
{
	int r=-1;memset(fst,0,sizeof(fst));
	sscanf(line,"%s",fst);
#define bindInst(a,b) if(!strcmp(fst,a))r=b
	bindInst("nop",0x00);
	bindInst("push",0x01);bindInst("call",0x02);
	bindInst("mov",0x03);bindInst("add",0x04);
	bindInst("sub",0x05);bindInst("mul",0x06);
	bindInst("div",0x07);bindInst("mod",0x08);
	bindInst("and",0x09);bindInst("lor",0x0A);
	bindInst("xor",0x0B);bindInst("not",0x0C);
	bindInst("inc",0x0D);bindInst("dec",0x0E);
	bindInst("clrstk",0x0F);
	bindInst("ltz",0x11);bindInst("elz",0x12);
	bindInst("gtz",0x13);bindInst("egz",0x14);
	bindInst("eqz",0x15);bindInst("nez",0x16);
	bindInst("jmp",0x21);bindInst("jez",0x22);
	bindInst("jnz",0x23);bindInst("for",0x24);
	bindInst("brk",0x25);bindInst("cont",0x26);
#undef bindInst
	if(~r)inst->id=r;else return r=inst->id=0;
	char second[16],third[16];
	switch(r)
	{
		case 0x01:
			sscanf(line,"%*s%s",second);
			return parsePara(second,second+strlen(second),&inst->para1,0);
		case 0x02:
			sscanf(line,"%*s%s",second);
			return parsePara(second,second+strlen(second),&inst->para1,6);
		case 0x03:
		case 0x04:
		case 0x05:
		case 0x06:
		case 0x07:
			sscanf(line,"%*s%s%s",second,third);
			return
			parsePara(second,second+strlen(second),&inst->para1,1)||
			parsePara(third,third+strlen(third),&inst->para2,0);
		case 0x08:
		case 0x09:
		case 0x0A:
		case 0x0B:
			sscanf(line,"%*s%s%s",second,third);
			return
			parsePara(second,second+strlen(second),&inst->para1,4)||
			parsePara(third,third+strlen(third),&inst->para2,3);
		case 0x0C:
			sscanf(line,"%*s%s",second);
			return parsePara(second,second+strlen(second),&inst->para1,4);
		case 0x0D:
		case 0x0E:
			sscanf(line,"%*s%s",second);
			return parsePara(second,second+strlen(second),&inst->para1,1);
		case 0x11:
		case 0x12:
		case 0x13:
		case 0x14:
		case 0x15:
		case 0x16:
			sscanf(line,"%*s%s",second);
			return parsePara(second,second+strlen(second),&inst->para1,1);
		case 0x21:
			sscanf(line,"%*s%s",second);
			return parsePara(second,second+strlen(second),&inst->para1,8);
		case 0x22:
		case 0x23:
		case 0x24:
			sscanf(line,"%*s%s%s",second,third);
			bool ret=
			parsePara(second,second+strlen(second),&inst->para1,1)||
			parsePara(third,third+strlen(third),&inst->para2,8);
			if(r==0x24)
			{
				lppos[lops++]=inst->para2.data.i;
				if(lppos[lops-1]>lppos[lops-2])
				error("intersecting loops?");
			}
			return ret;
	}
	return 0;
}
#define printPara(x) \
if(x.type!=8) \
printf("para type: %d\npara data: %d/0x%X/%f\n",x.type,x.data.i,x.data.i,x.data.r); \
else \
printf("para type: %d\npara data: %s\n",x.type,x.fnc);
void compile()
{
	infunc=lc=0;
	while(fgets(line,512,stdin))
	{
		for(unsigned i=0;i<strlen(line);++i)
		if(line[i]==';'||line[i]==0x0A){line[i]='\0';}
		++lc;
		if(lops>0&&lc==lppos[lops-1])--lops;
		if(line[0]=='.')
		{
			if(infunc)error("error at line %d: subroutine is not supported.",lc);
			infunc=1;result[lc].id=0xFF;
			result[lc].para1.type=8;
			result[lc].para1.fnc=(char*)calloc(16,sizeof(char));
			memcpy(result[lc].para1.fnc,line+1,strlen(line+1));
		}else
		if(line[0]==',')
		{
			if(!infunc)error("error at line %d: end of no function?",lc);
			infunc=0;result[lc].id=0xFE;
		}else
		if(parseInstruction(line,&result[lc]))error("error at line %d.",lc);
		if(result[lc].id==0x25||result[lc].id==0x26)
		if(!lops)error("%s is only allowed to be used within a loop.",
		result[lc].id==0x25?"brk":"cont");
		if(!infunc&&result[lc].id&&result[lc].id<0xFE)error("error at line %d:\
 no instrunctions except nops are allowed out of a function.",lc);
	}
}
void writePara(SPara a)
{
	fputc(a.type,stdout);
	int startbit=7;
	if(a.type==0||a.type==4||a.type==5)startbit=4;
	if(a.type==1)startbit=0;
	unsigned long long d=a.data.d;
	unsigned long long c[8],shft=0,und=0xFFLL;
	for(int i=7;i>=0;--i)
	{
		c[i]=d&und;c[i]>>=shft;
		und<<=8LL;shft+=8LL;
	}
	//fprintf(stderr,"writtend lld: %lld=0x%llx\n0x",d,d);
	//for(int i=startbit;i<8;++i)fprintf(stderr,"%llx",c[i]);
	//fprintf(stderr,"\n");
	for(int i=startbit;i<8;++i)fputc((int)c[i],stdout);
}
void writeResult()
{
	for(int i=1;i<=lc;++i)
	{
		//fprintf(stderr,"InstID=0x%X\n",result[i].id);
		switch(result[i].id)
		{
			case 0xFF: case 0x02:
				fputc(result[i].id,stdout);
				fputc(strlen(result[i].para1.fnc),stdout);
				fputs(result[i].para1.fnc,stdout);
				break;
			case 0x00: case 0x0F: case 0xFE:
			case 0x25: case 0x26:
				fputc(result[i].id,stdout);
				break;
			case 0x01: case 0x0C: case 0x0D:
			case 0x0E: case 0x11: case 0x12:
			case 0x13: case 0x14: case 0x15:
			case 0x16: case 0x21:
				fputc(result[i].id,stdout);
				writePara(result[i].para1);
				break;
			case 0x03: case 0x04: case 0x05:
			case 0x06: case 0x07: case 0x08:
			case 0x09: case 0x0A: case 0x0B:
			case 0x22: case 0x23: case 0x24:
				fputc(result[i].id,stdout);
				writePara(result[i].para1);
				writePara(result[i].para2);
				break;
		}
	}
}
int main(int argc,char** argv)
{
	if(argc<3)return puts("Usage: lsrc <input file> <output file>"),0;
	freopen(argv[1],"r",stdin);
	compile();
	freopen(argv[2],"w",stdout);
	writeResult();
	return 0;
}

