#include "bullet.hpp"
#include "../master/resources.hpp"
#include <cstdlib>
const char* bsnames[]={"green_bullet","cyan_bullet","yellow_bullet","purple_bullet",
					 "red_bullet","white_bullet","blue_bullet","orange_bullet",
					 "grey_bullet","circle_bullet"};
void bulletBase::init(...){exist=true;renderscale=1;}
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

void bulletBonus::update()
{
	//the player is not implemented yet...
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
