#include "smelt.hpp"
#include "player.hpp"
#include "../master/resources.hpp"
SMELT* playerBase::sm=NULL;
playerBase::playerBase(double _x,double _y)
{
	sm=smGetInterface(SMELT_APILEVEL);
	playerent=new smEntity2D(ssanm.getTextureInfo("player")->tex,ssanm.getTextureInfo("player")->rect);
	playerent->setCentre(12,12);
	pos.x=_x;pos.y=_y;
	plyrctl[0]=SMK_UP;plyrctl[1]=SMK_DOWN;
	plyrctl[2]=SMK_LEFT;plyrctl[3]=SMK_RIGHT;
	plyrctl[4]=SMK_SHIFT;
	rot=0;
}
playerBase::~playerBase()
{
	delete playerent;sm->smRelease();
}
void playerBase::update()
{
	//player control...
	static double realspeed=0;
	if(sm->smGetKeyState(plyrctl[4]))
	realspeed=0.85;else realspeed=3.5;
	if(sm->smGetKeyState(plyrctl[0]))
	{if(pos.y>15)pos.y-=realspeed;else pos.y=15;}
	if(sm->smGetKeyState(plyrctl[1]))
	{if(pos.y<585)pos.y+=realspeed;else pos.y=585;}
	if(sm->smGetKeyState(plyrctl[2]))
	{if(pos.x>15)pos.x-=realspeed;else pos.x=15;}
	if(sm->smGetKeyState(plyrctl[3]))
	{if(pos.x<785)pos.x+=realspeed;else pos.x=785;}
	rot+=17./1800.*PI;
}
void playerBase::render()
{
	playerent->render(pos.x+8.4,pos.y+8.4,rot,0.7);
}
playerBase* player;
