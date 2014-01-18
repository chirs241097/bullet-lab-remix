//Chrisoft Bullet Lab Remix HGE
//Towers and Bullets Implementations
//"Copyleft" Chrisoft 2013
//WANTED:
//Human-being which really knows what these mean, please contact Chirsno which is puzzled by these shitty codes..
//[Perfect Freeze]: code here for BLR2 won't change a lot since 30/08/2013
//If you are expecting new code, please wait the full rewrite in BLR3...
//                                             --Announcement from Chirsno
#include "effects.h"
static const char* TOWERNBULLET_H_FN="towernbullet.h";

void DirectBullet(Bullet &a,double rad)
{
	a.bulletdir.x=cos(rad);
	a.bulletdir.y=sin(rad);
	a.dist=1;
}
int CreateBullet1(double x,double y,double bs,bool eff=false)
{
	++shots;
	int i;
	if (bulcnt==0)
		bulcnt=i=1;
	else
	{
		for (i=1;i<=bulcnt;++i)
			if (!bullet[i].exist)break;
		if (i>bulcnt)bulcnt=i;
	}
	bullet[i].exist=true;
	bullet[i].bullettype=1;
	bullet[i].bulletpos.x=x;
	bullet[i].bulletpos.y=y;
	bullet[i].bulletdir.x=x-playerpos.x;
	bullet[i].bulletdir.y=y-playerpos.y;
	bullet[i].dist=bullet[i].bulletdir.x*bullet[i].bulletdir.x+bullet[i].bulletdir.y*bullet[i].bulletdir.y;
	bullet[i].dist=sqrt(bullet[i].dist);
	bullet[i].bulletspeed=bs;
	bullet[i].bulletspr=new hgeSprite(SprSheet,48,0,24,24);
	bullet[i].bulletspr->SetColor(0x80FFFFFF);
	bullet[i].scollable=true;
	bullet[i].scale=1;
	bullet[i].bulletspr->SetHotSpot(12,12);
	if (eff)BulletEffect_Attatch(i);
	return i;
}
int CreateBullet2(double x,double y,double bs,double rad,bool eff=false)
{
	++shots;
	int i;
	if (bulcnt==0)
		bulcnt=i=1;
	else
	{
		for (i=1;i<=bulcnt;++i)
			if (!bullet[i].exist)break;
		if (i>bulcnt)bulcnt=i;
	}
	bullet[i].exist=true;
	bullet[i].bullettype=2;
	bullet[i].bulletpos.x=x;
	bullet[i].bulletpos.y=y;
	bullet[i].bulletdir.x=cos(rad);
	bullet[i].bulletdir.y=sin(rad);
	bullet[i].bulletspeed=bs;
	bullet[i].lifetime=0;
	bullet[i].bulletspr=new hgeSprite(SprSheet,0,0,24,24);
	bullet[i].bulletspr->SetColor(0x80FFFFFF);
	bullet[i].scollable=true;
	bullet[i].bulletaccel=bullet[i].limv=0;
	bullet[i].scale=1;
	bullet[i].bulletspr->SetHotSpot(12,12);
	if (eff)BulletEffect_Attatch(i);
	return i;
}
void CreateBullet3(double x,double y,double bs,int dir,bool eff=false)
{
	CreateBullet2(x,y,bs,dir*0.5235987756,eff);
}
void CreateBullet4(double x,double y,double bs,int yelbrk=0,bool eff=false)
{
	++shots;
	int i;
	if (bulcnt==0)
		bulcnt=i=1;
	else
	{
		for (i=1;i<=bulcnt;++i)
			if (!bullet[i].exist)break;
		if (i>bulcnt)bulcnt=i;
	}
	bullet[i].exist=true;
	bullet[i].bullettype=4;
	bullet[i].bulletpos.x=x;
	bullet[i].bulletpos.y=y;
	bullet[i].bulletdir.x=x-playerpos.x;
	bullet[i].bulletdir.y=y-playerpos.y;
	bullet[i].dist=bullet[i].bulletdir.x*bullet[i].bulletdir.x+bullet[i].bulletdir.y*bullet[i].bulletdir.y;
	bullet[i].dist=sqrt(bullet[i].dist);
	bullet[i].bulletspeed=bs;
	bullet[i].yelbrk=yelbrk;
	bullet[i].bulletspr=new hgeSprite(SprSheet,192,0,24,24);
	bullet[i].bulletspr->SetColor(0x80FFFFFF);
	bullet[i].scollable=true;
	bullet[i].scale=1;
	bullet[i].bulletspr->SetHotSpot(12,12);
	if (eff)BulletEffect_Attatch(i);
}
void CreateBullet5(double x,double y,double bs,bool eff=false)
{
	++shots;
	int i;
	if (bulcnt==0)
		bulcnt=i=1;
	else
	{
		for (i=1;i<=bulcnt;++i)
			if (!bullet[i].exist)break;
		if (i>bulcnt)bulcnt=i;
	}
	bullet[i].exist=true;
	bullet[i].bullettype=5;
	bullet[i].bulletpos.x=x;
	bullet[i].bulletpos.y=y;
	bullet[i].bulletdir.x=x-playerpos.x;
	bullet[i].bulletdir.y=y-playerpos.y;
	bullet[i].dist=bullet[i].bulletdir.x*bullet[i].bulletdir.x+bullet[i].bulletdir.y*bullet[i].bulletdir.y;
	bullet[i].dist=sqrt(bullet[i].dist);
	bullet[i].bulletspeed=bs;
	bullet[i].bulletspr=new hgeSprite(SprSheet,120,0,24,24);
	bullet[i].bulletspr->SetColor(0x80FFFFFF);
	bullet[i].scollable=true;
	bullet[i].scale=1;
	bullet[i].bulletspr->SetHotSpot(12,12);
	if (eff)BulletEffect_Attatch(i);
}
int CreateBullet6(double x,double y,double bs,int explo,int exp1=8,int exp2=12,bool eff=false)
{
	++shots;
	int i;
	if (bulcnt==0)
		bulcnt=i=1;
	else
	{
		for (i=1;i<=bulcnt;++i)
			if (!bullet[i].exist)break;
		if (i>bulcnt)bulcnt=i;
	}
	bullet[i].exist=true;
	bullet[i].bullettype=6;
	bullet[i].bulletpos.x=x;
	bullet[i].bulletpos.y=y;
	bullet[i].bulletdir.x=rand()%100-50;
	bullet[i].bulletdir.y=rand()%100-50;
	bullet[i].dist=bullet[i].bulletdir.x*bullet[i].bulletdir.x+bullet[i].bulletdir.y*bullet[i].bulletdir.y;
	bullet[i].dist=sqrt(bullet[i].dist);
	bullet[i].bulletspeed=bs;
	bullet[i].redattrib=0;
	bullet[i].exp1=exp1;
	bullet[i].exp2=exp2;
	bullet[i].oriexplo=bullet[i].redexplo=explo;
	bullet[i].bulletspr=new hgeSprite(SprSheet,144,0,24,24);
	bullet[i].bulletspr->SetColor(0x80FFFFFF);
	bullet[i].scollable=true;
	bullet[i].scale=1;
	bullet[i].bulletspr->SetHotSpot(12,12);
	if (eff)BulletEffect_Attatch(i);
	return i;
}
int CreateBullet7(double x,double y,double bs,int explo,bool eff=false)
{
	++shots;
	int i;
	if (bulcnt==0)
		bulcnt=i=1;
	else
	{
		for (i=1;i<=bulcnt;++i)
			if (!bullet[i].exist)break;
		if (i>bulcnt)bulcnt=i;
	}
	bullet[i].exist=true;
	bullet[i].bullettype=7;
	bullet[i].bulletpos.x=x;
	bullet[i].bulletpos.y=y;
	bullet[i].bulletdir.x=rand()%100-50;
	bullet[i].bulletdir.y=rand()%100-50;
	bullet[i].dist=bullet[i].bulletdir.x*bullet[i].bulletdir.x+bullet[i].bulletdir.y*bullet[i].bulletdir.y;
	bullet[i].dist=sqrt(bullet[i].dist);
	bullet[i].bulletspeed=bs;
	bullet[i].oriexplo=bullet[i].redexplo=explo;
	bullet[i].bulletspr=new hgeSprite(SprSheet,168,0,24,24);
	bullet[i].bulletspr->SetColor(0x80FFFFFF);
	bullet[i].redattrib=0;
	bullet[i].whirem=whicnt;
	bullet[i].whiskp=0;
	bullet[i].scollable=true;
	bullet[i].scale=1;
	bullet[i].bulletspr->SetHotSpot(12,12);
	if (eff)BulletEffect_Attatch(i);
	return i;
}
int CreateBullet8(double x,double y,double bs,bool eff=false)
{
	++shots;
	int i;
	if (bulcnt==0)
		bulcnt=i=1;
	else
	{
		for (i=1;i<=bulcnt;++i)
			if (!bullet[i].exist)break;
		if (i>bulcnt)bulcnt=i;
	}
	bullet[i].exist=true;
	bullet[i].bullettype=8;
	bullet[i].bulletpos.x=x;
	bullet[i].bulletpos.y=y;
	bullet[i].bulletdir.x=x-playerpos.x;
	bullet[i].bulletdir.y=y-playerpos.y;
	bullet[i].dist=bullet[i].bulletdir.x*bullet[i].bulletdir.x+bullet[i].bulletdir.y*bullet[i].bulletdir.y;
	bullet[i].dist=sqrt(bullet[i].dist);
	bullet[i].bulletspeed=bs;
	bullet[i].bulletspr=new hgeSprite(SprSheet,24,0,24,24);
	bullet[i].bulletspr->SetColor(0x80FFFFFF);
	bullet[i].scollable=true;
	bullet[i].scale=1;
	bullet[i].bulletspr->SetHotSpot(12,12);
	if (eff)BulletEffect_Attatch(i);
	return i;
}
int CreateBullet9(double x,double y,double bs,int explo,int cnt,int brk,bool eff=false)
{
	//This creates bullet9 in random direction and as attrib 0
	//change them if necessary.
	++shots;
	int i;
	if (bulcnt==0)
		bulcnt=i=1;
	else
	{
		for (i=1;i<=bulcnt;++i)
			if (!bullet[i].exist)break;
		if (i>bulcnt)bulcnt=i;
	}
	bullet[i].exist=true;
	bullet[i].bullettype=9;
	bullet[i].bulletpos.x=x;
	bullet[i].bulletpos.y=y;
	bullet[i].bulletdir.x=rand()%100-50;
	bullet[i].bulletdir.y=rand()%100-50;
	bullet[i].dist=bullet[i].bulletdir.x*bullet[i].bulletdir.x+bullet[i].bulletdir.y*bullet[i].bulletdir.y;
	bullet[i].dist=sqrt(bullet[i].dist);
	bullet[i].bulletspeed=bs;
	bullet[i].oriexplo=bullet[i].redexplo=explo;
	bullet[i].redattrib=0;
	bullet[i].whicnt=cnt;
	bullet[i].yelbrk=brk;
	bullet[i].bulletspr=new hgeSprite(SprSheet,72,0,24,24);
	bullet[i].bulletspr->SetColor(0x80FFFFFF);
	bullet[i].scollable=true;
	bullet[i].scale=1;
	bullet[i].bulletspr->SetHotSpot(12,12);
	if (eff)BulletEffect_Attatch(i);
	return i;
}
void CreateBullet255(double x,double y,double bs)
{
	int i;
	if (bulcnt==0)
		bulcnt=i=1;
	else
	{
		for (i=1;i<=bulcnt;++i)
			if (!bullet[i].exist)break;
		if (i>bulcnt)bulcnt=i;
	}
	bullet[i].exist=true;
	bullet[i].bullettype=255;
	bullet[i].bulletpos.x=x;
	bullet[i].bulletpos.y=y;
	bullet[i].bulletdir.x=x-playerpos.x;
	bullet[i].bulletdir.y=y-playerpos.y;
	bullet[i].dist=bullet[i].bulletdir.x*bullet[i].bulletdir.x+bullet[i].bulletdir.y*bullet[i].bulletdir.y;
	bullet[i].dist=sqrt(bullet[i].dist);
	bullet[i].bulletspeed=bs;
	bullet[i].bulletspr=new hgeSprite(SprSheet,96,0,24,24);
	bullet[i].bulletspr->SetColor(0x80FFFFFF);
}
void All2pnt()
{
	for (int i=1;i<=bulcnt;++i)
	{
		CreateBullet255(bullet[i].bulletpos.x,bullet[i].bulletpos.y,10);
		bullet[i].exist=false;
		bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
		bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
		bullet[i].dist=0;
		bullet[i].bullettype=0;
	}
}
void ProcessBullet1(int i)
{
	if (!bullet[i].exist||bullet[i].bullettype!=1)return;//If this bullet doesn't exist or is not of this type, do not render it.
	if (!DisablePlayer)
	{
		if (LOWFPS)
		{
			bullet[i].bulletpos.x-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20*17;//Process bullet's x coor.
			bullet[i].bulletpos.y-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20*17;//Process bullet's y coor.
		}
		else
		{
			bullet[i].bulletpos.x-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20;//Process bullet's x coor.
			bullet[i].bulletpos.y-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20;//Process bullet's y coor.
		}
	}
	BulletEffect_Process(i);
	double dis=GetDist(bullet[i].bulletpos,playerpos);//Get distance between player and bullet
	if (dis<=6||bullet[i].bulletpos.x<=-10||bullet[i].bulletpos.x>=800||bullet[i].bulletpos.y<=-10||bullet[i].bulletpos.y>=600)
	//If collision is detected or the bullet flys out of screen, delete it.
	{
		if (dis<=6&&clrrange<1e-5&&clrrad-pi/2<1e-7)++coll,scminus+=10000,Mult_BatClear();
		bullet[i].exist=false;
		bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
		bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
		bullet[i].dist=0;
		bullet[i].bullettype=0;
#ifndef NO_FREE
		if (bullet[i].bulletspr)free(bullet[i].bulletspr);
#endif
	}
	else
	{
		bullet[i].bulletspr->RenderEx(bullet[i].bulletpos.x+7.2,bullet[i].bulletpos.y+7.2,0,0.6*bullet[i].scale,0);
		if (dis<=16&&bullet[i].scollable)++semicoll,++dsmc,bullet[i].scollable=false,SCEffect_Attatch();
	}
}
void ProcessBullet2(int i)
{
	if (!bullet[i].exist||bullet[i].bullettype!=2)return;//If this bullet doesn't exist or is not of this type, do not render it.
	if (LOWFPS)bullet[i].lifetime+=17;else ++bullet[i].lifetime;
	if (bullet[i].lifetime>=15000&&Refliction)
	{
		bullet[i].exist=false;
		bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
		bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
		bullet[i].dist=0;
		bullet[i].bullettype=0;
		return;
	}
	if (!DisablePlayer)
	{
		if (LOWFPS)
		{
			if (bullet[i].bulletspeed<bullet[i].limv)bullet[i].bulletspeed+=bullet[i].bulletaccel*17;
			bullet[i].bulletpos.x-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.x)/20*17;//Process bullet's x coor.
			bullet[i].bulletpos.y-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.y)/20*17;//Process bullet's y coor.
		}
		else
		{
			if (bullet[i].bulletspeed<bullet[i].limv)bullet[i].bulletspeed+=bullet[i].bulletaccel;
			bullet[i].bulletpos.x-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.x)/20;//Process bullet's x coor.
			bullet[i].bulletpos.y-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.y)/20;//Process bullet's y coor.
		}
	}
	BulletEffect_Process(i);
	double dis=GetDist(bullet[i].bulletpos,playerpos);//Get distance between player and bullet
	if (bullet[i].bulletpos.x<=-25||bullet[i].bulletpos.x>=825||bullet[i].bulletpos.y<=-25||bullet[i].bulletpos.y>=625)
	{
		if (Refliction)
			bullet[i].bulletdir.x=-bullet[i].bulletdir.x,
			bullet[i].bulletdir.y=-bullet[i].bulletdir.y;
		else
		{
			bullet[i].exist=false;
			bullet[i].bulletpos.x=bullet[i].bulletpos.y=-999;
			bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
			bullet[i].dist=0;
			bullet[i].bullettype=0;
#ifndef NO_FREE
			if (bullet[i].bulletspr)free(bullet[i].bulletspr);
#endif
			return;
		}
	}
	if (dis<=6&&clrrange<1e-5&&clrrad-pi/2<1e-7)
	//If collision is detected or the bullet flys out of screen, delete it.
	{
		++coll,scminus+=10000,Mult_BatClear();
		bullet[i].exist=false;
		bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
		bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
		bullet[i].dist=0;
		bullet[i].bullettype=0;
#ifndef NO_FREE
		if (bullet[i].bulletspr)free(bullet[i].bulletspr);
#endif
		return;
	}
	else
	{
		bullet[i].bulletspr->RenderEx(bullet[i].bulletpos.x+7.2,bullet[i].bulletpos.y+7.2,0,0.6*bullet[i].scale,0);
		if (dis<=16&&bullet[i].scollable)++semicoll,++dsmc,bullet[i].scollable=false,SCEffect_Attatch();
	}
}
//There is no need for ProcessBullet3() because they are in fact bullet2
void ProcessBullet4(int i)
{
	if (!bullet[i].exist||bullet[i].bullettype!=4)return;//If this bullet doesn't exist or is not of this type, do not render it.
	if (!DisablePlayer)
	{
		if (LOWFPS)
			bullet[i].whirem+=17;
		else
			++bullet[i].whirem;
		if ((yelattrib&&bullet[i].whirem>=bullet[i].yelbrk)||!yelattrib)
		{
			bullet[i].whirem=0;
			bullet[i].bulletdir.x=bullet[i].bulletpos.x-playerpos.x;
			bullet[i].bulletdir.y=bullet[i].bulletpos.y-playerpos.y;
			bullet[i].dist=bullet[i].bulletdir.x*bullet[i].bulletdir.x+bullet[i].bulletdir.y*bullet[i].bulletdir.y;
			bullet[i].dist=sqrt(bullet[i].dist);
		}
		if (LOWFPS)
		{
			bullet[i].bulletpos.x-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20*17;//Process bullet's x coor.
			bullet[i].bulletpos.y-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20*17;//Process bullet's y coor.
		}
		else
		{
			bullet[i].bulletpos.x-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20;//Process bullet's x coor.
			bullet[i].bulletpos.y-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20;//Process bullet's y coor.
		}
		//bullet[i].bulletpos.x-=bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20;//Process bullet's x coor.
		//bullet[i].bulletpos.y-=bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20;//Process bullet's y coor.
	}
	BulletEffect_Process(i);
	double dis=GetDist(bullet[i].bulletpos,playerpos);//Get distance between player and bullet
	if (dis<=6||bullet[i].bulletpos.x<=-10||bullet[i].bulletpos.x>=800||bullet[i].bulletpos.y<=-10||bullet[i].bulletpos.y>=600)
	//If collision is detected or the bullet flys out of screen, delete it.
	{
		if (dis<=6&&clrrange<1e-5&&clrrad-pi/2<1e-7)++coll,scminus+=10000,Mult_BatClear();
		bullet[i].exist=false;
		bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
		bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
		bullet[i].dist=0;
		bullet[i].bullettype=0;
#ifndef NO_FREE
		if (bullet[i].bulletspr)free(bullet[i].bulletspr);
#endif
	}
	else
	{
		bullet[i].bulletspr->RenderEx(bullet[i].bulletpos.x+7.2,bullet[i].bulletpos.y+7.2,0,0.6*bullet[i].scale,0);
		if (dis<=16&&bullet[i].scollable)++semicoll,++dsmc,bullet[i].scollable=false,SCEffect_Attatch();
	}
}
void ProcessBullet5(int i)
{
	if (!bullet[i].exist||bullet[i].bullettype!=5)return;//If this bullet doesn't exist or is not of this type, do not render it.
	if (!DisablePlayer)
	{
		if (LOWFPS)
		{
			bullet[i].bulletpos.x-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20*17;//Process bullet's x coor.
			bullet[i].bulletpos.y-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20*17;//Process bullet's y coor.
		}
		else
		{
			bullet[i].bulletpos.x-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20;//Process bullet's x coor.
			bullet[i].bulletpos.y-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20;//Process bullet's y coor.
		}
		//bullet[i].bulletpos.x-=bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20;//Process bullet's x coor.
		//bullet[i].bulletpos.y-=bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20;//Process bullet's y coor.
	}
	BulletEffect_Process(i);
	double dis=GetDist(bullet[i].bulletpos,playerpos);//Get distance between player and bullet
	if (dis<=6||bullet[i].bulletpos.x<=-10||bullet[i].bulletpos.x>=800||bullet[i].bulletpos.y<=-10||bullet[i].bulletpos.y>=600)
	//If collision is detected or the bullet flys out of screen, delete it.
	{
		if (dis<=6&&clrrange<1e-5&&clrrad-pi/2<1e-7)playerspeed*=0.9,playerslospeed*=0.9;
		bullet[i].exist=false;
		bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
		bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
		bullet[i].dist=0;
		bullet[i].bullettype=0;
#ifndef NO_FREE
		if (bullet[i].bulletspr)free(bullet[i].bulletspr);
#endif
	}
	else
	{
		bullet[i].bulletspr->RenderEx(bullet[i].bulletpos.x+7.2,bullet[i].bulletpos.y+7.2,0,0.6*bullet[i].scale,0);
	}
}
void ProcessBullet6(int i)
{
	if (!bullet[i].exist||bullet[i].bullettype!=6)return;//If this bullet doesn't exist or is not of this type, do not render it.
	if (!DisablePlayer)
	{
		if (LOWFPS)
		{
			bullet[i].bulletpos.x-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20*17;//Process bullet's x coor.
			bullet[i].bulletpos.y-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20*17;//Process bullet's y coor.
		}
		else
		{
			bullet[i].bulletpos.x-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20;//Process bullet's x coor.
			bullet[i].bulletpos.y-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20;//Process bullet's y coor.
		}
		//bullet[i].bulletpos.x-=bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20;//Process bullet's x coor.
		//bullet[i].bulletpos.y-=bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20;//Process bullet's y coor.
	}
	if (!LOWFPS)
	{
		if (bullet[i].redattrib==0)
			--bullet[i].redexplo;
		else
			bullet[i].redexplo-=2;
	}
	else
	{
		if (bullet[i].redattrib==0)
			bullet[i].redexplo-=17;
		else
			bullet[i].redexplo-=34;
	}
	if (bullet[i].redexplo<=0&&!DisableAllTower)
	{
		if (bullet[i].redattrib==0)
		{
			for (int j=1;j<=bullet[i].exp1;++j)
			{
				int pnt=CreateBullet6(bullet[i].bulletpos.x,bullet[i].bulletpos.y,bullet[i].bulletspeed,bullet[i].oriexplo,bullet[i].exp1,bullet[i].exp2,bullet[i].scale>1.5?true:false);
				//hge->Effect_PlayEx(snd,100,(bullet[i].bulletpos.x-400)/4);
				bullet[pnt].setdir(2*pi/(double)bullet[i].exp1*j);
				bullet[pnt].redattrib=1;
			}
		}
		else
		{
			for (int j=1;j<=bullet[i].exp2;++j)
				CreateBullet2(bullet[i].bulletpos.x,bullet[i].bulletpos.y,bullet[i].bulletspeed,2*pi/(double)bullet[i].exp2*j+clockrot,bullet[i].scale>1.5?true:false);
			clockrot+=deltarot;
			deltarot+=0.004363322313;
		}
		bullet[i].exist=false;
		bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
		bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
		bullet[i].dist=0;
		bullet[i].bullettype=0;
#ifndef NO_FREE
		if (bullet[i].bulletspr)free(bullet[i].bulletspr);
#endif
	}
	BulletEffect_Process(i);
	double dis=GetDist(bullet[i].bulletpos,playerpos);//Get distance between player and bullet
	if (dis<=6||bullet[i].bulletpos.x<=-10||bullet[i].bulletpos.x>=800||bullet[i].bulletpos.y<=-10||bullet[i].bulletpos.y>=600)
	//If collision is detected or the bullet flys out of screen, delete it.
	{
		if (dis<=6&&clrrange<1e-5&&clrrad-pi/2<1e-7)++coll,scminus+=10000,Mult_BatClear();
		bullet[i].exist=false;
		bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
		bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
		bullet[i].dist=0;
		bullet[i].bullettype=0;
#ifndef NO_FREE
		if (bullet[i].bulletspr)free(bullet[i].bulletspr);
#endif
	}
	else
	{
		bullet[i].bulletspr->RenderEx(bullet[i].bulletpos.x+7.2,bullet[i].bulletpos.y+7.2,0,0.6*bullet[i].scale,0);
		if (dis<=16&&bullet[i].scollable)++semicoll,++dsmc,bullet[i].scollable=false,SCEffect_Attatch();
	}
}
void ProcessBullet7(int i)
{
	if (!bullet[i].exist||bullet[i].bullettype!=7)return;//If this bullet doesn't exist or is not of this type, do not render it.
	if (!DisablePlayer)
	{
		if (LOWFPS)
		{
			bullet[i].bulletpos.x-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20*17;//Process bullet's x coor.
			bullet[i].bulletpos.y-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20*17;//Process bullet's y coor.
		}
		else
		{
			bullet[i].bulletpos.x-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20;//Process bullet's x coor.
			bullet[i].bulletpos.y-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20;//Process bullet's y coor.
		}
		//bullet[i].bulletpos.x-=bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20;//Process bullet's x coor.
		//bullet[i].bulletpos.y-=bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20;//Process bullet's y coor.
	}
	if (!LOWFPS)
	{
		if (bullet[i].redattrib==0)
			--bullet[i].redexplo;
		else
			bullet[i].redexplo-=2;
	}
	else
	{
		if (bullet[i].redattrib==0)
			bullet[i].redexplo-=17;
		else
			bullet[i].redexplo-=34;
	}
	if (bullet[i].redexplo<=0&&!DisableAllTower)
	{
		if (bullet[i].redattrib==0)
		{
			int pnt=CreateBullet7(bullet[i].bulletpos.x,bullet[i].bulletpos.y,bullet[i].bulletspeed,bullet[i].oriexplo,bullet[i].scale>1.5?true:false);
			//hge->Effect_PlayEx(snd,100,(bullet[i].bulletpos.x-400)/4);
			bullet[pnt].bulletdir.x=0;
			bullet[pnt].bulletdir.y=0;
			bullet[pnt].dist=1;
			bullet[pnt].redattrib=1;
			bullet[i].exist=false;
			bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
			bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
			bullet[i].dist=0;
			bullet[i].bullettype=0;
#ifndef NO_FREE
			if (bullet[i].bulletspr)free(bullet[i].bulletspr);
#endif
		}
		else
		{
			if (!LOWFPS)
				++bullet[i].whiskp;
			else
				bullet[i].whiskp+=17;
			if (bullet[i].whiskp>50)
			{
				for (int j=1;j<=whrcnt;++j)
				{
					int pnt=CreateBullet2(bullet[i].bulletpos.x,bullet[i].bulletpos.y,bullet[i].bulletspeed,j*2.0f*pi/(double)whrcnt+whirot,bullet[i].scale>1.5?true:false);
					if(level==6&&part==1)
					{
						bullet[pnt].limv=8;
						bullet[pnt].bulletaccel=0.005;
						bullet[pnt].bulletspeed=0;
					}
					if (level==6&&part>=2&&part<=11&&(j&1))
					{
						bullet[pnt].limv=5;
						bullet[pnt].bulletaccel=0.005;
						bullet[pnt].bulletspeed=0;
					}
				}
				whirot+=dwhirot;
				dwhirot+=0.004363322313;
				bullet[i].whiskp=0;
				--bullet[i].whirem;
			}
			if (bullet[i].whirem<=0)
			{
				bullet[i].exist=false;
				bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
				bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
				bullet[i].dist=0;
				bullet[i].bullettype=0;
#ifndef NO_FREE
				if (bullet[i].bulletspr)free(bullet[i].bulletspr);
#endif
			}
		}
	}
	BulletEffect_Process(i);
	double dis=GetDist(bullet[i].bulletpos,playerpos);//Get distance between player and bullet
	if (dis<=6||bullet[i].bulletpos.x<=-10||bullet[i].bulletpos.x>=800||bullet[i].bulletpos.y<=-10||bullet[i].bulletpos.y>=600)
	//If collision is detected or the bullet flys out of screen, delete it.
	{
		if (dis<=6&&clrrange<1e-5&&clrrad-pi/2<1e-7)++coll,scminus+=10000,Mult_BatClear();
		bullet[i].exist=false;
		bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
		bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
		bullet[i].dist=0;
		bullet[i].bullettype=0;
#ifndef NO_FREE
		delete bullet[i].bulletspr;
#endif
	}
	else
	{
		bullet[i].bulletspr->RenderEx(bullet[i].bulletpos.x+7.2,bullet[i].bulletpos.y+7.2,0,0.6*bullet[i].scale,0);
		if (dis<=16&&bullet[i].scollable)++semicoll,++dsmc,bullet[i].scollable=false,SCEffect_Attatch();
	}
}
void ProcessBullet8(int i)
{
	if (!bullet[i].exist||bullet[i].bullettype!=8)return;//If this bullet doesn't exist or is not of this type, do not render it.
	if (!DisablePlayer)
	{
		if (LOWFPS)
		{
			bullet[i].bulletpos.x-=bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20*17;//Process bullet's x coor.
			bullet[i].bulletpos.y-=bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20*17;//Process bullet's y coor.
		}
		else
		{
			bullet[i].bulletpos.x-=bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20;//Process bullet's x coor.
			bullet[i].bulletpos.y-=bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20;//Process bullet's y coor.
		}
	}
	BulletEffect_Process(i);
	double dis=GetDist(bullet[i].bulletpos,playerpos);//Get distance between player and bullet
	if (dis<=6||bullet[i].bulletpos.x<=-10||bullet[i].bulletpos.x>=800||bullet[i].bulletpos.y<=-10||bullet[i].bulletpos.y>=600)
	//If collision is detected or the bullet flys out of screen, delete it.
	{
		if (dis<=6&&clrrange<1e-5&&clrrad-pi/2<1e-7)++coll,scminus+=10000,Mult_BatClear();
		else
		{
			int cnt=rand()%4+2;if (Dis8ref)cnt=0;
			for (int ii=1;ii<=cnt;++ii)
				CreateBullet2(bullet[i].bulletpos.x,bullet[i].bulletpos.y,bullet[i].bulletspeed,rand()%100);
		}
		bullet[i].exist=false;
		bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
		bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
		bullet[i].dist=0;
		bullet[i].bullettype=0;
#ifndef NO_FREE
		if (bullet[i].bulletspr)free(bullet[i].bulletspr);
#endif
	}
	else
	{
		bullet[i].bulletspr->RenderEx(bullet[i].bulletpos.x+7.2,bullet[i].bulletpos.y+7.2,0,0.6*bullet[i].scale,0);
		if (dis<=16&&bullet[i].scollable)++semicoll,++dsmc,bullet[i].scollable=false,SCEffect_Attatch();
	}
}
void ProcessBullet9(int i)
{
	if (!bullet[i].exist||bullet[i].bullettype!=9)return;//If this bullet doesn't exist or is not of this type, do not render it.
	if (!DisablePlayer)
	{
		if (LOWFPS)
		{
			bullet[i].bulletpos.x-=bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20*17;//Process bullet's x coor.
			bullet[i].bulletpos.y-=bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20*17;//Process bullet's y coor.
			if (bullet[i].redattrib==0)
			{
				bullet[i].redexplo-=17;
				if (bullet[i].redexplo<=0)
				{
					for (int ii=0;ii<bullet[i].whicnt;++ii)
					{
						int pnt=CreateBullet9(bullet[i].bulletpos.x,bullet[i].bulletpos.y,bullet[i].bulletspeed,0,0,bullet[i].yelbrk);
						bullet[pnt].setdir(2*pi/(double)bullet[i].whicnt*ii);
						bullet[pnt].redattrib=1;
					}
					bullet[i].exist=false;
					bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
					bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
					bullet[i].dist=0;
					bullet[i].bullettype=0;
#ifndef NO_FREE
					if (bullet[i].bulletspr)free(bullet[i].bulletspr);
#endif
				}
			}
			if (bullet[i].redattrib==1)
			{
				bullet[i].yelbrk-=17;
				if (bullet[i].yelbrk<=0)
				{
					bullet[i].redir(playerpos);
					bullet[i].redattrib=2;
				}
			}
		}
		else
		{
			bullet[i].bulletpos.x-=bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20;//Process bullet's x coor.
			bullet[i].bulletpos.y-=bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20;//Process bullet's y coor.
			if (bullet[i].redattrib==0)
			{
				--bullet[i].redexplo;
				if (bullet[i].redexplo<=0)
				{
					for (int ii=0;ii<bullet[i].whicnt;++ii)
					{
						int pnt=CreateBullet9(bullet[i].bulletpos.x,bullet[i].bulletpos.y,bullet[i].bulletspeed,0,0,bullet[i].yelbrk);
						bullet[pnt].setdir(2*pi/(double)bullet[i].whicnt*ii);
						bullet[pnt].redattrib=1;
					}
					bullet[i].exist=false;
					bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
					bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
					bullet[i].dist=0;
					bullet[i].bullettype=0;
#ifndef NO_FREE
					if (bullet[i].bulletspr)free(bullet[i].bulletspr);
#endif
				}
			}
			if (bullet[i].redattrib==1)
			{
				--bullet[i].yelbrk;
				if (bullet[i].yelbrk<=0)
				{
					bullet[i].redir(playerpos);
					bullet[i].redattrib=2;
				}
			}
		}
	}
	BulletEffect_Process(i);
	double dis=GetDist(bullet[i].bulletpos,playerpos);//Get distance between player and bullet
	if (dis<=6||bullet[i].bulletpos.x<=-10||bullet[i].bulletpos.x>=800||bullet[i].bulletpos.y<=-10||bullet[i].bulletpos.y>=600)
	//If collision is detected or the bullet flys out of screen, delete it.
	{
		if (dis<=6&&clrrange<1e-5&&clrrad-pi/2<1e-7)++coll,scminus+=10000,Mult_BatClear();
		bullet[i].exist=false;
		bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
		bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
		bullet[i].dist=0;
		bullet[i].bullettype=0;
#ifndef NO_FREE
		if (bullet[i].bulletspr)free(bullet[i].bulletspr);
#endif
	}
	else
	{
		bullet[i].bulletspr->RenderEx(bullet[i].bulletpos.x+7.2,bullet[i].bulletpos.y+7.2,0,0.6*bullet[i].scale,0);
		if (dis<=16&&bullet[i].scollable)++semicoll,++dsmc,bullet[i].scollable=false,SCEffect_Attatch();
	}
}
void ProcessBullet255(int i)
{
	if (!bullet[i].exist||bullet[i].bullettype!=255)return;//If this bullet doesn't exist or is not of this type, do not render it.
	if (!DisablePlayer)
	{
		bullet[i].bulletspeed=10;
		bullet[i].bulletdir.x=bullet[i].bulletpos.x-playerpos.x;
		bullet[i].bulletdir.y=bullet[i].bulletpos.y-playerpos.y;
		bullet[i].dist=bullet[i].bulletdir.x*bullet[i].bulletdir.x+bullet[i].bulletdir.y*bullet[i].bulletdir.y;
		bullet[i].dist=sqrt(bullet[i].dist);
		if (LOWFPS)
		{
			bullet[i].bulletpos.x-=bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20*17;//Process bullet's x coor.
			bullet[i].bulletpos.y-=bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20*17;//Process bullet's y coor.
		}
		else
		{
			bullet[i].bulletpos.x-=bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20;//Process bullet's x coor.
			bullet[i].bulletpos.y-=bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20;//Process bullet's y coor.
		}
		//bullet[i].bulletpos.x-=bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20;//Process bullet's x coor.
		//bullet[i].bulletpos.y-=bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20;//Process bullet's y coor.
	}
	double dis=GetDist(bullet[i].bulletpos,playerpos);//Get distance between player and bullet
	if (dis<=6||bullet[i].bulletpos.x<=-10||bullet[i].bulletpos.x>=800||bullet[i].bulletpos.y<=-10||bullet[i].bulletpos.y>=600)
	//If collision is detected or the bullet flys out of screen, delete it.
	{
		bullet[i].exist=false;
		bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
		bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
		bullet[i].dist=0;
		bullet[i].bullettype=0;
#ifndef NO_FREE
		if (bullet[i].bulletspr)free(bullet[i].bulletspr);
#endif
	}
	else
	{
		bullet[i].bulletspr->RenderEx(bullet[i].bulletpos.x,bullet[i].bulletpos.y,0,0.5,0);
	}
}
int CreateTower1(double x,double y,int timer,double bs,double offset=0,bool eff=false)//This returns the created tower number.
{
	int i;
	if (towcnt==0)
		towcnt=i=1;
	else
	{
		for (i=1;i<=towcnt;++i)
		{
			if (!tower[i].exist)break;
			if (abs(tower[i].towerpos.x-x)<=zero&&abs(tower[i].towerpos.y-y)<=zero)
			{
				return i;
			}
		}
		if (i>towcnt)
			towcnt=i;
	}
	tower[i].exist=true;
	tower[i].towertype=1;
	tower[i].bulletspeed=bs;
	tower[i].towertimer=tower[i].curtimer=timer;
	tower[i].towerpos.x=x,tower[i].towerpos.y=y;
	tower[i].towerspr=new hgeSprite(SprSheet,0,136,44,44);
	tower[i].towerspr->SetColor(0x80FFFFFF);
	tower[i].effect=eff;
	tower[i].offset=offset;
	tower[i].towerspr->SetHotSpot(22,22);
	return i;
}
int CreateTower2(double x,double y,int timer,double bs,bool eff=false)//This returns the created tower number.
{
	int i;
	if (towcnt==0)
		towcnt=i=1;
	else
	{
		for (i=1;i<=towcnt;++i)
		{
			if (!tower[i].exist)break;
			if (abs(tower[i].towerpos.x-x)<=zero&&abs(tower[i].towerpos.y-y)<=zero)return i;
		}
		if (i>towcnt)
			towcnt=i;
	}
	tower[i].exist=true;
	tower[i].towertype=2;
	tower[i].bulletspeed=bs;
	tower[i].towertimer=tower[i].curtimer=timer;
	tower[i].towerpos.x=x,tower[i].towerpos.y=y;
	tower[i].towerspr=new hgeSprite(SprSheet,0,48,44,44);
	tower[i].towerspr->SetHotSpot(22,22);
	tower[i].towerspr->SetColor(0x80FFFFFF);
	tower[i].effect=eff;
	return i;
}
int CreateTower3(double x,double y,int timer,double bs,int t3t,bool eff=false)//This returns the created tower number.
{
	int i;
	if (towcnt==0)
		towcnt=i=1;
	else
	{
		for (i=1;i<=towcnt;++i)
		{
			if (!tower[i].exist)break;
			if (abs(tower[i].towerpos.x-x)<=zero&&abs(tower[i].towerpos.y-y)<=zero)return i;
		}
		if (i>towcnt)
			towcnt=i;
	}
	tower[i].exist=true;
	tower[i].towertype=3;
	tower[i].bulletspeed=bs;
	tower[i].t3t=t3t;
	tower[i].towertimer=tower[i].curtimer=timer;
	tower[i].towerpos.x=x,tower[i].towerpos.y=y;
	tower[i].towerspr=new hgeSprite(SprSheet,0,48,44,44);
	tower[i].towerspr->SetHotSpot(22,22);
	tower[i].towerspr->SetColor(0x80FFFFFF);
	tower[i].effect=eff;
	return i;
}
int CreateTower3_fixeddir(double x,double y,int timer,double bs,double rad,bool eff=false)//This returns the created tower number.
{
	int i;
	if (towcnt==0)
		towcnt=i=1;
	else
	{
		for (i=1;i<=towcnt;++i)
		{
			if (!tower[i].exist)break;
			if (abs(tower[i].towerpos.x-x)<=zero&&abs(tower[i].towerpos.y-y)<=zero)return i;
		}
		if (i>towcnt)
			towcnt=i;
	}
	tower[i].exist=true;
	tower[i].towertype=3;
	tower[i].bulletspeed=bs;
	tower[i].offset=rad;tower[i].t3t=999;
	tower[i].towertimer=tower[i].curtimer=timer;
	tower[i].towerpos.x=x,tower[i].towerpos.y=y;
	tower[i].towerspr=new hgeSprite(SprSheet,0,48,44,44);
	tower[i].towerspr->SetHotSpot(22,22);
	tower[i].towerspr->SetColor(0x80FFFFFF);
	tower[i].effect=eff;
	return i;
}
int CreateTower4(double x,double y,int timer,double bs,int yelbrk=0,bool eff=false)//This returns the created tower number.
{
	int i;
	if (towcnt==0)
		towcnt=i=1;
	else
	{
		for (i=1;i<=towcnt;++i)
		{
			if (!tower[i].exist)break;
			if (abs(tower[i].towerpos.x-x)<=zero&&abs(tower[i].towerpos.y-y)<=zero)
			{
				return i;
			}
		}
		if (i>towcnt)
			towcnt=i;
	}
	tower[i].exist=true;
	tower[i].towertype=4;
	tower[i].bulletspeed=bs;
	tower[i].towertimer=tower[i].curtimer=timer;
	tower[i].towerpos.x=x,tower[i].towerpos.y=y;
	tower[i].towerspr=new hgeSprite(SprSheet,180,24,44,44);
	tower[i].towerspr->SetHotSpot(22,22);
	tower[i].towerspr->SetColor(0x80FFFFFF);
	tower[i].yelbrk=yelbrk;
	tower[i].effect=eff;
	return i;
}
int CreateTower5(double x,double y,int timer,double bs,bool eff=false)//This returns the created tower number.
{
	int i;
	if (towcnt==0)
		towcnt=i=1;
	else
	{
		for (i=1;i<=towcnt;++i)
		{
			if (!tower[i].exist)break;
			if (abs(tower[i].towerpos.x-x)<=zero&&abs(tower[i].towerpos.y-y)<=zero)
			{
				return i;
			}
		}
		if (i>towcnt)
			towcnt=i;
	}
	tower[i].exist=true;
	tower[i].towertype=5;
	tower[i].bulletspeed=bs;
	tower[i].towertimer=tower[i].curtimer=timer;
	tower[i].towerpos.x=x,tower[i].towerpos.y=y;
	tower[i].towerspr=new hgeSprite(SprSheet,48,24,44,44);
	tower[i].towerspr->SetHotSpot(22,22);
	tower[i].towerspr->SetColor(0x80FFFFFF);
	tower[i].effect=eff;
	return i;
}
int CreateTower6(double x,double y,int timer,double bs,int redexplo,int exp1=8,int exp2=12,bool eff=false)//This returns the created tower number.
{
	int i;
	if (towcnt==0)
		towcnt=i=1;
	else
	{
		for (i=1;i<=towcnt;++i)
		{
			if (!tower[i].exist)break;
			if (abs(tower[i].towerpos.x-x)<=zero&&abs(tower[i].towerpos.y-y)<=zero)
			{
				return i;
			}
		}
		if (i>towcnt)
			towcnt=i;
	}
	tower[i].exist=true;
	tower[i].towertype=6;
	tower[i].bulletspeed=bs;
	tower[i].redexplo=redexplo;
	tower[i].towertimer=tower[i].curtimer=timer;
	tower[i].towerpos.x=x,tower[i].towerpos.y=y;
	tower[i].exp1=exp1;tower[i].exp2=exp2;
	tower[i].towerspr=new hgeSprite(SprSheet,92,24,44,44);
	tower[i].towerspr->SetHotSpot(22,22);
	tower[i].towerspr->SetColor(0x80FFFFFF);
	tower[i].effect=eff;
	return i;
}
int CreateTower7(double x,double y,int timer,double bs,int redexplo,bool eff=false)//This returns the created tower number.
{
	int i;
	if (towcnt==0)
		towcnt=i=1;
	else
	{
		for (i=1;i<=towcnt;++i)
		{
			if (!tower[i].exist)break;
			if (abs(tower[i].towerpos.x-x)<=zero&&abs(tower[i].towerpos.y-y)<=zero)
			{
				return i;
			}
		}
		if (i>towcnt)
			towcnt=i;
	}
	tower[i].exist=true;
	tower[i].towertype=7;
	tower[i].bulletspeed=bs;
	tower[i].redexplo=redexplo;
	tower[i].towertimer=tower[i].curtimer=timer;
	tower[i].towerpos.x=x,tower[i].towerpos.y=y;
	tower[i].towerspr=new hgeSprite(SprSheet,136,24,44,44);
	tower[i].towerspr->SetHotSpot(22,22);
	tower[i].towerspr->SetColor(0x80FFFFFF);
	tower[i].whicnt=whicnt;
	tower[i].effect=eff;
	return i;
}
int CreateTower8(double x,double y,int timer,double bs,int timer2,int scnt,bool eff=false)
{
	int i;
	if (towcnt==0)
		towcnt=i=1;
	else
	{
		for (i=1;i<=towcnt;++i)
		{
			if (!tower[i].exist)break;
			if (abs(tower[i].towerpos.x-x)<=zero&&abs(tower[i].towerpos.y-y)<=zero)
			{
				return i;
			}
		}
		if (i>towcnt)
			towcnt=i;
	}
	tower[i].exist=true;
	tower[i].towertype=8;
	tower[i].bulletspeed=bs;
	tower[i].towertimer=tower[i].curtimer=timer;
	tower[i].towertimer2=tower[i].curtimer2=timer2;
	tower[i].shotcount=tower[i].curshotcount=scnt;
	tower[i].dblstate=false;
	tower[i].towerpos.x=x,tower[i].towerpos.y=y;
	tower[i].towerspr=new hgeSprite(SprSheet,0,92,44,44);
	tower[i].towerspr->SetColor(0x80FFFFFF);
	tower[i].effect=eff;
	tower[i].towerspr->SetHotSpot(22,22);
	return i;
}
int CreateTower9(double x,double y,int timer,double bs,int explo,int cnt,int brk,bool eff=false)
{
	int i;
	if (towcnt==0)
		towcnt=i=1;
	else
	{
		for (i=1;i<=towcnt;++i)
		{
			if (!tower[i].exist)break;
			if (abs(tower[i].towerpos.x-x)<=zero&&abs(tower[i].towerpos.y-y)<=zero)
			{
				return i;
			}
		}
		if (i>towcnt)
			towcnt=i;
	}
	tower[i].exist=true;
	tower[i].towertype=9;
	tower[i].bulletspeed=bs;
	tower[i].redexplo=explo;
	tower[i].whicnt=cnt;
	tower[i].yelbrk=brk;
	tower[i].towertimer=tower[i].curtimer=timer;
	tower[i].towerpos.x=x,tower[i].towerpos.y=y;
	tower[i].towerspr=new hgeSprite(SprSheet,0,180,44,44);
	tower[i].towerspr->SetColor(0x80FFFFFF);
	tower[i].effect=eff;
	tower[i].towerspr->SetHotSpot(22,22);
	return i;
}
void ProcessTower1()
{
	for (int i=1;i<=towcnt;++i)
	{
		if (!tower[i].exist||tower[i].towertype!=1)continue;
		tower[i].towerspr->RenderEx(tower[i].towerpos.x+7.2,tower[i].towerpos.y+7.2,0,0.545);
		if (DisableAllTower)continue;
		if (LOWFPS)
			tower[i].curtimer-=17;
		else
			--tower[i].curtimer;
		if (tower[i].curtimer<=0)
		{
			tower[i].curtimer=tower[i].towertimer;
			if (fabs(tower[i].offset)>1e-7)
			{
				double trad=atan2l(tower[i].towerpos.y-playerpos.y,tower[i].towerpos.x-playerpos.x)+tower[i].offset;
				CreateBullet2(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,trad,tower[i].effect);
			}
			else
			CreateBullet1(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,tower[i].effect);
		}
	}
}
void ProcessTower2()
{
	for (int i=1;i<=towcnt;++i)
	{
		if (!tower[i].exist||tower[i].towertype!=2)continue;
		tower[i].towerspr->RenderEx(tower[i].towerpos.x+7.2,tower[i].towerpos.y+7.2,0,0.545);
		if (DisableAllTower)continue;
		if (LOWFPS)
			tower[i].curtimer-=17;
		else
			--tower[i].curtimer;
		if (tower[i].curtimer<=0)
		{
			tower[i].curtimer=tower[i].towertimer;
			for (int j=1;j<=12;++j)
				CreateBullet2(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,j*0.5236+clockrot,tower[i].effect);
			clockrot+=deltarot;
			deltarot+=deltadelta;
		}
	}
}
void ProcessTower3()
{
	for (int i=1;i<=towcnt;++i)
	{
		if (!tower[i].exist||tower[i].towertype!=3)continue;
		tower[i].towerspr->RenderEx(tower[i].towerpos.x+7.2,tower[i].towerpos.y+7.2,0,0.545);
		if (DisableAllTower)continue;
		if (LOWFPS)
			tower[i].curtimer-=17;
		else
			--tower[i].curtimer;
		if (tower[i].curtimer<=0)
		{
			tower[i].curtimer=tower[i].towertimer;
			if (tower[i].t3t==999)
				CreateBullet2(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,tower[i].offset,tower[i].effect);
			if (tower[i].t3t==0)
				for (int j=1;j<=12;++j)
					CreateBullet3(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,j,tower[i].effect);
			if (tower[i].t3t==1)
			{
				CreateBullet3(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,12,tower[i].effect);
				CreateBullet3(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,3,tower[i].effect);
				CreateBullet3(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,6,tower[i].effect);
				CreateBullet3(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,9,tower[i].effect);
			}
			if (tower[i].t3t==4)
			{
				CreateBullet2(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,pi/4.0f,tower[i].effect);
				CreateBullet2(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,pi*3/4.0f,tower[i].effect);
				CreateBullet2(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,pi*5/4.0f,tower[i].effect);
				CreateBullet2(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,pi*7/4.0f,tower[i].effect);
			}
			if (tower[i].t3t==5)
			{
				CreateBullet2(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,pi/4.0f,tower[i].effect);
				CreateBullet2(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,pi*3/4.0f,tower[i].effect);
				CreateBullet2(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,pi*5/4.0f,tower[i].effect);
				CreateBullet2(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,pi*7/4.0f,tower[i].effect);
				CreateBullet2(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,0,tower[i].effect);
				CreateBullet2(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,pi/2.0f,tower[i].effect);
				CreateBullet2(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,pi,tower[i].effect);
				CreateBullet2(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,pi*3/2.0f,tower[i].effect);
			}
			if (tower[i].t3t==2)
			{
				if (rand()%2==0)
					CreateBullet3(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,12,tower[i].effect);
				else
					CreateBullet3(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,6,tower[i].effect);
			}
			if (tower[i].t3t==3)
			{
				if (rand()%2==0)
					CreateBullet3(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,3,tower[i].effect);
				else
					CreateBullet3(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,9,tower[i].effect);
			}
		}
	}
}
void ProcessTower4()
{
	for (int i=1;i<=towcnt;++i)
	{
		if (!tower[i].exist||tower[i].towertype!=4)continue;
		tower[i].towerspr->RenderEx(tower[i].towerpos.x+7.2,tower[i].towerpos.y+7.2,0,0.545);
		if (DisableAllTower)continue;
		if (LOWFPS)
			tower[i].curtimer-=17;
		else
			--tower[i].curtimer;
		if (tower[i].curtimer<=0)
		{
			tower[i].curtimer=tower[i].towertimer;
			CreateBullet4(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,tower[i].yelbrk,tower[i].effect);
		}
	}
}
void ProcessTower5()
{
	for (int i=1;i<=towcnt;++i)
	{
		if (!tower[i].exist||tower[i].towertype!=5)continue;
		tower[i].towerspr->RenderEx(tower[i].towerpos.x+7.2,tower[i].towerpos.y+7.2,0,0.545);
		if (DisableAllTower)continue;
		if (LOWFPS)
			tower[i].curtimer-=17;
		else
			--tower[i].curtimer;
		if (tower[i].curtimer<=0)
		{
			tower[i].curtimer=tower[i].towertimer;
			CreateBullet5(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,tower[i].effect);
		}
	}
}
void ProcessTower6()
{
	for (int i=1;i<=towcnt;++i)
	{
		if (!tower[i].exist||tower[i].towertype!=6)continue;
		tower[i].towerspr->RenderEx(tower[i].towerpos.x+7.2,tower[i].towerpos.y+7.2,0,0.545);
		if (DisableAllTower)continue;
		if (LOWFPS)
			tower[i].curtimer-=17;
		else
			--tower[i].curtimer;
		if (tower[i].curtimer<=0)
		{
			tower[i].curtimer=tower[i].towertimer;
			CreateBullet6(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,tower[i].redexplo,tower[i].exp1,tower[i].exp2,tower[i].effect);
		}
	}
}
void ProcessTower7()
{
	for (int i=1;i<=towcnt;++i)
	{
		if (!tower[i].exist||tower[i].towertype!=7)continue;
		tower[i].towerspr->RenderEx(tower[i].towerpos.x+7.2,tower[i].towerpos.y+7.2,0,0.545);
		if (DisableAllTower)continue;
		if (LOWFPS)
			tower[i].curtimer-=17;
		else
			--tower[i].curtimer;
		if (tower[i].curtimer<=0)
		{
			tower[i].curtimer=tower[i].towertimer;
			CreateBullet7(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,tower[i].redexplo,tower[i].effect);
		}
	}
}
void ProcessTower8()
{
	for (int i=1;i<=towcnt;++i)
	{
		if (!tower[i].exist||tower[i].towertype!=8)continue;
		tower[i].towerspr->RenderEx(tower[i].towerpos.x+7.2,tower[i].towerpos.y+7.2,0,0.545);
		if (DisableAllTower)continue;
		if (!tower[i].dblstate)
		{
			if (LOWFPS)
				tower[i].curtimer-=17;
			else
				--tower[i].curtimer;
			if (tower[i].curtimer<=0)
			{
				tower[i].curtimer=tower[i].towertimer;
				tower[i].dblstate=true;
				tower[i].curtimer2=tower[i].towertimer2;
				tower[i].curshotcount=tower[i].shotcount;
				if (!Dis8ref)BTarg.TargShow(),BTarg.targpos=playerpos;
			}
		}
		else
		{
			if (LOWFPS)
				tower[i].curtimer2-=17;
			else
				--tower[i].curtimer2;
			if (tower[i].curtimer2<=0)
			{
				if (tower[i].curshotcount<=0)
				{
					tower[i].curtimer=tower[i].towertimer;
					tower[i].dblstate=false;
					tower[i].curtimer2=tower[i].towertimer2;
					tower[i].curshotcount=tower[i].shotcount;
					if (!Dis8ref)BTarg.TargHide();
					continue;
				}
				int pnt=CreateBullet8(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,tower[i].effect);
				if (Dis8ref)
				if (tower[i].towerpos.y<300)
				DirectBullet(bullet[pnt],-pi/2);else DirectBullet(bullet[pnt],pi/2);
				if (tower[i].curshotcount==tower[i].shotcount)
					tower[i].tdir=bullet[pnt].bulletdir;
				else
				{
					bullet[pnt].bulletdir=tower[i].tdir;
					bullet[pnt].dist=bullet[pnt].bulletdir.x*bullet[pnt].bulletdir.x+bullet[pnt].bulletdir.y*bullet[pnt].bulletdir.y;
					bullet[pnt].dist=sqrt(bullet[pnt].dist);
				}
				tower[i].curtimer2=tower[i].towertimer2;
				--tower[i].curshotcount;
			}
		}
	}
}
void ProcessTower9()
{
	for (int i=1;i<=towcnt;++i)
	{
		if (!tower[i].exist||tower[i].towertype!=9)continue;
		tower[i].towerspr->RenderEx(tower[i].towerpos.x+7.2,tower[i].towerpos.y+7.2,0,0.545);
		if (DisableAllTower)continue;
		if (LOWFPS)
			tower[i].curtimer-=17;
		else
			--tower[i].curtimer;
		if (tower[i].curtimer<=0)
		{
			tower[i].curtimer=tower[i].towertimer;
			CreateBullet9(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,tower[i].redexplo,tower[i].whicnt,tower[i].yelbrk,tower[i].effect);
			//hge->Effect_PlayEx(snd,100,(tower[i].towerpos.x-400)/4);
		}
	}
}
//Laser Implementation
int Lasercnt;
class Laser
{
private:
	hgeDistortionMesh *graphic;
	int Res;
	vector2d data1[MaxRes],data2[MaxRes];
public:
	bool EnableColl;
	vector2d RenCtr;
	int collbrk,scollbrk;
	void SetRes(int _Res){Res=_Res;}
	void Render()
	{
		graphic->Render(RenCtr.x,RenCtr.y);
	}
	void Init(int _Res=0)
	{
		graphic=new hgeDistortionMesh(MaxRes,2);
		graphic->Clear(0x00000000);
		collbrk=scollbrk=0;
		Res=_Res;
		EnableColl=false;
	}
	void SetTexture(HTEXTURE Texture,double x=0.0f,double y=0.0f,double w=0.0f,double h=0.0f)
	{
		graphic->SetTexture(Texture);
		if (x||y||w||h)graphic->SetTextureRect(x,y,w,h);
	}
	void Setdata(int x,vector2d pa,vector2d pb,DWORD color)
	{
		data1[x]=pa;data2[x]=pb;
		graphic->SetDisplacement(x,0,data1[x].x,data1[x].y,HGEDISP_TOPLEFT);
		graphic->SetDisplacement(x,1,data2[x].x,data2[x].y,HGEDISP_TOPLEFT);
		graphic->SetColor(x,0,color);graphic->SetColor(x,1,color);
	}
	bool InsPoint(vector2d pa,vector2d pb,DWORD color)
	{
		if (Res==MaxRes)return false;
		data1[++Res-1]=pa;data2[Res-1]=pb;
		graphic->SetDisplacement(Res-1,0,data1[Res].x,data1[Res].y,HGEDISP_TOPLEFT);
		graphic->SetDisplacement(Res-1,1,data2[Res].x,data2[Res].y,HGEDISP_TOPLEFT);
		graphic->SetColor(Res-1,0,color);graphic->SetColor(Res-1,1,color);
		return true;
	}
	void RemoveLastPoint(DWORD color)
	{
		for (int i=2;i<=Res;++i)
		{
			data1[i-1]=data1[i];
			data2[i-1]=data2[i];
			graphic->SetDisplacement(i-1,0,data1[i-1].x,data1[i-1].y,HGEDISP_TOPLEFT);
			graphic->SetDisplacement(i-1,1,data2[i-1].x,data2[i-1].y,HGEDISP_TOPLEFT);
			graphic->SetColor(i-1,0,color);graphic->SetColor(i-1,1,color);
		}
		graphic->SetDisplacement(Res-1,0,data1[Res].x,data1[Res].y,HGEDISP_TOPLEFT);
		graphic->SetDisplacement(Res-1,1,data2[Res].x,data2[Res].y,HGEDISP_TOPLEFT);
		graphic->SetColor(Res-1,0,color);graphic->SetColor(Res-1,1,color);
		--Res;
	}
	double GetDist()
	{
		double res=99999.9999f;
		double tres=99999.9999f;
		//Initalize: 999'99.9'999
		for (int i=0;i<Res-1;++i)
		{
			hgeRect box;memset(&box,0,sizeof(box));
			box.x1=box.x2=data1[i].x+RenCtr.x,box.y1=box.y2=data1[i].y+RenCtr.y;
			//box.Encapsulate(data1[i].x+RenCtr.x,data1[i].y+RenCtr.y);
			box.Encapsulate(data1[i+1].x+RenCtr.x,data1[i+1].y+RenCtr.y);
			{
				//Debugging collision box
				hgeSprite colbox=*(new hgeSprite(0,0,0,0,0));
				colbox.SetColor(0x0FFFFFFF);
				colbox.RenderStretch(box.x1,box.y1,box.x2,box.y2);
			}
			if (box.TestPoint(playerpos.x,playerpos.y))
			{
				double dx=data1[i].x-data1[i+1].x,dy=data1[i].y-data1[i+1].y;
				double a,b,c;
				if (abs(dx)<1e-4)
				{
					a=1;b=0;c=data1[i].x+RenCtr.x;
				}
				else
				{
					b=1;a=-dy/dx;c=(data1[i].x+RenCtr.x)*a-data1[i].y-RenCtr.y;
				}
				tres=abs(a*playerpos.x+b*playerpos.y+c)/sqrt(sqr(a)+sqr(b));
			}
			else
			{
				vector2d t0=data1[i];data1[i].x+=RenCtr.x,data1[i].y+=RenCtr.y;
				tres=::GetDist(playerpos,t0);
				vector2d t1=data1[i+1];data1[i+1].x+=RenCtr.x,data1[i+1].y+=RenCtr.y;
				tres=tres<(::GetDist(playerpos,t1))?tres:(::GetDist(playerpos,t1));
				data1[i]=t0;data1[i+1]=t1;
			}
			if (tres<res)res=tres;
		}
		return res;
	}
	void Process()
	{
		Render();
		if (EnableColl)
		{
			if (GetDist()<8.0f&&clrrange<1e-5&&clrrad-pi/2<1e-7)
			{
				if (!LOWFPS)++collbrk;else collbrk+=17;
				if (collbrk>200)
					++coll,scminus+=10000,collbrk=0,Mult_BatClear();
			}
		}
		if (GetDist()<16.0f)
		{
			if (!LOWFPS)++scollbrk;else scollbrk+=17;
				if (scollbrk>200)
					++semicoll,scollbrk=0,++dsmc,SCEffect_Attatch();
		}

	}
}laser[200];
void ProcessLaser()
{
	//Well, I only cares rendering and collision checking..
	//Change laser data in the level code.
	for (int i=1;i<=Lasercnt;++i)laser[i].Process();
}
//Special bullet creation and processing code for some level...
void CreateBullet2(Bullet &Tar,double x,double y,double bs,double rad,bool eff=false)
{
	Tar.exist=true;
	Tar.bullettype=2;
	Tar.bulletpos.x=x;
	Tar.bulletpos.y=y;
	Tar.bulletdir.x=cos(rad);
	Tar.bulletdir.y=sin(rad);
	Tar.bulletspeed=bs;
	Tar.scollable=true;
	Tar.bulletaccel=0;
	Tar.bulletspr=new hgeSprite(SprSheet,0,0,24,24);
	Tar.bulletspr->SetColor(0x80FFFFFF);
	Tar.bulletspr->SetHotSpot(12,12);
}
void ProcessBullet2(Bullet &xbul)
{
	if (xbul.bulletspeed<xbul.limv)xbul.bulletspeed+=xbul.bulletaccel;
	if (!xbul.exist||xbul.bullettype!=2)return;//If this bullet doesn't exist or is not of this type, do not render it.
	if (!xbul.dist)xbul.dist=1;
	if (LOWFPS)
	xbul.bulletpos.x-=xbul.bulletspeed*(xbul.bulletdir.x/xbul.dist)/20*17,//Process bullet's x coor.
	xbul.bulletpos.y-=xbul.bulletspeed*(xbul.bulletdir.y/xbul.dist)/20*17;//Process bullet's y coor.
	else
	xbul.bulletpos.x-=xbul.bulletspeed*(xbul.bulletdir.x/xbul.dist)/20,//Process bullet's x coor.
	xbul.bulletpos.y-=xbul.bulletspeed*(xbul.bulletdir.y/xbul.dist)/20;//Process bullet's y coor.
	double dis=GetDist(xbul.bulletpos,playerpos);
	/*if (xbul.bulletpos.x<=-100||xbul.bulletpos.x>=900||xbul.bulletpos.y<=-100||xbul.bulletpos.y>=700)
	{
		xbul.exist=false;
		xbul.bulletpos.x=xbul.bulletpos.y=0;
		xbul.bulletdir.x=xbul.bulletdir.y=0;
		xbul.bullettype=0;
	}*/
	if (dis<=6&&clrrange<1e-5&&clrrad-pi/2<1e-7)
	//If collision is detected or the bullet flys out of screen, delete it.
	{
		++coll,scminus+=10000,Mult_BatClear();
		return;
	}
	if (dis<=16&&xbul.scollable)++semicoll,++dsmc,xbul.scollable=false,SCEffect_Attatch();
	xbul.bulletspr->RenderEx(xbul.bulletpos.x+7.2,xbul.bulletpos.y+7.2,0,0.5);
}
//"Noname"
class Noname01dotpas
{
private:
	Laser untitledlas;
	Bullet untitledbul;
	double x,y,range1,range2;
	double r1lim,r2lim;
	bool las,reverse,done;
	int PMod,pos,boomlim;
	DWORD color;
public:
	bool Exist()
	{
		return (fabs(y)>1e-6);
	}
	void Init(int x,int pmd,double _r1lim,double _r2lim,int _boomlim,DWORD _color)
	{
		untitledlas.Init();
		this->x=x,this->y=2;color=_color;
		CreateBullet2(untitledbul,x,2,0,3*pi/2);
		untitledbul.bulletaccel=0.0001;
		untitledbul.limv=1;
		las=false;
		reverse=false;
		done=false;
		PMod=pmd;
		r1lim=_r1lim;r2lim=_r2lim;boomlim=_boomlim;
		if (rand()%100>boomlim)
			pos=rand()%600;
		else
			pos=999;
		untitledlas.SetTexture(SprSheet,0,264,248,8);
	}
	void Process()
	{
		if (!las)
			ProcessBullet2(untitledbul),x=untitledbul.bulletpos.x,y=untitledbul.bulletpos.y;
		else
			untitledlas.EnableColl=true,
			untitledlas.Process();
		if (!untitledbul.exist)y=-1;
		if (y>pos&&!done&&!las)
		{
			las=true;
			range1=range2=2;
			for (int i=0;i<60;++i)
			{
				double trad=(i/60.0f)*pi*2;
				vector2d a,b;
				a.x=cos(trad)*range1;a.y=sin(trad)*range1;
				b.x=cos(trad)*(range1-10);b.y=sin(trad)*(range1-10);
				untitledlas.InsPoint(a,b,color);
			}
			int i=60;
			double trad=1.0f/60*pi*2;
			vector2d a,b;
			if (!(i%PMod))
			{
				a.x=cos(trad)*range2;a.y=sin(trad)*range2;
				b.x=cos(trad)*(range2-10);b.y=sin(trad)*(range2-10);
			}
			else
			{
				a.x=cos(trad)*range1;a.y=sin(trad)*range1;
				b.x=cos(trad)*(range1-10);b.y=sin(trad)*(range1-10);
			}
			for (int i=60;i<MaxRes;++i)untitledlas.InsPoint(a,b,color);
		}
		if (las)
		{
			untitledlas.RenCtr=vector2d(x,y);
			untitledlas.Render();
			if (!reverse)
			{
				if (range1<r1lim)range1+=0.2,range2=range1;
				if (range1>=r1lim&&range2<r2lim)range2+=0.1;
				if (range2>=r2lim)reverse=true;
			}
			else
			{
				if (range2>=r1lim)range2-=0.1;else range1-=0.2,range2=range1;
				if (range1<=2)las=false,done=true;
			}
			for (int i=0;i<60;++i)
			{
				double trad=(i/60.0f)*pi*2;
				vector2d a,b;
				if (!(i%PMod))
				{
					a.x=cos(trad)*range2;a.y=sin(trad)*range2;
					b.x=cos(trad)*(range2-10);b.y=sin(trad)*(range2-10);
				}
				else
				{
					a.x=cos(trad)*range1;a.y=sin(trad)*range1;
					b.x=cos(trad)*(range1-10);b.y=sin(trad)*(range1-10);
				}
				untitledlas.Setdata(i,a,b,color);
			}
			int i=60;
			double trad=pi*2;
			vector2d a,b;
			if (!(i%PMod))
			{
				a.x=cos(trad)*range2;a.y=sin(trad)*range2;
				b.x=cos(trad)*(range2-10);b.y=sin(trad)*(range2-10);
			}
			else
			{
				a.x=cos(trad)*range1;a.y=sin(trad)*range1;
				b.x=cos(trad)*(range1-10);b.y=sin(trad)*(range1-10);
			}
			for (int i=60;i<MaxRes;++i)
			untitledlas.Setdata(60,a,b,color);
		}
	}
}noname[1000];
int nonamecnt;
//"CTarg"
struct SimpleBullet
{
	hgeSprite *bulletspr;
	vector2d bulletpos;
	int scollable,lastcoll;
	bool Update_SimpBul()
	{
		if (lastcoll)
		{
			++lastcoll;
			if (LOWFPS)lastcoll+=16;
		}
		if (scollable)
		{
			++scollable;
			if (LOWFPS)scollable+=16;
		}
		if (lastcoll>=200)lastcoll=0;
		if (scollable>=200)scollable=0;
		double dis=GetDist(bulletpos,playerpos);
		if (dis<=6&&clrrange<1e-5&&clrrad-pi/2<1e-7&&!lastcoll)
		//If collision is detected or the bullet flys out of screen, delete it.
		{
			++coll,scminus+=10000;lastcoll=1;
			return true;//Collision
		}
		else
		{
			bulletspr->RenderEx(bulletpos.x+7.2,bulletpos.y+7.2,0,0.6,0);
			if (dis<=16&&!scollable)++semicoll,++dsmc,scollable=1,SCEffect_Attatch();
			return false;
		}
	}
};
class TCTarg
{
private:
	Target Targ;
	SimpleBullet CircBul[37];
	int BulLim,bul;
	double radian,range;
	double Ubrk,Ulim;
public:
	void Init(int _BulLim,double _InitRange,double _Ulim)
	{
		Targ.Init(-0.01,playerpos);
		Targ.TargShow();
		BulLim=_BulLim;
		Ulim=_Ulim;
		bul=BulLim;
		radian=0;
		range=_InitRange;
		for (int i=1;i<=BulLim;++i)
		{
			CircBul[i].bulletpos=vector2d(3+Targ.targpos.x+range*sin(radian-i*(2*pi/BulLim)),
			                              3+Targ.targpos.y-range*cos(radian-i*(2*pi/BulLim)));
			CircBul[i].bulletspr=new hgeSprite(SprSheet,72,0,24,24);
			CircBul[i].bulletspr->SetHotSpot(12,12);
			CircBul[i].bulletspr->SetColor(0x80FFFFFF);
			CircBul[i].scollable=0;
		}
	}
	double GetRange()
	{
		return range;
	}
	void SetRange(double _range)
	{
		range=_range;
	}
	void Update()
	{
		Targ.TargRender();
		if (LOWFPS)radian+=17*60*pi/50000.0f;else radian+=60*pi/50000.0f;
		Ubrk+=hge->Timer_GetDelta();
		hgeColorRGB tcol;
		tcol.a=tcol.r=1;
		tcol.b=tcol.g=Ubrk>Ulim?0.0f:(Ulim-Ubrk)/Ulim;
		Targ.targspr->SetColor(tcol.GetHWColor());
		if (Ubrk>Ulim)
		{
			Targ.TargFollowPlayer();
			if (GetDist(Targ.targpos,playerpos)<4.0f)Ubrk=0.0f;
		}
		for (int i=1;i<=bul;++i)
		{
			CircBul[i].bulletpos=vector2d(3+Targ.targpos.x+range*sin(radian-i*(2*pi/BulLim))-6,
			                              3+Targ.targpos.y-range*cos(radian-i*(2*pi/BulLim))-6);
			CircBul[i].Update_SimpBul();
		}
	}
};
TCTarg CTarg;
class BCircle
{
private:
	SimpleBullet Bullets[360];
	int BCnt;
	double radian,range,DT,drad;
	vector2d Centre;
public:
	void Init(double _irange,double _drad,int _Cnt,vector2d _Centre)
	{
		range=_irange;
		BCnt=_Cnt;
		radian=0;
		DT=0.0f;
		drad=_drad;
		Centre=_Centre;
		for (int i=1;i<=BCnt;++i)
		{
			Bullets[i].bulletpos=vector2d(3+Centre.x+range*sin(radian-i*(2*pi/BCnt))-6,
			                              3+Centre.y-range*cos(radian-i*(2*pi/BCnt))-6);
			Bullets[i].bulletspr=new hgeSprite(SprSheet,0,0,24,24);
			Bullets[i].bulletspr->SetHotSpot(12,12);
			Bullets[i].bulletspr->SetColor(0x80FFFFFF);
		}
	}
	double GetRange(){return range;}
	void SetRange(double _range){range=_range;}
	void SetDT(double _DT){DT=_DT;}
	double GetDT(){return DT;}
	double GetRad(){return radian;}
	void Update()
	{
		DT+=hge->Timer_GetDelta();
		if (LOWFPS)radian+=17*drad;else radian+=drad;
		for (int i=1;i<=BCnt;++i)
		{
			Bullets[i].bulletpos=vector2d(3+Centre.x+range*sin(radian-i*(2*pi/BCnt))-6,
			                              3+Centre.y-range*cos(radian-i*(2*pi/BCnt))-6);
			Bullets[i].Update_SimpBul();
		}
	}
};
class BulletnLaser
{
private:
	Laser line;
	Bullet headb;
	vector2d a,b;
	double lifetime;
public:
	bool active;
	void Init(vector2d _a,vector2d _b)
	{
		a=_a;b=_b;
		line.Init();
		line.SetTexture(SprSheet,0,264,248,8);
		line.RenCtr.x=line.RenCtr.y=0;
		line.EnableColl=false;
		CreateBullet2(headb,a.x,b.x,6,0);
		headb.redir(b);
		double theta=(a.y-b.y,a.x-b.x);
		vector2d a2=vector2d(a.x+4*sin(theta),a.y+4*cos(theta));
		vector2d b2=vector2d(b.x+4*sin(theta),b.y+4*cos(theta));
		//line.InsPoint(a,a2,0xCC33CCFF);
		//while(line.InsPoint(b,b2,0xCC33CCFF));
		line.SetRes(3);
		line.Setdata(0,a,a2,0xCC33CCFF);
		for (int i=1;i<80;++i)line.Setdata(i,b,b2,0xCC33CCFF);
		active=true;
		lifetime=0;
	}
	void Update()
	{
		lifetime+=hge->Timer_GetDelta();
		if (lifetime>1.0&&!line.EnableColl)line.EnableColl=true;
		if (lifetime>4.0&&line.EnableColl)line.EnableColl=false;
		if (lifetime>4.5)active=false;
		ProcessBullet2(headb);line.Process();
	}
};
