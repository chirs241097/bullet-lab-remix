//Chrisoft Bullet Lab Remix HGE
//Main Code
//"Copyleft" Chrisoft 2013
//#define Debug
#include "hge.h"
#include "hgefont.h"
#include "hgegui.h"
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include "menuitem.h"
#include "global.h"
#include "towernbullet.h"
#include "levels.h"
#include "scorec.h"
#include "menus.h"
void firststartup()
{
	/*if (MessageBoxA(NULL,"It seems that you are running BLR for the First time!\nLet's do some \
basic settings first!\n\nEnable Low FPS Mode?","First Start Up",0x00000024)==6)
		fpslvl=1;
	else*/
	fpslvl=0;
	/*if (MessageBoxA(NULL,"Enable Fullscreen?","First Start Up",0x00000024)==6)
		tfs=1;
	else*/
		tfs=0;
	diffkey=false;
	plrspd=3;plrslospd=3;clrbns=0;
	hge->System_Log("Finishing first start up configuraion...");
	Options_Writeback();
	Score_Initailize();
}
void Player_Clear()
{
	if (LOWFPS)
		clrrange+=13.6;
	else
		clrrange+=0.8;
	for (int i=1;i<=bulcnt;++i)
	{
		double dis=GetDist(bullet[i].bulletpos,playerpos);
		if (dis<=clrrange&&bullet[i].exist)
		{
			CreateBullet255(bullet[i].bulletpos.x,bullet[i].bulletpos.y,10);
			bullet[i].exist=false;
			bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
			bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
			bullet[i].dist=0;
			bullet[i].bullettype=0;
		}
	}
}
void ProcessPlayer()
{
	playerspr->RenderEx(playerpos.x+8.4,playerpos.y+8.4,playerrot,0.7,0);
	if (DisablePlayer)return;
	if (!LOWFPS)
		playerrot+=0.00174533;
	else
		playerrot+=0.00174533*17;
	double realspd;
	if (hge->Input_GetKeyState(HGEK_SHIFT))
		if (LOWFPS)
			realspd=playerslospeed*17;
		else
			realspd=playerslospeed;
	else
		if (LOWFPS)
			realspd=playerspeed*17;
		else
			realspd=playerspeed;
	if (hge->Input_GetKeyState(HGEK_LEFT))
	{
		if (playerpos.x>10)
			playerpos.x-=realspd;
	}
	if (hge->Input_GetKeyState(HGEK_RIGHT))
	{
		if (playerpos.x<770)
			playerpos.x+=realspd;
	}
	if (hge->Input_GetKeyState(HGEK_UP))
	{
		if (playerpos.y>10)
			playerpos.y-=realspd;
	}
	if (hge->Input_GetKeyState(HGEK_DOWN))
	{
		if (playerpos.y<570)
			playerpos.y+=realspd;
	}
	if (hge->Input_GetKeyState(HGEK_Z)&&clrrange==0&&clrtime+clrbns&&!diffkey)
	{
		Player_Clear();--clrtime;++clrusg;
	}
	if (hge->Input_GetKeyState(HGEK_X)&&clrrange==0&&clrtime+clrbns&&diffkey)
	{
		Player_Clear();--clrtime;++clrusg;
	}
	//Player_Attack();
	if (clrrange!=0)Player_Clear();
	if (clrrange>=300)clrrange=0;
}
void RefreshScore()
{
	if (DisablePlayer)return;
	int multp=1;
	if (mode==2)multp=5;
	if (LOWFPS)
		score+=multp*16;
	else
		score+=multp;
	score+=100*shots;
	score-=scminus;
	score+=2000*dsmc;
	++frms;
	averfps=(averfps*(frms-1)+hge->Timer_GetFPS())/(double)frms;
}
void CallLevels()
{
	//Use this to call level procedures.
	//Don't use this to call the first level!
	if (level<6)clrtime=0;
	if ((mode==4||mode<=2)&&coll!=0){DeathGUI_Init();return;}
	if (!IfCallLevel) return;
	if (level==7&&part==0&&mode==4)//Easy
	{
		CompleteGUI_Init();
		return;
	}
	if (level==8&&part==0&&mode==4)//Easy
	{
		CompleteGUI_Init();
		return;
	}
	if (level==8&&part==12&&(mode==2||mode==3))//Extreme or FPM
	{
		CompleteGUI_Init();
		return;
	}
	if (level==1&&part==1)Level1Part1();
	if (level==1&&part==2)Level1Part2();
	if (level==1&&part==3)Level1Part3();
	if (level==1&&part==4)Level1Part4();
	if (level==2&&part==0)Level2Part0();
	if (level==2&&part==1)Level2Part1();
	if (level==2&&part==2)Level2Part2();
	if (level==2&&part==3)Level2Part3();
	if (level==3&&part==0)Level3Part0();
	if (level==3&&part==1)Level3Part1();
	if (level==3&&part==2)Level3Part2();
	if (level==3&&part==3)Level3Part3();
	if (level==3&&part==4)Level3Part4();
	if (level==3&&part==5)Level3Part5();
	if (level==3&&part==6)Level3Part6();
	if (level==3&&part==7)Level3Part7();
	if (level==4&&part==0)Level4Part0();
	if (level==4&&part==1)Level4Part1();
	if (level==4&&part==2)Level4Part2();
	if (level==4&&part==3)Level4Part3();
	if (level==4&&part==4)Level4Part4();
	if (level==4&&part==5)Level4Part5();
	if (level==4&&part==6)Level4Part6();
	if (level==5&&part==0)Level5Part0();
	if (level==5&&part==1)Level5Part1();
	if (level==5&&part==2)Level5Part2();
	if (level==5&&part==3)Level5Part3();
	if (level==5&&part==4)Level5Part4();
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
	if (level==8&&part==0)Level8Part0();
	if (level==8&&part==1)Level8Part1();
	if (level==8&&part==2)Level8Part2();
	if (level==8&&part==3)Level8Part3();
	if (level==8&&part==4)Level8Part4();
	if (level==8&&part==5)Level8Part5();
	if (level==8&&part==6)Level8Part6();
	if (level==8&&part==7)Level8Part7();
	if (level==8&&part==8)Level8Part8();
	if (level==8&&part==9)Level8Part9();
	if (level==8&&part==10)Level8Part10();
	if (level==8&&part==11)Level8Part11();
}
void AboutScene()
{
	if (LOWFPS)scroll+=0.51;else scroll+=0.03;
	Credits->Render(200,600-scroll);
	CreditsRail->Render(200,0);
	if(hge->Input_GetKeyState(HGEK_Z)||scroll>1624)
	{
		Current_Position=0;
		gui->SetFocus(1);
		gui->Enter();
	}
}
bool FrameFunc()
{
	float dt=hge->Timer_GetDelta();
	static float t=0.0f;
	float tx,ty;
	int id;
	static int lastid=0;
	// If ESCAPE was pressed, tell the GUI to finish
	if (hge->Input_GetKeyState(HGEK_ESCAPE)&&Current_Position==0) { lastid=5; gui->Leave(); }
	if (Current_Position==1&&hge->Input_GetKeyState(HGEK_ESCAPE))PauseGUI_Init();
	// We update the GUI and take an action if
	// one of the menu items was selected
	if (Current_Position==0)
	{
		id=gui->Update(dt);
		if(id == -1)
		{
			switch(lastid)
			{
				case 1:Current_Position=3; StartGUI_Init();gui->Leave();break;
				case 2:gui->Leave();HighScoreGUI_Init();break;
				case 3:gui->Leave();OptionsGUI_Init();break;
				case 4:
					Credits=new hgeSprite(TexCredits,0,0,400,1024);
					CreditsRail=new hgeSprite(TexCredits,400,0,400,1024);
					scroll=0;
					Current_Position=4;
					AboutScene();
					lastid=0;
					break;
				case 5: return true;
			}
		}
		else if(id) { lastid=id; gui->Leave(); }
	}
	if (Current_Position==3)StartGUI_FrameFnk();
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
	return false;
}
bool RenderFunc()
{
	// Render graphics
	hge->Gfx_BeginScene();
	hge->Gfx_RenderQuad(&quad);
	if (Current_Position==0||Current_Position==3||Current_Position==8||
		Current_Position==9||Current_Position==10||Current_Position==13||Current_Position==14)
	{
		if (Current_Position==0)
			gui->Render();
		titlespr->Render(160,0);
	}
	if (Current_Position==3)
		StartGUI->Render();
	if (Current_Position==1||Current_Position==2||Current_Position==5||Current_Position==11||Current_Position==12)
	{
	//If we are at the main scene or tip scene(which towers and bullets should still appear..)
	//Render towers, bullets and player.
		shots=0;
		dsmc=0;
		scminus=0;
		ProcessTower1();
		ProcessTower2();
		ProcessTower3();
		ProcessTower4();
		ProcessTower5();
		ProcessTower6();
		ProcessTower7();
		ProcessBullet1();
		ProcessBullet2();
		//No ProcessBullet3() needed
		ProcessBullet4();
		ProcessBullet5();
		ProcessBullet6();
		ProcessBullet7();
		ProcessBullet255();
		ProcessPlayer();
		SCEffect_Process();
		RefreshScore();
		if (!DisablePlayer)
		--frameleft;//If we are at the tip scene, disable the player movement.
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
	if (frameleft == 0&&Current_Position==1)
	{
		IfCallLevel=true;
		++part;
		IfShowTip=true;
		if (level==1&&part==5)++level,part=0;
		if (level==2&&part==4)++level,part=0;
		if (level==3&&part==8)++level,part=0;
		if (level==4&&part==7)++level,part=0;
		if (level==5&&part==5)++level,part=0;
		if (level==6&&part==10)++level,part=0;
		if (level==7&&part==13)++level,part=0;
	}
	if (Current_Position==1)
	{
		CallLevels();
	}
	if (shots)hge->Effect_Play(snd);
	if (Current_Position==2)
	{
		ShowTip(lasttip);
		//if (Complete)
		//	TipFont->printf(200,200,HGETEXT_LEFT,"Score");
	}
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
	fnt->printf(680, 575, HGETEXT_LEFT, "FPS: %d", hge->Timer_GetFPS());
	if (Current_Position==1||Current_Position==2)
	{
		fnt->printf(670,555, HGETEXT_LEFT, "AF: %.2f", averfps);
		fnt->printf(5, 0, HGETEXT_LEFT, "Frames to go: %d",frameleft);
		fnt->printf(5, 25, HGETEXT_LEFT, "Score: %lld",score);
		fnt->printf(5, 50, HGETEXT_LEFT, "Level %d Part %d",level,part);
		if (mode==3)
			fnt->printf(5, 75, HGETEXT_LEFT, "Collisions: %d",coll);
		else
			fnt->printf(5, 75, HGETEXT_LEFT, "Restarts: %d",restarts);
		fnt->printf(5, 100, HGETEXT_LEFT, "Semi-Collisions: %d",semicoll);
		fnt->printf(5, 125, HGETEXT_LEFT, "Clear Range Left: %d",clrtime+clrbns);
	}
	hge->Gfx_EndScene();
	return false;
}
int main()
{
	srand(time(NULL));
	hge = hgeCreate(HGE_VERSION);
	hge->System_SetState(HGE_LOGFILE, "BLRLOG.txt");
	hge->System_Log("Bullet Lab Remix Log File");
	hge->System_Log("Folder Decompressed created successfully.");
	/*
	Resourece Files list
	bg.lz->bg.png
	blnsns.lz->blnsns.png
	charmap.lz->charmap.fnt
	ss1.lz->ss1.png
	ss2.lz->ss2.png
	title.lz->title.png
	credits.lz->credits.png
	tap.lz->tap.wav
	*/
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, "Bullet Lab Remix");
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, 800);
	hge->System_SetState(HGE_SCREENHEIGHT, 600);
	hge->System_SetState(HGE_SCREENBPP, 32);
	hge->System_SetState(HGE_SHOWSPLASH, false);
	hge->System_SetState(HGE_FPS,0);
	if((access("blr.cfg",0))==-1)
	{
		hge->System_Log("Config file not found. Calling first startup.");
		firststartup();
	}
	hge->System_Log("Loading config file");
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
	tch=getchar();//FULLSCRREEN
	tfs=false;
	if (tch==1)
	hge->System_SetState(HGE_WINDOWED, false),tfs=true;
	tch=getchar();//LockFPS
	if (tch==1&&!LOWFPS)
	{
		hge->System_SetState(HGE_FPS,1000);
		fpslvl=2;
	}
	tch=getchar();//Key binding
	if (tch==1)diffkey=true;
	plrspd=tch=getchar();
	playerfulspd=(tch)*0.05f;
	playerspeed=playerfulspd;
	plrslospd=tch=getchar();
	playerfulslospd=(tch)*0.0125f;
	playerslospeed=playerfulslospd;
	tch=getchar();
	clrbns=tch;
	fclose(stdin);
	if (AP_Update(plrspd,plrslospd,clrbns)>10000)Error("Invalid configuration!\nDelete blr.cfg and run the game again!");
	hge->System_Log("Loading Score file");
	Score_Init();
#ifdef Debug
	playerspeed=playerfulspd=0.2;
	playerslospeed=playerfulslospd=0.05;
#endif
	Current_Position=0;//We are at the main menu at first
	if(hge->System_Initiate())
	{
		quad.tex=hge->Texture_Load("./Resources/bg.png");
		SprSheet1=hge->Texture_Load("./Resources/ss1.png");
		SprSheet2=hge->Texture_Load("./Resources/ss2.png");
		TexTitle=hge->Texture_Load("./Resources/title.png");
		TexCredits=hge->Texture_Load("./Resources/credits.png");
		snd=hge->Effect_Load("./Resources/tap.ogg");
		titlespr=new hgeSprite(TexTitle,0,0,640,320);
		playerspr=new hgeSprite(SprSheet1,47,46,24,24);
		playerspr->SetHotSpot(12,12);//Set player anchor
		playerspr->SetColor(0xC0FFFFFF);
		if(!quad.tex||!SprSheet1||!SprSheet2||!TexTitle||!TexCredits)
		{
			Error("Error Loading Resources!",true);
		}
		quad.blend=BLEND_ALPHABLEND | BLEND_COLORMUL | BLEND_NOZWRITE;
		for(int i=0;i<4;i++)
		{
			quad.v[i].z=0.5f;
			quad.v[i].col=0xFFFFFFFF;
		}
		quad.v[0].x=0; quad.v[0].y=0; 
		quad.v[1].x=800; quad.v[1].y=0; 
		quad.v[2].x=800; quad.v[2].y=600; 
		quad.v[3].x=0; quad.v[3].y=600; 
		fnt=new hgeFont("./Resources/charmap.fnt");
		TipFont=new hgeFont("./Resources/charmap.fnt");
		spr=new hgeSprite(SprSheet1,24,46,24,24);
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
		if (LOWFPS)
			hge->System_Log("Low FPS Mode Enabled.\n");
		hge->System_Start();
	}
	// Clean up and shutdown
	hge->System_Shutdown();
	hge->Release();
	return 0;
}
