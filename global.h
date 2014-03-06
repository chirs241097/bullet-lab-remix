//Chrisoft Bullet Lab Remix HGE
//Global varibles and implementations
//Copyright Chrisoft 2014
#include <hge.h>
#include <hgefont.h>
#include <hgegui.h>
#define MaxRes 80
#define Resd 20.0f
HGE *hge=0;
HEFFECT				snd;
hgeQuad				quad;
hgeGUI				*gui;
hgeFont				*fnt;
hgeSprite			*spr,*titlespr;
int					Current_Position;//Where we are now
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
12: BackToTitle Confirmation
13: Options scene
14: Player Profile scene
*/
HTEXTURE			SprSheet,TexTitle,TexCredits;
/*
Texture Mapping:
SprSheet:ss.png
Bullet Blue			0,0,24,24
Bullet Dark Blue	24,0,24,24
Bullet Green		48,0,24,24
Bullet Orange		72,0,24,24
Bullet Pnt			96,0,24,24
Bullet Purple		120,0,24,24
Bullet Red			144,0,24,24
Bullet White		168,0,24,24
Bullet Yellow		192,0,24,24
Cursor				216,0,24,24
Player				0,24,24,24
Bullet Circle		24,24,24,24
Tower Blue			0,48,44,44
Tower Dark Blue		0,92,44,44
Tower Green			0,136,44,44
Tower Orange		0,180,44,44
Tower Purple		48,24,44,44
Tower Red			92,24,44,44
Tower White			136,24,44,44
Tower Yellow		180,24,44,44
Target				63,71,193,193
Laser Module		0,264,248,8
Ribbon Module		151,264,2,8
Multiplier"+1"		0,272,48,48
Text:blnsns.png
"Multiplier bonus!"	0,235,163,21
*/
enum TColors
{green=0,blue,yellow,purple,red,white,dblue,orange,grey,circle,COLOR_COUNT};
hgeSprite *bulletspr[COLOR_COUNT],*towerspr[COLOR_COUNT];
const double zero=1e-5;
vector2d playerpos;
bool playerLockX,playerLockY;
bool DisableAllTower=false;
bool DisablePlayer=false;
bool LOWFPS=false,diffkey=false;
inline double GetDist(vector2d,vector2d);
class Bullet
{
public:
	vector2d bulletpos;
	vector2d bulletdir;
	double dist;
	int bullettype;
	int redexplo,redattrib,oriexplo,whicnt;
	DWORD sccolor;
	/*In Orange bullets
	//redattrib also serves as oraattrib to determine if they will explode or change direction
	//redexplo also serves as orange explo
	//yelbrk serves as direction-change timer
	//whicnt describes how much one will explode into (into an exactly circle)*/
	double bulletspeed;
	double bulletaccel,limv;
	bool exist,inv;
	int whirem,whiskp,yelbrk;
	int exp1,exp2;
	double lifetime,rot;
	bool scollable,collable;
	double scale;int effbrk;
	TColors alterColor,alterColor2;
	void redir(vector2d targ)
	{
		bulletdir.x=bulletpos.x-targ.x;
		bulletdir.y=bulletpos.y-targ.y;
		dist=bulletdir.x*bulletdir.x+bulletdir.y*bulletdir.y;
		dist=sqrt(dist);
		bulletdir.x/=dist;bulletdir.y/=dist;dist=1;
	}
	void setdir(double rad)
	{
		bulletdir.x=cos(rad);
		bulletdir.y=sin(rad);
		dist=1;
	}
}bullet[10000];
/*Something about bullets:
//bullettype:
//1: player dir-based green bullet
//2: degree-based blue bullet (for clocks only)[are they clocks?]
//3: 12direction-based blue bullet
//4: yellow chaser bullet
//5: purple slow down bullet
//6: red exploding bullet
//7: white stalled bullet
//8: Orange Redir bullet
//9: dark Blue bullet
//254: Semi-collision effect
//255: Score point*/
struct Tower
{
	vector2d towerpos;
	int towertype;
	int towertimer,curtimer;
	int towertimer2,curtimer2,shotcount,curshotcount;
	vector2d tdir;
	bool dblstate;
	double bulletspeed;
	int redexplo,whicnt,yelbrk;
	int exp1,exp2;
	int t3t;
	bool exist,effect;
	double offset;
	DWORD RendColor;
}tower[100];
//t3t is for Tower3
//0:All 12 directions
//1:four default directions
//2:random left/right
//3:random up/down
struct Target//An annoying circle
{
	hgeSprite *targspr;
	vector2d targpos,targdir;
	double rot,rotspd;
	bool isonshow,isonhide,visible;
	void Init(double _rotspd,vector2d ipos)
	{
		targspr=new hgeSprite(SprSheet,63,71,193,193);
		targspr->SetHotSpot(96.5f,96.5f);
		rotspd=_rotspd;
		rot=0;
		targpos=ipos;
	}
	void TargShow()
	{
		if (!visible)
			isonshow=true,isonhide=false,visible=true;
	}
	void TargHide()
	{
		if (visible)
			isonhide=true,isonshow=false;
	}
	void TargShowProc()
	{
		if (LOWFPS)
			for (int i=1;i<=17;++i)
				targspr->SetColor(targspr->GetColor()+0x01000000);
		else
			targspr->SetColor(targspr->GetColor()+0x01000000);
		if (GETA(targspr->GetColor())>=0x80)
			isonshow=isonhide=false;
	}
	void TargHideProc()
	{
		if (LOWFPS)
			for (int i=1;i<=17;++i)
				targspr->SetColor(targspr->GetColor()-0x01000000);
		else
			targspr->SetColor(targspr->GetColor()-0x01000000);
		if (GETA(targspr->GetColor())==0x00)
			isonshow=isonhide=visible=false;
	}
	void TargFollowPlayer()
	{
		double curspd=0.01f;
		if (GetDist(playerpos,targpos)>1)curspd=0.02f;
		if (GetDist(playerpos,targpos)>2)curspd=0.1f;
		if (GetDist(playerpos,targpos)>5)curspd=0.5f;
		if (GetDist(playerpos,targpos)>10)curspd=0.75f;
		if (GetDist(playerpos,targpos)>20)curspd=1.0f;
		if (GetDist(playerpos,targpos)>30)curspd=2.0f;
		if (GetDist(playerpos,targpos)>40)curspd=5.0f;
		targdir.x=targpos.x-playerpos.x;
		targdir.y=targpos.y-playerpos.y;
		double dist=sqr(targdir.x)+sqr(targdir.y);
		dist=sqrt(dist);
		if (dist<1e-4)return;
		if (LOWFPS)
			targpos.x-=targdir.x/dist*curspd*17/20,
			targpos.y-=targdir.y/dist*curspd*17/20;
		else
			targpos.x-=targdir.x/dist*curspd/20,
			targpos.y-=targdir.y/dist*curspd/20;
	}
	void TargGoto(vector2d pos)
	{
		double curspd=0.01f;
		if (GetDist(pos,targpos)>1)curspd=0.02f;
		if (GetDist(pos,targpos)>2)curspd=0.1f;
		if (GetDist(pos,targpos)>5)curspd=0.5f;
		if (GetDist(pos,targpos)>10)curspd=0.75f;
		if (GetDist(pos,targpos)>20)curspd=1.0f;
		if (GetDist(pos,targpos)>30)curspd=2.0f;
		if (GetDist(pos,targpos)>40)curspd=5.0f;
		targdir.x=targpos.x-pos.x;
		targdir.y=targpos.y-pos.y;
		double dist=sqr(targdir.x)+sqr(targdir.y);
		dist=sqrt(dist);
		if (dist<1e-4)return;
		if (LOWFPS)
			targpos.x-=targdir.x/dist*curspd*17/20,
			targpos.y-=targdir.y/dist*curspd*17/20;
		else
			targpos.x-=targdir.x/dist*curspd/20,
			targpos.y-=targdir.y/dist*curspd/20;
	}
	void TargRender()
	{
		if (isonshow)TargShowProc();if(isonhide)TargHideProc();
		targspr->RenderEx(targpos.x+7,targpos.y+7,rot,0.8);
		if (!DisableAllTower)
		{
			if (LOWFPS)
				rot+=17*rotspd;
			else
				rot+=rotspd;
		}
	}
}ATarg,BTarg;
int bulcnt=0,towcnt=0,linecnt=0;
double playerrot;
double playerspeed;
double playerslospeed;
double playerfulspd=0.2;
double playerfulslospd=0.05;
double clockrot,deltarot,deltadelta;
double whirot,dwhirot;
hgeSprite *playerspr;
DWORD DBGColor;
int frameleft,infofade;
int level,part,clrtime,clrbns;
int coll,semicoll,mode,dsmc,restarts;
double clrrange,clrrad,clrmaxrange,clrind;
hgeSprite *clrcircle;
bool IfCallLevel;
bool Dis8ref,t8special;
int frameskips=0,stepskips=0;
bool IfShowTip=false,FadeTip=false;
hgeFont *TipFont;
char lasttip[200];
int whicnt,whrcnt,shots,clrusg;
bool yelattrib;
bool Complete=false;
double bsscale;
long long score,scminus;
double mult,lsc;
int multbrk,multbat;
int frms;double averfps;
int plrspd,plrslospd;
int TenSeconds=10000,TwentySeconds=20000,ThirtySeconds=30000,AMinute=60000;
int Infinity=999999999;
int effskp=0;
hgeSprite *Credits,*CreditsRail;
int creditsp;double creditfly,creditacc,credbrk;
bool credstop,creddone;
bool tfs;
int fpslvl,clrmode;
//static const char* GLOBAL_H_FN="global.h";

void Throw(char *Filename,char *Info)
{
	fprintf(stderr,"%s: %s\n",Filename,Info);
	hge->System_Log("%s: %s\n",Filename,Info);
}
void Error(const char *EC,bool hgecreated=false)
{
#ifndef WIN32
	fprintf(stderr,"%s\n",EC);
#else
	MessageBox(NULL,EC,"Error!",MB_ICONERROR);
#endif
	if (hgecreated)
	{
		hge->System_Shutdown();
		hge->Release();
	}
#ifdef WIN32
	remove("./Resources/b_diff.png");
	remove("./Resources/b_inter.png");
	remove("./Resources/b_null.png");
	remove("./Resources/e_sflake.png");
	remove("./Resources/e_skyitem.png");
	remove("./Resources/blnsns.png");
	remove("./Resources/charmap.fnt");
	remove("./Resources/ss.png");
	remove("./Resources/title.png");
	remove("./Resources/credits.png");
	remove("./Resources/b_leaves.png");
	remove("./Resources/e_leaf.png");
	remove("./Resources/tap.ogg");
	remove("./Resources/Music/BLR2_TR01.ogg");
	remove("./Resources/Music/BLR2_TR07.ogg");
	remove("./Resources/Music/BLR2_TR09.ogg");
	remove("./Resources/Music/CanonTechno.ogg");
	_rmdir("./Resources/Music");
	_rmdir("./Resources");
#endif
	exit(0);
}
void ShowTip(const char *tip)
{
	if (strcmp(tip,lasttip)!=0)
	{
		TipFont->SetColor(0x00FFFFFF);
	}
	memcpy(lasttip,tip,sizeof(lasttip));
	DisableAllTower=true;
	DisablePlayer=true;
	if (hge->Input_GetKeyStateEx(HGEK_Z)==HGEKST_HIT)
		FadeTip=true;
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
void All2pnt();//forward that...
void ClearAll(bool cbullet=true)
{
	DisableAllTower=true;
	bool none=true;
	for (int i=1;i<=towcnt;++i)
	{
		if (!tower[i].exist)continue;
		if (LOWFPS)
		{
			if (tower[i].RendColor>>24>=0x08)
			{
				tower[i].RendColor=tower[i].RendColor-0x8000000;
				none=false;
			}
		}
		else
		{
			if (tower[i].RendColor>>24>=0x01)
			{
				tower[i].RendColor=tower[i].RendColor-0x1000000;
				none=false;
			}
		}
	}
	if (none)
	{
		towcnt=0;
		memset(tower,0,sizeof(tower));
		if (cbullet)All2pnt();
	}
}
TextureRect GetTextureRect(int type,TColors color)
{
	if (type==0)
	{
		switch(color)
		{
			case green:return TextureRect(48,0,24,24);
			case blue:return TextureRect(0,0,24,24);
			case yellow:return TextureRect(192,0,24,24);
			case purple:return TextureRect(120,0,24,24);
			case red:return TextureRect(144,0,24,24);
			case white:return TextureRect(168,0,24,24);
			case dblue:return TextureRect(24,0,24,24);
			case orange:return TextureRect(72,0,24,24);
			case grey:return TextureRect(96,0,24,24);
			case circle:return TextureRect(24,24,24,24);
			default:return TextureRect(0,0,0,0);
		}
	}
	if (type==1)
	{
		switch(color)
		{
			case green:return TextureRect(0,136,44,44);
			case blue:return TextureRect(0,48,44,44);
			case yellow:return TextureRect(180,24,44,44);
			case purple:return TextureRect(48,24,44,44);
			case red:return TextureRect(92,24,44,44);
			case white:return TextureRect(136,24,44,44);
			case dblue:return TextureRect(0,92,44,44);
			case orange:return TextureRect(0,180,44,44);
			default:return TextureRect(0,0,0,0);
		}
	}
	return TextureRect(0,0,0,0);
}
DWORD ColorToDWORD(TColors a)
{
	switch(a)
	{
		case green:return 0xCCFF00;
		case blue:return 0x33CCFF;
		case yellow:return 0xFFFF00;
		case purple:return 0x9966FF;
		case red:return 0xFFFF3333;
		case white:return 0xFFFEFEFE;
		case dblue:return 0xFF0000FF;
		case orange:return 0xFFFF8800;
		default:return 0xFF000000;
	}
}
