//Chrisoft Bullet Lab Remix HGE
//Global varibles and implementations
//"Copyleft" Chrisoft 2013
#include "hge.h"
#include "hgefont.h"
#include "hgegui.h"
HGE *hge=0;
HEFFECT				snd;
HTEXTURE			tex;
hgeQuad				quad;
hgeGUI				*gui;
hgeFont				*fnt;
hgeSprite			*spr,*titlespr;
//Here are some Varibles in Bullet Lab
int					Current_Position;//Where are we now.
/*Scenes: 
0: main menu
1: game scene
2: tip scene
3: start menu
4: about scene
5: death scene
6: complete scene
7: new highscore scene
8: highscore scene
9: highscore view scene
10: highscore details scene
11: Pause scene
12: BackToTitle Confirm
13: Options scene
14: Player Profile scene
*/
HTEXTURE			SprSheet1,SprSheet2,TexTitle,TexCredits;
/*
Texture Mapping:
SprSheet1:
Player	47,46,24,24
Cursor	24,46,24,24
Blue	0,0,24,24
Green	23,0,24,24
Pnt		46,0,24,24
Purple	0,23,24,24
Red		23,23,24,24
White	46,23,24,24
Yellow	0,46,24,24
SprSheet2:
Blue	0,0,44,44
Green	44,0,44,44
Purple	88,0,44,44
Red		0,44,44,44
White	44,44,44,44
Yellow	88,44,44,44
*/
const double zero=1e-3;
struct vector2d
{
	double x,y;
};
struct Bullet
{
	hgeSprite *bulletspr;
	vector2d bulletpos;
	vector2d bulletdir;
	double dist;
	int bullettype;
	int redexplo,redattrib,oriexplo,whicnt;
	double bulletspeed;
	bool exist;
	double scale;
	int whirem,whiskp,yelbrk;
	int lifetime;
	bool scollable;
	int effbrk;
}bullet[10000];
//Something about bullets:
//bullettype:
//1: dir-based green bullet
//2: degree-based blue bullet (for clocks only)
//3: 12direction-based blue bullet
//4: yellow chaser bullet
//5: purple slow down bullet
//6: red exploding bullet
//7: white stalled bullet
//8: black shading bullet (dummy in version 1)
//254: Semi-collision effect
//255: Score point
struct Tower
{
	hgeSprite *towerspr;
	vector2d towerpos;
	int towertype;
	int towertimer,curtimer;
	double bulletspeed;
	int redexplo,whicnt,yelbrk;
	int t3t;
	bool exist;
	bool effect;
}tower[100];
//t3t is for Tower3
//0:All 12 directions
//1:four default directions
//2:random left/right
//3:random up/down
struct Line
{
	vector2d pos;
	double radian;
	DWORD color;
	bool exist;
}line[12];
//Line is currently dummy.
int bulcnt=0,towcnt=0,linecnt=0;
vector2d playerpos;
double playerrot;
double playerspeed;
double playerslospeed;
double playerfulspd=0.2;
double playerfulslospd=0.05;
double clockrot,deltarot,deltadelta;
double whirot,dwhirot;
hgeSprite *playerspr;
int frameleft;
int level,part,clrtime,clrbns;
int coll,semicoll,mode,dsmc,restarts;
double clrrange;
bool IfCallLevel;
bool DisableAllTower=false;
bool DisablePlayer=false;
int frameskips=0,stepskips=0;
bool IfShowTip=false,FadeTip=false;
hgeFont *TipFont;
char lasttip[200];
int p2t1,p2t2,p2t3,p2t4;
int whicnt,shots,clrusg;
bool yelattrib;
bool LOWFPS=false,diffkey=false;
bool Complete=false;
bool Refliction=false;
double linerad=0;
double bsscale;
long long score,scminus;
int frms;double averfps;
int plrspd,plrslospd;
int TenSeconds=10000,TwentySeconds=20000,ThirtySeconds=30000,AMinute=60000;
int effskp=0;
hgeSprite *Credits,*CreditsRail;
double scroll;
bool tfs;
int fpslvl;

void Error(char EC[],bool hgecreated=false)
{
	fprintf(stderr,EC);
	hge->System_Log(EC);
	if (hgecreated)
	{
		hge->System_Shutdown();
		hge->Release();
	}
	exit(0);
}
inline double GetDist(const vector2d a,const vector2d b)
{
	return sqrtf((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
void ShowTip(char tip[])
{
	if (strcmp(tip,lasttip)!=0)
	{
		TipFont->SetColor(0x00FFFFFF);
	}
	memcpy(lasttip,tip,sizeof(lasttip));
	DisableAllTower=true;
	DisablePlayer=true;
	if (hge->Input_GetKeyStateEx(HGEK_Z)==HGEKST_HIT)
	{
		//DisableAllTower=false;
		//DisablePlayer=false;
		//Current_Position=1;
		FadeTip=true;
	}
	double width=TipFont->GetStringWidth(tip);
	TipFont->printf(400-width/2,400,HGETEXT_LEFT,tip);
	if (FadeTip)
	{
		if (LOWFPS)
		{
			if (TipFont->GetColor()>>24>=0x08)
				TipFont->SetColor(TipFont->GetColor()-0x8000000);		
			else
			{
				DisableAllTower=false;
				DisablePlayer=false;
				Current_Position=1;
			}
		}
		else
		{
			if (TipFont->GetColor()>>24>=0x01)
				TipFont->SetColor(TipFont->GetColor()-0x1000000);
			else
			{
				DisableAllTower=false;
				DisablePlayer=false;
				Current_Position=1;
			}
		}
		return;
	}
	if (!LOWFPS)
	{
		if (TipFont->GetColor()>>24<=0xFE)
			TipFont->SetColor(TipFont->GetColor()+0x01000000);
	}
	else
	{
		if (TipFont->GetColor()>>24<=0xF7)
			TipFont->SetColor(TipFont->GetColor()+0x08000000);
	}
}
void ClearAll()
{
	DisableAllTower=true;
	bool none=true;
	for (int i=1;i<=towcnt;++i)
	{
		if (!tower[i].exist)continue;
		if (LOWFPS)
		{
			if (tower[i].towerspr->GetColor()>>24>=0x08)
			{
				tower[i].towerspr->SetColor(tower[i].towerspr->GetColor()-0x8000000);
				none=false;
			}
		}
		else
		{
			if (tower[i].towerspr->GetColor()>>24>=0x01)
			{
				tower[i].towerspr->SetColor(tower[i].towerspr->GetColor()-0x1000000);
				none=false;
			}
		}
	}
	if (none)
	{
		towcnt=0;
		memset(tower,0,sizeof(tower));
	}
	none=true;
	for (int i=1;i<=bulcnt;++i)
	{
		if (LOWFPS)
		{
			if (bullet[i].bulletspr->GetColor()>>24>=0x08)
			{
				bullet[i].bulletspr->SetColor(bullet[i].bulletspr->GetColor()-0x8000000);
				none=false;
			}
		}
		else
		{
			if (bullet[i].bulletspr->GetColor()>>24>=0x01)
			{
				bullet[i].bulletspr->SetColor(bullet[i].bulletspr->GetColor()-0x1000000);
				none=false;
			}
		}
	}
	if (none)
	{
		bulcnt=0;
		memset(bullet,0,sizeof(bullet));
	}
	none=true;
	for (int i=1;i<=bulcnt;++i)if (bullet[i].bulletspr->GetColor()>>24>=0x3F){none=false;break;}
	if (none)
		bulcnt=0,memset(bullet,0,sizeof(bullet));
}
void SaySomethingAndBye(char *text)
{
	ClearAll();
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip(text);
		return;
	}
	Current_Position=0;
	towcnt=bulcnt=0;
	memset(tower,0,sizeof(tower));
	memset(bullet,0,sizeof(bullet));
	gui->Enter();
}
