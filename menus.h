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
//==================================================================================
//Here's where old code dies...
hgeGUI			*StartGUI,*DeathGUI,*CompleteGUI,*HighScoreGUI;
hgeGUI			*HSViewGUI,*HSDetailGUI,*PauseGUI,*BkTTitleGUI;
hgeGUI			*OptionsGUI,*PlayerProfGUI;
char			ds1[255],ds2[255],ds3[255],ds4[255];
char			hs1[255],hs2[255],hs3[255],hs4[255],hs5[255],hs6[255],hs7[255];
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
	StartGUI->AddCtrl(new hgeGUIMenuItem(2,fnt,snd,400,240,0.1f,""));
	StartGUI->AddCtrl(new hgeGUIMenuItem(3,fnt,snd,400,280,0.2f,"Assessment Mode"));
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
			case 2:
			case 3:
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
			case 4:
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
		case 1:sprintf(ds2,"Mode: Classic");break;
		case 3:sprintf(ds2,"What Happened?! You died in Free Play Mode?!");break;
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
char *getRank()
{
	static char retval[256];
	//stub!
	//sprintf something to retval
	if(level<=3)sprintf(retval,"Try more...");
	if(level<=6)sprintf(retval,"Still need more effort!");
	if(level==7)sprintf(retval,"You've done it!");
	if(level==-1)sprintf(retval,"Why do you come to Earth?");
	return retval;
}
void CompleteGUI_Init()
{
	CompleteGUI=new hgeGUI();
	Current_Position=6;
	DisableAllTower=true;DisablePlayer=true;
	CompleteGUI->AddCtrl(new hgeGUIMenuItem(1,fnt,snd,400,120,0.0f,"It Ends Here!"));
#ifdef WIN32
	if (CheckHighScore()!=-1)
		sprintf(hs1,"New Highscore %I64d!",score);
	else
		sprintf(hs1,"Score %I64d",score);
#else
	if (~CheckHighScore())
		sprintf(hs1,"New Highscore %lld!",score);
	else
		sprintf(hs1,"Score %lld",score);
#endif
	CompleteGUI->AddCtrl(new hgeGUIMenuItem(2,fnt,snd,400,160,0.1f,hs1));
	sprintf(hs7,"Your Ranking: %s",getRank());
	CompleteGUI->AddCtrl(new hgeGUIMenuItem(3,fnt,snd,400,200,0.1f,hs7));
	switch (mode)
	{
		case 1:sprintf(hs2,"Restarts %d",restarts);break;
		case 3:sprintf(hs2,"Collisions %d",coll);break;
	}
	CompleteGUI->AddCtrl(new hgeGUIMenuItem(4,fnt,snd,400,240,0.2f,hs2));
	sprintf(hs3,"Semi-Collisions %d",semicoll);
	CompleteGUI->AddCtrl(new hgeGUIMenuItem(5,fnt,snd,400,280,0.3f,hs3));
	sprintf(hs4,"CLR usage %d",clrusg);
	CompleteGUI->AddCtrl(new hgeGUIMenuItem(6,fnt,snd,400,320,0.3f,hs4));
	sprintf(hs5,"Average FPS %.2f",averfps);
	CompleteGUI->AddCtrl(new hgeGUIMenuItem(7,fnt,snd,400,360,0.4f,hs5));
	if (CheckHighScore()!=-1)
	{
		CompleteGUI->AddCtrl(new hgeGUIMenuItem(8,fnt,snd,400,400,0.5f,"Keep this in your record?"));
		CompleteGUI->AddCtrl(new hgeGUIMenuItem(9,fnt,snd,400,440,0.6f,"Yes"));
		CompleteGUI->AddCtrl(new hgeGUIMenuItem(10,fnt,snd,400,480,0.7f,"No thanks..."));
	}
	else
	{
		CompleteGUI->AddCtrl(new hgeGUIMenuItem(8,fnt,snd,400,400,0.5f,""));
		CompleteGUI->AddCtrl(new hgeGUIMenuItem(9,fnt,snd,400,440,0.6f,""));
		CompleteGUI->AddCtrl(new hgeGUIMenuItem(10,fnt,snd,400,480,0.7f,"Back to menu"));
	}
	for (int i=1;i<=7;++i)CompleteGUI->EnableCtrl(i,false);
	CompleteGUI->SetCursor(spr);
	CompleteGUI->SetNavMode(HGEGUI_UPDOWN|HGEGUI_CYCLED);
	CompleteGUI->SetFocus(8);
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
			case 9:NewHighScoreGUI_Init();CompleteGUI->Leave();break;
			case 10:Current_Position=0;gui->Enter();CompleteGUI->Leave();break;
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
		case 0:sprintf(opt[1],"FPS Level: 60");break;
		case 1:sprintf(opt[1],"FPS Level: ?");break;
		case 2:sprintf(opt[1],"FPS Level: Vsync");break;
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
						fpslvl=2;LOWFPS=true;
						hge->System_SetState(HGE_FPS,61);
						TenSeconds=600;
						TwentySeconds=1200;
						ThirtySeconds=1800;
						AMinute=3600;
						if(fFast)TenSeconds/=2,TwentySeconds/=2,ThirtySeconds/=2,AMinute/=2;
						break;
					case 1:
						/*fpslvl=2;LOWFPS=false;
						hge->System_SetState(HGE_FPS,1000);
						TenSeconds=10000;
						TwentySeconds=20000;
						ThirtySeconds=30000;
						AMinute=60000;
						if(fFast)TenSeconds/=2,TwentySeconds/=2,ThirtySeconds/=2,AMinute/=2;
						break;*/
					case 2:
						fpslvl=0;LOWFPS=true;
						hge->System_SetState(HGE_FPS,HGEFPS_VSYNC);
						TenSeconds=600;
						TwentySeconds=1200;
						ThirtySeconds=1800;
						AMinute=3600;
						if(fFast)TenSeconds/=2,TwentySeconds/=2,ThirtySeconds/=2,AMinute/=2;
						break;
				}
				switch (fpslvl)
				{
					case 0:sprintf(opt[1],"FPS Level: 60");break;
					case 1:sprintf(opt[1],"FPS Level: ?");break;
					case 2:sprintf(opt[1],"FPS Level: Vsync");break;
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
