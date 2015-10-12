#ifndef BULLET_H
#define BULLET_H
#include "smmath.hpp"
#include "smentity.hpp"
#include "coreshared.hpp"
class bulletBase
{
public:
	smvec2d pos,vel,acc;
	double velim;
	//velim: velocity scalar limit.
	double collrange,scollrange;
	float renderscale;
	//collision range and semi-collision range. Replacing "collable" and "scollable".
	bool extborder,invincible;
	//extborder: true=not removed if out of screen.
	//invincible: true=not removed if collided with player or in range of CLR.
	bool exist,addblend,special;
	int attrd[16],scb,cscb,cb,ccb;
	double attrf[16];
	TColors basecolor;
	DWORD rendercolor;
	virtual void init(char fstarg,...);
	virtual void update();
	virtual void render();
	virtual ~bulletBase();
};
class bulletBonus:public bulletBase
{
public:
	void init(char fstarg,...)override;
	void update()override;
};
class bulletFX:public bulletBase
{
public:
	void init(char fstarg,...)override;
	void update()override;
};
class bulletManager
{
private:
	bulletBase* bullets[10240];
	int alloced,used;
	smEntity2D* bulent2d[COLOR_COUNT];
	smEntity3D* bulent3d[COLOR_COUNT];
public:
	void init();
	void deinit();
	template<class T>int allocBullet()
	{
		if(!alloced)
		{
			alloced=1;
			bullets[0]=new T;
			return 0;
		}
		else
		{
			int i;
			for(i=0;i<alloced;++i)
			if(!bullets[i]->exist)break;
			if(i==alloced)
				bullets[alloced++]=new T;
			else
			{
				delete bullets[i];
				bullets[i]=new T;
			}
			return i;
		}
		return -1;
	}
	template<class T>int createBullet()
	{
		//stub...
		int ptr=allocBullet<T>();
		bullets[ptr]->init(0);
		return ptr;
	}
	void updateBullet();
	void renderBullet();
	void addFXBullet(TColors col,int base,int var);
	bulletBase* getHandle(int id);
	smEntity2D* getBulEntity2D(TColors col);
	smEntity3D* getBulEntity3D(TColors col);
};
extern bulletManager *bmInstance;
#endif
