#include "bullet.hpp"
#include "../master/resources.hpp"
#include <cstdlib>
#include <cstdarg>
#include "player.hpp"
const char* bsnames[]={"green_bullet","cyan_bullet","yellow_bullet","purple_bullet",
					 "red_bullet","white_bullet","blue_bullet","orange_bullet",
					 "grey_bullet","circle_bullet"};
void bulletBase::init(char fstarg,...){++fstarg;exist=true;renderscale=1;special=false;}
void bulletBase::update()
{
	if(!exist)return;
	vel=vel+acc;
	if(vel.l()>velim&&velim>0)vel=velim*vel.getNormalized();
	pos=pos-vel;
	if(!extborder&&(pos.x<-10||pos.y<-10||pos.x>810||pos.y>610))exist=false;
	//check clr & collision
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
	va_end(val);renderscale=0.5;
	attrf[0]=0;attrd[0]=0;exist=special=true;
	vel.x=0;vel.y=-2;acc.x=0;acc.y=0.1;
}
void bulletBonus::update()
{
	//the player is not implemented yet...
	if(vel.y>0)attrd[0]=1,acc=smvec2d(0,0);
	if(attrd[0])
	{
		if(attrf[0]<10)attrf[0]+=.5;else attrf[0]=10.1;
		vel=vel-player->pos;
		vel.normalize();
		vel=attrf[0]*vel;
	}
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
		int ptr=allocBullet<bulletBonus>();
		bullets[ptr]->init(0,bullets[i]->vel.x,bullets[i]->vel.y);
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
smEntity2D* bulletManager::getBulEntity2D(TColors col){return bulent2d[col];}
smEntity3D* bulletManager::getBulEntity3D(TColors col){return bulent3d[col];}
bulletBase* bulletManager::getHandle(int id){if(id<alloced)return bullets[id];else return NULL;}
bulletManager *bmInstance;
