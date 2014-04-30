// Chrisoft Bullet Lab Remix HGE -*- C++ -*-
// Score Recording Implementations
// Copyright Chrisoft 2014
//static const char* SCOREC_H_FN="scorec.h";

struct TRecord
{
	long long score;
	int len,rescol,scoll,clrusg;
	int af_int,af_fric;
	char name[16];
}ERec[10],NRec[10],ExRec[10],FPMRec[10];
unsigned int Ecnt,Ncnt,Excnt,FPMcnt;
unsigned int header,seprt;
char			newname[16];
int				newlen,tbframebrk;
unsigned int Getuint()
{
	unsigned int c1,c2,c3,c4,res;
	c1=c2=c3=c4=0;
	c1=getchar();c2=getchar();c3=getchar();c4=getchar();
	res=(c1<<24)+(c2<<16)+(c3<<8)+c4;
	return res;
}
int Getint()
{
	return (int)Getuint();
}
long long Getll()
{
	long long c1,c2,c3,c4,c5,c6,c7,c8,res;
	c1=c2=c3=c4=c5=c6=c7=c8=0;
	c1=getchar();c2=getchar();c3=getchar();c4=getchar();
	c5=getchar();c6=getchar();c7=getchar();c8=getchar();
	res=(c1<<56)+(c2<<48)+(c3<<40)+(c4<<32)+(c5<<24)+(c6<<16)+(c7<<8)+c8;
	return res;
}
void Putuint(unsigned int a)
{
	unsigned int c1,c2,c3,c4;
	c1=a&0xFF000000;c1>>=24;c2=a&0x00FF0000;c2>>=16;
	c3=a&0x0000FF00;c3>>=8;c4=a&0x000000FF;
	printf("%c%c%c%c",c1,c2,c3,c4);
}
void Putint(int a)
{
	Putuint((unsigned int)a);
}
void Putll(unsigned long long a)
{
	unsigned long long c1,c2,c3,c4,c5,c6,c7,c8;
	c1=a&0xFF00000000000000LL;c1>>=44LL;
	c2=a&0x00FF000000000000LL;c2>>=40LL;
	c3=a&0x0000FF0000000000LL;c3>>=36LL;
	c4=a&0x000000FF00000000LL;c4>>=32LL;
	c5=a&0x00000000FF000000LL;c5>>=24LL;
	c6=a&0x0000000000FF0000LL;c6>>=16LL;
	c7=a&0x000000000000FF00LL;c7>>=8LL;
	c8=a&0x00000000000000FFLL;
	printf("%c%c%c%c%c%c%c%c",(int)c1,(int)c2,(int)c3,(int)c4,(int)c5,(int)c6,(int)c7,(int)c8);
}
TRecord GetTRecord()
{
	TRecord res;
	res.len=Getint();
	memset(res.name,0,sizeof(res.name));
	for (int i=0;i<res.len;++i)scanf("%c",&res.name[i]);
	res.score=Getll();
	res.rescol=Getint();
	res.scoll=Getint();
	res.clrusg=Getint();
	res.af_int=Getint();res.af_fric=Getint();
	return res;
}
void PutTRecord(TRecord a)
{
	Putint(a.len);
	for (int i=0;i<a.len;++i)printf("%c",a.name[i]);
	Putll(a.score);
	Putint(a.rescol);
	Putint(a.scoll);
	Putint(a.clrusg);
	Putint(a.af_int);Putint(a.af_fric);
}
void Score_Init()
{
	freopen("score.cfg","r",stdin);
	header=Getuint();
	if (header!=0x3b424c53)//0x3b424c53=";BLS"
	{
		fclose(stdin);
		Error("Error when loading score file!");
	}
	seprt=Getuint();
	if (seprt!=0xd1ffa0c0)
	{
		fclose(stdin);
		Error("Error when loading score file!");
	}
	Ecnt=Getuint();
	for (unsigned int i=1;i<=Ecnt;++i)ERec[i]=GetTRecord();
	seprt=Getuint();
	if (seprt!=0xd1ffa0c1)
	{
		fclose(stdin);
		Error("Error when loading score file!");
	}
	Ncnt=Getuint();
	for (unsigned int i=1;i<=Ncnt;++i)NRec[i]=GetTRecord();
	seprt=Getuint();
	if (seprt!=0xd1ffa0c2)
	{
		fclose(stdin);
		Error("Error when loading score file!");
	}
	Excnt=Getuint();
	for (unsigned int i=1;i<=Excnt;++i)ExRec[i]=GetTRecord();
	seprt=Getuint();
	if (seprt!=0xd1ffa0c3)
	{
		fclose(stdin);
		Error("Error when loading score file!");
	}
	FPMcnt=Getuint();
	for (unsigned int i=1;i<=FPMcnt;++i)FPMRec[i]=GetTRecord();
	fclose(stdin);
}
int CheckHighScore()
{
	unsigned i;
	switch (mode)
	{
		case 4:
			for (i=1;i<=Ecnt;++i)
				if (ERec[i].score<score)break;
			if (i==5&&ERec[i].score>score)return -1;
			if (Ecnt<5&&ERec[Ecnt].score>score)return Ecnt+1;
			return i;
			break;
		case 1:
			for (i=1;i<=Ncnt;++i)
				if (NRec[i].score<score)break;
			if (i==5&&NRec[i].score>score)return -1;
			if (Ncnt<5&&NRec[Ncnt].score>score)return Ncnt+1;
			return i;
			break;
		case 2:
			for (i=1;i<=Excnt;++i)
				if (ExRec[i].score<score)break;
			if (i==5&&ExRec[i].score>score)return -1;
			if (Excnt<5&&ExRec[Ncnt].score>score)return Excnt+1;
			return i;
			break;
		case 3:
			for (i=1;i<=FPMcnt;++i)
				if (FPMRec[i].score<score)break;
			if (i==5&&FPMRec[i].score>score)return -1;
			if (FPMcnt<5&&FPMRec[Ncnt].score>score)return FPMcnt+1;
			return i;
			break;
	}
	return 100;
}
void Score_Write()
{
	freopen("score.cfg","w",stdout);
	Putuint(0x3b424c53);
	Putuint(0xd1ffa0c0);
	Putint(Ecnt);
	for (unsigned i=1;i<=Ecnt;++i)
		PutTRecord(ERec[i]);
	Putuint(0xd1ffa0c1);
	Putint(Ncnt);
	for (unsigned i=1;i<=Ncnt;++i)
		PutTRecord(NRec[i]);
	Putuint(0xd1ffa0c2);
	Putint(Excnt);
	for (unsigned i=1;i<=Excnt;++i)
		PutTRecord(ExRec[i]);
	Putuint(0xd1ffa0c3);
	Putint(FPMcnt);
	for (unsigned i=1;i<=FPMcnt;++i)
		PutTRecord(FPMRec[i]);
	fclose(stdout);
}
void Score_Initailize()
{
	freopen("score.cfg","w",stdout);
	Putuint(0x3b424c53);
	Putuint(0xd1ffa0c0);Putuint(0);
	Putuint(0xd1ffa0c1);Putuint(0);
	Putuint(0xd1ffa0c2);Putuint(0);
	Putuint(0xd1ffa0c3);Putuint(0);
	fclose(stdout);
}
void InsertHighScore()
{
	unsigned pos=CheckHighScore();
	switch (mode)
	{
		case 4:
			//deprecated...
			if (pos<=Ecnt)
			for (unsigned i=5;i>pos;--i)
				ERec[i]=ERec[i-1];
			else ++Ecnt;
			if (Ecnt<5)++Ecnt;
			ERec[pos].score=score;
			ERec[pos].len=newlen;
			memcpy(ERec[pos].name,newname,sizeof(newname));
			ERec[pos].clrusg=clrusg;
			ERec[pos].rescol=restarts;ERec[pos].scoll=semicoll;
			ERec[pos].af_int=(int)averfps;
			ERec[pos].af_fric=(int)(averfps*10)%10*10+(int)(averfps*100)%10;
			break;
		case 1:
			if (pos<=Ncnt)
			for (unsigned i=5;i>pos;--i)
				NRec[i]=NRec[i-1];
			if (Ncnt<5)++Ncnt;
			NRec[pos].score=score;
			NRec[pos].len=newlen;
			memcpy(NRec[pos].name,newname,sizeof(newname));
			NRec[pos].clrusg=clrusg;
			NRec[pos].rescol=restarts;NRec[pos].scoll=semicoll;
			NRec[pos].af_int=(int)averfps;
			NRec[pos].af_fric=(int)(averfps*10)%10*10+(int)(averfps*100)%10;
			break;
		case 2:
			if (pos<=Excnt)
			for (unsigned i=5;i>pos;--i)
				ExRec[i]=ExRec[i-1];
			if (Excnt<5)++Excnt;
			ExRec[pos].score=score;
			ExRec[pos].len=newlen;
			memcpy(ExRec[pos].name,newname,sizeof(newname));
			ExRec[pos].clrusg=clrusg;
			ExRec[pos].rescol=restarts;ExRec[pos].scoll=semicoll;
			ExRec[pos].af_int=(int)averfps;
			ExRec[pos].af_fric=(int)(averfps*10)%10*10+(int)(averfps*100)%10;
			break;
		case 3:
			if (pos<=FPMcnt)
			for (unsigned i=5;i>pos;--i)
				FPMRec[i]=FPMRec[i-1];
			if (FPMcnt<5)++FPMcnt;
			FPMRec[pos].score=score;
			FPMRec[pos].len=newlen;
			memcpy(FPMRec[pos].name,newname,sizeof(newname));
			FPMRec[pos].clrusg=clrusg;
			FPMRec[pos].rescol=coll;FPMRec[pos].scoll=semicoll;
			FPMRec[pos].af_int=(int)averfps;
			FPMRec[pos].af_fric=(int)(averfps*10)%10*10+(int)(averfps*100)%10;
			break;
	}
	Score_Write();
}
