#include "master.hpp"
#include "resources.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "../ui/menus.hpp"
#define XOFFSET 75
#define YOFFSET 100

extern sceneManager *sceneMgr;
SMELT *introScene::sm=0;
bool introScene::sceneUpdate()
{
	bool done=bcnt>400;
	for(int i=0;i<bcnt;++i)
	{
		pos[i]=pos[i]+vel[i];
		vel[i]=vel[i]+acc[i];
		if(pos[i].x>-40&&pos[i].x<1000&&pos[i].y>-40&&pos[i].y<800)done=false;
		if(scale[i]>0.7)scale[i]-=0.1;else scale[i]=0.6;
	}
	if(done)
	{
		mainMenuScn=new mainMenuScene;
		sceneMgr->activateScene("MainMenu");
		delete this;
	}
	delay+=sm->smGetDelta();
	if(delay<0.016)return false;
	delay=0;
	for(int cc=0;cc<3;++cc)
	{
		++step;
		if(ch==0)//C
		{
			float angle=(60-step)/45.*PI+PI/3.;
			pos[bcnt]=smvec2d(100+XOFFSET+80*cos(angle),200+YOFFSET+80*sin(angle));
			vel[bcnt]=smvec2d(0,0);acc[bcnt]=smvec2d(0,0);scale[bcnt]=1.5;++bcnt;
			if(step>=60){++ch;step=0;}
		}
		if(ch==1)//h
		{
			if(step<=40)
			{
				pos[bcnt]=smvec2d(180+XOFFSET,120+YOFFSET+step*4);
				vel[bcnt]=smvec2d(0,0);acc[bcnt]=smvec2d(0,0);scale[bcnt]=1.5;++bcnt;
			}
			if(step>40&&step<70)
			{
				float angle=(step-40)/30.*PI+PI;
				pos[bcnt]=smvec2d(210+XOFFSET+30*cos(angle),220+YOFFSET+30*sin(angle));
				vel[bcnt]=smvec2d(0,0);acc[bcnt]=smvec2d(0,0);scale[bcnt]=1.5;++bcnt;
			}
			if(step>=70)
			{
				pos[bcnt]=smvec2d(240+XOFFSET,220+YOFFSET+(step-70)*4);
				vel[bcnt]=smvec2d(0,0);acc[bcnt]=smvec2d(0,0);scale[bcnt]=1.5;++bcnt;
				if(step>=85){++ch;step=0;}
			}
		}
		if(ch==2)//r
		{
			if(step<=20)
			{
				pos[bcnt]=smvec2d(280+XOFFSET,200+YOFFSET+step*4);
				vel[bcnt]=smvec2d(0,0);acc[bcnt]=smvec2d(0,0);scale[bcnt]=1.5;++bcnt;
			}
			if(step>20)
			{
				float angle=(step-20)/30.*PI+PI;
				pos[bcnt]=smvec2d(310+XOFFSET+30*cos(angle),230+YOFFSET+30*sin(angle));
				vel[bcnt]=smvec2d(0,0);acc[bcnt]=smvec2d(0,0);scale[bcnt]=1.5;++bcnt;
				if(step>=45){++ch;step=0;}
			}
		}
		if(ch==3)//i
		{
			if(step<=20)
			{
				pos[bcnt]=smvec2d(360+XOFFSET,200+YOFFSET+step*4);
				vel[bcnt]=smvec2d(0,0);acc[bcnt]=smvec2d(0,0);scale[bcnt]=1.5;++bcnt;
			}
			if(step>20)
			{
				pos[bcnt]=smvec2d(360+XOFFSET,180+YOFFSET);
				vel[bcnt]=smvec2d(0,0);acc[bcnt]=smvec2d(0,0);scale[bcnt]=1.5;++bcnt;
				++ch;step=0;
			}
		}
		if(ch==4)//s
		{
			if(step<=30)
			{
				float angle=(30-step)/30.*PI+2*PI/3.;
				pos[bcnt]=smvec2d(450+XOFFSET+40*cos(angle),170+YOFFSET+40*sin(angle));
				vel[bcnt]=smvec2d(0,0);acc[bcnt]=smvec2d(0,0);scale[bcnt]=1.5;++bcnt;
			}
			if(step>30)
			{
				float angle=(step-30)/30.*PI+5*PI/3.;
				pos[bcnt]=smvec2d(410+XOFFSET+40*cos(angle),239.282+YOFFSET+40*sin(angle));
				vel[bcnt]=smvec2d(0,0);acc[bcnt]=smvec2d(0,0);scale[bcnt]=1.5;++bcnt;
				if(step>60){++ch;step=0;}
			}
		}
		if(ch==5)
		{
			float angle=-step/30.*PI+3*PI/2.;
			pos[bcnt]=smvec2d(520+XOFFSET+40*cos(angle),240+YOFFSET+40*sin(angle));
			vel[bcnt]=smvec2d(0,0);acc[bcnt]=smvec2d(0,0);scale[bcnt]=1.5;++bcnt;
			if(step>60){++ch;step=0;}
		}
		if(ch==6)
		{
			if(step<=30)
			{
				float angle=(30-step)/30.*PI+PI;
				pos[bcnt]=smvec2d(620+XOFFSET+30*cos(angle),160+YOFFSET+30*sin(angle));
				vel[bcnt]=smvec2d(0,0);acc[bcnt]=smvec2d(0,0);scale[bcnt]=1.5;++bcnt;
			}
			if(step>30&&step<=55)
			{
				pos[bcnt]=smvec2d(590+XOFFSET,160+YOFFSET+(step-30)*5);
				vel[bcnt]=smvec2d(0,0);acc[bcnt]=smvec2d(0,0);scale[bcnt]=1.5;++bcnt;
			}
			if(step>55)
			{
				pos[bcnt]=smvec2d(570+XOFFSET+(step-55)*4,190+YOFFSET);
				vel[bcnt]=smvec2d(0,0);acc[bcnt]=smvec2d(0,0);scale[bcnt]=1.5;++bcnt;
				if(step>75){++ch;step=0;}
			}
		}
		if(ch==7)
		{
			if(step<=20)
			{
				pos[bcnt]=smvec2d(700+XOFFSET,160+YOFFSET+step*5);
				vel[bcnt]=smvec2d(0,0);acc[bcnt]=smvec2d(0,0);scale[bcnt]=1.5;++bcnt;
			}
			if(step>25&&step<=55)
			{
				float angle=(55-step)/30.*PI;
				pos[bcnt]=smvec2d(730+XOFFSET+30*cos(angle),260+YOFFSET+30*sin(angle));
				vel[bcnt]=smvec2d(0,0);acc[bcnt]=smvec2d(0,0);scale[bcnt]=1.5;++bcnt;
			}
			if(step>55)
			{
				pos[bcnt]=smvec2d(680+XOFFSET+(step-55)*4,190+YOFFSET);
				vel[bcnt]=smvec2d(0,0);acc[bcnt]=smvec2d(0,0);scale[bcnt]=1.5;++bcnt;
				if(step>75){++ch;step=0;}
			}
		}
		if(ch==8)
		{if(step>120){++ch;step=0;}}
		if(ch==9)
		{
			for(int i=0;i<bcnt;++i)
			{
				do{acc[i]=smvec2d(rand()%100-50.,rand()%100-50.);acc[i].normalize();
				}while(acc[i].l()<1E-6);
				acc[i]=(rand()%100/400.+0.2)*acc[i];
			}
			++ch;
		}
		if(ch==10)
		{if(step>180){++ch;step=0;}}
	}
	return false;
}
bool introScene::sceneRender()
{
	if(ch!=11)
	sm->smClrscr(0xFF000000);
	else
	{int c=step*4>255?255:step*4;sm->smClrscr(ARGB(255,c,c,c));}
	for(int i=0;i<bcnt;++i)
	blt->render(pos[i].x,pos[i].y,0,scale[i],scale[i]);
	return false;
}
introScene::introScene()
{
	sm=smGetInterface(SMELT_APILEVEL);
	pos=new smvec2d[1024];vel=new smvec2d[1024];
	scale=new float[1024];acc=new smvec2d[1024];
	extern const char* bsnames[];delay=0;
	smTexInfo *ti=ssanm.getTextureInfo(bsnames[rand()%8]);
	blt=new smEntity2D(ti->tex,ti->rect);
	blt->setCentre(12,12);
	blt->setColor(0xC0FFFFFF);
	sceneMgr->registerScene(this,"Intro",1000);
}
void introScene::introInit()
{
	bcnt=step=ch=0;
	sceneMgr->activateScene("Intro");
}
introScene::~introScene()
{
	sceneMgr->deactivateScene("Intro");
	delete[] pos;delete[] vel;delete[] acc;delete[] scale;delete blt;
	sm->smRelease();
}
