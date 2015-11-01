// -*- C++ -*-
//Chrisoft Bullet Lab Remix HGE
//Towers and Bullets Implementations
//"Copyleft" Chrisoft 2013
//WANTED:
//Human-being which really knows what these mean, please contact Chirsno which is puzzled by these shitty codes..
#include "effects.h"
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
	bullet[i].bulletspr=new hgeSprite(SprSheet1,23,0,24,24);
	bullet[i].bulletspr->SetColor(0x80FFFFFF);
	bullet[i].scollable=true;
	bullet[i].scale=1;
	bullet[i].bulletspr->SetHotSpot(12,12);
	if (eff)BulletEffect_Attatch(i);
	return i;
}
void CreateBullet2(double x,double y,double bs,double rad,bool eff=false)
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
	bullet[i].bulletspr=new hgeSprite(SprSheet1,0,0,24,24);
	bullet[i].bulletspr->SetColor(0x80FFFFFF);
	bullet[i].scollable=true;
	bullet[i].scale=1;
	bullet[i].bulletspr->SetHotSpot(12,12);
	if (eff)BulletEffect_Attatch(i);
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
	bullet[i].bulletspr=new hgeSprite(SprSheet1,0,46,24,24);
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
	bullet[i].bulletspr=new hgeSprite(SprSheet1,0,23,24,24);
	bullet[i].bulletspr->SetColor(0x80FFFFFF);
	bullet[i].scollable=true;
	bullet[i].scale=1;
	bullet[i].bulletspr->SetHotSpot(12,12);
	if (eff)BulletEffect_Attatch(i);
}
int CreateBullet6(double x,double y,double bs,int explo,bool eff=false)
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
	bullet[i].oriexplo=bullet[i].redexplo=explo;
	bullet[i].bulletspr=new hgeSprite(SprSheet1,23,23,24,24);
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
	bullet[i].bulletspr=new hgeSprite(SprSheet1,46,23,24,24);
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
	bullet[i].bulletspr=new hgeSprite(SprSheet1,46,0,24,24);
	bullet[i].bulletspr->SetColor(0x80FFFFFF);
}
void ProcessBullet1()
{
	for (int i=1;i<=bulcnt;++i)
	{
		if (!bullet[i].exist||bullet[i].bullettype!=1)continue;//If this bullet doesn't exist or is not of this type, do not render it.
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
			if (dis<=6)++coll,scminus+=10000;
			bullet[i].exist=false;
			bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
			bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
			bullet[i].dist=0;
			bullet[i].bullettype=0;
		}
		else
		{
			bullet[i].bulletspr->RenderEx(bullet[i].bulletpos.x+7.2,bullet[i].bulletpos.y+7.2,0,0.6*bullet[i].scale,0);
			if (dis<=16&&bullet[i].scollable)++semicoll,++dsmc,bullet[i].scollable=false,SCEffect_Attatch();
		}
	}
}
void ProcessBullet2()
{
	for (int i=1;i<=bulcnt;++i)
	{
		if (!bullet[i].exist||bullet[i].bullettype!=2)continue;//If this bullet doesn't exist or is not of this type, do not render it.
		if (LOWFPS)bullet[i].lifetime+=17;else ++bullet[i].lifetime;
		if (bullet[i].lifetime>=15000&&Refliction)
		{
			bullet[i].exist=false;
			bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
			bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
			bullet[i].dist=0;
			bullet[i].bullettype=0;
			continue;
		}
		if (!DisablePlayer)
		{
			if (LOWFPS)
			{
				bullet[i].bulletpos.x-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.x)/20*17;//Process bullet's x coor.
				bullet[i].bulletpos.y-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.y)/20*17;//Process bullet's y coor.
			}
			else
			{
				bullet[i].bulletpos.x-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.x)/20;//Process bullet's x coor.
				bullet[i].bulletpos.y-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.y)/20;//Process bullet's y coor.
			}
		}
		BulletEffect_Process(i);
		double dis=GetDist(bullet[i].bulletpos,playerpos);//Get distance between player and bullet
		if (bullet[i].bulletpos.x<=-10||bullet[i].bulletpos.x>=800||bullet[i].bulletpos.y<=-10||bullet[i].bulletpos.y>=600)
		{
			if (Refliction)
				bullet[i].bulletdir.x=-bullet[i].bulletdir.x,
				bullet[i].bulletdir.y=-bullet[i].bulletdir.y;
			else
			{
				bullet[i].exist=false;
				bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
				bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
				bullet[i].dist=0;
				bullet[i].bullettype=0;
				continue;
			}
		}
		if (dis<=6)
		//If collision is detected or the bullet flys out of screen, delete it.
		{
			++coll,scminus+=10000;
			bullet[i].exist=false;
			bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
			bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
			bullet[i].dist=0;
			bullet[i].bullettype=0;
			continue;
		}
		else
		{
			bullet[i].bulletspr->RenderEx(bullet[i].bulletpos.x+7.2,bullet[i].bulletpos.y+7.2,0,0.6*bullet[i].scale,0);
			if (dis<=16&&bullet[i].scollable)++semicoll,++dsmc,bullet[i].scollable=false,SCEffect_Attatch();
		}
	}
}
//There is no need for ProcessBullet3() because they are in fact bullet2
void ProcessBullet4()
{
	for (int i=1;i<=bulcnt;++i)
	{
		if (!bullet[i].exist||bullet[i].bullettype!=4)continue;//If this bullet doesn't exist or is not of this type, do not render it.
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
			if (dis<=6)++coll,scminus+=10000;
			bullet[i].exist=false;
			bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
			bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
			bullet[i].dist=0;
			bullet[i].bullettype=0;
		}
		else
		{
			bullet[i].bulletspr->RenderEx(bullet[i].bulletpos.x+7.2,bullet[i].bulletpos.y+7.2,0,0.6*bullet[i].scale,0);
			if (dis<=16&&bullet[i].scollable)++semicoll,++dsmc,bullet[i].scollable=false,SCEffect_Attatch();
		}
	}
}
void ProcessBullet5()
{
	for (int i=1;i<=bulcnt;++i)
	{
		if (!bullet[i].exist||bullet[i].bullettype!=5)continue;//If this bullet doesn't exist or is not of this type, do not render it.
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
			if (dis<=6)playerspeed*=0.9,playerslospeed*=0.9;
			bullet[i].exist=false;
			bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
			bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
			bullet[i].dist=0;
			bullet[i].bullettype=0;
		}
		else
		{
			bullet[i].bulletspr->RenderEx(bullet[i].bulletpos.x+7.2,bullet[i].bulletpos.y+7.2,0,0.6*bullet[i].scale,0);
		}
	}
}
void ProcessBullet6()
{
	for (int i=1;i<=bulcnt;++i)
	{
		if (!bullet[i].exist||bullet[i].bullettype!=6)continue;//If this bullet doesn't exist or is not of this type, do not render it.
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
				for (int j=1;j<=8;++j)
				{
					int pnt=CreateBullet6(bullet[i].bulletpos.x,bullet[i].bulletpos.y,bullet[i].bulletspeed,bullet[i].oriexplo);
					//hge->Effect_PlayEx(snd,100,(bullet[i].bulletpos.x-400)/4);
					bullet[pnt].bulletdir.x=cos(j*0.785398);
					bullet[pnt].bulletdir.y=sin(j*0.785398);
					bullet[pnt].dist=bullet[pnt].bulletdir.x*bullet[pnt].bulletdir.x+bullet[pnt].bulletdir.y*bullet[pnt].bulletdir.y;
					bullet[pnt].dist=sqrt(bullet[pnt].dist);
					bullet[pnt].redattrib=1;
				}
			}
			else
			{
				for (int j=1;j<=12;++j)
					CreateBullet2(bullet[i].bulletpos.x,bullet[i].bulletpos.y,bullet[i].bulletspeed,j*0.5236+clockrot);
				clockrot+=deltarot;
				deltarot+=0.004363322313;
			}
			bullet[i].exist=false;
			bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
			bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
			bullet[i].dist=0;
			bullet[i].bullettype=0;
		}
		double dis=GetDist(bullet[i].bulletpos,playerpos);//Get distance between player and bullet
		if (dis<=6||bullet[i].bulletpos.x<=-10||bullet[i].bulletpos.x>=800||bullet[i].bulletpos.y<=-10||bullet[i].bulletpos.y>=600)
		//If collision is detected or the bullet flys out of screen, delete it.
		{
			if (dis<=6)++coll,scminus+=10000;
			bullet[i].exist=false;
			bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
			bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
			bullet[i].dist=0;
			bullet[i].bullettype=0;
		}
		else
		{
			bullet[i].bulletspr->RenderEx(bullet[i].bulletpos.x+7.2,bullet[i].bulletpos.y+7.2,0,0.6*bullet[i].scale,0);
			if (dis<=16&&bullet[i].scollable)++semicoll,++dsmc,bullet[i].scollable=false,SCEffect_Attatch();
		}
	}
}
void ProcessBullet7()
{
	for (int i=1;i<=bulcnt;++i)
	{
		if (!bullet[i].exist||bullet[i].bullettype!=7)continue;//If this bullet doesn't exist or is not of this type, do not render it.
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
		if (!LOWFPS)
		{
			if (bullet[i].redattrib==0)
				--bullet[i].redexplo;
			else
				bullet[i].redexplo-=3;
		}
		else
		{
			if (bullet[i].redattrib==0)
				bullet[i].redexplo-=17;
			else
				bullet[i].redexplo-=51;
		}
		if (bullet[i].redexplo<=0&&!DisableAllTower)
		{
			if (bullet[i].redattrib==0)
			{
				int pnt=CreateBullet7(bullet[i].bulletpos.x,bullet[i].bulletpos.y,bullet[i].bulletspeed,bullet[i].oriexplo);
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
			}
			else
			{
				if (!LOWFPS)
					++bullet[i].whiskp;
				else
					bullet[i].whiskp+=17;
				if (bullet[i].whiskp>50)
				{
					for (int j=1;j<=12;++j)
						CreateBullet2(bullet[i].bulletpos.x,bullet[i].bulletpos.y,bullet[i].bulletspeed,j*0.5236+whirot);
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
				}
			}
		}
		double dis=GetDist(bullet[i].bulletpos,playerpos);//Get distance between player and bullet
		if (dis<=6||bullet[i].bulletpos.x<=-10||bullet[i].bulletpos.x>=800||bullet[i].bulletpos.y<=-10||bullet[i].bulletpos.y>=600)
		//If collision is detected or the bullet flys out of screen, delete it.
		{
			if (dis<=6)++coll,scminus+=10000;
			bullet[i].exist=false;
			bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
			bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
			bullet[i].dist=0;
			bullet[i].bullettype=0;
		}
		else
		{
			bullet[i].bulletspr->RenderEx(bullet[i].bulletpos.x+7.2,bullet[i].bulletpos.y+7.2,0,0.6*bullet[i].scale,0);
			if (dis<=16&&bullet[i].scollable)++semicoll,++dsmc,bullet[i].scollable=false,SCEffect_Attatch();
		}
	}
}
void ProcessBullet255()
{
	for (int i=1;i<=bulcnt;++i)
	{
		if (!bullet[i].exist||bullet[i].bullettype!=255)continue;//If this bullet doesn't exist or is not of this type, do not render it.
		if (!DisablePlayer)
		{
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
		}
		else
		{
			bullet[i].bulletspr->RenderEx(bullet[i].bulletpos.x,bullet[i].bulletpos.y,0,0.5,0);
		}
	}
}
int CreateTower1(double x,double y,int timer,double bs,bool eff=false)//This returns the created tower number.
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
	tower[i].towerspr=new hgeSprite(SprSheet2,44,0,44,44);
	tower[i].towerspr->SetHotSpot(22,22);
	tower[i].towerspr->SetColor(0x80FFFFFF);
	tower[i].effect=eff;
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
	tower[i].towerspr=new hgeSprite(SprSheet2,0,0,44,44);
	tower[i].towerspr->SetHotSpot(22,22);
	tower[i].towerspr->SetColor(0x80FFFFFF);
	tower[i].effect=eff;
	return i;
}
int CreateTower3(double x,double y,int timer,double bs,bool eff=false)//This returns the created tower number.
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
	tower[i].towertimer=tower[i].curtimer=timer;
	tower[i].towerpos.x=x,tower[i].towerpos.y=y;
	tower[i].towerspr=new hgeSprite(SprSheet2,0,0,44,44);
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
	tower[i].towerspr=new hgeSprite(SprSheet2,88,44,44,44);
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
	tower[i].towerspr=new hgeSprite(SprSheet2,88,0,44,44);
	tower[i].towerspr->SetHotSpot(22,22);
	tower[i].towerspr->SetColor(0x80FFFFFF);
	tower[i].effect=eff;
	return i;
}
int CreateTower6(double x,double y,int timer,double bs,int redexplo,bool eff=false)//This returns the created tower number.
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
	tower[i].towerspr=new hgeSprite(SprSheet2,0,44,44,44);
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
	tower[i].towerspr=new hgeSprite(SprSheet2,44,44,44,44);
	tower[i].towerspr->SetHotSpot(22,22);
	tower[i].towerspr->SetColor(0x80FFFFFF);
	tower[i].whicnt=whicnt;
	tower[i].effect=eff;
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
			//hge->Effect_PlayEx(snd,100,(tower[i].towerpos.x-400)/4);
			tower[i].curtimer=tower[i].towertimer;
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
				//hge->Effect_PlayEx(snd,100,(tower[i].towerpos.x-400)/4);
			clockrot+=deltarot;
			//deltarot+=0.004363322313;
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
			if (tower[i].t3t==0)
				for (int j=1;j<=12;++j)
					CreateBullet3(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,j,tower[i].effect);
					//hge->Effect_PlayEx(snd,100,(tower[i].towerpos.x-400)/4);
			if (tower[i].t3t==1)
			{
				CreateBullet3(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,12,tower[i].effect);
				//hge->Effect_PlayEx(snd,100,(tower[i].towerpos.x-400)/4);
				CreateBullet3(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,3,tower[i].effect);
				//hge->Effect_PlayEx(snd,100,(tower[i].towerpos.x-400)/4);
				CreateBullet3(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,6,tower[i].effect);
				//hge->Effect_PlayEx(snd,100,(tower[i].towerpos.x-400)/4);
				CreateBullet3(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,9,tower[i].effect);
				//hge->Effect_PlayEx(snd,100,(tower[i].towerpos.x-400)/4);
			}
			if (tower[i].t3t==2)
			{
				if (rand()%2==0)
					CreateBullet3(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,12,tower[i].effect);
					//hge->Effect_PlayEx(snd,100,(tower[i].towerpos.x-400)/4);
				else
					CreateBullet3(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,6,tower[i].effect);
					//hge->Effect_PlayEx(snd,100,(tower[i].towerpos.x-400)/4);
			}
			if (tower[i].t3t==3)
			{
				if (rand()%2==0)
					CreateBullet3(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,3,tower[i].effect);
					//hge->Effect_PlayEx(snd,100,(tower[i].towerpos.x-400)/4);
				else
					CreateBullet3(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,9,tower[i].effect);
					//hge->Effect_PlayEx(snd,100,(tower[i].towerpos.x-400)/4);
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
			//hge->Effect_PlayEx(snd,100,(tower[i].towerpos.x-400)/4);
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
			//hge->Effect_PlayEx(snd,100,(tower[i].towerpos.x-400)/4);
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
			CreateBullet6(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,tower[i].redexplo,tower[i].effect);
			//hge->Effect_PlayEx(snd,100,(tower[i].towerpos.x-400)/4);
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
			//hge->Effect_PlayEx(snd,100,(tower[i].towerpos.x-400)/4);
		}
	}
}
