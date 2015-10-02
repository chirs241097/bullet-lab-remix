#include "menuframework.hpp"
#include <cstring>
#include <cmath>
SMELT* menuCtrlLCD::sm=NULL;
SMELT* menuLCD::sm=NULL;
void menuCtrlLCD::render(float x,float y)
{
	fnt->setColor(color);
	fnt->render(x+skv,y,1,ALIGN_LEFT,NULL,rt);
}
void menuCtrlLCD::update()
{
	if(overlen)
	{
		if(selected)
		{
			++scd;
			if(scd>30)++scv,scd=0;
			if(scv>(int)strlen(tr))scv=0;
			char rr[48];sprintf(rr,"%s %s",tr,tr);
			sprintf(rt,"%s %.*s",tl,(int)(maxw-strlen(tl)-1),rr+scv);
		}
		else
		{
			scv=0;
			sprintf(rt,"%s %.*s...",tl,(int)(maxw-strlen(tl)-4),tr);
		}
	}
	if(skd>0){skv=-skv;--skd;}else skd=skv=0;
	if(selected)
	{color=SETA(color,(int)(0x60*fabsf(sin(6*sm->smGetTime())))+0x90);}
	else
	color=SETA(color,0x80);
}
void menuCtrlLCD::setText(const char* l,const char* r)
{
	if(!l)l="";if(!r)r="";
	tl=l;tr=r;
	if((int)(strlen(l)+strlen(r)+1)>maxw)
	{
		overlen=true;scv=0;scd=0;
	}
	else
	{
		overlen=false;
		sprintf(rt,"%s %*s",l,(int)(maxw-strlen(l)-1),r);
	}
}
void menuLCD::addCtrl(menuCtrlLCD *ctrl)
{
	if(ctrl->id==0)ctrl->selected=true;else ctrl->selected=false;
	menuCtrlLCD *last=ctrls;
	if(!ctrls)
	{
		ctrls=ctrl;
		ctrl->last=0;
		ctrl->next=0;
	}
	else
	{
		while(last->next)last=last->next;
		last->next=ctrl;
		ctrl->last=last;
		ctrl->next=0;
	}
	ctrl->color=0x80333333;
}
menuCtrlLCD* menuLCD::getCtrl(int id)
{
	for(menuCtrlLCD* i=ctrls;i;i=i->next)
	if(i->id==id)return i;
	return NULL;
}
bool menuLCD::update()
{
	if(sm->smGetKeyState(SMK_DOWN)==SMKST_HIT)
	{
		getCtrl(selected)->selected=false;
		menuCtrlLCD* c;
		for(int i=selected+1;(c=getCtrl(i));++i)
		{if(c->enabled){selected=i;break;}}
		getCtrl(selected)->selected=true;
	}
	if(sm->smGetKeyState(SMK_UP)==SMKST_HIT)
	{
		getCtrl(selected)->selected=false;
		menuCtrlLCD* c;
		for(int i=selected-1;(c=getCtrl(i));++i)
		{if(c->enabled){selected=i;break;}}
		getCtrl(selected)->selected=true;
	}
	for(menuCtrlLCD* i=ctrls;i;i=i->next)i->update();
	if(sm->smGetKey())
		return getCtrl(selected)->ikp();
	else return false;
}
void menuLCD::render()
{
	int cr=rows/2+1;
	getCtrl(selected)->render(x,y+(cr-1)*itemh);
	menuCtrlLCD* t=getCtrl(selected);
	for(int ccr=cr-1;ccr>0;--ccr)
	{
		if(t)t=getCtrl(t->id-1);
		if(!t){fnt->setColor(0x80333333);fnt->printf(x,y+(ccr-1)*itemh,1,ALIGN_LEFT,NULL,"%*s",maxw," ");}
		else t->render(x,y+(ccr-1)*itemh);
	}
	t=getCtrl(selected);
	for(int ccr=cr+1;ccr<=rows;++ccr)
	{
		if(t)t=getCtrl(t->id+1);
		if(!t){fnt->setColor(0x80333333);fnt->printf(x,y+(ccr-1)*itemh,1,ALIGN_LEFT,NULL,"%*s",maxw," ");}
		else t->render(x,y+(ccr-1)*itemh);
	}
}
