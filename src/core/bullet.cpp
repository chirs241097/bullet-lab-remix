#include "bullet.hpp"
#include "../master/resources.hpp"
#include <cstdlib>
#include <cstdarg>
#include "player.hpp"
const char* bsnames[]={"green_bullet","cyan_bullet","yellow_bullet","purple_bullet",
					 "red_bullet","white_bullet","blue_bullet","orange_bullet",
					 "grey_bullet","circle_bullet"};
void bulletBase::init(char fstarg,...)
{
	++fstarg;exist=true;renderscale=1;
	special=invincible=false;scollrange=64;collrange=16;
	scb=cb=8;
}
void bulletBase::update()
{
	if(!exist)return;
	vel=vel+acc;
	if(vel.l()>velim&&velim>0)vel=velim*vel.getNormalized();
	pos=pos-vel;
	if(!extborder&&(pos.x<-10||pos.y<-10||pos.x>810||pos.y>610))exist=false;
	if((pos-player->pos).l()>scollrange)if(invincible)cscb=scb;
	if((pos-player->pos).l()>collrange)if(invincible)ccb=cb;
	if((pos-player->pos).l()<=scollrange&&(pos-player->pos).l()>collrange)
	{
		if(!invincible)scollrange=-1,++player->scoll,bmInstance->addFXBullet(grey,5,5);
		else{if(++cscb>scb)cscb=0,++player->scoll,bmInstance->addFXBullet(grey,5,5);}
	}
	if((pos-player->pos).l()<=collrange)
	{
		if(!invincible)exist=false,++player->coll,bmInstance->addFXBullet(red,15,15);
		else{if(++ccb>cb)ccb=0,++player->coll,bmInstance->addFXBullet(red,15,15);}
	}
}
void bulletBase::render()
{
	//test view mode
	bmInstance->getBulEntity2D(basecolor)->setColor(rendercolor);
	bmInstance->getBulEntity2D(basecolor)->render(pos.x,pos.y,0,renderscale*0.6);
}
bulletBase::~bulletBase(){}

void bulletBonus::init(char fstarg,...)
{
	fstarg=0;va_list val;va_start(val,fstarg);
	pos.x=va_arg(val,double);
	pos.y=va_arg(val,double);
	basecolor=grey;rendercolor=0x33FFFFFF;
	va_end(val);renderscale=0.8;
	attrf[0]=0;attrd[0]=0;exist=special=true;
	vel.x=0;vel.y=2;acc.x=0;acc.y=-0.1;
}
void bulletBonus::update()
{
	if(!exist)return;
	vel=vel+acc;
	if(vel.l()>velim&&velim>0)vel=velim*vel.getNormalized();
	pos=pos-vel;
	if((pos-player->pos).l()<9)exist=false;

	if(vel.y<0&&!attrd[0])attrd[0]=1,acc=smvec2d(0,0);
	if(attrd[0])
	{
		if(attrf[0]<10)attrf[0]+=.5;else attrf[0]=10.1;
		vel=pos-player->pos;
		vel.normalize();
		vel=attrf[0]*vel;
	}
}
void bulletFX::init(char fstarg,...)
{
	fstarg=0;va_list val;va_start(val,fstarg);
	pos=player->pos;
	basecolor=(TColors)va_arg(val,int);
	rendercolor=0x33FFFFFF;
	va_end(val);renderscale=0.4;collrange=scollrange=-1;
	attrf[0]=0;attrd[0]=0;exist=special=invincible=true;
	vel.x=rand()%1000-500;vel.y=rand()%1000-500;
	vel=(2+rand()%3+rand()%10/10.)*vel.getNormalized();
}
void bulletFX::update()
{
	pos=pos-vel;
	rendercolor=SETA(rendercolor,GETA(rendercolor)-2);
	if(GETA(rendercolor)<=2)exist=false;
}

void bulletManager::init()
{
	alloced=used=0;
	for(int i=0;i<(int)COLOR_COUNT;++i)
	{
		bulent2d[i]=new smEntity2D(ssanm.getTextureInfo(bsnames[i])->tex,ssanm.getTextureInfo(bsnames[i])->rect);
		bulent3d[i]=new smEntity3D(ssanm.getTextureInfo(bsnames[i])->tex,ssanm.getTextureInfo(bsnames[i])->rect);
	}
}
void bulletManager::deinit()
{
	if(alloced){for(int i=0;i<alloced;++i)delete bullets[i];alloced=used=0;}
	for(int i=0;i<(int)COLOR_COUNT;++i)
	{delete bulent2d[i];delete bulent3d[i];}
}
void bulletManager::updateBullet()
{
	extern SMELT *sm;
	if(sm->smGetKeyState(SMK_SPACE)==SMKST_HIT)
	for(int i=0;i<alloced;++i)
	if(bullets[i]->exist&&!bullets[i]->special)
	{
		bullets[i]->exist=false;
		smvec2d p=bullets[i]->pos;
		bullets[allocBullet<bulletBonus>()]->init(0,p.x,p.y);
	}
	for(int i=0;i<alloced;++i)
	if(bullets[i]->exist)
		bullets[i]->update();
}
void bulletManager::renderBullet()
{
	for(int i=0;i<alloced;++i)
	if(bullets[i]->exist)
	{
		bullets[i]->render();
	}
}
void bulletManager::addFXBullet(TColors col,int base,int var)
{
	int c=rand()%var+base;
	for(int i=0;i<c;++i)
	bullets[allocBullet<bulletFX>()]->init(0,col);
}
smEntity2D* bulletManager::getBulEntity2D(TColors col){return bulent2d[col];}
smEntity3D* bulletManager::getBulEntity3D(TColors col){return bulent3d[col];}
bulletBase* bulletManager::getHandle(int id){if(id<alloced)return bullets[id];else return NULL;}
bulletManager *bmInstance;
