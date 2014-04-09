//Chrisoft Bullet Lab Remix HGE
//Menu Implementations
//Copyright Chrisoft 2014
//Now this is being rewritten...
//                                --Announcement from Chirsno
//static const char* MENUS_H_FN="menus.h";
//Here's where new code grows...
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
	freopen("blr.cfg","w",stdout);
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
		ConfigureQuad(&UpperGradient,xoffset-140,100,320,50);
		UpperGradient.v[0].col=UpperGradient.v[1].col=SETA(DBGColor,0xFF);
		UpperGradient.v[2].col=UpperGradient.v[3].col=SETA(DBGColor,0x00);
		ConfigureQuad(&LowerGradient,xoffset-140,300,320,100);
		LowerGradient.v[0].col=LowerGradient.v[1].col=SETA(DBGColor,0x00);
		LowerGradient.v[2].col=LowerGradient.v[3].col=SETA(DBGColor,0xFF);
	}
	void Leave(){onOut=true;}
	int Update()
	{
		if(DBGColor!=0xFF0A0A0A)
		{
			for(int i=0;i<4;++i)DBGColor=ColorTransfer(DBGColor,0xFF0A0A0A);
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
		ConfigureQuad(&LowerGradient,xoffset-140,400,320,110);
		if(hge->Input_GetKeyStateEx(HGEK_UP)==HGEKST_HIT&&selected>0)--selected;
		if(hge->Input_GetKeyStateEx(HGEK_DOWN)==HGEKST_HIT&&selected<5-1)++selected;
		if(hge->Input_GetKeyStateEx(HGEK_ESCAPE)==HGEKST_HIT)selected=4;
		yoffset=-selected*30;
		if(fabs(dyoffset-yoffset)<7)dyoffset=yoffset;
		if(dyoffset<yoffset)dyoffset+=hge->Timer_GetDelta()*400;
		if(dyoffset>yoffset)dyoffset-=hge->Timer_GetDelta()*400;
		if(hge->Input_GetKeyStateEx(HGEK_Z)==HGEKST_HIT||hge->Input_GetKeyStateEx(HGEK_ENTER)==HGEKST_HIT)
			return selected;
		return -1;
	}
	void Render()
	{
		for(int i=0;i<5;++i)
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
		if(hge->Input_GetKeyStateEx(HGEK_LEFT)==HGEKST_HIT&&selected>0)--selected;
		if(hge->Input_GetKeyStateEx(HGEK_RIGHT)==HGEKST_HIT&&selected<3-1)++selected;
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
		if(hge->Input_GetKeyStateEx(HGEK_Z)==HGEKST_HIT||hge->Input_GetKeyStateEx(HGEK_ENTER)==HGEKST_HIT)
			return selected;
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
			if(hge->Input_GetKeyStateEx(HGEK_UP)==HGEKST_HIT&&selected>0)--selected;
			if(hge->Input_GetKeyStateEx(HGEK_DOWN)==HGEKST_HIT&&selected<6-1)++selected;
			if(hge->Input_GetKeyStateEx(HGEK_ESCAPE)==HGEKST_HIT)selected=5;
		}
		yoffset=-selected*30;
		if(fabs(dyoffset-yoffset)<7)dyoffset=yoffset;
		if(dyoffset<yoffset)dyoffset+=hge->Timer_GetDelta()*400;
		if(dyoffset>yoffset)dyoffset-=hge->Timer_GetDelta()*400;
		if(hge->Input_GetKeyStateEx(HGEK_RIGHT)==HGEKST_HIT&&hge->Input_GetKeyStateEx(HGEK_LEFT)==HGEKST_HIT)return -1;
		if(hge->Input_GetKeyStateEx(HGEK_RIGHT)==HGEKST_HIT||hge->Input_GetKeyStateEx(HGEK_Z)==HGEKST_HIT||hge->Input_GetKeyStateEx(HGEK_ENTER)==HGEKST_HIT)
		{
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
			--selected==4?--selected:0;
			if(hge->Input_GetKeyStateEx(HGEK_DOWN)==HGEKST_HIT&&selected<6-1)
			++selected==4?++selected:0;
			if(hge->Input_GetKeyStateEx(HGEK_ESCAPE)==HGEKST_HIT)selected=5;
		}
		yoffset=-selected*30;
		if(fabs(dyoffset-yoffset)<7)dyoffset=yoffset;
		if(dyoffset<yoffset)dyoffset+=hge->Timer_GetDelta()*400;
		if(dyoffset>yoffset)dyoffset-=hge->Timer_GetDelta()*400;
		if(hge->Input_GetKeyStateEx(HGEK_RIGHT)==HGEKST_HIT&&hge->Input_GetKeyStateEx(HGEK_LEFT)==HGEKST_HIT)return -1;
		if(hge->Input_GetKeyStateEx(HGEK_RIGHT)==HGEKST_HIT)
		{
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
			if(onSwitch||onSwitchi)return -1;
			if(selected<=3){onSwitchi=true;swoffset=0;}
			if(selected==0)--plrspd<1?plrspd=5:0;
			if(selected==1)--plrslospd<1?plrslospd=5:0;
			if(selected==2)--clrbns<0?clrbns=4:0;
			if(selected==3)clrmode=!clrmode;
			if(selected<=3)return selected;
		}
		if(hge->Input_GetKeyStateEx(HGEK_Z)==HGEKST_HIT||hge->Input_GetKeyStateEx(HGEK_ENTER)==HGEKST_HIT)
			return selected;
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
	void Leave(){onOut=true;}
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
			}
		}
		ConfigureQuad(&UpperGradient,xoffset-140,190,320,100);
		ConfigureQuad(&LowerGradient,xoffset-140,340,320,110);
		if(hge->Input_GetKeyStateEx(HGEK_UP)==HGEKST_HIT&&selected>1)--selected;
		if(hge->Input_GetKeyStateEx(HGEK_DOWN)==HGEKST_HIT&&selected<3-1)++selected;
		yoffset=-selected*30;
		if(fabs(dyoffset-yoffset)<7)dyoffset=yoffset;
		if(dyoffset<yoffset)dyoffset+=hge->Timer_GetDelta()*400;
		if(dyoffset>yoffset)dyoffset-=hge->Timer_GetDelta()*400;
		if(hge->Input_GetKeyStateEx(HGEK_Z)==HGEKST_HIT||hge->Input_GetKeyStateEx(HGEK_ENTER)==HGEKST_HIT)
			return selected;
		if(hge->Input_GetKeyStateEx(HGEK_ESCAPE)==HGEKST_HIT&&!onIn)return 1;
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
		if(hge->Input_GetKeyStateEx(HGEK_UP)==HGEKST_HIT&&selected>1)--selected;
		if(hge->Input_GetKeyStateEx(HGEK_DOWN)==HGEKST_HIT&&selected<3-1)++selected;
		yoffset=-selected*30;
		if(fabs(dyoffset-yoffset)<7)dyoffset=yoffset;
		if(dyoffset<yoffset)dyoffset+=hge->Timer_GetDelta()*400;
		if(dyoffset>yoffset)dyoffset-=hge->Timer_GetDelta()*400;
		if(hge->Input_GetKeyStateEx(HGEK_Z)==HGEKST_HIT||hge->Input_GetKeyStateEx(HGEK_ENTER)==HGEKST_HIT)
			return selected;
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
		if(hge->Input_GetKeyStateEx(HGEK_UP)==HGEKST_HIT&&selected>1)--selected;
		if(hge->Input_GetKeyStateEx(HGEK_DOWN)==HGEKST_HIT&&selected<3-1)++selected;
		yoffset=-selected*30;
		if(fabs(dyoffset-yoffset)<7)dyoffset=yoffset;
		if(dyoffset<yoffset)dyoffset+=hge->Timer_GetDelta()*400;
		if(dyoffset>yoffset)dyoffset-=hge->Timer_GetDelta()*400;
		if(hge->Input_GetKeyStateEx(HGEK_Z)==HGEKST_HIT||hge->Input_GetKeyStateEx(HGEK_ENTER)==HGEKST_HIT)
			return selected;
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
		MenuFont->printf(xoffset-100,250,HGETEXT_LEFT,
#ifdef WIN32
	"You scored %I64d at level %d"
#else
	"You scored %lld at level %d"
#endif
	,score,level);
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
		if(hge->Input_GetKeyStateEx(HGEK_UP)==HGEKST_HIT&&selected>1)--selected;
		if(hge->Input_GetKeyStateEx(HGEK_DOWN)==HGEKST_HIT&&selected<3-1)++selected;
		yoffset=-selected*30;
		if(fabs(dyoffset-yoffset)<7)dyoffset=yoffset;
		if(dyoffset<yoffset)dyoffset+=hge->Timer_GetDelta()*400;
		if(dyoffset>yoffset)dyoffset-=hge->Timer_GetDelta()*400;
		if(hge->Input_GetKeyStateEx(HGEK_Z)==HGEKST_HIT||hge->Input_GetKeyStateEx(HGEK_ENTER)==HGEKST_HIT)
			return selected;
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
		MenuFont->printf(xoffset-100,250,HGETEXT_LEFT,
#ifdef WIN32
	"New Highscore %I64d!"
#else
	"New Highscore %lld!"
#endif
	,score);
		else
		MenuFont->printf(xoffset-100,250,HGETEXT_LEFT,
#ifdef WIN32
	"Score %I64d"
#else
	"Score %lld"
#endif
	,score);
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
//==================================================================================
//Here's where old code dies...
hgeGUI			*HighScoreGUI;
hgeGUI			*HSViewGUI,*HSDetailGUI;
char			HSVstr[7][255];
char			HSDetstr[10][255];
int				view,detv;
void HSViewGUI_Init();
void HighScoreGUI_Init();
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
				sprintf(HSDetstr[2],"Scored %I64d by %s",ExRec[detv].score,ExRec[detv].name);
#else
				sprintf(HSDetstr[2],"Scored %lld by %s",ExRec[detv].score,ExRec[detv].name);
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
				sprintf(HSDetstr[2],"Scored %I64d by %s",FPMRec[detv].score,FPMRec[detv].name);
#else
				sprintf(HSDetstr[2],"Scored %lld by %s",FPMRec[detv].score,FPMRec[detv].name);
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
	HighScoreGUI->AddCtrl(new hgeGUIMenuItem(2,fnt,snd,400,240,0.1f,"Classic"));
	HighScoreGUI->AddCtrl(new hgeGUIMenuItem(3,fnt,snd,400,280,0.2f,"Normal"));
	HighScoreGUI->AddCtrl(new hgeGUIMenuItem(4,fnt,snd,400,320,0.3f,"Assessment Mode"));
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
			case 6:Current_Position=0;HighScoreGUI->Leave();break;
		}
	}

}
