//Chrisoft Bullet Lab Remix HGE
//Menu Implementations
//Copyright Chrisoft 2014
//[Perfect Freeze]: Code for menus won't change... until ...?
//                                --Announcement from Chirsno
//static const char* MENUS_H_FN="menus.h";

hgeGUI			*StartGUI,*DeathGUI,*CompleteGUI,*HighScoreGUI;
hgeGUI			*HSViewGUI,*HSDetailGUI,*PauseGUI,*BkTTitleGUI;
hgeGUI			*OptionsGUI,*PlayerProfGUI;
char			ds1[255],ds2[255],ds3[255],ds4[255];
char			hs1[255],hs2[255],hs3[255],hs4[255],hs5[255],hs6[255];
char			HSVstr[7][255];
char			HSDetstr[10][255];
char			opt[10][255];
bool			toogleundl;
int				view,detv;
int				lastkeypressed;
void HSViewGUI_Init();
void HighScoreGUI_Init();
void PauseGUI_Init();
void StartGUI_Init()
{
	StartGUI=new hgeGUI();
	StartGUI->AddCtrl(new hgeGUIMenuItem(1,fnt,snd,400,200,0.0f,"Classic"));
	StartGUI->AddCtrl(new hgeGUIMenuItem(2,fnt,snd,400,240,0.1f,"Not Available!!"));
	StartGUI->AddCtrl(new hgeGUIMenuItem(3,fnt,snd,400,280,0.2f,"Same as the second one"));
	StartGUI->AddCtrl(new hgeGUIMenuItem(4,fnt,snd,400,320,0.3f,"Free Play Mode"));
	StartGUI->AddCtrl(new hgeGUIMenuItem(5,fnt,snd,400,360,0.4f,"Back"));
	StartGUI->SetCursor(spr);
	StartGUI->SetNavMode(HGEGUI_UPDOWN);
	StartGUI->SetFocus(1);
	StartGUI->Enter();
}
void StartGUI_FrameFnk()
{
	float dt=hge->Timer_GetDelta();
	int id=StartGUI->Update(dt);
	if (id)
	{
		switch (id)
		{
			case 1:
				playerpos.x=400,playerpos.y=400,playerrot=0;
				frameleft=ThirtySeconds;infofade=0xFF;Dis8ref=t8special=false;
				level=1,part=1;frms=0,averfps=0.0;bsscale=1;
				towcnt=bulcnt=0;whrcnt=12;skyactive=false;
				score=0;Mult_Init();//Music_Init("./Resources/Music/CanonTechno.ogg");
				lpst=4625568;lped=9234584;//Music_Play();
				coll=semicoll=clrusg=0;playerLockX=playerLockY=false;
				Lock.Init(2);IfShowTip=true;lsc=0;
				//Lock.SetTexture(SprSheet,151,264,2,8);
				clrrad=pi/2;clrrange=0;
				memset(tower,0,sizeof(tower));
				memset(bullet,0,sizeof(bullet));
				Complete=false;
				Current_Position=1;
				Level1Part1();
				IfCallLevel=true;
				mode=1;
				break;
			case 2:
				/*playerpos.x=400,playerpos.y=400,playerrot=0;
				frameleft=TenSeconds;
				level=1,part=1;frms=0,averfps=0.0;restarts=0;bsscale=1;
				towcnt=bulcnt=0;
				mode=1;
				score=0;
				coll=semicoll=clrusg=0;
				clrrad=pi/2;clrrange=0;
				memset(tower,0,sizeof(tower));
				memset(bullet,0,sizeof(bullet));
				Complete=false;
				Refliction=false;
				Level1Part1();
				IfCallLevel=true;
				break;*/
			case 3:
				/*playerpos.x=400,playerpos.y=400,playerrot=0;
				frameleft=ThirtySeconds;
				level=3,part=1;frms=0,averfps=0.0;restarts=0;bsscale=1.5;
				towcnt=4;bulcnt=0;
				clrrad=pi/2;clrrange=0;
				memset(tower,0,sizeof(tower));
				memset(bullet,0,sizeof(bullet));
				mode=2;
				score=0;
				coll=semicoll=clrusg=0;
				IfShowTip=true;
				Complete=false;
				Refliction=false;
				Level3Part0();
				IfCallLevel=true;*/
				break;
			case 4:
				playerpos.x=400,playerpos.y=400,playerrot=0;
				frameleft=ThirtySeconds;infofade=0xFF;Dis8ref=t8special=false;
				level=1,part=1;frms=0,averfps=0.0;bsscale=1;
				towcnt=bulcnt=0;whrcnt=12;skyactive=false;
				score=0;Mult_Init();//Music_Init("./Resources/Music/CanonTechno.ogg");
				lpst=4625568;lped=9234584;//Music_Play();
				coll=semicoll=clrusg=0;playerLockX=playerLockY=false;
				Lock.Init(2);IfShowTip=true;lsc=0;
				//Lock.SetTexture(SprSheet,151,264,2,8);
				clrrad=pi/2;clrrange=0;
				memset(tower,0,sizeof(tower));
				memset(bullet,0,sizeof(bullet));
				Complete=false;
				Current_Position=1;
				Level1Part1();
				IfCallLevel=true;
				mode=3;
				break;
			case 5:
				Current_Position=0;
				StartGUI->Leave();
				gui->Enter();
		}
	}
}
void DeathGUI_Init()
{
	DeathGUI=new hgeGUI();
	Current_Position=5;Music_Stop();
	DisableAllTower=true;DisablePlayer=true;
	DeathGUI->AddCtrl(new hgeGUIMenuItem(1,fnt,snd,400,160,0.0f,"You Are Dead!"));
#ifdef WIN32
	sprintf(ds1,"You scored %I64d at level %d",score,level);
#else
	sprintf(ds1,"You scored %lld at level %d",score,level);
#endif
	DeathGUI->AddCtrl(new hgeGUIMenuItem(2,fnt,snd,400,200,0.1f,ds1));
	switch (mode)
	{
		case 1:sprintf(ds2,"Difficulty: Normal");break;
		case 2:sprintf(ds2,"Difficulty: Extreme");break;
		case 3:sprintf(ds2,"What Happened?! You died in Free Play Mode?!");break;
		case 4:sprintf(ds2,"Difficulty: Easy");break;
	}
	DeathGUI->AddCtrl(new hgeGUIMenuItem(3,fnt,snd,400,240,0.2f,ds2));
	sprintf(ds3,"Average FPS: %.2f",averfps);
	DeathGUI->AddCtrl(new hgeGUIMenuItem(4,fnt,snd,400,280,0.3f,ds3));
	DeathGUI->AddCtrl(new hgeGUIMenuItem(5,fnt,snd,400,320,0.3f,""));
	DeathGUI->AddCtrl(new hgeGUIMenuItem(6,fnt,snd,400,360,0.4f,"Continue from beginning of level? Your score will be set to minus!"));
	DeathGUI->AddCtrl(new hgeGUIMenuItem(7,fnt,snd,400,400,0.5f,"Continue!"));
	DeathGUI->AddCtrl(new hgeGUIMenuItem(8,fnt,snd,400,440,0.6f,"No thanks..."));
	for (int i=1;i<=6;++i)DeathGUI->EnableCtrl(i,false);
	DeathGUI->SetCursor(spr);
	DeathGUI->SetNavMode(HGEGUI_UPDOWN|HGEGUI_CYCLED);
	DeathGUI->SetFocus(7);
	DeathGUI->Enter();
}
void DeathGUI_FrameFnk()
{
	float dt=hge->Timer_GetDelta();
	int id=DeathGUI->Update(dt);
	if (id)
	{
		switch (id)
		{
			case 7:
				IfCallLevel=true;
				IfShowTip=true;
				Current_Position=1;
				DeathGUI->Leave();
				score=-abs(score);
				++restarts;
				part=0;
				clockrot=deltarot=0;
				coll=towcnt=bulcnt=0;
				DisableAllTower=DisablePlayer=false;
				break;
			case 8:Current_Position=0;gui->Enter();DeathGUI->Leave();break;
		}
	}
}
void NewHighScoreGUI_Init()
{
	Current_Position=7;
	memset(newname,0,sizeof(newname));newlen=0;tbframebrk=0;toogleundl=false;
	TipFont->SetColor(0xFFFFFFFF);
}
void nameins(char a)
{
	if (newlen<=14)
		newname[newlen++]=a;
}
void namedel()
{
	if (newlen>0)newname[--newlen]=0;
}
void NewHighScoreGUI_FrameFnk()
{
	int key=hge->Input_GetKey();
	if (key>=0x30&&key<=0x39)nameins('0'+key-0x30);
#ifdef WIN32
	if (key>=0x41&&key<=0x5A)
		if (GetKeyState(VK_CAPITAL)&1)nameins('A'+key-0x41);else nameins('a'+key-0x41);
#else
	if (key>=0x41&&key<=0x5A)
		nameins('A'+key-0x41);
#endif
	if (key==HGEK_SPACE)nameins('_');
	if (key==HGEK_BACKSPACE)namedel();
	if (key==HGEK_ENTER)
	{
		InsertHighScore();
		switch (mode)
		{
			case 4:view=1;HSViewGUI_Init();break;
			case 1:view=2;HSViewGUI_Init();break;
			case 2:view=3;HSViewGUI_Init();break;
			case 3:view=4;HSViewGUI_Init();break;
		}
	}
}
void NewHighScoreGUI_Render()
{
	if (LOWFPS)tbframebrk+=17;else ++tbframebrk;
	if (tbframebrk>=500)toogleundl=!toogleundl,tbframebrk=0;
	TipFont->printf(200,200,HGETEXT_LEFT,"Please Enter Your Honorable Name...");
	if (!toogleundl)
		TipFont->printf(200,240,HGETEXT_LEFT,"%s",newname);
	else
		TipFont->printf(200,240,HGETEXT_LEFT,"%s_",newname);
}
void CompleteGUI_Init()
{
	CompleteGUI=new hgeGUI();
	Current_Position=6;
	DisableAllTower=true;DisablePlayer=true;
	CompleteGUI->AddCtrl(new hgeGUIMenuItem(1,fnt,snd,400,120,0.0f,"YOU DID THAT!"));
#ifdef WIN32
	if (CheckHighScore()!=-1)
		sprintf(hs1,"New Highscore %I64d!",score);
	else
		sprintf(hs1,"Score %I64d",score);
#else
	if (CheckHighScore()!=-1)
		sprintf(hs1,"New Highscore %lld!",score);
	else
		sprintf(hs1,"Score %lld",score);
#endif
	CompleteGUI->AddCtrl(new hgeGUIMenuItem(2,fnt,snd,400,160,0.1f,hs1));
	switch (mode)
	{
		case 1:
		case 2:
		case 4:sprintf(hs2,"Restarts %d",restarts);break;
		case 3:sprintf(hs2,"Collisions %d",coll);break;
	}
	CompleteGUI->AddCtrl(new hgeGUIMenuItem(3,fnt,snd,400,200,0.2f,hs2));
	sprintf(hs3,"Semi-Collisions %d",semicoll);
	CompleteGUI->AddCtrl(new hgeGUIMenuItem(4,fnt,snd,400,240,0.3f,hs3));
	sprintf(hs4,"CLR usage %d",clrusg);
	CompleteGUI->AddCtrl(new hgeGUIMenuItem(5,fnt,snd,400,280,0.3f,hs4));
	sprintf(hs5,"Average FPS %.2f",averfps);
	CompleteGUI->AddCtrl(new hgeGUIMenuItem(6,fnt,snd,400,320,0.4f,hs5));
	if (CheckHighScore()!=-1)
	{
		CompleteGUI->AddCtrl(new hgeGUIMenuItem(7,fnt,snd,400,360,0.5f,"Keep this in your record?"));
		CompleteGUI->AddCtrl(new hgeGUIMenuItem(8,fnt,snd,400,400,0.6f,"Yes"));
		CompleteGUI->AddCtrl(new hgeGUIMenuItem(9,fnt,snd,400,440,0.7f,"No thanks..."));
	}
	else
	{
		CompleteGUI->AddCtrl(new hgeGUIMenuItem(7,fnt,snd,400,360,0.5f,""));
		CompleteGUI->AddCtrl(new hgeGUIMenuItem(8,fnt,snd,400,400,0.6f,""));
		CompleteGUI->AddCtrl(new hgeGUIMenuItem(9,fnt,snd,400,440,0.7f,"Back to menu"));
	}
	for (int i=1;i<=7;++i)CompleteGUI->EnableCtrl(i,false);
	CompleteGUI->SetCursor(spr);
	CompleteGUI->SetNavMode(HGEGUI_UPDOWN|HGEGUI_CYCLED);
	CompleteGUI->SetFocus(7);
	CompleteGUI->Enter();
}
void CompleteGUI_FrameFnk()
{
	float dt=hge->Timer_GetDelta();
	int id=CompleteGUI->Update(dt);
	if (id)
	{
		switch (id)
		{
			case 8:NewHighScoreGUI_Init();CompleteGUI->Leave();break;
			case 9:Current_Position=0;gui->Enter();CompleteGUI->Leave();break;
		}
	}
}
void HSDetGUI_Init()
{
	HSDetailGUI=new hgeGUI();
	Current_Position=10;
	switch (view)
	{
		case 1:
			memset(HSDetstr,0,sizeof(HSDetstr));
			if (!ERec[detv].score)sprintf(HSDetstr[1],"Nothing here...");
			else
			{
				sprintf(HSDetstr[1],"No. %d of Easy Mode",detv);
#ifdef WIN32
				sprintf(HSDetstr[2],"Scored %I64d by %s",ERec[detv].score,ERec[detv].name);
#else
				sprintf(HSDetstr[2],"Scored %lld by %s",ERec[detv].score,ERec[detv].name);
#endif
				sprintf(HSDetstr[3],"Restarts %d",ERec[detv].rescol);
				sprintf(HSDetstr[4],"Semi-Collisions %d",ERec[detv].scoll);
				sprintf(HSDetstr[5],"CLR Usage %d",ERec[detv].clrusg);
				sprintf(HSDetstr[6],"Average FPS %d.%d",ERec[detv].af_int,ERec[detv].af_fric);
			}
			for (int i=1;i<=6;++i)
				HSDetailGUI->AddCtrl(new hgeGUIMenuItem(i,fnt,snd,400,170+30*i,0.1f*i-0.1f,HSDetstr[i])),
				HSDetailGUI->EnableCtrl(i,false);
			HSDetailGUI->AddCtrl(new hgeGUIMenuItem(7,fnt,snd,400,380,0.6f,"Back"));
			break;
		case 2:
			memset(HSDetstr,0,sizeof(HSDetstr));
			if (!NRec[detv].score)sprintf(HSDetstr[1],"Nothing here...");
			else
			{
				sprintf(HSDetstr[1],"No. %d of Normal Mode",detv);
#ifdef WIN32
				sprintf(HSDetstr[2],"Scored %I64d by %s",NRec[detv].score,NRec[detv].name);
#else
				sprintf(HSDetstr[2],"Scored %lld by %s",NRec[detv].score,NRec[detv].name);
#endif
				sprintf(HSDetstr[3],"Restarts %d",NRec[detv].rescol);
				sprintf(HSDetstr[4],"Semi-Collisions %d",NRec[detv].scoll);
				sprintf(HSDetstr[5],"CLR Usage %d",NRec[detv].clrusg);
				sprintf(HSDetstr[6],"Average FPS %d.%d",NRec[detv].af_int,NRec[detv].af_fric);
			}
			for (int i=1;i<=6;++i)
				HSDetailGUI->AddCtrl(new hgeGUIMenuItem(i,fnt,snd,400,170+30*i,0.1f*i-0.1f,HSDetstr[i])),
				HSDetailGUI->EnableCtrl(i,false);
			HSDetailGUI->AddCtrl(new hgeGUIMenuItem(7,fnt,snd,400,380,0.6f,"Back"));
			break;
		case 3:
			memset(HSDetstr,0,sizeof(HSDetstr));
			if (!ExRec[detv].score)sprintf(HSDetstr[1],"Nothing here...");
			else
			{
				sprintf(HSDetstr[1],"No. %d of Extreme Mode",detv);
#ifdef WIN32
				sprintf(HSDetstr[2],"Scored %I64d by %s",NRec[detv].score,NRec[detv].name);
#else
				sprintf(HSDetstr[2],"Scored %lld by %s",NRec[detv].score,NRec[detv].name);
#endif
				sprintf(HSDetstr[3],"Restarts %d",ExRec[detv].rescol);
				sprintf(HSDetstr[4],"Semi-Collisions %d",ExRec[detv].scoll);
				sprintf(HSDetstr[5],"CLR Usage %d",ExRec[detv].clrusg);
				sprintf(HSDetstr[6],"Average FPS %d.%d",ExRec[detv].af_int,ExRec[detv].af_fric);
			}
			for (int i=1;i<=6;++i)
				HSDetailGUI->AddCtrl(new hgeGUIMenuItem(i,fnt,snd,400,170+30*i,0.1f*i-0.1f,HSDetstr[i])),
				HSDetailGUI->EnableCtrl(i,false);
			HSDetailGUI->AddCtrl(new hgeGUIMenuItem(7,fnt,snd,400,380,0.6f,"Back"));
			break;
		case 4:
			memset(HSDetstr,0,sizeof(HSDetstr));
			if (!FPMRec[detv].score)sprintf(HSDetstr[1],"Nothing here...");
			else
			{
				sprintf(HSDetstr[1],"No. %d of Free Play Mode",detv);
#ifdef WIN32
				sprintf(HSDetstr[2],"Scored %I64d by %s",NRec[detv].score,NRec[detv].name);
#else
				sprintf(HSDetstr[2],"Scored %lld by %s",NRec[detv].score,NRec[detv].name);
#endif
				sprintf(HSDetstr[3],"Collisions %d",FPMRec[detv].rescol);
				sprintf(HSDetstr[4],"Semi-Collisions %d",FPMRec[detv].scoll);
				sprintf(HSDetstr[5],"CLR Usage %d",FPMRec[detv].clrusg);
				sprintf(HSDetstr[6],"Average FPS %d.%d",FPMRec[detv].af_int,FPMRec[detv].af_fric);
			}
			for (int i=1;i<=6;++i)
				HSDetailGUI->AddCtrl(new hgeGUIMenuItem(i,fnt,snd,400,170+30*i,0.1f*i-0.1f,HSDetstr[i])),
				HSDetailGUI->EnableCtrl(i,false);
			HSDetailGUI->AddCtrl(new hgeGUIMenuItem(7,fnt,snd,400,380,0.6f,"Back"));
			break;
	}
	HSDetailGUI->SetCursor(spr);
	HSDetailGUI->SetNavMode(HGEGUI_UPDOWN);
	HSDetailGUI->SetFocus(7);
	HSDetailGUI->Enter();
}
void HSDetGUI_FrameFnk()
{
	float dt=hge->Timer_GetDelta();
	int id=HSDetailGUI->Update(dt);
	if (id)
	{
		switch (id)
		{
			case 7:Current_Position=9;HSDetailGUI->Leave();HSViewGUI->Enter();break;
		}
	}
}
void HSViewGUI_Init()
{
	Current_Position=9;
	HSViewGUI=new hgeGUI();
	switch (view)
	{
		case 1:
			HSViewGUI->AddCtrl(new hgeGUIMenuItem(1,fnt,snd,400,200,0.0f,"Highscore - Easy"));
			for (unsigned i=1;i<=Ecnt;++i)
			{
#ifdef WIN32
				sprintf(HSVstr[i],"%u. %s - %I64d",i,ERec[i].name,ERec[i].score);
#else
				sprintf(HSVstr[i],"%u. %s - %lld",i,ERec[i].name,ERec[i].score);
#endif
				HSViewGUI->AddCtrl(new hgeGUIMenuItem(i+1,fnt,snd,400,200+30*i,0.1f*i,HSVstr[i]));
			}
			for (unsigned i=Ecnt+1;i<=5;++i)
			{
				sprintf(HSVstr[i],"%u. ----------",i);
				HSViewGUI->AddCtrl(new hgeGUIMenuItem(i+1,fnt,snd,400,200+30*i,0.1f*i,HSVstr[i]));
			}
			break;
		case 2:
			HSViewGUI->AddCtrl(new hgeGUIMenuItem(1,fnt,snd,400,200,0.0f,"Highscore - Normal"));
			for (unsigned i=1;i<=Ncnt;++i)
			{
#ifdef WIN32
				sprintf(HSVstr[i],"%u. %s - %I64d",i,NRec[i].name,NRec[i].score);
#else
				sprintf(HSVstr[i],"%u. %s - %lld",i,NRec[i].name,NRec[i].score);
#endif
				HSViewGUI->AddCtrl(new hgeGUIMenuItem(i+1,fnt,snd,400,200+30*i,0.1f*i,HSVstr[i]));
			}
			for (unsigned i=Ncnt+1;i<=5;++i)
			{
				sprintf(HSVstr[i],"%u. ----------",i);
				HSViewGUI->AddCtrl(new hgeGUIMenuItem(i+1,fnt,snd,400,200+30*i,0.1f*i,HSVstr[i]));
			}
			break;
		case 3:
			HSViewGUI->AddCtrl(new hgeGUIMenuItem(1,fnt,snd,400,200,0.0f,"Highscore - Extreme"));
			for (unsigned i=1;i<=Excnt;++i)
			{
#ifdef WIN32
				sprintf(HSVstr[i],"%u. %s - %I64d",i,ExRec[i].name,ExRec[i].score);
#else
				sprintf(HSVstr[i],"%u. %s - %lld",i,ExRec[i].name,ExRec[i].score);
#endif
				HSViewGUI->AddCtrl(new hgeGUIMenuItem(i+1,fnt,snd,400,200+30*i,0.1f*i,HSVstr[i]));
			}
			for (unsigned i=Excnt+1;i<=5;++i)
			{
				sprintf(HSVstr[i],"%u. ----------",i);
				HSViewGUI->AddCtrl(new hgeGUIMenuItem(i+1,fnt,snd,400,200+30*i,0.1f*i,HSVstr[i]));
			}
			break;
		case 4:
			HSViewGUI->AddCtrl(new hgeGUIMenuItem(1,fnt,snd,400,200,0.0f,"Highscore - Free Play Mode"));
			for (unsigned i=1;i<=FPMcnt;++i)
			{
#ifdef WIN32
				sprintf(HSVstr[i],"%u. %s - %I64d",i,FPMRec[i].name,FPMRec[i].score);
#else
				sprintf(HSVstr[i],"%u. %s - %lld",i,FPMRec[i].name,FPMRec[i].score);
#endif
				HSViewGUI->AddCtrl(new hgeGUIMenuItem(i+1,fnt,snd,400,200+30*i,0.1f*i,HSVstr[i]));
			}
			for (unsigned i=FPMcnt+1;i<=5;++i)
			{
				sprintf(HSVstr[i],"%u. ----------",i);
				HSViewGUI->AddCtrl(new hgeGUIMenuItem(i+1,fnt,snd,400,200+30*i,0.1f*i,HSVstr[i]));
			}
			break;
	}
	HSViewGUI->AddCtrl(new hgeGUIMenuItem(7,fnt,snd,400,380,0.6f,"Select one record to view details."));
	HSViewGUI->AddCtrl(new hgeGUIMenuItem(8,fnt,snd,400,410,0.7f,"Back"));
	HSViewGUI->EnableCtrl(1,false);HSViewGUI->EnableCtrl(7,false);
	HSViewGUI->SetCursor(spr);
	HSViewGUI->SetNavMode(HGEGUI_UPDOWN|HGEGUI_CYCLED);
	HSViewGUI->SetFocus(2);
	HSViewGUI->Enter();
}
void HSViewGUI_FrameFnk()
{
	float dt=hge->Timer_GetDelta();
	int id=HSViewGUI->Update(dt);
	if (id)
	{
		switch (id)
		{
			case 2:detv=1;HSDetGUI_Init();break;
			case 3:detv=2;HSDetGUI_Init();break;
			case 4:detv=3;HSDetGUI_Init();break;
			case 5:detv=4;HSDetGUI_Init();break;
			case 6:detv=5;HSDetGUI_Init();break;
			case 8:Current_Position=8;HSViewGUI->Leave();if (!HighScoreGUI)HighScoreGUI_Init();HighScoreGUI->Enter();break;
		}
	}
}
void HighScoreGUI_Init()
{
	HighScoreGUI=new hgeGUI();
	Current_Position=8;
	HighScoreGUI->AddCtrl(new hgeGUIMenuItem(1,fnt,snd,350,200,0.0f,"View Highscores && Records for..."));
	HighScoreGUI->AddCtrl(new hgeGUIMenuItem(2,fnt,snd,400,240,0.1f,"Easy"));
	HighScoreGUI->AddCtrl(new hgeGUIMenuItem(3,fnt,snd,400,280,0.2f,"Normal"));
	HighScoreGUI->AddCtrl(new hgeGUIMenuItem(4,fnt,snd,400,320,0.3f,"Extreme"));
	HighScoreGUI->AddCtrl(new hgeGUIMenuItem(5,fnt,snd,400,360,0.4f,"Free Play Mode"));
	HighScoreGUI->AddCtrl(new hgeGUIMenuItem(6,fnt,snd,400,400,0.5f,"Back"));
	HighScoreGUI->EnableCtrl(1,false);
	HighScoreGUI->SetCursor(spr);
	HighScoreGUI->SetNavMode(HGEGUI_UPDOWN|HGEGUI_CYCLED);
	HighScoreGUI->SetFocus(7);
	HighScoreGUI->Enter();
}
void HighScoreGUI_FrameFnk()
{
	float dt=hge->Timer_GetDelta();
	int id=HighScoreGUI->Update(dt);
	if (id)
	{
		switch (id)
		{
			case 2:view=1;HSViewGUI_Init();break;
			case 3:view=2;HSViewGUI_Init();break;
			case 4:view=3;HSViewGUI_Init();break;
			case 5:view=4;HSViewGUI_Init();break;
			case 6:Current_Position=0;HighScoreGUI->Leave();gui->Enter();break;
		}
	}

}
void BkTTitleGUI_Init()
{
	BkTTitleGUI=new hgeGUI();
	Current_Position=12;
	BkTTitleGUI->AddCtrl(new hgeGUIMenuItem(1,fnt,snd,400,200,0.0f,"Really?"));
	BkTTitleGUI->AddCtrl(new hgeGUIMenuItem(2,fnt,snd,200,250,0.1f,"I've pressed the wrong key"));
	BkTTitleGUI->AddCtrl(new hgeGUIMenuItem(3,fnt,snd,600,250,0.2f,"Do return to menu!"));
	BkTTitleGUI->EnableCtrl(1,false);
	BkTTitleGUI->SetCursor(spr);
	BkTTitleGUI->SetNavMode(HGEGUI_LEFTRIGHT|HGEGUI_CYCLED);
	BkTTitleGUI->SetFocus(2);
	BkTTitleGUI->Enter();
}
void BkTTitleGUI_FrameFnk()
{
	float dt=hge->Timer_GetDelta();
	int id=BkTTitleGUI->Update(dt);
	if (id)
	{
		switch (id)
		{
			case 2:
				BkTTitleGUI->Leave();
				Current_Position=11;
				PauseGUI_Init();
				break;
			case 3:
				Current_Position=0;BkTTitleGUI->Leave();gui->Enter();Music_Stop();
				break;
		}
	}
}
void PauseGUI_Init()
{
	PauseGUI=new hgeGUI();Music_Pause();
	Current_Position=11;
	DisableAllTower=DisablePlayer=true;
	PauseGUI->AddCtrl(new hgeGUIMenuItem(1,fnt,snd,400,200,0.0f,"Paused..."));
	PauseGUI->AddCtrl(new hgeGUIMenuItem(2,fnt,snd,400,240,0.1f,"Return to Game"));
	PauseGUI->AddCtrl(new hgeGUIMenuItem(3,fnt,snd,400,280,0.2f,"Return to Title"));
	PauseGUI->EnableCtrl(1,false);
	PauseGUI->SetCursor(spr);
	PauseGUI->SetNavMode(HGEGUI_UPDOWN|HGEGUI_CYCLED);
	PauseGUI->SetFocus(2);
	PauseGUI->Enter();
}
void PauseGUI_FrameFnk()
{
	float dt=hge->Timer_GetDelta();
	int id=PauseGUI->Update(dt);
	if (id)
	{
		switch (id)
		{
			case 2:
				PauseGUI->Leave();
				Current_Position=1;Music_Resume();
				DisableAllTower=DisablePlayer=false;
				break;
			case 3:
				BkTTitleGUI_Init();
				break;
		}
	}
}
int AP_Update(int plrspd,int plrslospd,int clrbns)
{
	int res=0;
	if (plrspd<=4)res+=plrspd*1200;else res+=5000;
	switch (plrslospd)
	{
		case 1:res+=4000;break;
		case 2:res+=3200;break;
		case 3:res+=2000;break;
		case 4:res+=1500;break;
		case 5:res+=700;break;
	}
	switch (clrbns)
	{
		case 0:break;
		case 1:res+=1500;break;
		case 2:res+=2700;break;
		case 3:res+=4000;break;
		case 4:res+=5500;break;
	}
	return res;
}
void Options_Writeback()
{
	freopen("blr.cfg","w",stdout);
	printf(";CBL");
	printf("%c",fpslvl==1?1:0);
	printf("%c",tfs?1:0);
	printf("%c",fpslvl==2?1:0);
	printf("%c",diffkey?1:0);
	printf("%c%c%c%c",plrspd,plrslospd,clrbns,clrmode);
	fclose(stdout);
}
void OptionsGUI_Init()
{
	OptionsGUI=new hgeGUI();
	Current_Position=13;
	if (!tfs)
		sprintf(opt[0],"Fullscreen: Off");
	else
		sprintf(opt[0],"Fullscreen: On");
	OptionsGUI->AddCtrl(new hgeGUIMenuItem(1,fnt,snd,400,200,0.0f,opt[0]));
	switch (fpslvl)
	{
		case 0:sprintf(opt[1],"FPS Level: Natural");break;
		case 1:sprintf(opt[1],"FPS Level: Low FPS");break;
		case 2:sprintf(opt[1],"FPS Level: Highest");break;
	}
	OptionsGUI->AddCtrl(new hgeGUIMenuItem(2,fnt,snd,400,240,0.1f,opt[1]));
	if (diffkey)
		sprintf(opt[2],"Use Key X for Clear Range");
	else
		sprintf(opt[2],"Use Key Z for Clear Range");
	OptionsGUI->AddCtrl(new hgeGUIMenuItem(3,fnt,snd,400,280,0.2f,opt[2]));
	OptionsGUI->AddCtrl(new hgeGUIMenuItem(4,fnt,snd,400,320,0.3f,"Player Profile"));
	OptionsGUI->AddCtrl(new hgeGUIMenuItem(5,fnt,snd,400,360,0.4f,"Save and Exit"));
	OptionsGUI->SetNavMode(HGEGUI_UPDOWN);
	OptionsGUI->SetCursor(spr);
	OptionsGUI->SetFocus(1);
	OptionsGUI->Enter();
}
void PlayerProfGUI_Init()
{
	PlayerProfGUI=new hgeGUI();
	Current_Position=14;
	sprintf(opt[3],"Moving Speed: -%d+",plrspd);
	sprintf(opt[4],"Precise Moving Speed: -%d+",plrslospd);
	sprintf(opt[5],"Clear Range Bonus: -%d+",clrbns);
	sprintf(opt[6],"Clear Range Mode: %s",clrmode?"Rotate":"Expand");
	sprintf(opt[7],"Ability Point %d/10000",AP_Update(plrspd,plrslospd,clrbns));
	PlayerProfGUI->AddCtrl(new hgeGUIMenuItem(1,fnt,snd,400,200,0.0f,opt[3]));
	PlayerProfGUI->AddCtrl(new hgeGUIMenuItem(2,fnt,snd,400,240,0.1f,opt[4]));
	PlayerProfGUI->AddCtrl(new hgeGUIMenuItem(3,fnt,snd,400,280,0.2f,opt[5]));
	PlayerProfGUI->AddCtrl(new hgeGUIMenuItem(4,fnt,snd,400,320,0.3f,opt[6]));
	PlayerProfGUI->AddCtrl(new hgeGUIMenuItem(5,fnt,snd,400,360,0.4f,opt[7]));
	PlayerProfGUI->AddCtrl(new hgeGUIMenuItem(6,fnt,snd,400,400,0.5f,"Back"));
	PlayerProfGUI->SetNavMode(HGEGUI_UPDOWN);
	PlayerProfGUI->SetCursor(spr);
	PlayerProfGUI->SetFocus(1);
	PlayerProfGUI->Enter();
}
void PlayerProfGUI_FrameFnk()
{
	float dt=hge->Timer_GetDelta();
	int id=PlayerProfGUI->Update(dt);
	if (id==6&&AP_Update(plrspd,plrslospd,clrbns)<=10000)
	{PlayerProfGUI->Leave();OptionsGUI_Init();}
	if (id==4)
	{
		clrmode=!clrmode;
		sprintf(opt[6],"Clear Range Mode: %s",clrmode?"Rotate":"Expand");
		((hgeGUIMenuItem*)PlayerProfGUI->GetCtrl(4))->RePos(400,320);
	}
	if (hge->Input_GetKeyState(HGEK_LEFT))
	{
		if (!LOWFPS)++lastkeypressed;else lastkeypressed+=17;
		if (lastkeypressed>=100)
		{
			switch (PlayerProfGUI->GetFocus())
			{
				case 1:
					if (plrspd>1)--plrspd;
					sprintf(opt[3],"Moving Speed: -%d+",plrspd);
					((hgeGUIMenuItem*)PlayerProfGUI->GetCtrl(1))->RePos(400,200);
					sprintf(opt[7],"Ability Point %d/10000",AP_Update(plrspd,plrslospd,clrbns));
					((hgeGUIMenuItem*)PlayerProfGUI->GetCtrl(5))->RePos(400,360);
					break;
				case 2:
					if (plrslospd>1)--plrslospd;
					sprintf(opt[4],"Precise Moving Speed: -%d+",plrslospd);
					((hgeGUIMenuItem*)PlayerProfGUI->GetCtrl(2))->RePos(400,240);
					sprintf(opt[7],"Ability Point %d/10000",AP_Update(plrspd,plrslospd,clrbns));
					((hgeGUIMenuItem*)PlayerProfGUI->GetCtrl(5))->RePos(400,360);
					break;
				case 3:
					if (clrbns>0)--clrbns;
					sprintf(opt[5],"Clear Range Bonus: -%d+",clrbns);
					((hgeGUIMenuItem*)PlayerProfGUI->GetCtrl(3))->RePos(400,280);
					sprintf(opt[7],"Ability Point %d/10000",AP_Update(plrspd,plrslospd,clrbns));
					((hgeGUIMenuItem*)PlayerProfGUI->GetCtrl(5))->RePos(400,360);
					break;
			}
			lastkeypressed=0;
		}
	}
	if (hge->Input_GetKeyState(HGEK_RIGHT))
	{
		if (!LOWFPS)++lastkeypressed;else lastkeypressed+=17;
		if (lastkeypressed>=100)
		{
			switch (PlayerProfGUI->GetFocus())
			{
				case 1:
					if (plrspd<5)++plrspd;
					sprintf(opt[3],"Moving Speed: -%d+",plrspd);
					((hgeGUIMenuItem*)PlayerProfGUI->GetCtrl(1))->RePos(400,200);
					sprintf(opt[7],"Ability Point %d/10000",AP_Update(plrspd,plrslospd,clrbns));
					((hgeGUIMenuItem*)PlayerProfGUI->GetCtrl(4))->RePos(400,320);
					break;
				case 2:
					if (plrslospd<5)++plrslospd;
					sprintf(opt[4],"Precise Moving Speed: -%d+",plrslospd);
					((hgeGUIMenuItem*)PlayerProfGUI->GetCtrl(2))->RePos(400,240);
					sprintf(opt[7],"Ability Point %d/10000",AP_Update(plrspd,plrslospd,clrbns));
					((hgeGUIMenuItem*)PlayerProfGUI->GetCtrl(4))->RePos(400,320);
					break;
				case 3:
					if (clrbns<4)++clrbns;
					sprintf(opt[5],"Clear Range Bonus: -%d+",clrbns);
					((hgeGUIMenuItem*)PlayerProfGUI->GetCtrl(3))->RePos(400,280);
					sprintf(opt[7],"Ability Point %d/10000",AP_Update(plrspd,plrslospd,clrbns));
					((hgeGUIMenuItem*)PlayerProfGUI->GetCtrl(4))->RePos(400,320);
					break;
			}
			lastkeypressed=0;
		}
	}
}
void OptionsGUI_FrameFnk()
{
	float dt=hge->Timer_GetDelta();
	int id=OptionsGUI->Update(dt);
	if (id)
	{
		switch (id)
		{
			case 1:
				tfs=!tfs;
				if (!tfs)
					sprintf(opt[0],"Fullscreen: Off");
				else
					sprintf(opt[0],"Fullscreen: On");
				((hgeGUIMenuItem*)OptionsGUI->GetCtrl(1))->RePos(400,200);
				break;
			case 2:
				switch (fpslvl)
				{
					case 0:
						fpslvl=1;LOWFPS=true;
						hge->System_SetState(HGE_FPS,61);
						TenSeconds=600;
						TwentySeconds=1200;
						ThirtySeconds=1800;
						AMinute=3600;
						break;
					case 1:
						fpslvl=2;LOWFPS=false;
						hge->System_SetState(HGE_FPS,1000);
						TenSeconds=10000;
						TwentySeconds=20000;
						ThirtySeconds=30000;
						AMinute=60000;
						break;
					case 2:
						fpslvl=0;LOWFPS=false;
						hge->System_SetState(HGE_FPS,0);
						TenSeconds=10000;
						TwentySeconds=20000;
						ThirtySeconds=30000;
						AMinute=60000;
						break;
				}
				switch (fpslvl)
				{
					case 0:sprintf(opt[1],"FPS Level: Natural");break;
					case 1:sprintf(opt[1],"FPS Level: Low FPS");break;
					case 2:sprintf(opt[1],"FPS Level: Highest");break;
				}
				((hgeGUIMenuItem*)OptionsGUI->GetCtrl(2))->RePos(400,240);
				break;
			case 3:
				diffkey=!diffkey;
				if (diffkey)
					sprintf(opt[2],"Use Key X for Clear Range");
				else
					sprintf(opt[2],"Use Key Z for Clear Range");
				((hgeGUIMenuItem*)OptionsGUI->GetCtrl(3))->RePos(400,280);
				break;
			case 4:
				PlayerProfGUI_Init();
				break;
			case 5:
				Options_Writeback();
				OptionsGUI->Leave();
				gui->Enter();
				Current_Position=0;
				break;
		}
	}
}
