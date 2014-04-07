//Chrisoft Bullet Lab Remix HGE
//Main Code
//Copyright Chrisoft 2014
//Now that we use BSD license, so let's paste it here.
//(although it may be awful)
/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name of the  nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
//#define Debug
#include <hge.h>
#include <hgefont.h>
#include <hgegui.h>
#include <hgedistort.h>
#include <hgerect.h>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#ifdef WIN32
#include <io.h>
#include <direct.h>
#include <shlwapi.h>
#include <shellapi.h>
#include <windows.h>
#include <mmsystem.h>
#endif
#include "libcgh.h"
#include "hgeft.h"
#include "menuitem.h"
#include "global.h"
#include "music.h"
#include "scoresystem.h"
#include "towernbullet.h"
#include "background.h"
#include "levels.h"
#include "scorec.h"
#include "menus.h"
static const char* MAIN_SRC_FN="main.cpp";
#ifdef WIN32
void Expand(const char *source,const char *dist)
{
	char cmd[255];
	sprintf(cmd,"%s -F:* %s",source,dist);
	int res=(int)ShellExecuteA(NULL,"open","expand.exe",cmd,NULL,SW_HIDE);
	if (res<32) Error("Error while decompressing resources!\nCheck if expand.exe works correctly.");
}
void firststartup()
{
	if (MessageBoxA(NULL,"It seems that you are running BLR for the First time!\nLet's do some \
basic settings first!\n\nUse vsync??","First Start Up",0x00000024)==6)
		fpslvl=2;
	else
		fpslvl=0;
	if (MessageBoxA(NULL,"Enable Fullscreen?","First Start Up",0x00000024)==6)
		tfs=1;
	else
		tfs=0;
	diffkey=false;
	plrspd=3;plrslospd=3;clrbns=clrmode=0;
	hge->System_Log("%s: Finishing first start up configuraion...",MAIN_SRC_FN);
	Options_Writeback();
	Score_Initailize();
}
#endif
#ifndef WIN32
void firststartup()
{
	fpslvl=0;
	tfs=0;
	diffkey=false;
	plrspd=3;plrslospd=3;clrbns=clrmode=0;
	hge->System_Log("%s: Finishing first start up configuraion...",MAIN_SRC_FN);
	Options_Writeback();
	Score_Initailize();
}
#endif
void Player_Clear_Expand()
{
	if (LOWFPS)
		clrrange+=13.6;
	else
		clrrange+=0.8;
	int ds;
	for (int i=1;i<=bulcnt;++i)
	{
		double dis=GetDist(bullet[i].bulletpos,playerpos);ds=0;
		if(PlayerSplit)
		for(int j=1;j<4;++j)
		{
			if(dis>GetDist(bullet[i].bulletpos,playerpos+splitData[j]))
			dis=GetDist(bullet[i].bulletpos,playerpos+splitData[j]),ds=j;
		}
		if (bullet[i].bullettype!=255&&dis<=clrrange&&bullet[i].exist&&!bullet[i].inv)
		{
			CreateBullet255(bullet[i].bulletpos.x,bullet[i].bulletpos.y,10,ds);
			bullet[i].exist=false;
			bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
			bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
			bullet[i].dist=0;
			bullet[i].bullettype=0;
		}
	}
}
void Player_Clear_Rotate()
{
	if (LOWFPS)
		clrrad+=pi/450*17;
	else
		clrrad+=pi/450;
	for (int i=1;i<=bulcnt;++i)
	{
		double dis=GetDist(bullet[i].bulletpos,playerpos);
		double rad=atan2l(bullet[i].bulletpos.y-playerpos.y,bullet[i].bulletpos.x-playerpos.x);
		hge->Gfx_RenderLine(playerpos.x+8,playerpos.y+8,playerpos.x+cos(clrrad)*clrmaxrange,playerpos.y+sin(clrrad)*clrmaxrange);
		while (rad<0)rad+=2*pi;
		if (bullet[i].bullettype!=255&&dis<=clrmaxrange&&bullet[i].exist&&!bullet[i].inv&&rad>normalizerad(clrrad)-pi/12&&rad<normalizerad(clrrad)+pi/12)
		{
			CreateBullet255(bullet[i].bulletpos.x,bullet[i].bulletpos.y,10);
			bullet[i].exist=false;
			bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
			bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
			bullet[i].dist=0;
			bullet[i].bullettype=0;
		}
		if(PlayerSplit)
		for(int j=1;j<4;++j)
		{
			vector2d plsp=playerpos+splitData[j];
			double dis=GetDist(bullet[i].bulletpos,plsp);
			double rad=atan2l(bullet[i].bulletpos.y-plsp.y,bullet[i].bulletpos.x-plsp.x);
			hge->Gfx_RenderLine(plsp.x+8,plsp.y+8,plsp.x+cos(clrrad)*clrmaxrange,plsp.y+sin(clrrad)*clrmaxrange);
			while (rad<0)rad+=2*pi;
			if (bullet[i].bullettype!=255&&dis<=clrmaxrange&&bullet[i].exist&&!bullet[i].inv&&rad>normalizerad(clrrad)-pi/12&&rad<normalizerad(clrrad)+pi/12)
			{
				CreateBullet255(bullet[i].bulletpos.x,bullet[i].bulletpos.y,10,j);
				bullet[i].exist=false;
				bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
				bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
				bullet[i].dist=0;
				bullet[i].bullettype=0;
			}
		}
	}
}
void ProcessPlayer()
{
	if (!clrcircle)
	{
		clrcircle=new hgeSprite(SprSheet,63,71,193,193);
		clrcircle->SetHotSpot(96.5f,96.5f);
		clrcircle->SetBlendMode(BLEND_ALPHAADD);
	}
	if(clrmode)clrcircle->SetColor(0x30008080);else clrcircle->SetColor(0x30800000);;
	if (playerLockX)
	{
		Lock.Setdata(0,vector2d(playerpos.x-1,0),vector2d(playerpos.x-1,600),0xC0FFFFFF);
		for (int i=1;i<80;++i)
		Lock.Setdata(i,vector2d(playerpos.x+1,0),vector2d(playerpos.x+1,600),0xC0FFFFFF);
		Lock.Render();
	}
	if (playerLockY)
	{
		Lock.Setdata(0,vector2d(0,playerpos.y+5),vector2d(800,playerpos.y+5),0xC0FFFFFF);
		for (int i=1;i<80;++i)
		Lock.Setdata(i,vector2d(0,playerpos.y+7),vector2d(800,playerpos.y+7),0xC0FFFFFF);
		Lock.Render();
	}
	if(!PlayerSplit)
	playerspr->RenderEx(playerpos.x+8.4,playerpos.y+8.4,playerrot,0.7,0);
	else
	{
		for(int i=0;i<4;++i)
		playerspr->RenderEx(playerpos.x+splitData[i].x+8.4,playerpos.y+splitData[i].y+8.4,playerrot,0.7,0);
	}
	if (DisablePlayer)return;
	if (!LOWFPS)
		playerrot+=0.00174533;
	else
		playerrot+=0.00174533*17;
	double realspd;
	if (hge->Input_GetKeyState(HGEK_SHIFT))
		realspd=playerslospeed*(1000.0f/hge->Timer_GetFPS());
	else
		realspd=playerspeed*(1000.0f/hge->Timer_GetFPS());
	if (hge->Input_GetKeyState(HGEK_LEFT)&&!playerLockX)
	{
		if (playerpos.x>10)
			playerpos.x-=realspd;
	}
	if (hge->Input_GetKeyState(HGEK_RIGHT)&&!playerLockX)
	{
		if ((playerpos.x<770&&!PlayerSplit)||(playerpos.x<370&&PlayerSplit))
			playerpos.x+=realspd;
	}
	if (hge->Input_GetKeyState(HGEK_UP)&&!playerLockY)
	{
		if (playerpos.y>10)
			playerpos.y-=realspd;
	}
	if (hge->Input_GetKeyState(HGEK_DOWN)&&!playerLockY)
	{
		if ((playerpos.y<570&&!PlayerSplit)||(playerpos.y<270&&PlayerSplit))
			playerpos.y+=realspd;
	}
	if(mode!=2)
	{
		if (!clrmode)
		{
			if (hge->Input_GetKeyStateEx(HGEK_Z)==HGEKST_HIT&&clrrange==0&&!diffkey)
			{
				clrmaxrange=0;clrind=0;
			}
			if (hge->Input_GetKeyStateEx(HGEK_X)==HGEKST_HIT&&clrrange==0&&diffkey)
			{
				clrmaxrange=0;clrind=0;
			}
			if (hge->Input_GetKeyStateEx(HGEK_Z)==HGEKST_KEEP&&clrrange==0&&!diffkey)
			{
				if (clrmaxrange<=400)
				{
					if (LOWFPS)clrmaxrange+=1.6;else clrmaxrange+=0.1;
				}
				if (!LOWFPS)clrind+=0.001*pi;else clrind+=0.016*pi;
				clrcircle->RenderEx(playerpos.x+7.2,playerpos.y+7.2,clrind,2*clrmaxrange/193.0f);
				if(PlayerSplit)for(int i=1;i<4;++i)
				clrcircle->RenderEx(playerpos.x+splitData[i].x+7.2,playerpos.y+splitData[i].y+7.2,clrind,2*clrmaxrange/193.0f);
			}
			if (hge->Input_GetKeyStateEx(HGEK_X)==HGEKST_KEEP&&clrrange==0&&diffkey)
			{
				if (clrmaxrange<=400)
				{
					if (LOWFPS)clrmaxrange+=1.6;else clrmaxrange+=0.1;
				}
				if (!LOWFPS)clrind+=0.001*pi;else clrind+=0.016*pi;
				clrcircle->RenderEx(playerpos.x+7.2,playerpos.y+7.2,clrind,2*clrmaxrange/193.0f);
				if(PlayerSplit)for(int i=1;i<4;++i)
				clrcircle->RenderEx(playerpos.x+splitData[i].x+7.2,playerpos.y+splitData[i].y+7.2,clrind,2*clrmaxrange/193.0f);
			}
			if (hge->Input_GetKeyStateEx(HGEK_Z)==HGEKST_RELEASE&&clrrange==0&&!diffkey)
			{
				if (clrmaxrange<=50)
				{
					if (clrtime+clrbns){--clrtime;clrmaxrange=350;Player_Clear_Expand();++clrusg;}
				}
				else
				{
					Player_Clear_Expand();++clrusg;
				}
			}
			if (hge->Input_GetKeyStateEx(HGEK_X)==HGEKST_RELEASE&&clrrange==0&&diffkey)
			{
				if (clrmaxrange<=50)
				{
					if (clrtime+clrbns){--clrtime;clrmaxrange=350;Player_Clear_Expand();++clrusg;}
				}
				else
				{
					Player_Clear_Expand();++clrusg;
				}
			}
			if (clrrange!=0)
			{
				Player_Clear_Expand();
				clrcircle->RenderEx(playerpos.x+7.2,playerpos.y+7.2,clrind,2*(clrmaxrange-clrrange)/193.0f);
				if(PlayerSplit)for(int i=1;i<4;++i)
				clrcircle->RenderEx(playerpos.x+splitData[i].x+7.2,playerpos.y+splitData[i].y+7.2,clrind,2*(clrmaxrange-clrrange)/193.0f);
				clrind+=(LOWFPS?0.016*pi:0.001*pi);
			}
			if (clrrange>=clrmaxrange)clrrange=0;
		}
		else
		{
			if (hge->Input_GetKeyStateEx(HGEK_Z)==HGEKST_HIT&&clrrad-pi/2<1e-7&&!diffkey)
			{
				clrmaxrange=0;clrind=0;
			}
			if (hge->Input_GetKeyStateEx(HGEK_X)==HGEKST_HIT&&clrrad-pi/2<1e-7&&diffkey)
			{
				clrmaxrange=0;clrind=0;
			}
			if (hge->Input_GetKeyStateEx(HGEK_Z)==HGEKST_KEEP&&clrrange==0&&!diffkey)
			{
				if (clrmaxrange<=400)
				{
					if (LOWFPS)clrmaxrange+=1.6;else clrmaxrange+=0.1;
				}
				if (!LOWFPS)clrind+=0.001*pi;else clrind+=0.016*pi;
				clrcircle->RenderEx(playerpos.x+7.2,playerpos.y+7.2,clrind,2*clrmaxrange/193.0f);
				if(PlayerSplit)for(int i=1;i<4;++i)
				clrcircle->RenderEx(playerpos.x+splitData[i].x+7.2,playerpos.y+splitData[i].y+7.2,clrind,2*clrmaxrange/193.0f);
			}
			if (hge->Input_GetKeyStateEx(HGEK_X)==HGEKST_KEEP&&clrrange==0&&diffkey)
			{
				if (clrmaxrange<=400)
				{
					if (LOWFPS)clrmaxrange+=1.6;else clrmaxrange+=0.1;
				}
				if (!LOWFPS)clrind+=0.001*pi;else clrind+=0.016*pi;
				clrcircle->RenderEx(playerpos.x+7.2,playerpos.y+7.2,clrind,2*clrmaxrange/193.0f);
				if(PlayerSplit)for(int i=1;i<4;++i)
				clrcircle->RenderEx(playerpos.x+splitData[i].x+7.2,playerpos.y+splitData[i].y+7.2,clrind,2*clrmaxrange/193.0f);
			}
			if (hge->Input_GetKeyStateEx(HGEK_Z)==HGEKST_RELEASE&&clrrad-pi/2<1e-7&&clrtime+clrbns&&!diffkey)
			{
				Player_Clear_Rotate();if(clrmaxrange<50)--clrtime,clrmaxrange=350;++clrusg;
			}
			if (hge->Input_GetKeyStateEx(HGEK_X)==HGEKST_RELEASE&&clrrad-pi/2<1e-7&&clrtime+clrbns&&diffkey)
			{
				Player_Clear_Rotate();if(clrmaxrange<50)--clrtime,clrmaxrange=350;++clrusg;
			}
			if (clrrad-pi/2>1e-7)
			{
				Player_Clear_Rotate();
				clrcircle->RenderEx(playerpos.x+7.2,playerpos.y+7.2,clrind,2*clrmaxrange/193.0f*(5*pi/2.0f-clrrad)/(2*pi));
				if(PlayerSplit)for(int i=1;i<4;++i)
				clrcircle->RenderEx(playerpos.x+splitData[i].x+7.2,playerpos.y+splitData[i].y+7.2,clrind,2*clrmaxrange/193.0f*(5*pi/2.0f-clrrad)/(2*pi));
				clrind+=(LOWFPS?0.016*pi:0.001*pi);
			}
			if (5*pi/2-clrrad<1e-7)clrrad=pi/2;
		}
	}
}
void RefreshScore()
{
	Mult_FrameFunc();
	if (DisablePlayer)return;
	mult+=0.01f*dsmc;
	if (LOWFPS)
		score+=16*mult;
	else
		score+=mult;
	if(scminus){if(mult/2>0.1)mult/=2;else mult=0.5;}
	score+=100*shots*mult;
	score-=scminus*mult;
	score+=2000*dsmc*mult;
	++frms;
	averfps=(averfps*(frms-1)+hge->Timer_GetFPSf())/(double)frms;
}
void CallLevels()
{
	//Use this to call level procedures.
	if ((mode==1)&&coll!=0){DeathGUI_Init();return;}
	if ((mode==2)&&coll!=0){assetime=0;++part;coll=0;IfCallLevel=IfShowTip=true;return;}
	if (!IfCallLevel) return;
	if (mode==2)assetime+=hge->Timer_GetDelta();
	//Check Complete here
	if (level==1&&part==0)Level1Part0();
	if (level==1&&part==1)Level1Part1();
	if (level==1&&part==2)Level1Part2();
	if (level==1&&part==3)Level1Part3();
	if (level==1&&part==4)Level1Part4();
	if (level==2&&part==0)Level2Part0();
	if (level==2&&part==1)Level2Part1();
	if (level==2&&part==2)Level2Part2();
	if (level==2&&part==3)Level2Part3();
	if (level==2&&part==4)Level2Part4();
	if (level==2&&part==5)Level2Part5();
	if (level==2&&part==6)Level2Part6();
	if (level==2&&part==7)Level2Part7();
	if (level==2&&part==8)Level2Part8();
	if (level==2&&part==9)Level2Part9();
	if (level==3&&part==0)Level3Part0();
	if (level==3&&part==1)Level3Part1();
	if (level==3&&part==2)Level3Part2();
	if (level==3&&part==3)Level3Part3();
	if (level==3&&part==4)Level3Part4();
	if (level==3&&part==5)Level3Part5();
	if (level==3&&part==6)Level3Part6();
	if (level==4&&part==0)Level4Part0();
	if (level==4&&part==1)Level4Part1();
	if (level==4&&part==2)Level4Part2();
	if (level==4&&part==3)Level4Part3();
	if (level==4&&part==4)Level4Part4();
	if (level==4&&part==5)Level4Part5();
	if (level==4&&part==6)Level4Part6();
	if (level==4&&part==7)Level4Part7();
	if (level==4&&part==8)Level4Part8();
	if (level==4&&part==9)Level4Part9();
	if (level==4&&part==10)Level4Part10();
	if (level==4&&part==11)Level4Part11();
	if (level==4&&part==12)Level4Part12();
	if (level==4&&part==13)Level4Part13();
	if (level==4&&part==14)Level4Part14();
	if (level==4&&part==15)Level4Part15();
	if (level==4&&part==16)Level4Part16();
	if (level==4&&part==17)Level4Part17();
	if (level==4&&part==18)Level4Part18();
	if (level==4&&part==19)Level4Part19();
	if (level==4&&part==20)Level4Part20();
	if (level==4&&part==21)Level4Part21();
	if (level==4&&part==22)Level4Part22();
	if (level==4&&part==23)Level4Part23();
	if (level==4&&part==24)Level4Part24();
	if (level==4&&part==25)Level4Part25();
	if (level==5&&part==0)Level5Part0();
	if (level==5&&part==1)Level5Part1();
	if (level==5&&part==2)Level5Part2();
	if (level==5&&part==3)Level5Part3();
	if (level==5&&part==4)Level5Part4();
	if (level==5&&part==5)Level5Part5();
	if (level==5&&part==6)Level5Part6();
	if (level==5&&part==7)Level5Part7();
	if (level==5&&part==8)Level5Part8();
	if (level==5&&part==9)Level5Part9();
	if (level==5&&part==10)Level5Part10();
	if (level==5&&part==11)Level5Part11();
	if (level==5&&part==12)Level5Part12();
	if (level==5&&part==13)Level5Part13();
	if (level==5&&part==14)Level5Part14();
	if (level==5&&part==15)Level5Part15();
	if (level==5&&part==16)Level5Part16();
	if (level==5&&part==17)Level5Part17();
	if (level==5&&part==18)Level5Part18();
	if (level==5&&part==19)Level5Part19();
	if (level==5&&part==20)Level5Part20();
	if (level==5&&part==21)Level5Part21();
	if (level==5&&part==22)Level5Part22();
	if (level==6&&part==0)Level6Part0();
	if (level==6&&part==1)Level6Part1();
	if (level==6&&part==2)Level6Part2();
	if (level==6&&part==3)Level6Part3();
	if (level==6&&part==4)Level6Part4();
	if (level==6&&part==5)Level6Part5();
	if (level==6&&part==6)Level6Part6();
	if (level==6&&part==7)Level6Part7();
	if (level==6&&part==8)Level6Part8();
	if (level==6&&part==9)Level6Part9();
	if (level==6&&part==10)Level6Part10();
	if (level==6&&part==11)Level6Part11();
	if (level==6&&part==12)Level6Part12();
	if (level==6&&part==13)Level6Part13();
	if (level==6&&part==14)Level6Part14();
	if (level==6&&part==15)Level6Part15();
	if (level==6&&part==16)Level6Part16();
	if (level==6&&part==17)Level6Part17();
	if (level==6&&part==18)Level6Part18();
	if (level==6&&part==19)Level6Part19();
	if (level==6&&part==20)Level6Part20();
	if (level==6&&part==21)Level6Part21();
	if (level==6&&part==22)Level6Part22();
	if (level==6&&part==23)Level6Part23();
	if (level==6&&part==24)Level6Part24();
	if (level==6&&part==25)Level6Part25();
	if (level==6&&part==26)Level6Part26();
	if (level==6&&part==27)Level6Part27();
	if (level==6&&part==28)Level6Part28();
	if (level==6&&part==29)Level6Part29();
	if (level==6&&part==30)Level6Part30();
	if (level==6&&part==31)Level6Part999999999();
	if (level==7&&part==0)Level7Part0();
	if (level==7&&part==1)Level7Part1();
	if (level==7&&part==2)Level7Part2();
	if (level==7&&part==3)Level7Part3();
	if (level==7&&part==4)Level7Part4();
	if (level==7&&part==5)Level7Part5();
	if (level==7&&part==6)Level7Part6();
	if (level==7&&part==7)Level7Part7();
	if (level==7&&part==8)Level7Part8();
	if (level==7&&part==9)Level7Part9();
	if (level==7&&part==10)Level7Part10();
	if (level==7&&part==11)Level7Part11();
	if (level==7&&part==12)Level7Part12();
	if (level==7&&part==13)Level7Part13();
	if (level==7&&part==14)Level7Part14();
	if (level==7&&part==15)Level7Part15();
	if (level==7&&part==16)Level7Part16();
	if (level==7&&part==17)Level7Part17();
	if (level==7&&part==18)Level7Part18();
	if (level==7&&part==19)Level7Part19();
	if (level==7&&part==20)Level7Part20();
	if (level==7&&part==21)Level7Part21();
	if (level==7&&part==22)Level7Part22();
	if (level==7&&part==23)Level7Part23();
	if (level==7&&part==24)Level7Part24();
	if (level==7&&part==25)Level7Part25();
	if (level==7&&part==26)Level7Part26();
	if (level==-1&&part==0)Levelm1Part0();
	if (level==-1&&part==1)Levelm1Part1();
	if (level==-1&&part==2)Levelm1Part2();
	if (level==-1&&part==3)Levelm1Part3();
	if (level==-1&&part==4)Levelm1Part4();
	if (level==-1&&part==5)Levelm1Part5();
	if (level==-1&&part==6)Levelm1Part6();
	if (level==-1&&part==7)Levelm1Part7();
	if (level==-1&&part==8)Levelm1Part8();
	if (level==-1&&part==9)Levelm1Part9();
	if (level==-1&&part==10)Levelm1Part10();
	if (level==-1&&part==11)Levelm1Part11();
	if (level==-1&&part==12)Levelm1Part12();
	if (level==-1&&part==13)Levelm1Part13();
	if (level==-1&&part==14)Levelm1Part14();
	if (level==-1&&part==15)Levelm1Part15();
	if (level==-1&&part==16)Levelm1Part16();
	if (level==-1&&part==17)Levelm1Part17();
	if (level==-1&&part==18)Levelm1Part18();
	if (level==-1&&part==19)Levelm1Part19();
	if (level==-1&&part==20)Levelm1Part20();
	if (level==-1&&part==21)Levelm1Part21();
	if (level==-2&&part==0)Levelm2Part0();
	if (level==-2&&part==1)Levelm2Part1();
	if (level==-2&&part==2)Levelm2Part2();
	if (level==-2&&part==3)Levelm2Part3();
	if (level==-2&&part==4)Levelm2Part4();
	if (level==-2&&part==5)Levelm2Part5();
	if (level==-2&&part==6)Levelm2Part6();
	if (level==-2&&part==7)Levelm2Part7();
	if (level==-2&&part==8)Levelm2Part8();
	if (level==-2&&part==9)Levelm2Part9();
	if (level==-2&&part==10)Levelm2Part10();
	if (level==-2&&part==11)Levelm2Part11();
	if (level==-2&&part==12)Levelm2Part12();
	if (level==-2&&part==13)Levelm2Part13();
	if (level==-2&&part==14)Levelm2Part14();
	if (level==-2&&part==15)Levelm2Part15();
	if (level==-2&&part==16)Levelm2Part16();
	if (level==-2&&part==17)Levelm2Part17();
	if (level==-2&&part==18)Levelm2Part18();
	if (level==-2&&part==19)Levelm2Part19();
	if (level==-2&&part==20)Levelm2Part20();
	if (level==-2&&part==21)Levelm2Part21();
	if (level==-2&&part==22)Levelm2Part22();
	if (level==-2&&part==23)Levelm2Part23();
	if (level==-2&&part==24)Levelm2Part24();
	if (level==-2&&part==25)Levelm2Part25();
	if (level==-2&&part==26)Levelm2Part26();

	if (level==1&&part==5)level=2,part=0;
	if (level==2&&part==10)
	{
		if(mode==3&&coll>10){CompleteGUI_Init();return;}
		if(mode==1&&restarts>1){CompleteGUI_Init();return;}
		level=3,part=0;
	}
	if (level==3&&part==7)
	{
		if(mode==3&&coll>40){CompleteGUI_Init();return;}
		if(mode==1&&restarts>2){CompleteGUI_Init();return;}
		level=4,part=0;
	}
	if (level==4&&part==26)
	{
		if(mode==3&&coll>75){CompleteGUI_Init();return;}
		if(mode==1&&restarts>3){CompleteGUI_Init();return;}
		level=5,part=0;
	}
	if (level==5&&part==23)
	{
		if(mode==3&&coll>125){CompleteGUI_Init();return;}
		if(mode==1&&restarts>5){CompleteGUI_Init();return;}
		level=6,part=0;
	}
	if (level==6&&part==32)
	{
		if(mode==3&&coll>200){CompleteGUI_Init();return;}
		if(mode==1&&restarts>8){CompleteGUI_Init();return;}
		level=7,part=0;
	}
	if (level==7&&part==27)
	{
		if(mode==3&&coll>50){CompleteGUI_Init();return;}
		if(mode==1&&restarts>2){CompleteGUI_Init();return;}
		level=-1,part=0;
	}
	if (level==-1&&part==22){CompleteGUI_Init();return;}
}
bool ProcessCurCred()
{
	CreditsRail->RenderEx(400,300,0,4,1);
	Credits->Render(creditfly,300);
	int times=1;if (LOWFPS)times=17;
	if (credstop)credbrk+=hge->Timer_GetDelta();
	if (credbrk>=4.5&&!creddone)creddone=true,credstop=false,creditacc=0,credbrk=0;
	if (!credstop)for (int i=1;i<=times;++i)creditfly-=creditacc;
	if (creditfly<-300)return true;
	for (int i=1;i<=times;++i)if (creditacc<2)creditacc+=0.015;
	if (abs(creditfly-400)<5&&!creddone&&!credstop)credstop=true;
	return false;
}
void AboutScene()
{
	if (ProcessCurCred())
		creditfly=1200,creditacc=0,credstop=creddone=false,++creditsp,
		Credits=new hgeSprite(TexCredits,0,creditsp*200,600,200),
		Credits->SetHotSpot(300,100);
	if(hge->Input_GetKeyStateEx(HGEK_Z)==HGEKST_HIT||creditsp>11)
	{
		Current_Position=0;
		mainMenu.Init(-200);
		Music_Stop();
	}
}
bool Foclost()
{
	if (Current_Position==1)PauseGUI_Init();
	return false;
}
bool FrameFunc()
{
	float dt=hge->Timer_GetDelta();
	static float t=0.0f;
	float tx,ty;
	if (Current_Position==1&&hge->Input_GetKeyState(HGEK_ESCAPE))PauseGUI_Init();
	if (mainMenu.isActive())mainMenu.Update();
	if (startMenu.isActive())startMenu.Update();
	if (Current_Position==0)
	{
		if(!mainMenu.isActive())return true;
		if(hge->Input_GetKeyStateEx(HGEK_ENTER)==HGEKST_HIT||hge->Input_GetKeyStateEx(HGEK_Z)==HGEKST_HIT)
		{
            switch(mainMenu.GetSelected())
            {
            	case 0:Current_Position=3;startMenu.Init();mainMenu.Leave();break;
            	case 3:
					Credits->SetHotSpot(300,100);
					CreditsRail->SetHotSpot(300,100);
					creditsp=0;
					Music_Init("./Resources/Music/BLR2_TR09.ogg");
					lpst=lped=0;
					Music_Play();
					creditfly=1200;creditacc=0;credstop=creddone=false;
					Current_Position=4;
					mainMenu.Leave();
					break;
            	case 4:mainMenu.Leave();break;
            }
            return false;
		}
	}
	if (Current_Position==3)
	{
		if(hge->Input_GetKeyStateEx(HGEK_ESCAPE)==HGEKST_HIT)
		{
            startMenu.Leave();mainMenu.Init(800);Current_Position=0;
		}
		if(hge->Input_GetKeyStateEx(HGEK_ENTER)==HGEKST_HIT||hge->Input_GetKeyStateEx(HGEK_Z)==HGEKST_HIT)
		{
			startMenu.Leave();
			switch(startMenu.GetSelected())
			{
                case 0:
					playerpos.x=400,playerpos.y=400,playerrot=0;
					frameleft=ThirtySeconds;infofade=0xFF;Dis8ref=t8special=false;
					level=1,part=1;frms=0,averfps=0.0;bsscale=1;
					towcnt=bulcnt=0;whrcnt=12;skyactive=false;PlayerSplit=false;
					score=0;Mult_Init();//Music_Init("./Resources/Music/CanonTechno.ogg");
					lpst=4625568;lped=9234584;//Music_Play();
					coll=semicoll=clrusg=0;playerLockX=playerLockY=false;
					Lock.Init(2);IfShowTip=true;lsc=0;
					//Lock.SetTexture(SprSheet,151,264,2,8);
					clrrad=pi/2;clrrange=0;re.SetSeed(time(NULL));
					memset(tower,0,sizeof(tower));
					memset(bullet,0,sizeof(bullet));
					Complete=false;
					Current_Position=1;
					Level1Part1();
					IfCallLevel=true;
					mode=1;
				break;
				case 1:
					playerpos.x=400,playerpos.y=400,playerrot=0;
					frameleft=ThirtySeconds;infofade=0xFF;Dis8ref=t8special=false;
					level=-2,part=0;frms=0,averfps=0.0;bsscale=1;assetime=0;
					towcnt=bulcnt=0;whrcnt=12;skyactive=false;PlayerSplit=false;
					score=0;Mult_Init();//Music_Init("./Resources/Music/CanonTechno.ogg");
					lpst=4625568;lped=9234584;//Music_Play();
					coll=semicoll=clrusg=0;playerLockX=playerLockY=false;
					Lock.Init(2);IfShowTip=true;lsc=0;
					//Lock.SetTexture(SprSheet,151,264,2,8);
					clrrad=pi/2;clrrange=0;re.SetSeed(time(NULL));
					memset(tower,0,sizeof(tower));
					memset(bullet,0,sizeof(bullet));
					Complete=false;
					Current_Position=1;
					IfCallLevel=true;
					mode=2;
				break;
				case 2:
					playerpos.x=400,playerpos.y=400,playerrot=0;
					frameleft=ThirtySeconds;infofade=0xFF;Dis8ref=t8special=false;
					level=1,part=1;frms=0,averfps=0.0;bsscale=1;
					towcnt=bulcnt=0;whrcnt=12;skyactive=false;PlayerSplit=false;
					score=0;Mult_Init();//Music_Init("./Resources/Music/CanonTechno.ogg");
					lpst=4625568;lped=9234584;//Music_Play();
					coll=semicoll=clrusg=0;playerLockX=playerLockY=false;
					Lock.Init(2);IfShowTip=true;lsc=0;
					//Lock.SetTexture(SprSheet,151,264,2,8);
					clrrad=pi/2;clrrange=0;re.SetSeed(time(NULL));
					memset(tower,0,sizeof(tower));
					memset(bullet,0,sizeof(bullet));
					Complete=false;
					Current_Position=1;
					Level1Part1();
					IfCallLevel=true;
					mode=3;
				break;
			}
			return false;
		}
	}
	if (Current_Position==5)DeathGUI_FrameFnk();
	if (Current_Position==6)CompleteGUI_FrameFnk();
	if (Current_Position==7)NewHighScoreGUI_FrameFnk();
	if (Current_Position==8)HighScoreGUI_FrameFnk();
	if (Current_Position==9)HSViewGUI_FrameFnk();
	if (Current_Position==10)HSDetGUI_FrameFnk();
	if (Current_Position==11)PauseGUI_FrameFnk();
	if (Current_Position==12)BkTTitleGUI_FrameFnk();
	if (Current_Position==13)OptionsGUI_FrameFnk();
	if (Current_Position==14)PlayerProfGUI_FrameFnk();
	// Here we update our background animation
	t+=dt;
	tx=50*cosf(t/60);
	ty=50*sinf(t/60);
	quad.v[0].tx=tx;        quad.v[0].ty=ty;
	quad.v[1].tx=tx+800/64; quad.v[1].ty=ty;
	quad.v[2].tx=tx+800/64; quad.v[2].ty=ty+600/64;
	quad.v[3].tx=tx;        quad.v[3].ty=ty+600/64;
	//Rendering***********************************************************************************
	//Super Spliter!*****Super Spliter!*****Super Spliter!*****Super Spliter!*****Super Spliter!**
	//******Super Spliter!*****Super Spliter!*****Super Spliter!*****Super Spliter!***************
	hge->Gfx_BeginScene();
	for(int i=0;i<4;i++)quad.v[i].col=DBGColor;
	hge->Gfx_Clear(SETA(DBGColor,0xFF));
	if (skyactive)sky.Update(),sky.Render();
	hge->Gfx_RenderQuad(&quad);
	if(mainMenu.isActive())mainMenu.Render();
	//if (Current_Position==3)StartGUI->Render();
	if(startMenu.isActive())startMenu.Render();
	if (Current_Position==0||Current_Position==3||Current_Position==8||
		Current_Position==9||Current_Position==10||Current_Position==13||Current_Position==14)
	{
		//titlespr->Render(160,0);
		//if (Current_Position==0)gui->Render();
		//mainMenu.Render();
		titlespr->Render(160,0);
	}
	if (Current_Position==1||Current_Position==2||Current_Position==5||Current_Position==11||Current_Position==12)
	{
	//If we are at the main scene or tip scene(which towers and bullets should still appear..)
	//Render towers, bullets and player.
		if (Leaves.IsActive())Leaves.Update();
		if (binter.active())binter.Update();
		if (bdiff.active())bdiff.Update();
		if (LE_Active)Leaf.Update();
		shots=0;
		dsmc=scminus=0;
		Music_Update();
		ProcessTower1();
		ProcessTower2();
		ProcessTower3();
		ProcessTower4();
		ProcessTower5();
		ProcessTower6();
		ProcessTower7();
		ProcessTower8();
		ProcessTower9();
		ProcessLaser();
		for (int i=1;i<=bulcnt;++i)
		{
			switch (bullet[i].bullettype)
			{
				case 1:ProcessBullet1(i);break;
				case 2:ProcessBullet2(i);break;
				case 4:ProcessBullet4(i);break;
				case 5:ProcessBullet5(i);break;
				case 6:ProcessBullet6(i);break;
				case 7:ProcessBullet7(i);break;
				case 8:ProcessBullet8(i);break;
				case 9:ProcessBullet9(i);break;
				case 253:BulletDeath_Process(i);break;
				case 254:SCEffect_Process(i);break;
				case 255:ProcessBullet255(i);break;
			}
		}
		if (Current_Position==1)CallLevels();
		ProcessPlayer();
		RefreshScore();
		{
			if (ATarg.visible)ATarg.TargFollowPlayer(),ATarg.TargRender();
		}
		{
			if (BTarg.visible)BTarg.TargRender();
		}
		if (!DisablePlayer)--frameleft;
		if (!LOWFPS)
		{
			if (playerspeed<playerfulspd)playerspeed+=playerfulspd/400;
			if (playerslospeed<playerfulslospd)playerslospeed+=playerfulslospd/400;
		}
		else
		{
			if (playerspeed<playerfulspd)playerspeed+=playerfulspd/25;
			if (playerslospeed<playerfulslospd)playerslospeed+=playerfulslospd/25;
		}
	}
	if (frameleft==0&&Current_Position==1)
	{
		IfCallLevel=true;
		++part;
		IfShowTip=true;
	}
	if (shots)hge->Effect_Play(snd);
	if (Current_Position==2)ShowTip(lasttip);
	if (Current_Position==4)AboutScene();
	if (Current_Position==5)DeathGUI->Render();
	if (Current_Position==6)CompleteGUI->Render();
	if (Current_Position==7)NewHighScoreGUI_Render();
	if (Current_Position==8)HighScoreGUI->Render();
	if (Current_Position==9)HSViewGUI->Render();
	if (Current_Position==10)HSDetailGUI->Render();
	if (Current_Position==11)PauseGUI->Render();
	if (Current_Position==12)BkTTitleGUI->Render();
	if (Current_Position==13)OptionsGUI->Render();
	if (Current_Position==14)PlayerProfGUI->Render();
	fnt->SetColor(0xFFFFFFFF);
	rbPanelFont.UpdateString(L" FPS: %.2f",hge->Timer_GetFPSf());
	rbPanelFont.Render(785,595,0xFFFFFFFF,1);
	if (Current_Position==1||Current_Position==2)
	{
		rbPanelFont.UpdateString(L"AF: %.2f",averfps);
		rbPanelFont.Render(785,575,0xFFFFFFFF,1);
		if (playerpos.x<220&&playerpos.y<200)
		{
			if (!LOWFPS&&infofade>=0x33)--infofade;
			if (LOWFPS&&infofade>0x33)infofade-=16;
		}
		else
		{
			if (!LOWFPS&&infofade<0xFF)++infofade;
			if (LOWFPS&&infofade<=0xEF)infofade+=16;
		}
		fnt->SetColor(SETA(0xFFFFFF,infofade));
		fnt->printf(5, 0, HGETEXT_LEFT, "Frames to go: %d",frameleft);
#ifdef WIN32
		fnt->printf(5, 25, HGETEXT_LEFT, "Score: %I64d",score);
#endif
#ifndef WIN32
		fnt->printf(5, 25, HGETEXT_LEFT, "Score: %lld",score);
#endif
		fnt->printf(5, 50, HGETEXT_LEFT, "Level %d",level);
		if (mode==3)
			fnt->printf(5, 75, HGETEXT_LEFT, "Collisions: %d",coll);
		else if (mode==2)
			fnt->printf(5, 75, HGETEXT_LEFT, "Elapsed Time: %.2lf",assetime);
		else
			fnt->printf(5, 75, HGETEXT_LEFT, "Restarts: %d",restarts);
		fnt->printf(5, 100, HGETEXT_LEFT, "Semi-Collisions: %d",semicoll);
		if(mode==2)
		{
			fnt->printf(5, 125, HGETEXT_LEFT, "Multiplier: %.2lf",mult);
		}
		else
		{
			fnt->printf(5, 125, HGETEXT_LEFT, "Clear Range Left: %d",clrtime+clrbns);
			fnt->printf(5, 150, HGETEXT_LEFT, "Multiplier: %.2lf",mult);
		}
	}
	if(hge->Input_GetKeyStateEx(HGEK_S)==HGEKST_HIT)hge->System_Snapshot();
	hge->Gfx_EndScene();
	return false;
}
void printHelp(char *exec,const char* str="")
{
	printf("Usage: %s [options]...\n",exec);
	printf("To run the game normally, just start without arguments.\n");
	printf("Options:\n");
	printf("--help            Print this help and exit.\n");
	printf("--version         Print version and exit.\n");
	printf("--start=x,y       Start free play mode directly from level x part y. The part must be valid.\n");
	printf("--nosound         Forcibly use no sound.\n");
	printf("--fullscreen=1/0  Forcibly use fullscreen/windowed. This will override your configuration.\n");
	printf("--firststartup    Forcibly run first start up. This will reset the score file.\n");
	printf("--fast            Fast mode. All levels are two times shorter.\n");
	printf("--logfile=...     Use an alternate log file name instead of the default \"BLRLOG.txt\".\n");
#ifdef WIN32
	printf("--nohideconsole   Do not hide console (Windows version only).\n");
#endif
	if(strcmp(str,""))printf("%s\n",str);
	exit(0);
}
void parseArgs(int argc,char *argv[])
{
	for(int i=1;i<argc;++i)
	{
		if(!strcmp(argv[i],"--help"))printHelp(argv[0]);
		if(!strcmp(argv[i],"--version"))
		{
			printf("Bullet Lab Remix II %s\n",BLRVERSION);
			printf("Built Date: %s",BuiltDate);
			exit(0);
		}
		bool valid=false;
		if(!strcmp(argv[i],"--nosound"))fNoSound=true,valid=true;
		if(!strcmp(argv[i],"--fast"))fFast=true,valid=true;
		if(!strcmp(argv[i],"--firststartup"))fFristStartUp=true,valid=true;
		if(!strncmp(argv[i],"--fullscreen",12))
		{
			char *ptr=argv[i];while(*ptr!='='&&*ptr)++ptr;
			if(!*ptr)printHelp(argv[0],"--fullscreen need a parameter!\n");
			++ptr;
			int para=strtol(ptr,&ptr,10);
			if(*ptr||(para!=1&&para!=0))printHelp(argv[0],"Invalid parameter for --fullscreen!\n");
			if(para)fFullScreen=2;else fFullScreen=1;
			valid=true;
		}
		if(!strncmp(argv[i],"--start",7))
		{
			char *ptr=argv[i];while(*ptr!='='&&*ptr)++ptr;
			if(!*ptr)printHelp(argv[0],"--start need two parameters!");
			++ptr;startLvl=strtol(ptr,&ptr,10);
			if(*ptr!=',')printHelp(argv[0],"Invalid parameter for --start!\n");
			++ptr;startPrt=strtol(ptr,&ptr,10);
			if(*ptr)printHelp(argv[0],"Invalid parameter for --start!\n");
			valid=true;
		}
		if(!strncmp(argv[i],"--logfile",9))
		{
			char *ptr=argv[i];while(*ptr!='='&&*ptr)++ptr;
			if(!*ptr)printHelp(argv[0],"--logfile need a parameter!");
			++ptr;strcpy(alterLog,ptr);
			valid=true;
		}
#ifdef WIN32
		if(!strncmp(argv[i],"--nohideconsole",15))noHideConsole=true,valid=true;
#endif
		if(!valid)
		{
			char err[256];sprintf(err,"Unknown option: %s\n",argv[i]);
			printHelp(argv[0],err);
		}
	}
}
int main(int argc,char *argv[])
{
	parseArgs(argc,argv);
#ifdef WIN32
	if(!noHideConsole)FreeConsole();
#endif
	srand(time(NULL));
	hge=hgeCreate(HGE_VERSION);
	if(alterLog[0])
	hge->System_SetState(HGE_LOGFILE, alterLog);
	else
	hge->System_SetState(HGE_LOGFILE, "BLRLOG.txt");
	hge->System_Log("%s: Bullet Lab Remix Log File",MAIN_SRC_FN);
#ifdef WIN32
#ifdef MINGW_BUILD
	hge->System_Log("%s: Build: MinGW_w64 cross build",MAIN_SRC_FN);
#else
	hge->System_Log("%s: Build: Win32 build",MAIN_SRC_FN);
#endif
#else
	hge->System_Log("%s: Build: Unix build",MAIN_SRC_FN);
#endif
	hge->System_Log("%s: Version: %s",MAIN_SRC_FN,BLRVERSION);
	hge->System_Log("%s: Built Date: %s",MAIN_SRC_FN,BuiltDate);
#ifdef WIN32
	if (_mkdir("./Resources")!=0||_mkdir("./Resources/Music")!=0)
		Error("Cannot decompress resources!\nDetailed Information: An error occured while creating folder.\n\nTry restarting the game.");
	hge->System_Log("%s: Folders created successfully.",MAIN_SRC_FN);
	Expand("BLRData.dtp","Resources");
	Expand("BLRMusic.dtp","Resources/Music");
	hge->System_Log("%s: Resources decompressed successfully.",MAIN_SRC_FN);
#endif
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_FOCUSLOSTFUNC, Foclost);
	hge->System_SetState(HGE_DONTSUSPEND, true);
	hge->System_SetState(HGE_TITLE, "Bullet Lab Remix");
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, 800);
	hge->System_SetState(HGE_SCREENHEIGHT, 600);
	hge->System_SetState(HGE_SCREENBPP, 32);
	if(fNoSound)hge->System_SetState(HGE_USESOUND,false);
#ifdef WIN32
	hge->System_SetState(HGE_ICON, MAKEINTRESOURCE(1));
#endif
	hge->System_SetState(HGE_FPS,0);
	if((access("blr.cfg",0))==-1)
	{
		hge->System_Log("%s: Config file not found. Calling first startup.",MAIN_SRC_FN);
		firststartup();
	}
	if(fFristStartUp)firststartup();
	hge->System_Log("%s: Loading config file",MAIN_SRC_FN);
	freopen("blr.cfg","r",stdin);
	char tch=getchar();
	if (tch!=';'){}
	tch=getchar();
	if (tch!='C'){}
	tch=getchar();
	if (tch!='B'){}
	tch=getchar();
	if (tch!='L'){}
	fpslvl=0;
	LOWFPS=true;//always LowFPS, deprecate 1000 FPS mode...
	hge->System_SetState(HGE_FPS,HGEFPS_VSYNC);//try vsync first
	tch=getchar();//LOWFPS
	if (tch==1)
	{
		LOWFPS=true;
		TenSeconds=600;
		TwentySeconds=1200;
		ThirtySeconds=1800;
		AMinute=3600;
		hge->System_SetState(HGE_FPS,61);
		fpslvl=1;
	}
	if(fFast)TenSeconds/=2,TwentySeconds/=2,ThirtySeconds/=2,AMinute/=2;
	tch=getchar();//FULLSCRREEN
	tfs=false;
	if (tch==1)
	hge->System_SetState(HGE_WINDOWED, false),tfs=true;
	if(fFullScreen==2)hge->System_SetState(HGE_WINDOWED, false),tfs=true;
	if(fFullScreen==1)hge->System_SetState(HGE_WINDOWED, true),tfs=false;
	tch=getchar();//vsync
	if (tch==1)
	{
		hge->System_SetState(HGE_FPS,HGEFPS_VSYNC);
		fpslvl=2;
	}
	tch=getchar();//Key binding
	if (tch==1)diffkey=true;
	plrspd=tch=getchar();
	playerfulspd=(tch)*0.08f;
	playerspeed=playerfulspd;
	plrslospd=tch=getchar();
	playerfulslospd=(tch)*0.02f;
	playerslospeed=playerfulslospd;
	tch=getchar();
	clrbns=tch;
	tch=getchar();
	clrmode=tch;
	fclose(stdin);
	if (AP_Update(plrspd,plrslospd,clrbns)>10000)Error("Invalid configuration!\nDelete blr.cfg and run the game again!");
	hge->System_Log("%s: Loading Score file",MAIN_SRC_FN);
	Score_Init();
#ifdef Debug
	playerspeed=playerfulspd=0.2;
	playerslospeed=playerfulslospd=0.05;
#endif
	Current_Position=0;
	LE_Active=false;
	if(hge->System_Initiate())
	{
		quad.tex=hge->Texture_Load("./Resources/b_null.png");
		SprSheet=hge->Texture_Load("./Resources/ss.png");
		TLeaf=hge->Texture_Load("./Resources/e_leaf.png");
		TSflake=hge->Texture_Load("./Resources/e_sflake.png");
		TexTitle=hge->Texture_Load("./Resources/title.png");
		TexCredits=hge->Texture_Load("./Resources/credits.png");
		MenuTex=hge->Texture_Load("./Resources/menus.png");
		sky.Init();
		snd=hge->Effect_Load("./Resources/tap.ogg");
		titlespr=new hgeSprite(TexTitle,0,0,640,320);
		playerspr=new hgeSprite(SprSheet,0,24,24,24);
		playerspr->SetHotSpot(12,12);
		playerspr->SetColor(0xC0FFFFFF);
		ATarg.Init(-0.001,vector2d(400,300));
		BTarg.Init(-0.001,vector2d(400,300));
		BTarg.targspr->SetColor(0xFFC00000);
		if(!quad.tex||!SprSheet||!TexTitle||!TexCredits)
		Error("Error Loading Resources!",true);
		quad.blend=BLEND_ALPHABLEND | BLEND_COLORMUL | BLEND_NOZWRITE;
		DBGColor=0xFF888820;
		for(int i=0;i<4;i++)
		{
			quad.v[i].z=0.5f;
			quad.v[i].col=DBGColor;
		}
		quad.v[0].x=0; quad.v[0].y=0;
		quad.v[1].x=800; quad.v[1].y=0;
		quad.v[2].x=800; quad.v[2].y=600;
		quad.v[3].x=0; quad.v[3].y=600;
#ifdef WIN32
		if(!rbPanelFont.Init("C:/Windows/Fonts/cour.ttf",18))return 1;
#else
		if(!rbPanelFont.Init("/usr/share/fonts/truetype/freefont/FreeMono.ttf",18))return 1;
#endif
		fnt=new hgeFont("./Resources/charmap.fnt");
		MenuFont=new hgeFont("./Resources/charmap.fnt");
		TipFont=new hgeFont("./Resources/charmap.fnt");
		MultFnt=new hgeFont("./Resources/charmap.fnt");
		spr=new hgeSprite(SprSheet,216,0,24,24);
		Credits=new hgeSprite(TexCredits,0,0,600,200);
		CreditsRail=new hgeSprite(TexCredits,0,2400,600,200);
		for (int ii=0;ii<COLOR_COUNT;++ii)
		{
			TColors i=(TColors)ii;
			TextureRect a=GetTextureRect(0,i);
			bulletspr[i]=new hgeSprite(SprSheet,a.x,a.y,a.w,a.h);
			bulletspr[i]->SetHotSpot(12,12);bulletspr[i]->SetColor(0x80FFFFFF);
		}
		for (int ii=0;ii<grey;++ii)
		{
			TColors i=(TColors)ii;
			TextureRect a=GetTextureRect(1,i);
			towerspr[i]=new hgeSprite(SprSheet,a.x,a.y,a.w,a.h);
			towerspr[i]->SetHotSpot(22,22);bulletspr[i]->SetColor(0x80FFFFFF);
		}
		mainMenu.Init_Once();mainMenu.Init(-200);
		startMenu.Init_Once();
		gui=new hgeGUI();
		gui->AddCtrl(new hgeGUIMenuItem(1,fnt,snd,400,200,0.0f,"Start"));
		gui->AddCtrl(new hgeGUIMenuItem(2,fnt,snd,400,240,0.1f,"Highscores && Records"));
		gui->AddCtrl(new hgeGUIMenuItem(3,fnt,snd,400,280,0.2f,"Options"));
		gui->AddCtrl(new hgeGUIMenuItem(4,fnt,snd,400,320,0.3f,"About"));
		gui->AddCtrl(new hgeGUIMenuItem(5,fnt,snd,400,360,0.4f,"Exit"));
		gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
		gui->SetCursor(spr);
		gui->SetFocus(1);
		gui->Enter();
		if(LOWFPS)hge->System_Log("%s: Low FPS Mode Enabled.",MAIN_SRC_FN);
		if(fNoSound)hge->System_Log("%s: Sound is disabled.",MAIN_SRC_FN);
		if(startLvl)
		{
			hge->System_Log("%s: Starting from Level%dPart%d",MAIN_SRC_FN,startLvl,startPrt);
			gui->Leave();
			playerpos.x=400,playerpos.y=400,playerrot=0;
			frameleft=ThirtySeconds;infofade=0xFF;Dis8ref=t8special=false;
			level=startLvl,part=startPrt;frms=0,averfps=0.0;bsscale=1;
			towcnt=bulcnt=0;whrcnt=12;skyactive=false;PlayerSplit=false;
			score=0;Mult_Init();//Music_Init("./Resources/Music/CanonTechno.ogg");
			lpst=4625568;lped=9234584;//Music_Play();
			coll=semicoll=clrusg=0;playerLockX=playerLockY=false;
			Lock.Init(2);IfShowTip=true;lsc=0;
			clrrad=pi/2;clrrange=0;re.SetSeed(time(NULL));
			memset(tower,0,sizeof(tower));
			memset(bullet,0,sizeof(bullet));
			Complete=false;Current_Position=1;
			IfCallLevel=true;
			mode=3;
		}
		hge->System_Start();
		delete gui;delete titlespr;
		delete fnt;delete playerspr;
		delete spr;
		for (int ii=0;ii<COLOR_COUNT;++ii)
		{
			TColors i=(TColors)ii;
			delete bulletspr[i];
			if(i<grey)delete towerspr[i];
		}
		hge->Texture_Free(SprSheet);hge->Texture_Free(TLeaf);
		hge->Texture_Free(quad.tex);hge->Texture_Free(TSflake);
		hge->Texture_Free(TexTitle);hge->Texture_Free(TexCredits);
	}
	hge->System_Shutdown();
	hge->Release();
#ifdef WIN32
	for(int i=0;i<arFilecount;++i)remove(archive[i]);
	_rmdir("./Resources/Music");
	_rmdir("./Resources");
#endif
	return 0;
}
