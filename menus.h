// Chrisoft Bullet Lab Remix HGE -*- C++ -*-
// Menu Implementations
// Copyright Chrisoft 2014
// The menu rewrite is almost complete...
//static const char* MENUS_H_FN="menus.h";
void TriggerSound(int type)
{
	switch(type)
	{
		case 0:hge->Effect_Play(snd);break;
		//case 1:hge->Effect_Play(menuin);break;
		//case 2:hge->Effect_Play(menuout);break;
	}
}
void ConfigureQuad(hgeQuad *quad,double x,double y,double w,double h)
{
	quad->tex=0;quad->blend=BLEND_ALPHABLEND;
	quad->v[0].tx=0;quad->v[0].ty=0;
	quad->v[1].tx=1;quad->v[1].ty=0;
	quad->v[2].tx=1;quad->v[2].ty=1;
	quad->v[3].tx=0;quad->v[3].ty=1;
	quad->v[0].x=x;quad->v[0].y=y;
	quad->v[1].x=x+w;quad->v[1].y=y;
	quad->v[2].x=x+w;quad->v[2].y=y+h;
	quad->v[3].x=x;quad->v[3].y=y+h;
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
	freopen(".blrrc","w",stdout);
	printf(";CBL");
	printf("%c",fpslvl==2?1:0);
	printf("%c",tfs?1:0);
	printf("%c",VidMode);
	printf("%c",diffkey?1:0);
	printf("%c%c%c%c",plrspd,plrslospd,clrbns,clrmode);
	fclose(stdout);
}
char *getRank()
{
	static char retval[256];
	//stub!
	//sprintf something to retval
	if(mode!=2)
	{
		if(level<=3)sprintf(retval,"Try more...");
		if(level<=6)sprintf(retval,"Still need more effort!");
		if(level==7)sprintf(retval,"You've done it!");
		if(level==-1)sprintf(retval,"Why do you come to Earth?");
	}
	return retval;
}
static const char* MMStr[]={
	"Start",
	"Highscore",
	"Options",
	"Help",
	"About",
	"Exit"
};
static const char* OMStr[]={
	"Fullscreen",
	"VSync",
	"Clear Range Key",
	"Resolution",
	"Player Preference",
	"Save and Exit",
	"On",
	"Off",
	"X",
	"Z",
	"800x600",
	"640x480",
	"960x720",
	"1024x768",
	"1280x960",
	"?"
};
static const char *PPMStr[]={
	"Moving Speed",
	"Precise Moving Speed",
	"Clear Range Bonus",
	"Clear Range Mode",
	"Ability Point",
	"Back",
	"Expand",
	"Rotate"
};
static const char *PMStr[]={
	"Paused...",
	"Return to Game",
	"Return to Title"
};
static const char *RTTMStr[]={
	"Really?",
	"I've pressed the wrong key...",
	"Do return to title!"
};
static const char *DMStr[]={
	"Continue? You score will be set to minus!",
	"Continue!",
	"No thanks..."
};
static const char *CMStr[]={
	"Keep this in your highscore record?",
	"Yes",
	"No thanks..."
};
static const char *HSMStr[]={
	"Classic Mode",
	"Assessment Mode",
	"Free Play Mode",
	"Back"
};
class MainMenu
{
private:
	bool active,onIn,onOut;
	int selected;
	double xoffset,yoffset,dyoffset;
	hgeSprite *Ribb;
	hgeQuad UpperGradient,LowerGradient;
public:
	bool isActive(){return active;}
	void Init_Once()
	{
		Ribb=new hgeSprite(MenuTex,256,350,64,16);
		Ribb->SetColor(0xCCFFFFFF);
	}
	void Init(double start)
	{
		xoffset=start;onIn=true;active=true;
		selected=0;dyoffset=yoffset=-selected*30;
		ConfigureQuad(&UpperGradient,xoffset-140,250,320,100);
		UpperGradient.v[0].col=UpperGradient.v[1].col=SETA(DBGColor,0xFF);
		UpperGradient.v[2].col=UpperGradient.v[3].col=SETA(DBGColor,0x00);
		ConfigureQuad(&LowerGradient,xoffset-140,420,320,110);
		LowerGradient.v[0].col=LowerGradient.v[1].col=SETA(DBGColor,0x00);
		LowerGradient.v[2].col=LowerGradient.v[3].col=SETA(DBGColor,0xFF);
	}
	void Leave(){onOut=true;}
	int Update()
	{
		if(DBGColor!=0xFF0A0A0A)
		{
			for(int i=0;i<6;++i)DBGColor=ColorTransfer(DBGColor,0xFF0A0A0A);
			UpperGradient.v[0].col=UpperGradient.v[1].col=SETA(DBGColor,0xFF);
			UpperGradient.v[2].col=UpperGradient.v[3].col=SETA(DBGColor,0x00);
			LowerGradient.v[0].col=LowerGradient.v[1].col=SETA(DBGColor,0x00);
			LowerGradient.v[2].col=LowerGradient.v[3].col=SETA(DBGColor,0xFF);
		}
		if(onIn)
		{
			if(fabs(xoffset-650)<hge->Timer_GetDelta()*1600)return xoffset=650,onIn=false,-1;
			if(xoffset<650)
			xoffset+=hge->Timer_GetDelta()*1600;
			else
			xoffset-=hge->Timer_GetDelta()*1600;
		}
		if(onOut)
		{
			xoffset+=hge->Timer_GetDelta()*1600;
			if(xoffset>=850)active=onOut=false;
		}
		ConfigureQuad(&UpperGradient,xoffset-140,250,320,100);
		ConfigureQuad(&LowerGradient,xoffset-140,420,320,110);
		if(hge->Input_GetKeyStateEx(HGEK_UP)==HGEKST_HIT&&selected>0)--selected,TriggerSound(0);
		if(hge->Input_GetKeyStateEx(HGEK_DOWN)==HGEKST_HIT&&selected<6-1)++selected,TriggerSound(0);
		if(hge->Input_GetKeyStateEx(HGEK_ESCAPE)==HGEKST_HIT)selected=5,TriggerSound(0);
		yoffset=-selected*30;
		if(fabs(dyoffset-yoffset)<7)dyoffset=yoffset;
		if(dyoffset<yoffset)dyoffset+=hge->Timer_GetDelta()*400;
		if(dyoffset>yoffset)dyoffset-=hge->Timer_GetDelta()*400;
		if(onIn||onOut)return -1;
		if(hge->Input_GetKeyStateEx(HGEK_Z)==HGEKST_HIT||hge->Input_GetKeyStateEx(HGEK_ENTER)==HGEKST_HIT)
			return TriggerSound(selected==4?2:1),selected;
		return -1;
	}
	void Render()
	{
		for(int i=0;i<6;++i)
		{
			double calcy=i*30+dyoffset+360;
			if(calcy>249.9&&calcy<500.1)
			MenuFont->printf(xoffset,calcy,HGETEXT_LEFT,MMStr[i]);
		}
		Ribb->RenderEx(xoffset-50,355,0,3,1);
		Ribb->RenderEx(xoffset-50,382,0,3,1);
		hge->Gfx_RenderQuad(&UpperGradient);
		hge->Gfx_RenderQuad(&LowerGradient);
	}
}mainMenu;
class StartMenu
{
private:
	bool active,onIn,onOut;
	double xoffset,yoffset,moffset;
	int selected;
	hgeQuad LeftGradient,RightGradient,LowerGradient;
	hgeSprite *clzk,*azmt,*fpmd,*msel;
public:
	bool isActive(){return active;}
	void Init_Once()
	{
		clzk=new hgeSprite(MenuTex,0,0,256,128);
		azmt=new hgeSprite(MenuTex,256,0,256,128);
		fpmd=new hgeSprite(MenuTex,0,128,256,128);
		msel=new hgeSprite(MenuTex,256,128,256,64);
		clzk->SetHotSpot(128,64);
		azmt->SetHotSpot(128,64);
		fpmd->SetHotSpot(128,64);
	}
	void Init()
	{
		active=true;onIn=true;yoffset=275;
		selected=0;xoffset=-selected*300;moffset=450;
		ConfigureQuad(&LowerGradient,0,400+yoffset,800,120);
		LowerGradient.v[0].col=LowerGradient.v[1].col=SETA(DBGColor,0x00);
		LowerGradient.v[2].col=LowerGradient.v[3].col=SETA(DBGColor,0xFF);
		ConfigureQuad(&LeftGradient,0,320+yoffset,100,200);
		LeftGradient.v[0].col=LeftGradient.v[3].col=SETA(DBGColor,0xFF);
		LeftGradient.v[1].col=LeftGradient.v[2].col=SETA(DBGColor,0x00);
		ConfigureQuad(&RightGradient,700,320+yoffset,100,200);
		RightGradient.v[0].col=RightGradient.v[3].col=SETA(DBGColor,0x00);
		RightGradient.v[1].col=RightGradient.v[2].col=SETA(DBGColor,0xFF);
	}
	void Leave(){onOut=true;}
	int Update()
	{
		LowerGradient.v[0].col=LowerGradient.v[1].col=SETA(DBGColor,0x00);
		LowerGradient.v[2].col=LowerGradient.v[3].col=SETA(DBGColor,0xFF);
		LeftGradient.v[0].col=LeftGradient.v[3].col=SETA(DBGColor,0xFF);
		LeftGradient.v[1].col=LeftGradient.v[2].col=SETA(DBGColor,0x00);
		RightGradient.v[0].col=RightGradient.v[3].col=SETA(DBGColor,0x00);
		RightGradient.v[1].col=RightGradient.v[2].col=SETA(DBGColor,0xFF);
		if(onIn)
		{
			bool alldone=true;
            if(fabs(yoffset-0)<hge->Timer_GetDelta()*800)
				yoffset=0;
			else
				alldone=false,yoffset-=hge->Timer_GetDelta()*800;
			if(fabs(moffset-0)<hge->Timer_GetDelta()*1200)
				moffset=0;
			else alldone=false,moffset-=hge->Timer_GetDelta()*1200;
			if(alldone)onIn=false;
		}
		if(onOut)
		{
            bool alldone=true;
            if(fabs(yoffset-275)<hge->Timer_GetDelta()*800)
				yoffset=275;
			else
				alldone=false,yoffset+=hge->Timer_GetDelta()*800;
			if(fabs(moffset-450)<hge->Timer_GetDelta()*1200)
				moffset=450;
			else alldone=false,moffset+=hge->Timer_GetDelta()*800;
			if(alldone)onOut=active=false;
		}
		if(hge->Input_GetKeyStateEx(HGEK_LEFT)==HGEKST_HIT&&selected>0)--selected,TriggerSound(0);
		if(hge->Input_GetKeyStateEx(HGEK_RIGHT)==HGEKST_HIT&&selected<3-1)++selected,TriggerSound(0);
		if(fabs(xoffset-(-selected*300))<hge->Timer_GetDelta()*1000)
			xoffset=-selected*300;
		else
		{
			if(xoffset<-selected*300)xoffset+=hge->Timer_GetDelta()*1000;
			if(xoffset>-selected*300)xoffset-=hge->Timer_GetDelta()*1000;
		}
		ConfigureQuad(&LowerGradient,0,400+yoffset,800,120);
		ConfigureQuad(&LeftGradient,0,320+yoffset,100,200);
		ConfigureQuad(&RightGradient,700,320+yoffset,100,200);
		if(onIn||onOut)return -1;
		if(hge->Input_GetKeyStateEx(HGEK_ESCAPE)==HGEKST_HIT)TriggerSound(2);
		if(hge->Input_GetKeyStateEx(HGEK_Z)==HGEKST_HIT||hge->Input_GetKeyStateEx(HGEK_ENTER)==HGEKST_HIT)
			return TriggerSound(1),selected;
		return -1;
	}
	void Render()
	{
		clzk->Render(400+xoffset,fabs((xoffset+0))*0.075+400+yoffset);
		azmt->Render(700+xoffset,fabs((xoffset+300))*0.075+400+yoffset);
		fpmd->Render(1000+xoffset,fabs((xoffset+600))*0.075+400+yoffset);
		hge->Gfx_RenderQuad(&LowerGradient);
		hge->Gfx_RenderQuad(&LeftGradient);
		hge->Gfx_RenderQuad(&RightGradient);
		msel->Render(0,moffset+200);
	}
}startMenu;
class OptionsMenu
{
private:
	bool active,onIn,onOut,onSwitch,onSwitchi;
	int selected;
	double xoffset,yoffset,dyoffset,swoffset,moffset;
	hgeSprite *Ribb,*optt;
	hgeQuad UpperGradient,LowerGradient;
public:
	bool isActive(){return active;}
	void Init_Once()
	{
		Ribb=new hgeSprite(MenuTex,256,350,64,16);
		optt=new hgeSprite(MenuTex,256,192,256,64);
		Ribb->SetColor(0xCCFFFFFF);
	}
	void Init(double start)
	{
		xoffset=start;onIn=active=true;onSwitch=onSwitchi=false;
		selected=0;dyoffset=yoffset=-selected*30;moffset=350;
		ConfigureQuad(&UpperGradient,xoffset-140,250,500,50);
		UpperGradient.v[0].col=UpperGradient.v[1].col=SETA(DBGColor,0xFF);
		UpperGradient.v[2].col=UpperGradient.v[3].col=SETA(DBGColor,0x00);
		ConfigureQuad(&LowerGradient,xoffset-140,430,500,100);
		LowerGradient.v[0].col=LowerGradient.v[1].col=SETA(DBGColor,0x00);
		LowerGradient.v[2].col=LowerGradient.v[3].col=SETA(DBGColor,0xFF);
	}
	void Leave(){onOut=true;}
	int Update()
	{
		if(onIn)
		{
			bool alldone=true;
			if(fabs(xoffset-450)<hge->Timer_GetDelta()*1600)xoffset=450;else
			{
				alldone=false;
				if(xoffset<450)
				xoffset+=hge->Timer_GetDelta()*1600;
				else
				xoffset-=hge->Timer_GetDelta()*1600;
			}
			if(fabs(moffset-0)<hge->Timer_GetDelta()*1200)
				moffset=0;
			else alldone=false,moffset-=hge->Timer_GetDelta()*1200;
			if(alldone)return onIn=false,-1;
		}
		if(onOut)
		{
			bool alldone=true;
			xoffset+=hge->Timer_GetDelta()*1600;
			if(xoffset<850)alldone=false;
			if(fabs(moffset-450)<hge->Timer_GetDelta()*1200)
				moffset=450;
			else alldone=false,moffset+=hge->Timer_GetDelta()*800;
			if(alldone)active=onOut=false;
		}
		ConfigureQuad(&UpperGradient,xoffset-140,250,500,100);
		ConfigureQuad(&LowerGradient,xoffset-140,430,500,100);
		if(!onSwitch)
		{
			if(hge->Input_GetKeyStateEx(HGEK_UP)==HGEKST_HIT&&selected>0)--selected,TriggerSound(0);
			if(hge->Input_GetKeyStateEx(HGEK_DOWN)==HGEKST_HIT&&selected<6-1)++selected,TriggerSound(0);
			if(hge->Input_GetKeyStateEx(HGEK_ESCAPE)==HGEKST_HIT)selected=5,TriggerSound(0);
		}
		yoffset=-selected*30;
		if(fabs(dyoffset-yoffset)<7)dyoffset=yoffset;
		if(dyoffset<yoffset)dyoffset+=hge->Timer_GetDelta()*400;
		if(dyoffset>yoffset)dyoffset-=hge->Timer_GetDelta()*400;
		if(onIn||onOut)return -1;
		if(hge->Input_GetKeyStateEx(HGEK_RIGHT)==HGEKST_HIT&&hge->Input_GetKeyStateEx(HGEK_LEFT)==HGEKST_HIT)return -1;
		if(hge->Input_GetKeyStateEx(HGEK_RIGHT)==HGEKST_HIT||hge->Input_GetKeyStateEx(HGEK_Z)==HGEKST_HIT||hge->Input_GetKeyStateEx(HGEK_ENTER)==HGEKST_HIT)
		{
			if(selected==5&&!(hge->Input_GetKeyStateEx(HGEK_Z)==HGEKST_HIT||hge->Input_GetKeyStateEx(HGEK_ENTER)==HGEKST_HIT))
				return -1;
			TriggerSound(selected==5?2:1);
			if(onSwitch||onSwitchi)return -1;
			if(selected<=3)
			{
				onSwitch=true;
				swoffset=100;
			}
			if(selected==0)tfs=!tfs;
			if(selected==1)
			{
				fpslvl=fpslvl==2?0:2;
				if(fpslvl==2)hge->System_SetState(HGE_FPS,HGEFPS_VSYNC);
				if(fpslvl==0)hge->System_SetState(HGE_FPS,61);
			}
			if(selected==2)diffkey=!diffkey;
			if(selected==3)
			{
				++VidMode;
				if(VidMode>4)VidMode=0;
			}
			return selected;
		}
		if(hge->Input_GetKeyStateEx(HGEK_LEFT)==HGEKST_HIT)
		{
			if(onSwitch||onSwitchi)return -1;
			TriggerSound(1);
			if(selected<=3){onSwitchi=true;swoffset=0;}
			if(selected==0)tfs=!tfs;
			if(selected==1)
			{
				fpslvl=fpslvl==2?0:2;
				if(fpslvl==2)hge->System_SetState(HGE_FPS,HGEFPS_VSYNC);
				if(fpslvl==0)hge->System_SetState(HGE_FPS,61);
			}
			if(selected==2)diffkey=!diffkey;
			if(selected==3)
			{
				--VidMode;
				if(VidMode<0)VidMode=4;
			}
			return selected;
		}
		return -1;
	}
	void Render()
	{
		for(int i=0;i<6;++i)
		{
			double calcy=i*30+dyoffset+360;
			if(calcy>249.9&&calcy<500.1)
			{
				MenuFont->SetColor(0xFFFFFFFF);
				MenuFont->printf(xoffset,calcy,HGETEXT_LEFT,OMStr[i]);
				if(i==0)
				{
					if(!(onSwitch||onSwitchi)||selected!=0)
						MenuFont->printf(xoffset+200,calcy,HGETEXT_LEFT,OMStr[tfs?6:7]);
					else
					{
						if(onSwitch)
						{
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+100+swoffset,calcy,HGETEXT_LEFT,OMStr[tfs?7:6]);
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f-255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+200+swoffset,calcy,HGETEXT_LEFT,OMStr[tfs?6:7]);
							swoffset-=hge->Timer_GetDelta()*400;
							if(swoffset<0)swoffset=0,onSwitch=false;
						}
						if(onSwitchi)
						{
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+100+swoffset,calcy,HGETEXT_LEFT,OMStr[tfs?6:7]);
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f-255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+200+swoffset,calcy,HGETEXT_LEFT,OMStr[tfs?7:6]);
							swoffset+=hge->Timer_GetDelta()*400;
							if(swoffset>100)swoffset=0,onSwitchi=false;
						}
					}
				}
				if(i==1)
				{
					if(!(onSwitch||onSwitchi)||selected!=1)
						MenuFont->printf(xoffset+200,calcy,HGETEXT_LEFT,OMStr[fpslvl==2?6:7]);
					else
					{
						if(onSwitch)
						{
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+100+swoffset,calcy,HGETEXT_LEFT,OMStr[fpslvl==2?7:6]);
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f-255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+200+swoffset,calcy,HGETEXT_LEFT,OMStr[fpslvl==2?6:7]);
							swoffset-=hge->Timer_GetDelta()*400;
							if(swoffset<0)swoffset=0,onSwitch=false;
						}
						if(onSwitchi)
						{
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+100+swoffset,calcy,HGETEXT_LEFT,OMStr[fpslvl==2?6:7]);
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f-255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+200+swoffset,calcy,HGETEXT_LEFT,OMStr[fpslvl==2?7:6]);
							swoffset+=hge->Timer_GetDelta()*400;
							if(swoffset>100)swoffset=0,onSwitchi=false;
						}
					}
				}
				if(i==2)
				{
					if(!(onSwitch||onSwitchi)||selected!=2)
						MenuFont->printf(xoffset+200,calcy,HGETEXT_LEFT,OMStr[diffkey?8:9]);
					else
					{
						if(onSwitch)
						{
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+100+swoffset,calcy,HGETEXT_LEFT,OMStr[diffkey?9:8]);
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f-255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+200+swoffset,calcy,HGETEXT_LEFT,OMStr[diffkey?8:9]);
							swoffset-=hge->Timer_GetDelta()*400;
							if(swoffset<0)swoffset=0,onSwitch=false;
						}
						if(onSwitchi)
						{
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+100+swoffset,calcy,HGETEXT_LEFT,OMStr[diffkey?8:9]);
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f-255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+200+swoffset,calcy,HGETEXT_LEFT,OMStr[diffkey?9:8]);
							swoffset+=hge->Timer_GetDelta()*400;
							if(swoffset>100)swoffset=0,onSwitchi=false;
						}
					}
				}
				if(i==3)
				{
					if(!(onSwitch||onSwitchi)||selected!=3)
						MenuFont->printf(xoffset+200,calcy,HGETEXT_LEFT,VidMode>=0&&VidMode<=4?OMStr[VidMode+10]:OMStr[15]);
					else
					{
						if(onSwitch)
						{
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+100+swoffset,calcy,HGETEXT_LEFT,VidMode>=0&&VidMode<=4?OMStr[VidMode==0?14:VidMode+9]:OMStr[15]);
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f-255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+200+swoffset,calcy,HGETEXT_LEFT,VidMode>=0&&VidMode<=4?OMStr[VidMode+10]:OMStr[15]);
							swoffset-=hge->Timer_GetDelta()*400;
							if(swoffset<0)swoffset=0,onSwitch=false;
						}
						if(onSwitchi)
						{
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+100+swoffset,calcy,HGETEXT_LEFT,VidMode>=0&&VidMode<=4?OMStr[VidMode+10]:OMStr[15]);
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f-255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+200+swoffset,calcy,HGETEXT_LEFT,VidMode>=0&&VidMode<=4?OMStr[VidMode==4?10:VidMode+11]:OMStr[15]);
							swoffset+=hge->Timer_GetDelta()*400;
							if(swoffset>100)swoffset=0,onSwitchi=false;
						}
					}
				}
			}
		}
		Ribb->RenderEx(xoffset-50,353,0,6,1);
		Ribb->RenderEx(xoffset-50,380,0,6,1);
		hge->Gfx_RenderQuad(&UpperGradient);
		hge->Gfx_RenderQuad(&LowerGradient);
		optt->Render(300,moffset+300);
	}
}optionMenu;
class PlayerPreferenceMenu
{
private:
	bool active,onIn,onOut,onSwitch,onSwitchi;
	int selected;
	double xoffset,yoffset,dyoffset,swoffset,moffset;
	double shaketime,shakeoffset,shakedelay;
	hgeSprite *Ribb,*optt;
	hgeQuad UpperGradient,LowerGradient;
public:
	bool isActive(){return active;}
	void Init_Once()
	{
		Ribb=new hgeSprite(MenuTex,256,350,64,16);
		optt=new hgeSprite(MenuTex,0,256,256,64);
		Ribb->SetColor(0xCCFFFFFF);
	}
	void Init(double start)
	{
		xoffset=start;onIn=active=true;onSwitch=onSwitchi=false;
		selected=0;dyoffset=yoffset=-selected*30;moffset=350;shaketime=0;
		ConfigureQuad(&UpperGradient,xoffset-140,250,520,50);
		UpperGradient.v[0].col=UpperGradient.v[1].col=SETA(DBGColor,0xFF);
		UpperGradient.v[2].col=UpperGradient.v[3].col=SETA(DBGColor,0x00);
		ConfigureQuad(&LowerGradient,xoffset-140,430,520,100);
		LowerGradient.v[0].col=LowerGradient.v[1].col=SETA(DBGColor,0x00);
		LowerGradient.v[2].col=LowerGradient.v[3].col=SETA(DBGColor,0xFF);
	}
	void Leave(){onOut=true;}
	void Shake(){shaketime=0.2;shakeoffset=10;shakedelay=0.033;}
	int Update()
	{
		if(onIn)
		{
			bool alldone=true;
			if(fabs(xoffset-430)<hge->Timer_GetDelta()*1600)xoffset=430;else
			{
				alldone=false;
				if(xoffset<430)
				xoffset+=hge->Timer_GetDelta()*1600;
				else
				xoffset-=hge->Timer_GetDelta()*1600;
			}
			if(fabs(moffset-0)<hge->Timer_GetDelta()*1200)
				moffset=0;
			else alldone=false,moffset-=hge->Timer_GetDelta()*1200;
			if(alldone)return onIn=false,-1;
		}
		if(onOut)
		{
			bool alldone=true;
			xoffset+=hge->Timer_GetDelta()*1600;
			if(xoffset<850)alldone=false;
			if(fabs(moffset-450)<hge->Timer_GetDelta()*1200)
				moffset=450;
			else alldone=false,moffset+=hge->Timer_GetDelta()*800;
			if(alldone)active=onOut=false;
		}
		ConfigureQuad(&UpperGradient,xoffset-140,250,520,100);
		ConfigureQuad(&LowerGradient,xoffset-140,430,520,100);
		if(!onSwitch)
		{
			if(hge->Input_GetKeyStateEx(HGEK_UP)==HGEKST_HIT&&selected>0)
			TriggerSound(0),--selected==4?--selected:0;
			if(hge->Input_GetKeyStateEx(HGEK_DOWN)==HGEKST_HIT&&selected<6-1)
			TriggerSound(0),++selected==4?++selected:0;
			if(hge->Input_GetKeyStateEx(HGEK_ESCAPE)==HGEKST_HIT)TriggerSound(0),selected=5;
		}
		yoffset=-selected*30;
		if(fabs(dyoffset-yoffset)<7)dyoffset=yoffset;
		if(dyoffset<yoffset)dyoffset+=hge->Timer_GetDelta()*400;
		if(dyoffset>yoffset)dyoffset-=hge->Timer_GetDelta()*400;
		if(onIn||onOut)return -1;
		if(hge->Input_GetKeyStateEx(HGEK_RIGHT)==HGEKST_HIT&&hge->Input_GetKeyStateEx(HGEK_LEFT)==HGEKST_HIT)return -1;
		if(hge->Input_GetKeyStateEx(HGEK_RIGHT)==HGEKST_HIT)
		{
			TriggerSound(1);
			if(onSwitch||onSwitchi)return -1;
			if(selected<=3)
			{
				onSwitch=true;
				swoffset=100;
			}
			if(selected==0)++plrspd>5?plrspd=1:0;
			if(selected==1)++plrslospd>5?plrslospd=1:0;
			if(selected==2)++clrbns>4?clrbns=0:0;
			if(selected==3)clrmode=!clrmode;
			if(selected<=3)return selected;
		}
		if(hge->Input_GetKeyStateEx(HGEK_LEFT)==HGEKST_HIT)
		{
			TriggerSound(1);
			if(onSwitch||onSwitchi)return -1;
			if(selected<=3){onSwitchi=true;swoffset=0;}
			if(selected==0)--plrspd<1?plrspd=5:0;
			if(selected==1)--plrslospd<1?plrslospd=5:0;
			if(selected==2)--clrbns<0?clrbns=4:0;
			if(selected==3)clrmode=!clrmode;
			if(selected<=3)return selected;
		}
		if(hge->Input_GetKeyStateEx(HGEK_Z)==HGEKST_HIT||hge->Input_GetKeyStateEx(HGEK_ENTER)==HGEKST_HIT)
			return TriggerSound(selected==5?2:1),selected;
		return -1;
	}
	void Render()
	{
		for(int i=0;i<6;++i)
		{
			double calcy=i*30+dyoffset+360;
			if(calcy>249.9&&calcy<500.1)
			{
				MenuFont->SetColor(0xFFFFFFFF);
				MenuFont->printf(xoffset-50,calcy,HGETEXT_LEFT,PPMStr[i]);
				if(i==0)
				{
					if(!(onSwitch||onSwitchi)||selected!=0)
						MenuFont->printf(xoffset+200,calcy,HGETEXT_LEFT,"%d",plrspd);
					else
					{
						if(onSwitch)
						{
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+100+swoffset,calcy,HGETEXT_LEFT,"%d",plrspd==1?5:plrspd-1);
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f-255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+200+swoffset,calcy,HGETEXT_LEFT,"%d",plrspd);
							swoffset-=hge->Timer_GetDelta()*400;
							if(swoffset<0)swoffset=0,onSwitch=false;
						}
						if(onSwitchi)
						{
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+100+swoffset,calcy,HGETEXT_LEFT,"%d",plrspd);
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f-255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+200+swoffset,calcy,HGETEXT_LEFT,"%d",plrspd==5?1:plrspd+1);
							swoffset+=hge->Timer_GetDelta()*400;
							if(swoffset>100)swoffset=0,onSwitchi=false;
						}
					}
				}
				if(i==1)
				{
					if(!(onSwitch||onSwitchi)||selected!=1)
						MenuFont->printf(xoffset+200,calcy,HGETEXT_LEFT,"%d",plrslospd);
					else
					{
						if(onSwitch)
						{
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+100+swoffset,calcy,HGETEXT_LEFT,"%d",plrslospd==1?5:plrslospd-1);
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f-255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+200+swoffset,calcy,HGETEXT_LEFT,"%d",plrslospd);
							swoffset-=hge->Timer_GetDelta()*400;
							if(swoffset<0)swoffset=0,onSwitch=false;
						}
						if(onSwitchi)
						{
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+100+swoffset,calcy,HGETEXT_LEFT,"%d",plrslospd);
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f-255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+200+swoffset,calcy,HGETEXT_LEFT,"%d",plrslospd==5?1:plrslospd+1);
							swoffset+=hge->Timer_GetDelta()*400;
							if(swoffset>100)swoffset=0,onSwitchi=false;
						}
					}
				}
				if(i==2)
				{
					if(!(onSwitch||onSwitchi)||selected!=2)
						MenuFont->printf(xoffset+200,calcy,HGETEXT_LEFT,"%d",clrbns);
					else
					{
						if(onSwitch)
						{
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+100+swoffset,calcy,HGETEXT_LEFT,"%d",clrbns==0?4:clrbns-1);
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f-255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+200+swoffset,calcy,HGETEXT_LEFT,"%d",clrbns);
							swoffset-=hge->Timer_GetDelta()*400;
							if(swoffset<0)swoffset=0,onSwitch=false;
						}
						if(onSwitchi)
						{
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+100+swoffset,calcy,HGETEXT_LEFT,"%d",clrbns);
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f-255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+200+swoffset,calcy,HGETEXT_LEFT,"%d",clrbns==4?0:clrbns+1);
							swoffset+=hge->Timer_GetDelta()*400;
							if(swoffset>100)swoffset=0,onSwitchi=false;
						}
					}
				}
				if(i==3)
				{
					if(!(onSwitch||onSwitchi)||selected!=3)
						MenuFont->printf(xoffset+200,calcy,HGETEXT_LEFT,PPMStr[clrmode?7:6]);
					else
					{
						if(onSwitch)
						{
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+100+swoffset,calcy,HGETEXT_LEFT,PPMStr[clrmode?6:7]);
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f-255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+200+swoffset,calcy,HGETEXT_LEFT,PPMStr[clrmode?7:6]);
							swoffset-=hge->Timer_GetDelta()*400;
							if(swoffset<0)swoffset=0,onSwitch=false;
						}
						if(onSwitchi)
						{
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+100+swoffset,calcy,HGETEXT_LEFT,PPMStr[clrmode?7:6]);
							MenuFont->SetColor(SETA(0xFFFFFF,255.0f-255.0f*(swoffset/100.0f)));
							MenuFont->printf(xoffset+200+swoffset,calcy,HGETEXT_LEFT,PPMStr[clrmode?6:7]);
							swoffset+=hge->Timer_GetDelta()*400;
							if(swoffset>100)swoffset=0,onSwitchi=false;
						}
					}
				}
				if(i==4)
				{
					if(shaketime>0)
					{
						shaketime-=hge->Timer_GetDelta();
						shakedelay-=hge->Timer_GetDelta();
						if(shakedelay<0)
						{shakeoffset=-shakeoffset;shakedelay=0.033;}
						if(shaketime<=0)shaketime=shakeoffset=0;
					}
					MenuFont->printf(xoffset+200+shakeoffset,calcy,HGETEXT_LEFT,"%d/10000",AP_Update(plrspd,plrslospd,clrbns));
				}
			}
		}
		Ribb->RenderEx(xoffset-80,355,0,7,1);
		Ribb->RenderEx(xoffset-80,382,0,7,1);
		hge->Gfx_RenderQuad(&UpperGradient);
		hge->Gfx_RenderQuad(&LowerGradient);
		optt->Render(125,moffset+300);
	}
}playerPreferenceMenu;
class PauseMenu
{
private:
	bool active,onIn,onOut;
	int selected;
	double xoffset,yoffset,dyoffset;
	hgeSprite *Ribb;
	hgeQuad UpperGradient,LowerGradient;
public:
	bool isActive(){return active;}
	void Init_Once()
	{
		Ribb=new hgeSprite(MenuTex,256,350,64,16);
		Ribb->SetColor(0xCCFFFFFF);
	}
	void Init(double start)
	{
		//special things to do..
		Music_Pause();
		Current_Position=11;
		DisableAllTower=DisablePlayer=true;
		xoffset=start;onIn=true;active=true;
		selected=1;dyoffset=yoffset=-selected*30;
		ConfigureQuad(&UpperGradient,xoffset-140,190,320,50);
		UpperGradient.v[0].col=UpperGradient.v[1].col=SETA(DBGColor,0xFF);
		UpperGradient.v[2].col=UpperGradient.v[3].col=SETA(DBGColor,0x00);
		ConfigureQuad(&LowerGradient,xoffset-140,340,320,100);
		LowerGradient.v[0].col=LowerGradient.v[1].col=SETA(DBGColor,0x00);
		LowerGradient.v[2].col=LowerGradient.v[3].col=SETA(DBGColor,0xFF);
	}
	void Leave(){if(!onIn)onOut=true;}
	int Update()
	{
		if(onIn)
		{
			if(fabs(xoffset-350)<hge->Timer_GetDelta()*1600)return xoffset=350,onIn=false,-1;
			if(xoffset<350)
			xoffset+=hge->Timer_GetDelta()*1600;
			else
			xoffset-=hge->Timer_GetDelta()*1600;
		}
		if(onOut)
		{
			xoffset+=hge->Timer_GetDelta()*1600;
			if(xoffset>=850)
			{
				active=onOut=false;
				if(selected==1)Current_Position=1,DisableAllTower=DisablePlayer=false;
				return -1;
			}
		}
		ConfigureQuad(&UpperGradient,xoffset-140,190,320,100);
		ConfigureQuad(&LowerGradient,xoffset-140,340,320,110);
		if(hge->Input_GetKeyStateEx(HGEK_UP)==HGEKST_HIT&&selected>1)--selected,TriggerSound(0);
		if(hge->Input_GetKeyStateEx(HGEK_DOWN)==HGEKST_HIT&&selected<3-1)++selected,TriggerSound(0);
		yoffset=-selected*30;
		if(fabs(dyoffset-yoffset)<7)dyoffset=yoffset;
		if(dyoffset<yoffset)dyoffset+=hge->Timer_GetDelta()*400;
		if(dyoffset>yoffset)dyoffset-=hge->Timer_GetDelta()*400;
		if(onIn||onOut)return -1;
		if(hge->Input_GetKeyStateEx(HGEK_Z)==HGEKST_HIT||hge->Input_GetKeyStateEx(HGEK_ENTER)==HGEKST_HIT)
			return TriggerSound(1),selected;
		if(hge->Input_GetKeyStateEx(HGEK_ESCAPE)==HGEKST_HIT&&!onIn)return TriggerSound(1),1;
		return -1;
	}
	void Render()
	{
		for(int i=0;i<3;++i)
		{
			double calcy=i*30+dyoffset+300;
			if(calcy>189.9&&calcy<440.1)
			MenuFont->printf(xoffset,calcy,HGETEXT_LEFT,PMStr[i]);
		}
		Ribb->RenderEx(xoffset-50,295,0,4,1);
		Ribb->RenderEx(xoffset-50,322,0,4,1);
		hge->Gfx_RenderQuad(&UpperGradient);
		hge->Gfx_RenderQuad(&LowerGradient);
	}
}pauseMenu;
class ReturnToTitleMenu
{
private:
	bool active,onIn,onOut;
	int selected;
	double xoffset,yoffset,dyoffset;
	hgeSprite *Ribb;
	hgeQuad UpperGradient,LowerGradient;
public:
	bool isActive(){return active;}
	void Init_Once()
	{
		Ribb=new hgeSprite(MenuTex,256,350,64,16);
		Ribb->SetColor(0xCCFFFFFF);
	}
	void Init(double start)
	{
		xoffset=start;onIn=true;active=true;
		selected=1;dyoffset=yoffset=-selected*30;
		ConfigureQuad(&UpperGradient,xoffset-140,190,320,50);
		UpperGradient.v[0].col=UpperGradient.v[1].col=SETA(DBGColor,0xFF);
		UpperGradient.v[2].col=UpperGradient.v[3].col=SETA(DBGColor,0x00);
		ConfigureQuad(&LowerGradient,xoffset-140,340,320,100);
		LowerGradient.v[0].col=LowerGradient.v[1].col=SETA(DBGColor,0x00);
		LowerGradient.v[2].col=LowerGradient.v[3].col=SETA(DBGColor,0xFF);
	}
	void Leave(){onOut=true;}
	int Update()
	{
		//The background color is likely on a change here...
		UpperGradient.v[0].col=UpperGradient.v[1].col=SETA(DBGColor,0xFF);
		UpperGradient.v[2].col=UpperGradient.v[3].col=SETA(DBGColor,0x00);
		LowerGradient.v[0].col=LowerGradient.v[1].col=SETA(DBGColor,0x00);
		LowerGradient.v[2].col=LowerGradient.v[3].col=SETA(DBGColor,0xFF);
		if(onIn)
		{
			if(fabs(xoffset-350)<hge->Timer_GetDelta()*1600)return xoffset=350,onIn=false,-1;
			if(xoffset<350)
			xoffset+=hge->Timer_GetDelta()*1600;
			else
			xoffset-=hge->Timer_GetDelta()*1600;
		}
		if(onOut)
		{
			xoffset+=hge->Timer_GetDelta()*1600;
			if(xoffset>=850)active=onOut=false;
		}
		ConfigureQuad(&UpperGradient,xoffset-140,190,320,100);
		ConfigureQuad(&LowerGradient,xoffset-140,340,320,110);
		if(hge->Input_GetKeyStateEx(HGEK_UP)==HGEKST_HIT&&selected>1)--selected,TriggerSound(0);
		if(hge->Input_GetKeyStateEx(HGEK_DOWN)==HGEKST_HIT&&selected<3-1)++selected,TriggerSound(0);
		yoffset=-selected*30;
		if(fabs(dyoffset-yoffset)<7)dyoffset=yoffset;
		if(dyoffset<yoffset)dyoffset+=hge->Timer_GetDelta()*400;
		if(dyoffset>yoffset)dyoffset-=hge->Timer_GetDelta()*400;
		if(onIn||onOut)return -1;
		if(hge->Input_GetKeyStateEx(HGEK_Z)==HGEKST_HIT||hge->Input_GetKeyStateEx(HGEK_ENTER)==HGEKST_HIT)
			return TriggerSound(1),selected;
		return -1;
	}
	void Render()
	{
		for(int i=0;i<3;++i)
		{
			double calcy=i*30+dyoffset+300;
			if(calcy>189.9&&calcy<440.1)
			MenuFont->printf(xoffset,calcy,HGETEXT_LEFT,RTTMStr[i]);
		}
		Ribb->RenderEx(xoffset-50,295,0,6.5,1);
		Ribb->RenderEx(xoffset-50,322,0,6.5,1);
		hge->Gfx_RenderQuad(&UpperGradient);
		hge->Gfx_RenderQuad(&LowerGradient);
	}
}returnToTitleMenu;
class DeathMenu
{
private:
	bool active,onIn,onOut;
	int selected;
	double xoffset,yoffset,dyoffset;
	hgeSprite *Ribb,*DeathTitle;
	hgeQuad UpperGradient,LowerGradient;
public:
	bool isActive(){return active;}
	void Init_Once()
	{
		Ribb=new hgeSprite(MenuTex,256,350,64,16);
		DeathTitle=new hgeSprite(MenuTex,256,256,256,64);
		Ribb->SetColor(0xCCFFFFFF);
	}
	void Init(double start)
	{
		//Magical things, again...
		Current_Position=5;Music_Stop();
		DisableAllTower=true;DisablePlayer=true;
		xoffset=start;onIn=true;active=true;
		selected=1;dyoffset=yoffset=-selected*30;
		ConfigureQuad(&UpperGradient,xoffset-140,290,600,50);
		UpperGradient.v[0].col=UpperGradient.v[1].col=SETA(DBGColor,0xFF);
		UpperGradient.v[2].col=UpperGradient.v[3].col=SETA(DBGColor,0x00);
		ConfigureQuad(&LowerGradient,xoffset-140,440,600,100);
		LowerGradient.v[0].col=LowerGradient.v[1].col=SETA(DBGColor,0x00);
		LowerGradient.v[2].col=LowerGradient.v[3].col=SETA(DBGColor,0xFF);
	}
	void Leave(){onOut=true;}
	int Update()
	{
		//The background color is likely on a change here...
		UpperGradient.v[0].col=UpperGradient.v[1].col=SETA(DBGColor,0xFF);
		UpperGradient.v[2].col=UpperGradient.v[3].col=SETA(DBGColor,0x00);
		LowerGradient.v[0].col=LowerGradient.v[1].col=SETA(DBGColor,0x00);
		LowerGradient.v[2].col=LowerGradient.v[3].col=SETA(DBGColor,0xFF);
		if(onIn)
		{
			if(fabs(xoffset-300)<hge->Timer_GetDelta()*1600)return xoffset=300,onIn=false,-1;
			if(xoffset<300)
			xoffset+=hge->Timer_GetDelta()*1600;
			else
			xoffset-=hge->Timer_GetDelta()*1600;
		}
		if(onOut)
		{
			xoffset+=hge->Timer_GetDelta()*1600;
			if(xoffset>=850)active=onOut=false;
		}
		ConfigureQuad(&UpperGradient,xoffset-140,290,600,100);
		ConfigureQuad(&LowerGradient,xoffset-140,440,600,110);
		if(hge->Input_GetKeyStateEx(HGEK_UP)==HGEKST_HIT&&selected>1)--selected,TriggerSound(0);
		if(hge->Input_GetKeyStateEx(HGEK_DOWN)==HGEKST_HIT&&selected<3-1)++selected,TriggerSound(0);
		yoffset=-selected*30;
		if(fabs(dyoffset-yoffset)<7)dyoffset=yoffset;
		if(dyoffset<yoffset)dyoffset+=hge->Timer_GetDelta()*400;
		if(dyoffset>yoffset)dyoffset-=hge->Timer_GetDelta()*400;
		if(onIn||onOut)return -1;
		if(hge->Input_GetKeyStateEx(HGEK_Z)==HGEKST_HIT||hge->Input_GetKeyStateEx(HGEK_ENTER)==HGEKST_HIT)
			return TriggerSound(1),selected;
		return -1;
	}
	void Render()
	{
		for(int i=0;i<3;++i)
		{
			double calcy=i*30+dyoffset+400;
			if(calcy>289.9&&calcy<540.1)
			MenuFont->printf(xoffset,calcy,HGETEXT_LEFT,DMStr[i]);
		}
		Ribb->RenderEx(xoffset-50,395,0,3.75,1);
		Ribb->RenderEx(xoffset-50,422,0,3.75,1);
		hge->Gfx_RenderQuad(&UpperGradient);
		hge->Gfx_RenderQuad(&LowerGradient);
		MenuFont->printf(xoffset-100,250,HGETEXT_LEFT,"You scored %lld at level %d",score,level);
		MenuFont->printf(xoffset-100,280,HGETEXT_LEFT,"Average FPS: %lf\n",averfps);
		DeathTitle->Render(xoffset-200,200);
	}
}deathMenu;
class CompleteMenu
{
private:
	bool active,onIn,onOut;
	int selected;
	double xoffset,yoffset,dyoffset;
	hgeSprite *Ribb,*CompleteTitle;
	hgeQuad UpperGradient,LowerGradient;
public:
	bool isActive(){return active;}
	void Init_Once()
	{
		Ribb=new hgeSprite(MenuTex,256,350,64,16);
		CompleteTitle=new hgeSprite(MenuTex,0,320,256,64);
		Ribb->SetColor(0xCCFFFFFF);
	}
	void Init(double start)
	{
		//Magical things, again...
		Current_Position=6;Music_Stop();
		DisableAllTower=true;DisablePlayer=true;
		xoffset=start;onIn=true;active=true;
		selected=1;dyoffset=yoffset=-selected*30;
		ConfigureQuad(&UpperGradient,xoffset-140,390,600,50);
		UpperGradient.v[0].col=UpperGradient.v[1].col=SETA(DBGColor,0xFF);
		UpperGradient.v[2].col=UpperGradient.v[3].col=SETA(DBGColor,0x00);
		ConfigureQuad(&LowerGradient,xoffset-140,540,600,100);
		LowerGradient.v[0].col=LowerGradient.v[1].col=SETA(DBGColor,0x00);
		LowerGradient.v[2].col=LowerGradient.v[3].col=SETA(DBGColor,0xFF);
	}
	void Leave(){onOut=true;}
	int Update()
	{
		//The background color is likely on a change here...
		UpperGradient.v[0].col=UpperGradient.v[1].col=SETA(DBGColor,0xFF);
		UpperGradient.v[2].col=UpperGradient.v[3].col=SETA(DBGColor,0x00);
		LowerGradient.v[0].col=LowerGradient.v[1].col=SETA(DBGColor,0x00);
		LowerGradient.v[2].col=LowerGradient.v[3].col=SETA(DBGColor,0xFF);
		if(onIn)
		{
			if(fabs(xoffset-300)<hge->Timer_GetDelta()*1600)return xoffset=300,onIn=false,-1;
			if(xoffset<300)
			xoffset+=hge->Timer_GetDelta()*1600;
			else
			xoffset-=hge->Timer_GetDelta()*1600;
		}
		if(onOut)
		{
			xoffset+=hge->Timer_GetDelta()*1600;
			if(xoffset>=850)active=onOut=false;
		}
		ConfigureQuad(&UpperGradient,xoffset-140,390,600,100);
		ConfigureQuad(&LowerGradient,xoffset-140,540,600,110);
		if(hge->Input_GetKeyStateEx(HGEK_UP)==HGEKST_HIT&&selected>1)--selected,TriggerSound(0);
		if(hge->Input_GetKeyStateEx(HGEK_DOWN)==HGEKST_HIT&&selected<3-1)++selected,TriggerSound(0);
		yoffset=-selected*30;
		if(fabs(dyoffset-yoffset)<7)dyoffset=yoffset;
		if(dyoffset<yoffset)dyoffset+=hge->Timer_GetDelta()*400;
		if(dyoffset>yoffset)dyoffset-=hge->Timer_GetDelta()*400;
		if(onIn||onOut)return -1;
		if(hge->Input_GetKeyStateEx(HGEK_Z)==HGEKST_HIT||hge->Input_GetKeyStateEx(HGEK_ENTER)==HGEKST_HIT)
			return TriggerSound(1),selected;
		return -1;
	}
	void Render()
	{
		for(int i=0;i<3;++i)
		{
			double calcy=i*30+dyoffset+500;
			if(calcy>389.9&&calcy<640.1)
			MenuFont->printf(xoffset-100,calcy,HGETEXT_LEFT,CMStr[i]);
		}
		Ribb->RenderEx(xoffset-150,495,0,3.75,1);
		Ribb->RenderEx(xoffset-150,522,0,3.75,1);
		hge->Gfx_RenderQuad(&UpperGradient);
		hge->Gfx_RenderQuad(&LowerGradient);
		if(~CheckHighScore())
		MenuFont->printf(xoffset-100,250,HGETEXT_LEFT,"New Highscore %lld!",score);
		else
		MenuFont->printf(xoffset-100,250,HGETEXT_LEFT,"Score %lld",score);
		MenuFont->printf(xoffset-100,280,HGETEXT_LEFT,"Your Ranking: %s",getRank());
		if(mode==2)
		{
			MenuFont->printf(xoffset-100,310,HGETEXT_LEFT,"Semi-collisions %d",semicoll);
			MenuFont->printf(xoffset-100,340,HGETEXT_LEFT,"Average FPS: %.02f",averfps);
		}
		else
		{
			if(mode==1)
				MenuFont->printf(xoffset-100,310,HGETEXT_LEFT,"Restarts %d",restarts);
			else
				MenuFont->printf(xoffset-100,310,HGETEXT_LEFT,"Restarts %d",coll);
			MenuFont->printf(xoffset-100,340,HGETEXT_LEFT,"Semi-collisions %d",semicoll);
			MenuFont->printf(xoffset-100,370,HGETEXT_LEFT,"CLR Usage %d",clrusg);
			MenuFont->printf(xoffset-100,400,HGETEXT_LEFT,"Average FPS: %.02f",averfps);
		}
		CompleteTitle->Render(xoffset-200,200);
	}
}completeMenu;
class NewHighScoreGUI
{
private:
	bool active,onIn,onOut,toogleundl;
	double xoffset;
	void nameins(char a)
	{
		if (newlen<=14)
			newname[newlen++]=a;
	}
	void namedel()
	{
		if (newlen>0)newname[--newlen]=0;
	}
public:
	bool isActive(){return active;}
	void Init()
	{
		Current_Position=7;active=true;
		memset(newname,0,sizeof(newname));newlen=0;tbframebrk=0;toogleundl=false;
		TipFont->SetColor(0xFFFFFFFF);xoffset=-500;onIn=true;onOut=false;
	}
	void Leave(){onOut=true;}
	void Update()
	{
		if(onIn)
		{
			xoffset+=hge->Timer_GetDelta()*1600;
			if(xoffset>0)xoffset=0,onIn=false;
		}
		if(onOut)
		{
			xoffset+=hge->Timer_GetDelta()*1600;
			if(xoffset>650)onOut=active=false;
		}
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
			TriggerSound(1);
			InsertHighScore();Leave();
			Current_Position=0;mainMenu.Init(-200);
			/*switch (mode)
			{
				case 4:view=1;HSViewGUI_Init();break;
				case 1:view=2;HSViewGUI_Init();break;
				case 2:view=3;HSViewGUI_Init();break;
				case 3:view=4;HSViewGUI_Init();break;
			}*/
		}
	}
	void Render()
	{
		if (LOWFPS)tbframebrk+=17;else ++tbframebrk;
		if (tbframebrk>=500)toogleundl=!toogleundl,tbframebrk=0;
		TipFont->printf(200+xoffset,200,HGETEXT_LEFT,"Please Enter Your Honorable Name...");
		if (!toogleundl)
			TipFont->printf(200+xoffset,240,HGETEXT_LEFT,"%s",newname);
		else
			TipFont->printf(200+xoffset,240,HGETEXT_LEFT,"%s_",newname);
	}
}newHighScoreGUI;
class HighScoreMenu
{
private:
	bool active,onIn,onOut;
	int selected;
	double xoffset,yoffset,dyoffset;
	hgeSprite *Ribb,*HSTitle;
	hgeQuad UpperGradient,LowerGradient;
public:
	bool isActive(){return active;}
	void Init_Once()
	{
		Ribb=new hgeSprite(MenuTex,256,350,64,16);
		HSTitle=new hgeSprite(MenuTex,0,376,256,64);
		Ribb->SetColor(0xCCFFFFFF);
	}
	void Init(double start)
	{
		xoffset=start;onIn=true;active=true;
		selected=0;dyoffset=yoffset=-selected*30;
		ConfigureQuad(&UpperGradient,xoffset-140,290,600,50);
		UpperGradient.v[0].col=UpperGradient.v[1].col=SETA(DBGColor,0xFF);
		UpperGradient.v[2].col=UpperGradient.v[3].col=SETA(DBGColor,0x00);
		ConfigureQuad(&LowerGradient,xoffset-140,440,600,100);
		LowerGradient.v[0].col=LowerGradient.v[1].col=SETA(DBGColor,0x00);
		LowerGradient.v[2].col=LowerGradient.v[3].col=SETA(DBGColor,0xFF);
	}
	void Leave(){onOut=true;}
	int Update()
	{
		if(onIn)
		{
			if(fabs(xoffset-500)<hge->Timer_GetDelta()*1600)return xoffset=500,onIn=false,-1;
			if(xoffset<500)
			xoffset+=hge->Timer_GetDelta()*1600;
			else
			xoffset-=hge->Timer_GetDelta()*1600;
		}
		if(onOut)
		{
			xoffset+=hge->Timer_GetDelta()*1600;
			if(xoffset>=850)active=onOut=false;
		}
		ConfigureQuad(&UpperGradient,xoffset-140,290,600,100);
		ConfigureQuad(&LowerGradient,xoffset-140,440,600,110);
		if(hge->Input_GetKeyStateEx(HGEK_UP)==HGEKST_HIT&&selected>0)--selected,TriggerSound(0);
		if(hge->Input_GetKeyStateEx(HGEK_DOWN)==HGEKST_HIT&&selected<4-1)++selected,TriggerSound(0);
		if(hge->Input_GetKeyStateEx(HGEK_ESCAPE)==HGEKST_HIT)selected=4-1,TriggerSound(0);
		yoffset=-selected*30;
		if(fabs(dyoffset-yoffset)<7)dyoffset=yoffset;
		if(dyoffset<yoffset)dyoffset+=hge->Timer_GetDelta()*400;
		if(dyoffset>yoffset)dyoffset-=hge->Timer_GetDelta()*400;
		if(onIn||onOut)return -1;
		if(hge->Input_GetKeyStateEx(HGEK_Z)==HGEKST_HIT||hge->Input_GetKeyStateEx(HGEK_ENTER)==HGEKST_HIT)
			return TriggerSound(selected==4-1?2:1),selected;
		return -1;
	}
	void Render()
	{
		for(int i=0;i<4;++i)
		{
			double calcy=i*30+dyoffset+400;
			if(calcy>289.9&&calcy<540.1)
			MenuFont->printf(xoffset,calcy,HGETEXT_LEFT,HSMStr[i]);
		}
		Ribb->RenderEx(xoffset-50,395,0,4.5,1);
		Ribb->RenderEx(xoffset-50,422,0,4.5,1);
		hge->Gfx_RenderQuad(&UpperGradient);
		hge->Gfx_RenderQuad(&LowerGradient);
		HSTitle->Render(xoffset-250,300);
	}
}highScoreMenu;
class HighScoreViewMenu
{
private:
	bool active,onIn,onOut;
	int selected,view;
	double xoffset,yoffset,dyoffset;
	hgeSprite *Ribb;
	hgeQuad UpperGradient,LowerGradient;
public:
	int View(){return view;}
	int GetViewCount(){return view==0?Ncnt:view==1?Excnt:view==2?FPMcnt:0;}
	bool isActive(){return active;}
	void Init_Once()
	{
		Ribb=new hgeSprite(MenuTex,256,350,64,16);
		Ribb->SetColor(0xCCFFFFFF);
	}
	void Init(double start,int _v)
	{
		xoffset=start;onIn=true;active=true;
		selected=1;dyoffset=yoffset=-selected*30;view=_v;
		ConfigureQuad(&UpperGradient,xoffset-140,290,600,50);
		UpperGradient.v[0].col=UpperGradient.v[1].col=SETA(DBGColor,0xFF);
		UpperGradient.v[2].col=UpperGradient.v[3].col=SETA(DBGColor,0x00);
		ConfigureQuad(&LowerGradient,xoffset-140,440,600,120);
		LowerGradient.v[0].col=LowerGradient.v[1].col=SETA(DBGColor,0x00);
		LowerGradient.v[2].col=LowerGradient.v[3].col=SETA(DBGColor,0xFF);
	}
	void Leave(){onOut=true;}
	int Update()
	{
		if(onIn)
		{
			if(fabs(xoffset-400)<hge->Timer_GetDelta()*1600)return xoffset=400,onIn=false,-1;
			if(xoffset<400)
			xoffset+=hge->Timer_GetDelta()*1600;
			else
			xoffset-=hge->Timer_GetDelta()*1600;
		}
		if(onOut)
		{
			xoffset+=hge->Timer_GetDelta()*1600;
			if(xoffset>=850)active=onOut=false;
		}
		ConfigureQuad(&UpperGradient,xoffset-140,290,600,100);
		ConfigureQuad(&LowerGradient,xoffset-140,440,600,120);
		if(hge->Input_GetKeyStateEx(HGEK_UP)==HGEKST_HIT&&selected>1)--selected,TriggerSound(0);
		if(hge->Input_GetKeyStateEx(HGEK_DOWN)==HGEKST_HIT&&selected<7-1)++selected,TriggerSound(0);
		if(hge->Input_GetKeyStateEx(HGEK_ESCAPE)==HGEKST_HIT)selected=7-1,TriggerSound(0);
		yoffset=-selected*30;
		if(fabs(dyoffset-yoffset)<7)dyoffset=yoffset;
		if(dyoffset<yoffset)dyoffset+=hge->Timer_GetDelta()*400;
		if(dyoffset>yoffset)dyoffset-=hge->Timer_GetDelta()*400;
		if(onIn||onOut)return -1;
		if(hge->Input_GetKeyStateEx(HGEK_Z)==HGEKST_HIT||hge->Input_GetKeyStateEx(HGEK_ENTER)==HGEKST_HIT)
			return TriggerSound(selected==7-1?2:1),selected;
		return -1;
	}
	void Render()
	{
		if(dyoffset+400>289.9)
		MenuFont->printf(xoffset,dyoffset+400,HGETEXT_LEFT,"Highscore - %s",HSMStr[view]);
#define WrapCnt \
		(view==0?Ncnt:view==1?Excnt:view==2?FPMcnt:0)
#define WrapRec\
		(view==0?NRec:view==1?ExRec:view==2?FPMRec:FPMRec)
		for(unsigned i=1;i<=5;++i)
		{
			double calcy=i*30+dyoffset+400;
			if(calcy>289.9&&calcy<540.1)
			{
				if(i<=WrapCnt)
				MenuFont->printf(xoffset,calcy,HGETEXT_LEFT,"%u. %s - %lld",i,WrapRec[i].name,WrapRec[i].score);
				else MenuFont->printf(xoffset,calcy,HGETEXT_LEFT,"%u. ----------",i);
			}
		}
		double calcy=6*30+dyoffset+400;
		if(calcy>289.9&&calcy<540.1)
			MenuFont->printf(xoffset,calcy,HGETEXT_LEFT,"back");
		Ribb->RenderEx(xoffset-50,395,0,7,1);
		Ribb->RenderEx(xoffset-50,422,0,7,1);
		hge->Gfx_RenderQuad(&UpperGradient);
		hge->Gfx_RenderQuad(&LowerGradient);
	}
}highScoreViewMenu;
class HighScoreDetailsMenu
{
private:
	bool active,onIn,onOut;
	int selected,view,no;
	double xoffset,yoffset,dyoffset;
	hgeSprite *Ribb,*HSTitle;
	hgeQuad UpperGradient,LowerGradient;
public:
	int View(){return view;}
	bool isActive(){return active;}
	void Init_Once()
	{
		Ribb=new hgeSprite(MenuTex,256,350,64,16);
		HSTitle=new hgeSprite(MenuTex,0,448,256,64);
		Ribb->SetColor(0xCCFFFFFF);
	}
	void Init(double start,int _v,int _n)
	{
		xoffset=start;onIn=true;active=true;no=_n;
		selected=0;dyoffset=yoffset=-selected*30;view=_v;
		ConfigureQuad(&UpperGradient,xoffset-140,290,600,50);
		UpperGradient.v[0].col=UpperGradient.v[1].col=SETA(DBGColor,0xFF);
		UpperGradient.v[2].col=UpperGradient.v[3].col=SETA(DBGColor,0x00);
		ConfigureQuad(&LowerGradient,xoffset-140,440,600,130);
		LowerGradient.v[0].col=LowerGradient.v[1].col=SETA(DBGColor,0x00);
		LowerGradient.v[2].col=LowerGradient.v[3].col=SETA(DBGColor,0xFF);
	}
	void Leave(){onOut=true;}
	int Update()
	{
		if(onIn)
		{
			if(fabs(xoffset-400)<hge->Timer_GetDelta()*1600)return xoffset=400,onIn=false,-1;
			if(xoffset<400)
			xoffset+=hge->Timer_GetDelta()*1600;
			else
			xoffset-=hge->Timer_GetDelta()*1600;
		}
		if(onOut)
		{
			xoffset+=hge->Timer_GetDelta()*1600;
			if(xoffset>=850)active=onOut=false;
		}
		ConfigureQuad(&UpperGradient,xoffset-140,290,600,100);
		ConfigureQuad(&LowerGradient,xoffset-140,440,600,130);
		if(hge->Input_GetKeyStateEx(HGEK_UP)==HGEKST_HIT&&selected>0)--selected,TriggerSound(0);
		if(hge->Input_GetKeyStateEx(HGEK_DOWN)==HGEKST_HIT&&selected<(view==1?5:7)-1)++selected,TriggerSound(0);
		if(hge->Input_GetKeyStateEx(HGEK_ESCAPE)==HGEKST_HIT)TriggerSound(0),selected=(view==1?5:7)-1;
		yoffset=-selected*30;
		if(fabs(dyoffset-yoffset)<7)dyoffset=yoffset;
		if(dyoffset<yoffset)dyoffset+=hge->Timer_GetDelta()*400;
		if(dyoffset>yoffset)dyoffset-=hge->Timer_GetDelta()*400;
		if(onIn||onOut)return -1;
		if(hge->Input_GetKeyStateEx(HGEK_Z)==HGEKST_HIT||hge->Input_GetKeyStateEx(HGEK_ENTER)==HGEKST_HIT)
			return TriggerSound(selected==(view==1?5:7)-1?2:1),selected;
		return -1;
	}
	void Render()
	{
#define WrapCnt \
		(view==0?Ncnt:view==1?Excnt:view==2?FPMcnt:0)
#define WrapRec\
		(view==0?NRec:view==1?ExRec:view==2?FPMRec:FPMRec)
		if(dyoffset+400>289.9)
		MenuFont->printf(xoffset,dyoffset+400,HGETEXT_LEFT,"No. %d of %s",no,HSMStr[view]);
		if(view==1)
		{
			if(dyoffset+430>289.9&&dyoffset+430<540.1)
				MenuFont->printf(xoffset,dyoffset+430,HGETEXT_LEFT,"Scored %lld by %s",WrapRec[no].score,WrapRec[no].name);
			if(dyoffset+460>289.9&&dyoffset+460<540.1)
				MenuFont->printf(xoffset,dyoffset+460,HGETEXT_LEFT,"Semi-Collisions %d",WrapRec[no].scoll);
			if(dyoffset+490>289.9&&dyoffset+490<540.1)
				MenuFont->printf(xoffset,dyoffset+490,HGETEXT_LEFT,"Average FPS %d.%d",WrapRec[no].af_int,WrapRec[no].af_fric);
		}
		else
		{
			if(dyoffset+430>289.9&&dyoffset+430<540.1)
				MenuFont->printf(xoffset,dyoffset+430,HGETEXT_LEFT,"Scored %lld by %s",WrapRec[no].score,WrapRec[no].name);
			if(dyoffset+460>289.9&&dyoffset+460<540.1)
			{
				if(view==0)
				MenuFont->printf(xoffset,dyoffset+460,HGETEXT_LEFT,"Restarts %d",WrapRec[no].rescol);
				else
				MenuFont->printf(xoffset,dyoffset+460,HGETEXT_LEFT,"Collisions %d",WrapRec[no].rescol);
			}
			if(dyoffset+490>289.9&&dyoffset+490<540.1)
				MenuFont->printf(xoffset,dyoffset+490,HGETEXT_LEFT,"Semi-Collisions %d",WrapRec[no].scoll);
			if(dyoffset+520>289.9&&dyoffset+520<540.1)
				MenuFont->printf(xoffset,dyoffset+520,HGETEXT_LEFT,"CLR Usage %d",WrapRec[no].clrusg);
			if(dyoffset+550>289.9&&dyoffset+550<540.1)
				MenuFont->printf(xoffset,dyoffset+550,HGETEXT_LEFT,"Average FPS %d.%d",WrapRec[no].af_int,WrapRec[no].af_fric);
		}
		double calcy=(view==1?4:6)*30+dyoffset+400;
		if(calcy>289.9&&calcy<540.1)
			MenuFont->printf(xoffset,calcy,HGETEXT_LEFT,"back");
		Ribb->RenderEx(xoffset-50,395,0,6,1);
		Ribb->RenderEx(xoffset-50,422,0,6,1);
		hge->Gfx_RenderQuad(&UpperGradient);
		hge->Gfx_RenderQuad(&LowerGradient);
		HSTitle->Render(xoffset-250,300);
	}
}highScoreDetailsMenu;
