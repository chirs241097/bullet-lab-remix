//Chrisoft Bullet Lab Remix HGE
//Towers and Bullets Implementations
//Copyright Chrisoft 2014
//[Perfect Freeze]: code here for BLR2 won't change a lot since 30/08/2013
//Sorry that I would break that...
//I found the rendering code stupid so I MUST rewrite it RIGHT NOW.
//                                             --Announcement from Chirsno
#include "effects.h"
//static const char* TOWERNBULLET_H_FN="towernbullet.h";

void RenderAlter(vector2d p,TColors ca,TColors cb,double rot=0,double scl=1)
{
	float x,y,w,h;
	bulletspr[ca]->GetTextureRect(&x,&y,&w,&h);
	bulletspr[ca]->SetTextureRect(x,y,12,h);
	bulletspr[ca]->SetHotSpot(12,12);
	bulletspr[ca]->RenderEx(p.x,p.y,rot,scl);
	bulletspr[ca]->SetTextureRect(x,y,w,h);
	bulletspr[ca]->SetHotSpot(12,12);

	bulletspr[cb]->GetTextureRect(&x,&y,&w,&h);
	bulletspr[cb]->SetTextureRect(x,y,12,h);
	bulletspr[cb]->SetHotSpot(12,12);
	bulletspr[cb]->RenderEx(p.x,p.y,rot+pi,scl);
	bulletspr[cb]->SetTextureRect(x,y,w,h);
	bulletspr[cb]->SetHotSpot(12,12);
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
	bullet[i].inv=false;
	bullet[i].bullettype=1;
	bullet[i].bulletpos.x=x;
	bullet[i].bulletpos.y=y;
	bullet[i].bulletdir.x=x-playerpos.x;
	bullet[i].bulletdir.y=y-playerpos.y;
	bullet[i].dist=bullet[i].bulletdir.x*bullet[i].bulletdir.x+bullet[i].bulletdir.y*bullet[i].bulletdir.y;
	bullet[i].dist=sqrt(bullet[i].dist);
	bullet[i].bulletspeed=bs;
	bullet[i].alterColor=green;bullet[i].alterColor2=COLOR_COUNT;
	bullet[i].scollable=true;
	bullet[i].scale=1;
	if (eff)BulletEffect_Attatch(i);
	return i;
}
int CreateBullet2(double x,double y,double bs,double rad,bool eff=false,bool invi=false)
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
	bullet[i].addblend=false;
	bullet[i].extborder=false;
	bullet[i].inv=invi;
	bullet[i].bullettype=2;
	bullet[i].bulletpos.x=x;
	bullet[i].bulletpos.y=y;
	bullet[i].bulletdir=vector2d(cos(rad),sin(rad));
	bullet[i].limpos=vector2d(-999,-999);
	bullet[i].bulletspeed=bs;
	bullet[i].alterColor=blue;
	bullet[i].alterColor2=COLOR_COUNT;
	bullet[i].lifetime=0;
	bullet[i].whirem=0;
	bullet[i].scollable=true;
	bullet[i].collable=true;
	bullet[i].bulletaccel=bullet[i].limv=0;
	bullet[i].scale=1;bullet[i].rot=0;
	if (eff)BulletEffect_Attatch(i);
	return i;
}
void CreateBullet3(double x,double y,double bs,int dir,bool eff=false)
{
	CreateBullet2(x,y,bs,dir*0.5235987756,eff,false);
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
	bullet[i].inv=false;
	bullet[i].bullettype=4;
	bullet[i].bulletpos.x=x;
	bullet[i].bulletpos.y=y;
	bullet[i].bulletdir.x=x-playerpos.x;
	bullet[i].bulletdir.y=y-playerpos.y;
	bullet[i].dist=bullet[i].bulletdir.x*bullet[i].bulletdir.x+bullet[i].bulletdir.y*bullet[i].bulletdir.y;
	bullet[i].dist=sqrt(bullet[i].dist);
	bullet[i].bulletspeed=bs;
	bullet[i].yelbrk=yelbrk;
	bullet[i].scollable=true;
	bullet[i].scale=1;bullet[i].lifetime=0;
	bullet[i].alterColor=yellow;bullet[i].alterColor2=COLOR_COUNT;
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
	bullet[i].inv=false;
	bullet[i].bullettype=5;
	bullet[i].bulletpos.x=x;
	bullet[i].bulletpos.y=y;
	bullet[i].bulletdir.x=x-playerpos.x;
	bullet[i].bulletdir.y=y-playerpos.y;
	bullet[i].dist=bullet[i].bulletdir.x*bullet[i].bulletdir.x+bullet[i].bulletdir.y*bullet[i].bulletdir.y;
	bullet[i].dist=sqrt(bullet[i].dist);
	bullet[i].bulletspeed=bs;
	bullet[i].alterColor=purple;bullet[i].alterColor2=COLOR_COUNT;
	bullet[i].scollable=true;
	bullet[i].scale=1;
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
	bullet[i].inv=false;
	bullet[i].bullettype=6;
	bullet[i].bulletpos.x=x;
	bullet[i].bulletpos.y=y;
	bullet[i].bulletdir.x=re.NextDouble(-1,1);
	bullet[i].bulletdir.y=re.NextDouble(-1,1);
	bullet[i].dist=bullet[i].bulletdir.x*bullet[i].bulletdir.x+bullet[i].bulletdir.y*bullet[i].bulletdir.y;
	bullet[i].dist=sqrt(bullet[i].dist);
	bullet[i].bulletspeed=bs;
	bullet[i].alterColor=red;bullet[i].alterColor2=COLOR_COUNT;
	bullet[i].redattrib=0;
	bullet[i].exp1=exp1;
	bullet[i].exp2=exp2;
	bullet[i].oriexplo=bullet[i].redexplo=explo;
	bullet[i].scollable=true;
	bullet[i].scale=1;
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
	bullet[i].inv=false;
	bullet[i].bullettype=7;
	bullet[i].bulletpos.x=x;
	bullet[i].bulletpos.y=y;
	bullet[i].bulletdir.x=re.NextDouble(-1,1);
	bullet[i].bulletdir.y=re.NextDouble(-1,1);
	bullet[i].dist=bullet[i].bulletdir.x*bullet[i].bulletdir.x+bullet[i].bulletdir.y*bullet[i].bulletdir.y;
	bullet[i].dist=sqrt(bullet[i].dist);
	bullet[i].bulletspeed=bs;
	bullet[i].alterColor=white;bullet[i].alterColor2=COLOR_COUNT;
	bullet[i].oriexplo=bullet[i].redexplo=explo;
	bullet[i].redattrib=0;
	bullet[i].whirem=whicnt;
	bullet[i].whiskp=0;
	bullet[i].scollable=true;
	bullet[i].scale=1;
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
	bullet[i].inv=false;
	bullet[i].bullettype=8;
	bullet[i].bulletpos.x=x;
	bullet[i].bulletpos.y=y;
	bullet[i].bulletdir.x=x-playerpos.x;
	bullet[i].bulletdir.y=y-playerpos.y;
	bullet[i].dist=bullet[i].bulletdir.x*bullet[i].bulletdir.x+bullet[i].bulletdir.y*bullet[i].bulletdir.y;
	bullet[i].dist=sqrt(bullet[i].dist);
	bullet[i].bulletspeed=bs;
	bullet[i].alterColor=dblue;bullet[i].alterColor2=COLOR_COUNT;
	bullet[i].scollable=true;
	bullet[i].scale=1;
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
	bullet[i].inv=false;
	bullet[i].bullettype=9;
	bullet[i].bulletpos.x=x;
	bullet[i].bulletpos.y=y;
	bullet[i].bulletdir.x=re.NextDouble(-1,1);
	bullet[i].bulletdir.y=re.NextDouble(-1,1);
	bullet[i].dist=bullet[i].bulletdir.x*bullet[i].bulletdir.x+bullet[i].bulletdir.y*bullet[i].bulletdir.y;
	bullet[i].dist=sqrt(bullet[i].dist);
	bullet[i].bulletspeed=bs;
	bullet[i].oriexplo=bullet[i].redexplo=explo;
	bullet[i].redattrib=0;
	bullet[i].whicnt=cnt;
	bullet[i].yelbrk=brk;
	bullet[i].alterColor=orange;bullet[i].alterColor2=COLOR_COUNT;
	bullet[i].scollable=true;
	bullet[i].scale=1;
	if (eff)BulletEffect_Attatch(i);
	return i;
}
void CreateBullet255(double x,double y,double bs,int spno=0)
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
	bullet[i].redattrib=spno;
	vector2d spos=playerpos+splitData[spno];
	bullet[i].bulletdir.x=x-spos.x;
	bullet[i].bulletdir.y=y-spos.y;
	bullet[i].dist=bullet[i].bulletdir.x*bullet[i].bulletdir.x+bullet[i].bulletdir.y*bullet[i].bulletdir.y;
	bullet[i].dist=sqrt(bullet[i].dist);
	bullet[i].bulletspeed=bs;
}
void All2pnt()
{
	for (int i=1;i<=bulcnt;++i)
	{
		if(bullet[i].bullettype<200&&bullet[i].exist)
		{
			CreateBullet255(bullet[i].bulletpos.x,bullet[i].bulletpos.y,10);
			bullet[i].exist=false;
			bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
			bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
			bullet[i].dist=0;
			bullet[i].bullettype=0;
		}
	}
}
void ProcessBullet1(int i)
{
	if (!bullet[i].exist||bullet[i].bullettype!=1)return;
	if (!DisablePlayer)
	{
		if (LOWFPS)
		{
			bullet[i].bulletpos.x-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20*17;
			bullet[i].bulletpos.y-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20*17;
		}
		else
		{
			bullet[i].bulletpos.x-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20;
			bullet[i].bulletpos.y-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20;
		}
	}
	BulletEffect_Process(i);
	double dis=GetDist(bullet[i].bulletpos,playerpos);
	if (dis<=6||bullet[i].bulletpos.x<=-10||bullet[i].bulletpos.x>=800||bullet[i].bulletpos.y<=-10||bullet[i].bulletpos.y>=600)
	{
		if (dis<=6&&clrrange<1e-5&&clrrad-pi/2<1e-7)++coll,scminus+=10000,Mult_BatClear();
		bullet[i].exist=false;
		bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
		bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
		bullet[i].dist=0;
		bullet[i].bullettype=0;
	}
	else
	{
		bulletspr[bullet[i].alterColor]->RenderEx(bullet[i].bulletpos.x+7.2,bullet[i].bulletpos.y+7.2,0,0.6*bullet[i].scale,0);
		if (dis<=16&&bullet[i].scollable)++semicoll,++dsmc,bullet[i].scollable=false,SCEffect_Attatch();
	}
}
void ProcessBullet2(int i)
{
	if (!bullet[i].exist||bullet[i].bullettype!=2)return;
	if (Current_Position==1)bullet[i].lifetime+=hge->Timer_GetDelta();
	if (!DisablePlayer)
	{
		//experimental new coor processing code, FPS independent
		if (bullet[i].whirem<=0)
		{
			if (bullet[i].bulletaccel>0&&bullet[i].bulletspeed<bullet[i].limv)bullet[i].bulletspeed+=bullet[i].bulletaccel*(1000.0f/hge->Timer_GetFPS());
			if (bullet[i].bulletaccel<0&&bullet[i].bulletspeed>bullet[i].limv)bullet[i].bulletspeed+=bullet[i].bulletaccel*(1000.0f/hge->Timer_GetFPS());
		}
		else
			bullet[i].whirem-=1000.0f/hge->Timer_GetFPS();
		bullet[i].bulletpos.x-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.x)/20*(1000.0f/hge->Timer_GetFPS());
		bullet[i].bulletpos.y-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.y)/20*(1000.0f/hge->Timer_GetFPS());
		if(GetDist(bullet[i].bulletpos,bullet[i].limpos)<1)
		{
			BulletEffect_Death(bullet[i],ColorToDWORD(bullet[i].alterColor));
			bullet[i].exist=false;
			bullet[i].bulletpos.x=bullet[i].bulletpos.y=-999;
			bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
			bullet[i].dist=0;
			bullet[i].bullettype=0;return;
		}
	}
	BulletEffect_Process(i);
	if(PlayerSplit)
	{
		bool rndr=true;
		for(int j=0;j<4;++j)
		{
			double dis=GetDist(bullet[i].bulletpos,playerpos+splitData[j]);
			if (bullet[i].bulletpos.x<=-25||bullet[i].bulletpos.x>=825||bullet[i].bulletpos.y<=-25||bullet[i].bulletpos.y>=625)
			{
				bullet[i].exist=false;rndr=false;
				bullet[i].bulletpos.x=bullet[i].bulletpos.y=-999;
				bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
				bullet[i].dist=0;
				bullet[i].bullettype=0;
				return;
			}
			if (bullet[i].scale<1.2&&dis<=6&&clrrange<1e-5&&clrrad-pi/2<1e-7&&bullet[i].collable)
			{
				++coll,scminus+=10000,Mult_BatClear();bullet[i].collable=false;rndr=false;
				if(!bullet[i].inv)
				{
					bullet[i].exist=false;
					bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
					bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
					bullet[i].dist=0;
					bullet[i].bullettype=0;
				}
				return;
			}
			else
			{
				if (dis<=16&&bullet[i].scollable)++semicoll,++dsmc,bullet[i].scollable=false,SCEffect_Attatch(playerpos+splitData[j]);
			}
		}
		if(rndr)
		{
			if(bullet[i].alterColor2==COLOR_COUNT)
				bulletspr[bullet[i].alterColor]->RenderEx(bullet[i].bulletpos.x+7.2,bullet[i].bulletpos.y+7.2,0,0.6*bullet[i].scale,0);
			else
				RenderAlter(vector2d(bullet[i].bulletpos.x+7.2,bullet[i].bulletpos.y+7.2),bullet[i].alterColor,bullet[i].alterColor2,bullet[i].rot,0.6*bullet[i].scale),
				Current_Position==1?bullet[i].rot+=(i&1?1:-1)*(1000/hge->Timer_GetFPS())*pi/1000:0;
		}
	}
	else
	{
		double dis=GetDist(bullet[i].bulletpos,playerpos);
		if ((!bullet[i].extborder&&(bullet[i].bulletpos.x<=-25||bullet[i].bulletpos.x>=825||bullet[i].bulletpos.y<=-25||bullet[i].bulletpos.y>=625))||
			(bullet[i].extborder&&(bullet[i].bulletpos.x<=-225||bullet[i].bulletpos.x>=1025||bullet[i].bulletpos.y<=-225||bullet[i].bulletpos.y>=825)))
		{
			bullet[i].exist=false;
			bullet[i].bulletpos.x=bullet[i].bulletpos.y=-999;
			bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
			bullet[i].dist=0;
			bullet[i].bullettype=0;
			return;
		}
		if (bullet[i].scale<1.2&&dis<=6&&clrrange<1e-5&&clrrad-pi/2<1e-7&&bullet[i].collable)
		{
			++coll,scminus+=10000,Mult_BatClear();bullet[i].collable=false;
			if(!bullet[i].inv)
			{
				bullet[i].exist=false;
				bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
				bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
				bullet[i].dist=0;
				bullet[i].bullettype=0;
			}
			return;
		}
		else
		{
			if(bullet[i].alterColor2==COLOR_COUNT)
			{
			if(bullet[i].addblend)bulletspr[bullet[i].alterColor]->SetBlendMode(0);
			bulletspr[bullet[i].alterColor]->RenderEx(bullet[i].bulletpos.x+7.2,bullet[i].bulletpos.y+7.2,0,0.6*bullet[i].scale,0);
			if(bullet[i].addblend)bulletspr[bullet[i].alterColor]->SetBlendMode(2);
			}
			else
			RenderAlter(vector2d(bullet[i].bulletpos.x+7.2,bullet[i].bulletpos.y+7.2),bullet[i].alterColor,bullet[i].alterColor2,bullet[i].rot,0.6*bullet[i].scale),
			Current_Position==1?bullet[i].rot+=(i&1?1:-1)*(1000/hge->Timer_GetFPS())*pi/1000:0;
			if (dis<=16&&bullet[i].scollable)++semicoll,++dsmc,bullet[i].scollable=false,SCEffect_Attatch();
		}
	}
}
//There is no need for ProcessBullet3() because they are in fact bullet2
void ProcessBullet4(int i)
{
	if (!bullet[i].exist||bullet[i].bullettype!=4)return;
	if (Current_Position==1)bullet[i].lifetime+=hge->Timer_GetDelta();
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
			bullet[i].bulletpos.x-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20*17;
			bullet[i].bulletpos.y-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20*17;
		}
		else
		{
			bullet[i].bulletpos.x-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20;
			bullet[i].bulletpos.y-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20;
		}
	}
	BulletEffect_Process(i);
	double dis=GetDist(bullet[i].bulletpos,playerpos);
	if (dis<=6||bullet[i].bulletpos.x<=-10||bullet[i].bulletpos.x>=800||bullet[i].bulletpos.y<=-10||bullet[i].bulletpos.y>=600)
	{
		if (dis<=6&&clrrange<1e-5&&clrrad-pi/2<1e-7)++coll,scminus+=10000,Mult_BatClear();
		bullet[i].exist=false;
		bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
		bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
		bullet[i].dist=0;
		bullet[i].bullettype=0;
	}
	else
	{
		bulletspr[bullet[i].alterColor]->RenderEx(bullet[i].bulletpos.x+7.2,bullet[i].bulletpos.y+7.2,0,0.6*bullet[i].scale,0);
		if (dis<=16&&bullet[i].scollable)++semicoll,++dsmc,bullet[i].scollable=false,SCEffect_Attatch();
	}
}
void ProcessBullet5(int i)
{
	if (!bullet[i].exist||bullet[i].bullettype!=5)return;
	if (!DisablePlayer)
	{
		if (LOWFPS)
		{
			bullet[i].bulletpos.x-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20*17;
			bullet[i].bulletpos.y-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20*17;
		}
		else
		{
			bullet[i].bulletpos.x-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20;
			bullet[i].bulletpos.y-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20;
		}
	}
	BulletEffect_Process(i);
	double dis=GetDist(bullet[i].bulletpos,playerpos);
	if (dis<=6||bullet[i].bulletpos.x<=-10||bullet[i].bulletpos.x>=800||bullet[i].bulletpos.y<=-10||bullet[i].bulletpos.y>=600)
	{
		if (dis<=6&&clrrange<1e-5&&clrrad-pi/2<1e-7)playerspeed*=0.9,playerslospeed*=0.9;
		bullet[i].exist=false;
		bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
		bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
		bullet[i].dist=0;
		bullet[i].bullettype=0;
	}
	else
	{
		bulletspr[bullet[i].alterColor]->RenderEx(bullet[i].bulletpos.x+7.2,bullet[i].bulletpos.y+7.2,0,0.6*bullet[i].scale,0);
	}
}
void ProcessBullet6(int i)
{
	if (!bullet[i].exist||bullet[i].bullettype!=6)return;
	if (!DisablePlayer)
	{
		if (LOWFPS)
		{
			bullet[i].bulletpos.x-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20*17;
			bullet[i].bulletpos.y-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20*17;
		}
		else
		{
			bullet[i].bulletpos.x-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20;
			bullet[i].bulletpos.y-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20;
		}
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
	}
	BulletEffect_Process(i);
	if(PlayerSplit)
	{
		bool rndr=true;
		for(int j=0;j<4;++j)
		{
			double dis=GetDist(bullet[i].bulletpos,playerpos+splitData[j]);
			if (bullet[i].bulletpos.x<=-25||bullet[i].bulletpos.x>=825||bullet[i].bulletpos.y<=-25||bullet[i].bulletpos.y>=625)
			{
				bullet[i].exist=false;rndr=false;
				bullet[i].bulletpos.x=bullet[i].bulletpos.y=-999;
				bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
				bullet[i].dist=0;
				bullet[i].bullettype=0;
				return;
			}
			if (bullet[i].scale<1.2&&dis<=6&&clrrange<1e-5&&clrrad-pi/2<1e-7&&bullet[i].collable)
			{
				++coll,scminus+=10000,Mult_BatClear();bullet[i].collable=false;rndr=false;
				if(!bullet[i].inv)
				{
					bullet[i].exist=false;
					bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
					bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
					bullet[i].dist=0;
					bullet[i].bullettype=0;
				}
				return;
			}
			else
			{
				if (dis<=16&&bullet[i].scollable)++semicoll,++dsmc,bullet[i].scollable=false,SCEffect_Attatch(playerpos+splitData[j]);
			}
		}
		if(rndr)
		{
			if(bullet[i].alterColor2==COLOR_COUNT)
				bulletspr[bullet[i].alterColor]->RenderEx(bullet[i].bulletpos.x+7.2,bullet[i].bulletpos.y+7.2,0,0.6*bullet[i].scale,0);
			else
				RenderAlter(vector2d(bullet[i].bulletpos.x+7.2,bullet[i].bulletpos.y+7.2),bullet[i].alterColor,bullet[i].alterColor2,bullet[i].rot,0.6*bullet[i].scale),
				Current_Position==1?bullet[i].rot+=(i&1?1:-1)*(1000/hge->Timer_GetFPS())*pi/1000:0;
		}
	}
	else
	{
		double dis=GetDist(bullet[i].bulletpos,playerpos);
		if (bullet[i].bulletpos.x<=-25||bullet[i].bulletpos.x>=825||bullet[i].bulletpos.y<=-25||bullet[i].bulletpos.y>=625)
		{
			bullet[i].exist=false;
			bullet[i].bulletpos.x=bullet[i].bulletpos.y=-999;
			bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
			bullet[i].dist=0;
			bullet[i].bullettype=0;
			return;
		}
		if (bullet[i].scale<1.2&&dis<=6&&clrrange<1e-5&&clrrad-pi/2<1e-7&&bullet[i].collable)
		{
			++coll,scminus+=10000,Mult_BatClear();bullet[i].collable=false;
			if(!bullet[i].inv)
			{
				bullet[i].exist=false;
				bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
				bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
				bullet[i].dist=0;
				bullet[i].bullettype=0;
			}
			return;
		}
		else
		{
			if(bullet[i].alterColor2==COLOR_COUNT)
			bulletspr[bullet[i].alterColor]->RenderEx(bullet[i].bulletpos.x+7.2,bullet[i].bulletpos.y+7.2,0,0.6*bullet[i].scale,0);
			else
			RenderAlter(vector2d(bullet[i].bulletpos.x+7.2,bullet[i].bulletpos.y+7.2),bullet[i].alterColor,bullet[i].alterColor2,bullet[i].rot,0.6*bullet[i].scale),
			Current_Position==1?bullet[i].rot+=(i&1?1:-1)*(1000/hge->Timer_GetFPS())*pi/1000:0;
			if (dis<=16&&bullet[i].scollable)++semicoll,++dsmc,bullet[i].scollable=false,SCEffect_Attatch();
		}
	}
}
void ProcessBullet7(int i)
{
	if (!bullet[i].exist||bullet[i].bullettype!=7)return;
	if (!DisablePlayer)
	{
		if (LOWFPS)
		{
			bullet[i].bulletpos.x-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20*17;
			bullet[i].bulletpos.y-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20*17;
		}
		else
		{
			bullet[i].bulletpos.x-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20;
			bullet[i].bulletpos.y-=bsscale*bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20;
		}
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
			}
		}
	}
	BulletEffect_Process(i);
	double dis=GetDist(bullet[i].bulletpos,playerpos);
	if (dis<=6||bullet[i].bulletpos.x<=-10||bullet[i].bulletpos.x>=800||bullet[i].bulletpos.y<=-10||bullet[i].bulletpos.y>=600)
	{
		if (dis<=6&&clrrange<1e-5&&clrrad-pi/2<1e-7)++coll,scminus+=10000,Mult_BatClear();
		bullet[i].exist=false;
		bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
		bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
		bullet[i].dist=0;
		bullet[i].bullettype=0;
	}
	else
	{
		bulletspr[bullet[i].alterColor]->RenderEx(bullet[i].bulletpos.x+7.2,bullet[i].bulletpos.y+7.2,0,0.6*bullet[i].scale,0);
		if (dis<=16&&bullet[i].scollable)++semicoll,++dsmc,bullet[i].scollable=false,SCEffect_Attatch();
	}
}
void ProcessBullet8(int i)
{
	if (!bullet[i].exist||bullet[i].bullettype!=8)return;
	if (!DisablePlayer)
	{
		if (LOWFPS)
		{
			bullet[i].bulletpos.x-=bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20*17;
			bullet[i].bulletpos.y-=bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20*17;
		}
		else
		{
			bullet[i].bulletpos.x-=bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20;
			bullet[i].bulletpos.y-=bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20;
		}
	}
	BulletEffect_Process(i);
	if(bullet[i].bulletpos.x<=-10||bullet[i].bulletpos.x>=800||bullet[i].bulletpos.y<=-10||bullet[i].bulletpos.y>=600)
	{
		int cnt=re.NextInt(2,5);if (Dis8ref)cnt=0;
		if(bullet[i].redattrib)
		{
			if(re.NextInt(0,3))//more possibility to reflect
			{
				if(bullet[i].bulletpos.x<=-10||bullet[i].bulletpos.x>=800)bullet[i].bulletdir.x=-bullet[i].bulletdir.x;
				if(bullet[i].bulletpos.y<=-10||bullet[i].bulletpos.y>=600)bullet[i].bulletdir.y=-bullet[i].bulletdir.y;
			}
			else//vanish or reflect?...
			{
				cnt=4-4*(frameleft/(double)(AMinute*1.5));
				for (int ii=1;ii<=cnt;++ii)
					CreateBullet2(bullet[i].bulletpos.x,bullet[i].bulletpos.y,2,re.NextDouble(-pi,pi));
				bullet[i].exist=false;
				bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
				bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
				bullet[i].dist=0;
				bullet[i].bullettype=0;
				return;
			}
		}
		else
		{
			for (int ii=1;ii<=cnt;++ii)
			{
				int pnt=CreateBullet2(bullet[i].bulletpos.x,bullet[i].bulletpos.y,bullet[i].bulletspeed,re.NextDouble(-pi,pi));
				if (t8special)
				{
					bullet[pnt].alterColor=(TColors)(re.NextInt(0,7));
					bullet[pnt].alterColor2=(TColors)(re.NextInt(0,7));
					if(re.NextInt(0,3)==3)bullet[pnt].redir(vector2d(400,300));
					if(re.NextInt(0,1))++ii;
				}
			}
			bullet[i].exist=false;
			bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
			bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
			bullet[i].dist=0;
			bullet[i].bullettype=0;
			return;
		}
	}
	if(PlayerSplit)
	{
		for(int j=0;j<4;++j)
		{
			double dis=GetDist(bullet[i].bulletpos,playerpos+splitData[j]);
			if (dis<=6)
			{
				if (dis<=6){if(clrrange<1e-5&&clrrad-pi/2<1e-7)++coll,scminus+=10000,Mult_BatClear();}
				bullet[i].exist=false;
				bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
				bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
				bullet[i].dist=0;
				bullet[i].bullettype=0;
			}
			else
			{
				if (dis<=16&&bullet[i].scollable)++semicoll,++dsmc,bullet[i].scollable=false,SCEffect_Attatch(playerpos+splitData[j]);
			}
		}
		bulletspr[bullet[i].alterColor]->RenderEx(bullet[i].bulletpos.x+7.2,bullet[i].bulletpos.y+7.2,0,0.6*bullet[i].scale,0);
	}
	else
	{
		double dis=GetDist(bullet[i].bulletpos,playerpos);
		if (dis<=6)
		{
			if (dis<=6){if(clrrange<1e-5&&clrrad-pi/2<1e-7)++coll,scminus+=10000,Mult_BatClear();}
			bullet[i].exist=false;
			bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
			bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
			bullet[i].dist=0;
			bullet[i].bullettype=0;return;
		}
		else
		{
			bulletspr[bullet[i].alterColor]->RenderEx(bullet[i].bulletpos.x+7.2,bullet[i].bulletpos.y+7.2,0,0.6*bullet[i].scale,0);
			if (dis<=16&&bullet[i].scollable)++semicoll,++dsmc,bullet[i].scollable=false,SCEffect_Attatch();
		}
	}
}
void ProcessBullet9(int i)
{
	if (!bullet[i].exist||bullet[i].bullettype!=9)return;
	if (!DisablePlayer)
	{
		if (LOWFPS)
		{
			bullet[i].bulletpos.x-=bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20*17;
			bullet[i].bulletpos.y-=bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20*17;
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
			bullet[i].bulletpos.x-=bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20;
			bullet[i].bulletpos.y-=bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20;
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
	double dis=GetDist(bullet[i].bulletpos,playerpos);
	if (dis<=6||bullet[i].bulletpos.x<=-10||bullet[i].bulletpos.x>=800||bullet[i].bulletpos.y<=-10||bullet[i].bulletpos.y>=600)
	{
		if (dis<=6&&clrrange<1e-5&&clrrad-pi/2<1e-7)++coll,scminus+=10000,Mult_BatClear();
		bullet[i].exist=false;
		bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
		bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
		bullet[i].dist=0;
		bullet[i].bullettype=0;
	}
	else
	{
		bulletspr[bullet[i].alterColor]->RenderEx(bullet[i].bulletpos.x+7.2,bullet[i].bulletpos.y+7.2,0,0.6*bullet[i].scale,0);
		if (dis<=16&&bullet[i].scollable)++semicoll,++dsmc,bullet[i].scollable=false,SCEffect_Attatch();
	}
}
void ProcessBullet255(int i)
{
	if (!bullet[i].exist||bullet[i].bullettype!=255)return;
	if (!DisablePlayer)
	{
		bullet[i].bulletspeed=10;
		vector2d spos=playerpos+splitData[bullet[i].redattrib];
		bullet[i].bulletdir.x=bullet[i].bulletpos.x-spos.x;
		bullet[i].bulletdir.y=bullet[i].bulletpos.y-spos.y;
		bullet[i].dist=bullet[i].bulletdir.x*bullet[i].bulletdir.x+bullet[i].bulletdir.y*bullet[i].bulletdir.y;
		bullet[i].dist=sqrt(bullet[i].dist);
		if (LOWFPS)
		{
			bullet[i].bulletpos.x-=bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20*17;
			bullet[i].bulletpos.y-=bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20*17;
		}
		else
		{
			bullet[i].bulletpos.x-=bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20;
			bullet[i].bulletpos.y-=bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20;
		}
	}
	double dis=GetDist(bullet[i].bulletpos,playerpos+splitData[bullet[i].redattrib]);
	if (dis<=6||bullet[i].bulletpos.x<=-10||bullet[i].bulletpos.x>=800||bullet[i].bulletpos.y<=-10||bullet[i].bulletpos.y>=600)
	{
		score+=mult*100;mult+=0.0002f;
		bullet[i].exist=false;
		bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
		bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
		bullet[i].dist=0;
		bullet[i].bullettype=0;
	}
	else
	{
		bulletspr[grey]->SetColor(0x20FFFFFF);
		bulletspr[grey]->SetBlendMode(BLEND_ALPHAADD);
		bulletspr[grey]->RenderEx(bullet[i].bulletpos.x+6,bullet[i].bulletpos.y+6,0,0.5,0);
		bulletspr[grey]->SetBlendMode(BLEND_ALPHABLEND);
	}
}
int CreateTower1(double x,double y,int timer,double bs,double offset=0,bool eff=false)
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
	tower[i].RendColor=0x80FFFFFF;
	tower[i].effect=eff;
	tower[i].offset=offset;
	return i;
}
int CreateTower2(double x,double y,int timer,double bs,bool eff=false)
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
	tower[i].RendColor=0x80FFFFFF;
	tower[i].effect=eff;
	return i;
}
int CreateTower3(double x,double y,int timer,double bs,int t3t,bool eff=false)
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
	tower[i].RendColor=0x80FFFFFF;
	tower[i].effect=eff;
	return i;
}
int CreateTower3_fixeddir(double x,double y,int timer,double bs,double rad,bool eff=false)
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
	tower[i].RendColor=0x80FFFFFF;
	tower[i].effect=eff;
	return i;
}
int CreateTower4(double x,double y,int timer,double bs,int yelbrk=0,bool eff=false)
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
	tower[i].RendColor=0x80FFFFFF;
	tower[i].yelbrk=yelbrk;
	tower[i].effect=eff;
	return i;
}
int CreateTower5(double x,double y,int timer,double bs,bool eff=false)
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
	tower[i].RendColor=0x80FFFFFF;
	tower[i].effect=eff;
	return i;
}
int CreateTower6(double x,double y,int timer,double bs,int redexplo,int exp1=8,int exp2=12,bool eff=false)
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
	tower[i].RendColor=0x80FFFFFF;
	tower[i].effect=eff;
	return i;
}
int CreateTower7(double x,double y,int timer,double bs,int redexplo,bool eff=false)
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
	tower[i].RendColor=0x80FFFFFF;
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
	tower[i].RendColor=0x80FFFFFF;
	tower[i].effect=eff;
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
	tower[i].RendColor=0x80FFFFFF;
	tower[i].effect=eff;
	return i;
}
void ProcessTower1()
{
	for (int i=1;i<=towcnt;++i)
	{
		if (!tower[i].exist||tower[i].towertype!=1)continue;
		towerspr[green]->SetColor(tower[i].RendColor);
		towerspr[green]->RenderEx(tower[i].towerpos.x+7.2,tower[i].towerpos.y+7.2,0,0.545);
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
		towerspr[blue]->SetColor(tower[i].RendColor);
		towerspr[blue]->RenderEx(tower[i].towerpos.x+7.2,tower[i].towerpos.y+7.2,0,0.545);
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
		towerspr[blue]->SetColor(tower[i].RendColor);
		towerspr[blue]->RenderEx(tower[i].towerpos.x+7.2,tower[i].towerpos.y+7.2,0,0.545);
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
				if (re.NextInt(0,1))
					CreateBullet3(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,12,tower[i].effect);
				else
					CreateBullet3(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,6,tower[i].effect);
			}
			if (tower[i].t3t==3)
			{
				if (re.NextInt(0,1))
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
		towerspr[yellow]->SetColor(tower[i].RendColor);
		towerspr[yellow]->RenderEx(tower[i].towerpos.x+7.2,tower[i].towerpos.y+7.2,0,0.545);
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
		towerspr[purple]->SetColor(tower[i].RendColor);
		towerspr[purple]->RenderEx(tower[i].towerpos.x+7.2,tower[i].towerpos.y+7.2,0,0.545);
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
		towerspr[red]->SetColor(tower[i].RendColor);
		towerspr[red]->RenderEx(tower[i].towerpos.x+7.2,tower[i].towerpos.y+7.2,0,0.545);
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
		towerspr[white]->SetColor(tower[i].RendColor);
		towerspr[white]->RenderEx(tower[i].towerpos.x+7.2,tower[i].towerpos.y+7.2,0,0.545);
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
		towerspr[dblue]->SetColor(tower[i].RendColor);
		towerspr[dblue]->RenderEx(tower[i].towerpos.x+7.2,tower[i].towerpos.y+7.2,0,0.545);
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
				if (!Dis8ref&&!t8special)BTarg.TargShow();
				if (!Dis8ref)BTarg.targpos=playerpos;
				if (PlayerSplit)
				{
					int r=0;
					for(int i=1;i<4;++i)
					if(GetDist(playerpos+splitData[r],vector2d(400,300))>
					GetDist(playerpos+splitData[i],vector2d(400,300)))r=i;
					BTarg.targpos=playerpos+splitData[r];
				}
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
				if (!t8special)
				{
					int pnt=CreateBullet8(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,tower[i].effect);
					if(level==-1&&part==21)bullet[pnt].redattrib=1;else bullet[pnt].redattrib=0;
					if (Dis8ref)
					{
						if (tower[i].towerpos.y<300)
						bullet[pnt].setdir(-pi/2);else bullet[pnt].setdir(pi/2);
					}
					else bullet[pnt].redir(BTarg.targpos);
				}
				else
				{
					for(int j=0;j<5;++j)
					{
						int pnt=CreateBullet8(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,tower[i].effect);
						bullet[pnt].alterColor=white;
						bullet[pnt].redir(BTarg.targpos);
						bullet[pnt].bulletdir.Rotate(j*2*pi/5);
					}
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
		towerspr[orange]->SetColor(tower[i].RendColor);
		towerspr[orange]->RenderEx(tower[i].towerpos.x+7.2,tower[i].towerpos.y+7.2,0,0.545);
		if (DisableAllTower)continue;
		if (LOWFPS)
			tower[i].curtimer-=17;
		else
			--tower[i].curtimer;
		if (tower[i].curtimer<=0)
		{
			tower[i].curtimer=tower[i].towertimer;
			CreateBullet9(tower[i].towerpos.x,tower[i].towerpos.y,tower[i].bulletspeed,tower[i].redexplo,tower[i].whicnt,tower[i].yelbrk,tower[i].effect);
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
	double GetDist()
	{
		double res=99999.9999f,tres;
		static vector2d correction=vector2d(8.4,8.4);
		for (int i=0;i<Res-1;++i)
		{
			vector2d sa,sb;
			sa=data1[i]+RenCtr;sb=data1[i+1]+RenCtr;
			tres=GetDistSeg(sa,sb,playerpos+correction);
			sa=data2[i]+RenCtr;sb=data2[i+1]+RenCtr;
			if(GetDistSeg(sa,sb,playerpos+correction)<tres)
			tres=GetDistSeg(sa,sb,playerpos+correction);
			if (tres<res)res=tres;
		}
		return res;
	}
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
	void Process()
	{
		Render();
		if (EnableColl)
		{
			if (GetDist()<3.0f&&clrrange<1e-5&&clrrad-pi/2<1e-7)
			{
				if (!LOWFPS)++collbrk;else collbrk+=17;
				if (collbrk>200)
					++coll,scminus+=10000,collbrk=0,Mult_BatClear();
			}
		}
		if (GetDist()<9.0f)
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
	Tar.alterColor=blue;
	Tar.scale=1;
	Tar.scollable=true;
	Tar.bulletaccel=0;
}
void ProcessBullet2(Bullet &xbul,bool colchk=true)
{
	if (!xbul.exist||xbul.bullettype!=2)return;
	if (!xbul.dist)xbul.dist=1;
	if (xbul.bulletaccel>0&&xbul.bulletspeed<xbul.limv)xbul.bulletspeed+=xbul.bulletaccel*(1000.0f/hge->Timer_GetFPS());
	if (xbul.bulletaccel<0&&xbul.bulletspeed>xbul.limv)xbul.bulletspeed+=xbul.bulletaccel*(1000.0f/hge->Timer_GetFPS());
	xbul.bulletpos.x-=xbul.bulletspeed*(xbul.bulletdir.x/xbul.dist)/20*(1000.0f/hge->Timer_GetFPS());
	xbul.bulletpos.y-=xbul.bulletspeed*(xbul.bulletdir.y/xbul.dist)/20*(1000.0f/hge->Timer_GetFPS());
	double dis=GetDist(xbul.bulletpos,playerpos);
	if (dis<=6&&clrrange<1e-5&&clrrad-pi/2<1e-7&&colchk&&xbul.collable)
	{
		++coll,scminus+=10000,Mult_BatClear();xbul.collable=false;
		return;
	}
	if (dis<=16&&xbul.scollable)++semicoll,++dsmc,xbul.scollable=false,SCEffect_Attatch();
	if (colchk)bulletspr[xbul.alterColor]->RenderEx(xbul.bulletpos.x+7.2,xbul.bulletpos.y+7.2,0,0.6*xbul.scale);
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
		untitledbul.bulletaccel=0.0005;
		untitledbul.limv=2;untitledbul.collable=true;
		las=false;
		reverse=false;
		done=false;
		PMod=pmd;
		r1lim=_r1lim;r2lim=_r2lim;boomlim=_boomlim;
		if (re.NextInt(0,100)>boomlim)
			pos=re.NextInt(0,600);
		else
			pos=999;
		untitledlas.SetTexture(SprSheet,0,264,248,8);
	}
	void noname2pnt()
	{
		if(!las)
		CreateBullet255(untitledbul.bulletpos.x,untitledbul.bulletpos.y,10);
		else
		{
			for (int i=0;i<60;++i)
			{
				double trad=(i/60.0f)*pi*2;
				vector2d a;
				if (!(i%PMod))
				{
					a.x=cos(trad)*range2;a.y=sin(trad)*range2;
				}
				else
				{
					a.x=cos(trad)*range1;a.y=sin(trad)*range1;
				}
				a=a+untitledbul.bulletpos;
				CreateBullet255(a.x,a.y,10);
			}
		}
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
		}else
		if (las)
		{
			untitledlas.RenCtr=vector2d(x+7.2,y+7.2);
			untitledlas.Render();untitledlas.EnableColl=true;
			untitledlas.Process();
			if (!reverse)
			{
				if (range1<r1lim)range1+=0.2*(1000.0/hge->Timer_GetFPS()),range2=range1;
				if (range1>=r1lim&&range2<r2lim)range2+=0.1*(1000.0/hge->Timer_GetFPS());
				if (range2>=r2lim)reverse=true;
			}
			else
			{
				if (range2>=r1lim)range2-=0.1*(1000.0/hge->Timer_GetFPS());else range1-=0.2*(1000.0/hge->Timer_GetFPS()),range2=range1;
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
//"CTarg"
class SimpleBullet
{
public:
	TColors aC,aC2;
	vector2d bulletpos;
	int scollable,lastcoll;
	double rot;
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
		if (aC2==COLOR_COUNT)bulletspr[aC]->RenderEx(bulletpos.x+7.2,bulletpos.y+7.2,0,0.6,0);//blink hack
		else RenderAlter(vector2d(bulletpos.x+7.2,bulletpos.y+7.2),aC,aC2,rot,0.6);
		double dis=GetDist(bulletpos,playerpos);
		if (dis<=6&&clrrange<1e-5&&clrrad-pi/2<1e-7&&!lastcoll)
		{
			++coll,scminus+=10000;lastcoll=1;Mult_BatClear();
			return true;//Collision
		}
		else
		{
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
			CircBul[i].aC=blue;CircBul[i].aC2=COLOR_COUNT;CircBul[i].rot=0;
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
#undef rad1
#undef rad2
class TROF
{
public:
	Bullet *Bul[32];
	double rad1,rad2,drad,srad,dtrad,dtrad2;
	double range,drange,dtrange,cdtrange;
	int stage,cnt,ccnt,delay,cf;
	double elasp;
	void init()
	{
		stage=0;rad1=rad2=srad;elasp=0.0f;ccnt=0;
		for (int i=0;i<cnt;++i)Bul[i]=&bullet[CreateBullet8(400,300,0,false)],Bul[i]->setdir(srad),Bul[i]->scale=0.01;
		Bul[0]->bulletspeed=2;Bul[0]->scale=1;
	}
	void stage0()
	{
		elasp+=hge->Timer_GetDelta();
		if ((int)(elasp/0.15f)>ccnt&&ccnt<cnt-1)
		{
			ccnt=(int)(elasp/0.2f);
			if (ccnt==1)dtrange=GetDist(Bul[0]->bulletpos,Bul[1]->bulletpos);
			Bul[ccnt]->bulletspeed=2;Bul[ccnt]->scale=1;
		}
		if (elasp>2)
		{
			stage=1;
			drange=GetDist(Bul[cnt-1]->bulletpos,vector2d(400,300));
			dtrad=(drad-srad);while (dtrad>pi/6.0f)dtrad-=pi/6.0f;dtrad/=delay;
			dtrad2=(2*pi-drad+srad);while (dtrad2>pi/6.0f)dtrad2-=pi/6.0f;dtrad2/=delay;
			for (int i=0;i<cnt;++i)Bul[i]->bulletspeed=0;
			cf=0;
		}
	}
	void stage1()
	{
		cf+=(LOWFPS?17:1);
		rad1=srad+dtrad*cf;rad2=srad-dtrad2*cf;
		for (int i=0;i<cnt;++i)
		if (Bul[i]->bullettype==8)
		{
			if (i&1)
			Bul[i]->bulletpos=vector2d(400+(drange+(cnt-i)*dtrange)*cos(rad1-pi),300+(drange+(cnt-i)*dtrange)*sin(rad1-pi));
			else
			Bul[i]->bulletpos=vector2d(400+(drange+(cnt-i)*dtrange)*cos(rad2-pi),300+(drange+(cnt-i)*dtrange)*sin(rad2-pi));
		}
		if (cf>delay)
		{
			cf=delay;
			rad1=srad+dtrad*cf;rad2=srad-dtrad2*cf;
			for (int i=0;i<cnt;++i)
			if (Bul[i]->bullettype==8)
			{
				if (i&1)
				Bul[i]->bulletpos=vector2d(400+(drange+(cnt-i)*dtrange)*cos(rad1-pi),300+(drange+(cnt-i)*dtrange)*sin(rad1-pi));
				else
				Bul[i]->bulletpos=vector2d(400+(drange+(cnt-i)*dtrange)*cos(rad2-pi),300+(drange+(cnt-i)*dtrange)*sin(rad2-pi));
				Bul[i]->bulletspeed=2,Bul[i]->redir(vector2d(400,300)),
				Bul[i]->bulletdir=vector2d(-Bul[i]->bulletdir.x,-Bul[i]->bulletdir.y);
			}
			stage=2;
		}
	}
	void stage2(){}
	void update()
	{
		switch(stage)
		{
			case 0:stage0();break;
			case 1:stage1();break;
			case 2:stage2();break;
		}
	}
};
class BCircle
{
private:
	SimpleBullet Bullets[360];
	int BCnt;
	double radian,range,DT,drad;
	vector2d Centre;
public:
	void Init(double _irange,double _drad,int _Cnt,vector2d _Centre,TColors _Col=blue,TColors _Col2=COLOR_COUNT)
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
			Bullets[i].aC=_Col;Bullets[i].aC2=_Col2;
			Bullets[i].rot=0;
		}
	}
	double GetRange(){return range;}
	void SetRange(double _range){range=_range;}
	void SetDT(double _DT){DT=_DT;}
	double GetDT(){return DT;}
	double GetRad(){return radian;}
	void circ2pnt()
	{
		for(int i=1;i<=BCnt;++i)
			CreateBullet255(Bullets[i].bulletpos.x,Bullets[i].bulletpos.y,10);
	}
	void Update()
	{
		DT+=hge->Timer_GetDelta();
		if (LOWFPS)radian+=17*drad;else radian+=drad;
		for (int i=1;i<=BCnt;++i)
		{
			Bullets[i].bulletpos=vector2d(3+Centre.x+range*sin(radian-i*(2*pi/BCnt))-6,
			                              3+Centre.y-range*cos(radian-i*(2*pi/BCnt))-6);
			Bullets[i].rot+=(LOWFPS?17:1)*pi/1000;
			Bullets[i].Update_SimpBul();
		}
	}
};
class BulletSine
{
private:
	Bullet headb;
	vector2d a,b,lastgenerated;
	Bullet* generated[400];
	int gencnt;
	bool OutOfBound()
	{
		if (headb.bulletpos.x<=-25||headb.bulletpos.x>=825||headb.bulletpos.y<=-25||headb.bulletpos.y>=625)
		return true;return false;
	}
public:
	bool active;
	void Init(vector2d _a,vector2d _b)
	{
		a=_a;b=_b;lastgenerated=_a;
		CreateBullet2(headb,a.x,a.y,6,0);
		headb.redir(b);
		active=true;memset(generated,0,sizeof(generated));
		gencnt=0;
	}
	void Update()
	{
		if (GetDist(lastgenerated,headb.bulletpos)>4.0f)
		{
            ++gencnt;
            double rad=(gencnt&1)?(gencnt+1)/2*pi/18.0f:-gencnt/2*pi/18.0f;
            generated[gencnt]=&bullet[CreateBullet2(headb.bulletpos.x,headb.bulletpos.y,0,rad,true)];
            generated[gencnt]->inv=true;
            lastgenerated=headb.bulletpos;
		}
		if (OutOfBound())
		{
            active=false;
			for (int i=1;i<=gencnt;++i)
			if (generated[i])
			generated[i]->bulletaccel=0.005,generated[i]->limv=2,
			generated[i]->inv=false,generated[i]->collable=true;
			memset(generated,0,sizeof(generated));
        }
		ProcessBullet2(headb);
	}
};
class WOP
{
private:
	int trail[200];
	double brk,blim,rad,k,ml;
	vector2d a,b;
	Bullet hbul;
	bool OutOfBound()
	{
		if (hbul.bulletpos.x<=-25||hbul.bulletpos.x>=825||hbul.bulletpos.y<=-25||hbul.bulletpos.y>=625)
		{
			for (int i=0;i<200;++i)if (trail[i])return false;
			return true;
		}return false;
	}
public:
	bool active;
	void Init(vector2d _a,vector2d _b,double _ml,double _bl)
	{
		a=_a,b=_b,ml=_ml,blim=_bl;rad=0;
		if (fabs(b.x-a.x)<1e-6)return;k=(b.y-a.y)/(b.x-a.x);
		CreateBullet2(hbul,a.x,a.y,7,0);hbul.redir(b);
		active=true;memset(trail,0,sizeof(trail));
	}
	void Update()
	{
		if (Current_Position!=1)return;
		ProcessBullet2(hbul,false);
		brk+=hge->Timer_GetDelta();
		if (brk>blim)
		{
			brk=0;
			for (int i=0;i<200;++i)
			{
				if (trail[i])
				if (bullet[trail[i]].lifetime>ml)BulletEffect_Death(bullet[trail[i]],0x8000CCFF),bullet[trail[i]].exist=false,trail[i]=0;
			}
			rad+=pi/16.0f;
			vector2d uv=ToUnitCircle(vector2d(1,-k));uv.Swap();
			int pnt=0;while (trail[pnt])++pnt;
			trail[pnt]=CreateBullet2(hbul.bulletpos.x+uv.x*50*sin(rad),hbul.bulletpos.y+uv.y*50*sin(rad),0,0,true);
			pnt=0;while (trail[pnt])++pnt;
			trail[pnt]=CreateBullet2(hbul.bulletpos.x-uv.x*50*sin(rad),hbul.bulletpos.y-uv.y*50*sin(rad),0,0,true);
		}
		if (OutOfBound())active=false;
	}
};
class BTail
{
//devide the screen into a 16*12 matrix, put random colored bullets, arranged
//in the shape of the snake, on to it.
//^Maybe this description is too bad to understand. See the code.
//Partly based on class WOP
private:
	class Pile
	{
	private:
		Bullet* pb[200];
		int matrixx,matrixy,progress,cnt;
		double brk;TColors color;
	public:
		int getProgress(){return progress;}
		void create(int _x,int _y,TColors _col)
		{
			matrixx=_x;matrixy=_y;color=_col;
			progress=1;cnt=0;
		}
		void kill()
		{
			for(int i=0;i<cnt;++i)
			{
				if(pb[i])
				{
					if(pb[i]->bullettype==2)
					{
						pb[i]->exist=false;pb[i]=0;
					}
				}
			}
		}
		void update()
		{
			if(!progress)return;
			if(progress<10)
			{
				brk+=hge->Timer_GetDelta();
				if(brk>0.03)
				{
					brk=0;if(progress++>5)return (void)(progress=10);
					for(int i=0;i<10;++i)
					{
						vector2d ran=vector2d(re.NextDouble(0,50)+matrixx*50,re.NextDouble(0,50)+matrixy*50);
						pb[cnt++]=&bullet[CreateBullet2(ran.x,ran.y,0,0,true)];
						pb[cnt-1]->alterColor=color;
					}
				}
			}
			else
			{
				brk+=hge->Timer_GetDelta();
				if(brk>0.03)
				{
					bool alldone=true;
					for(int i=0;i<cnt;++i)
					{
						if(pb[i])
						{
							if(pb[i]->bullettype==2&&pb[i]->lifetime>1)
							{
								BulletEffect_Death(*pb[i],ColorToDWORD(color));
								pb[i]->exist=false;pb[i]=0;
							}
							else alldone=false;
						}
					}
					if(alldone)progress=0;
				}
			}
		}
	};
	Pile piles[30];
	bool tactive;
	int listx[30],listy[30],cnt;
	TColors pcolor;double tlifetime;
	bool check(int x,int y)
	{
		if(x<0||x>15)return false;
		if(y<0||y>12)return false;
		for(int i=0;i<cnt;++i)
		if(x==listx[i]&&y==listy[i])return false;
		return true;
	}
public:
	bool isActive(){return tactive;}
	void Create()
	{
		pcolor=(TColors)re.NextInt(0,7);tactive=true;
		cnt=0;memset(listx,0,sizeof(listx));
		memset(listy,0,sizeof(listy));tlifetime=0;
		listx[cnt++]=re.NextInt(0,15);listy[cnt-1]=re.NextInt(0,11);
		piles[cnt-1].create(listx[cnt-1],listy[cnt-1],pcolor);
	}
	void Update()
	{
		tlifetime+=hge->Timer_GetDelta();
		if(tlifetime>15)
		{
			tactive=false;
			for(int i=0;i<30;++i)
			if(piles[i].getProgress())piles[i].kill();
		}
		if(piles[cnt-1].getProgress()==10)
		{
			int dlx[4],dly[4],dcnt=0;
			if(check(listx[cnt-1]+1,listy[cnt-1]))
			dlx[dcnt]=listx[cnt-1]+1,dly[dcnt++]=listy[cnt-1];
			if(check(listx[cnt-1]-1,listy[cnt-1]))
			dlx[dcnt]=listx[cnt-1]-1,dly[dcnt++]=listy[cnt-1];
			if(check(listx[cnt-1],listy[cnt-1]+1))
			dlx[dcnt]=listx[cnt-1],dly[dcnt++]=listy[cnt-1]+1;
			if(check(listx[cnt-1],listy[cnt-1]-1))
			dlx[dcnt]=listx[cnt-1],dly[dcnt++]=listy[cnt-1]-1;
			if(dcnt&&cnt<30)
			{
				int rd=re.NextInt(0,dcnt-1);
				listx[cnt++]=dlx[rd];listy[cnt-1]=dly[rd];
				piles[cnt-1].create(listx[cnt-1],listy[cnt-1],pcolor);
			}
		}
		bool none=true;
		for(int i=0;i<30;++i)
			if(piles[i].getProgress())none=false,piles[i].update();
		if(none)tactive=false;
	}
};
class SimpleThing
{
private:
	vector2d center;
	int step,cnt;
	double rad,dly,lr,ra;
	SimpleBullet b[500];
	double r[500],mr[500];
	bool create,rot;
public:
	void Init(vector2d _ctr)
	{
		center=_ctr;step=cnt=dly=lr=ra=0;
		create=true;rot=false;
	}
	void Update(bool rv)
	{
		dly+=hge->Timer_GetDelta();
		if(dly>0.2&&create)
		{
			dly=0;
			for(int i=0;i<10;++i)
			{
				b[cnt].bulletpos=center;
				b[cnt].aC=blue;b[cnt].aC2=COLOR_COUNT;
				r[cnt/10]=0;mr[cnt/10]=(lr+=2);
				if (lr>620)create=false;
				++cnt;
			}
		}
		bool all=!create;
		if(!rot)
		for(int i=0;i<cnt;++i)
		{
			b[i].bulletpos=vector2d(center.x+r[i/10]*cos(i/10*pi/12+pi/5*(i%10)),center.y+r[i/10]*sin(i/10*pi/12+pi/5*(i%10)));
			if(r[i/10]<mr[i/10])r[i/10]+=(LOWFPS?17:1)*0.01,all=false;
			else r[i/10]=mr[i/10];
			b[i].Update_SimpBul();
		}
		if(all||rot)
		{
			rot=true;
			rv?rad+=(LOWFPS?17:1)*ra:rad-=(LOWFPS?17:1)*ra;
			if(ra<pi/7200)ra+=(LOWFPS?17:1)*pi/630000000.0f;
			for(int i=0;i<cnt;++i)
			{
				b[i].bulletpos=vector2d(center.x+r[i/10]*cos(i/10*pi/12+rad+pi/5*(i%10)),center.y+r[i/10]*sin(i/10*pi/12+rad+pi/5*(i%10)));
				b[i].Update_SimpBul();
			}
		}
	}
	void toPoint()
	{
		for(int i=0;i<cnt;++i)
		CreateBullet255(b[i].bulletpos.x,b[i].bulletpos.y,10);
	}
};
class diffCreator
{
protected:
	bool active;
	double range;
	int cnt;
	vector2d center;
	Bullet* C;
	Bullet* target[200];
	vector2d created[200];
private:
	TColors rbGetColor(int a)
	{
		switch (a)
		{
			case 2:return orange;
			case 3:return yellow;
			case 4:return green;
			case 5:return blue;
			case 6:return dblue;
			case 7:return purple;
			default:return circle;
		}
	}
	bool test(vector2d a)
	{
		for(int i=0;i<cnt;++i)
		if(GetDist(a,created[i])<12)return false;
		return true;
	}
public:
	void init(vector2d _ctr)
	{
		active=true;
		cnt=0;range=0;
		center=_ctr;
		C=&bullet[CreateBullet2(center.x,center.y,0,0,true)];
		C->alterColor=red;
	}
	bool isActive(){return active;}
	void update()
	{
		range+=hge->Timer_GetDelta()*400;
		vector2d a;bool all=true;
		for(a=vector2d(center.x-15,center.y);a.x>-25;a.x-=15)
		if(GetDist(a,center)<=range)
		{
			if(test(a))
			target[cnt++]=&bullet[CreateBullet2(a.x,a.y,0,0,true)],
			created[cnt-1]=vector2d(a.x,a.y),
			target[cnt-1]->inv=true,
			target[cnt-1]->alterColor=red;
		}
		else all=false;
		for(a=vector2d(center.x+15,center.y);a.x<825;a.x+=15)
		if(GetDist(a,center)<=range)
		{
			if(test(a))
			target[cnt++]=&bullet[CreateBullet2(a.x,a.y,0,pi,true)],
			created[cnt-1]=vector2d(a.x,a.y),
			target[cnt-1]->inv=true,
			target[cnt-1]->alterColor=red;
		}
		else all=false;
		for(a=vector2d(center.x,center.y-15);a.y>-25;a.y-=15)
		if(GetDist(a,center)<=range)
		{
			if(test(a))
			target[cnt++]=&bullet[CreateBullet2(a.x,a.y,0,pi/2,true)],
			created[cnt-1]=vector2d(a.x,a.y),
			target[cnt-1]->inv=true,
			target[cnt-1]->alterColor=red;
		}
		else all=false;
		for(a=vector2d(center.x,center.y+15);a.y<625;a.y+=15)
		if(GetDist(a,center)<=range)
		{
			if(test(a))
			target[cnt++]=&bullet[CreateBullet2(a.x,a.y,0,-pi/2,true)],
			created[cnt-1]=vector2d(a.x,a.y),
			target[cnt-1]->inv=true,
			target[cnt-1]->alterColor=red;
		}
		else all=false;
		a=center;
#define _bat \
	target[cnt-1]->redir(center),\
	created[cnt-1]=target[cnt-1]->bulletpos,\
	target[cnt-1]->bulletdir.x=-target[cnt-1]->bulletdir.x,\
	target[cnt-1]->bulletdir.y=-target[cnt-1]->bulletdir.y,\
	target[cnt-1]->inv=true,\
	target[cnt-1]->alterColor=rbGetColor(i+j);
		for(int i=1;i<=6;++i)
		for(int j=1;j<=7-i;++j)
		if(GetDist(vector2d(a.x+i*15,a.y+j*15),center)<=range){
		if(test(vector2d(a.x+i*15,a.y+j*15)))
		target[cnt++]=&bullet[CreateBullet2(a.x+i*15,a.y+j*15,0,0,true)],_bat;}
		else all=false;
		for(int i=1;i<=6;++i)
		for(int j=1;j<=7-i;++j)
		if(GetDist(vector2d(a.x-i*15,a.y+j*15),center)<=range){
		if(test(vector2d(a.x-i*15,a.y+j*15)))
		target[cnt++]=&bullet[CreateBullet2(a.x-i*15,a.y+j*15,0,0,true)],_bat;}
		else all=false;
		for(int i=1;i<=6;++i)
		for(int j=1;j<=7-i;++j)
		if(GetDist(vector2d(a.x+i*15,a.y-j*15),center)<=range){
		if(test(vector2d(a.x+i*15,a.y-j*15)))
		target[cnt++]=&bullet[CreateBullet2(a.x+i*15,a.y-j*15,0,0,true)],_bat;}
		else all=false;
		for(int i=1;i<=6;++i)
		for(int j=1;j<=7-i;++j)
		if(GetDist(vector2d(a.x-i*15,a.y-j*15),center)<=range){
		if(test(vector2d(a.x-i*15,a.y-j*15)))
		target[cnt++]=&bullet[CreateBullet2(a.x-i*15,a.y-j*15,0,0,true)],_bat;}
		else all=false;
#undef _bat
		if(all)
		{
			BulletEffect_Death(*C,0x80FF3333);
			C->exist=false;
			for(int i=0;i<cnt;++i)
			{
				target[i]->bulletspeed=-0.5;
				target[i]->bulletaccel=0.0005;
				target[i]->limv=3;
				target[i]->inv=false;
				target[i]->collable=true;
			}
			active=false;
		}
	};
};
class RTV
{
private:
	int mode,cnt,stage,spnr,dcorr;
	bool active;TColors col;
	double drad,rad,brk;
	Bullet *targ[600];
public:
	bool isActive(){return active;}
	void Init(int _mode,double _drad,int _spnr,TColors _c,int _dcorr)
	{
		mode=_mode;drad=_drad;rad=0;spnr=_spnr;
		brk=0;active=true;cnt=0;stage=0;col=_c;
		memset(targ,0,sizeof(targ));dcorr=_dcorr;
	}
	void Update()
	{
		switch(mode)
		{
			case 1:
			{
				brk+=hge->Timer_GetDelta();
				bool dchk=(stage==1);
				for(int i=0;i<cnt;++i)
				{
					if(targ[i]->bulletspeed>1&&GetDist(vector2d(400,300),targ[i]->bulletpos)>=200)
					targ[i]->bulletspeed=0;
					if(targ[i]->bulletspeed>1)dchk=false;
				}
				if(dchk)
				{
					for(int i=0;i<cnt;++i)
					{
						double rad=atan2(targ[i]->bulletdir.y,targ[i]->bulletdir.x);
						int cc=(int)(rad/drad);
						if((cc/6+dcorr)&1)
						targ[i]->bulletaccel=0.005,
						targ[i]->limv=3;
						else
						targ[i]->bulletaccel=-0.005,
						targ[i]->limv=-3;
					}
					return(void)(active=false);
				}
				if(stage==0)
				{
					if(brk>0.05)
					{
						brk=0;rad+=drad;
						if(fabs(rad)>2*pi/spnr+pi/180)return(void)(stage=1);
						for(int i=0;i<spnr;++i)
						{
							targ[cnt]=&bullet[CreateBullet2(400,300,2,rad+i*2*pi/spnr)],
							targ[cnt]->inv=true,
							targ[cnt++]->alterColor=col;
						}
					}
				}
			}
			break;
			case 2:
			{
				brk+=hge->Timer_GetDelta();
				bool dchk=(stage==1);
				for(int i=0;i<cnt;++i)
				{
					if(targ[i]->bulletspeed>1&&GetDist(vector2d(400,300),targ[i]->bulletpos)>=200)
					targ[i]->bulletspeed=0;
					if(targ[i]->bulletspeed>1)dchk=false;
				}
				if(dchk)
				{
					if(re.NextInt(0,1))
					for(int i=0;i<cnt;++i)
						targ[i]->bulletaccel=-0.005,
						targ[i]->limv=-3;
					else
					for(int i=0;i<cnt;++i)
						targ[i]->bulletaccel=0.005,
						targ[i]->limv=3;
					return(void)(active=false);
				}
				if(stage==0)
				{
					if(brk>0.05)
					{
						brk=0;rad+=drad;
						if(fabs(rad)>2*pi/spnr+pi/180)return(void)(stage=1);
						for(int i=0;i<spnr;++i)
						{
							targ[cnt]=&bullet[CreateBullet2(400,300,2,rad+i*2*pi/spnr)],
							targ[cnt]->inv=true;
							targ[cnt++]->alterColor=col;
						}
					}
				}
			}
			break;
			case 3:
			{
				brk+=hge->Timer_GetDelta();
				if(brk>0.05)
				{
					brk=0;rad+=drad;
					if(fabs(rad)>2*pi/spnr+pi/180)return(void)(active=false);
					for(int i=0;i<spnr;++i)
					{
						targ[cnt]=&bullet[CreateBullet2(400,300,2,rad+i*2*pi/spnr)];
						targ[cnt]->inv=true;
						targ[cnt++]->alterColor=col;
						targ[cnt]=&bullet[CreateBullet2(400,300,2,-rad+i*2*pi/spnr)];
						targ[cnt]->inv=true;
						targ[cnt++]->alterColor=col;
					}
				}
			}
			break;
		}
	}
};
bool achromab,achromaB[100];
class achromaGroup
{
private:
	class achromaBullet:public SimpleBullet
	{
	private:
		bool active;
		double spd,acc,lim;
	public:
		bool isActive(){return active;}
		void achromaInit(vector2d pos,TColors initcol,double _lim)
		{
			bulletpos=pos;spd=0;acc=0.0005;lim=_lim;rot=0;
			lastcoll=0;aC=initcol;aC2=COLOR_COUNT;
			active=true;
		}
		void Reverse()
		{
			spd=0;
			if(aC==green)aC=red;
			else if(aC==red)aC=green;
		}
		void achromaUpdate()
		{
			if(aC==red)lastcoll=1;//ignore coll for red.
			bulletpos.y+=spd*(1000.0f/hge->Timer_GetFPS());
			if(spd+acc*(1000.0f/hge->Timer_GetFPS())<lim)spd+=acc*(1000.0f/hge->Timer_GetFPS());
			if(bulletpos.y>610)active=false;
			Update_SimpBul();
		}
	}bullets[1000];
public:
	double crbrk,llim;TColors col;
	void Init(TColors initcol,double _llim)
	{
		col=initcol;llim=_llim;
		crbrk=re.NextDouble(0,frameleft/(double)(AMinute+ThirtySeconds))*(part==36?0.07:0.02)+0.03;
	}
	void Reverse()
	{
		if(col==red)col=green;
		else if(col==green)col=red;
		for(int i=0;i<1000;++i)if(bullets[i].isActive())bullets[i].Reverse();
	}
	void achroma2pnt()
	{
		for(int i=0;i<1000;++i)if(bullets[i].isActive())CreateBullet255(bullets[i].bulletpos.x,bullets[i].bulletpos.y,10);
	}
	void Update(int msk=0)
	{
		crbrk-=hge->Timer_GetDelta();
		if(achromab)
		{
			if(crbrk<=0)
			{
				crbrk=re.NextDouble(0,frameleft/(double)AMinute)*(part==36?0.07:0.02)+0.03;
				for(int i=0;i<1000;++i)
				if(!bullets[i].isActive())
				{
					bullets[i].achromaInit(vector2d(re.NextDouble(10,790),-5),col,llim);
					break;
				}
			}
			for(int i=0;i<1000;++i)if(bullets[i].isActive())bullets[i].achromaUpdate();
		}
		else
		{
			if(crbrk<=0)
			{
				crbrk=1;
				if(msk)
				{
					memset(achromaB,0,sizeof(achromaB));
					for(int i=0;i<80;++i)achromaB[i]=re.NextInt(0,1);
				}
				for(int i=0;i<80;++i)
				{
					if(achromaB[i]&&col==green)
					{
						for(int j=0;j<1000;++j)
						if(!bullets[j].isActive())
						{
							bullets[j].achromaInit(vector2d(i*10,-5),col,llim);
							break;
						}
					}
					if(!achromaB[i]&&col==red)
					{
						for(int j=0;j<500;++j)
						if(!bullets[j].isActive())
						{
							bullets[j].achromaInit(vector2d(i*10,-5),col,llim);
							break;
						}
					}
				}
			}
			for(int i=0;i<500;++i)if(bullets[i].isActive())bullets[i].achromaUpdate();
		}
	}
};
class yellowGroup
{
private:
	Bullet *ylw[100];
	bool dirdone[100];
	bool active;
public:
	bool isActive(){return active;}
	void Init(int _cnt,double _yv)
	{
		memset(ylw,0,sizeof(ylw));active=true;
		memset(dirdone,0,sizeof(dirdone));
		for (int i=0;i<_cnt;++i)
		{
			int pnt=CreateBullet2(400,300,_yv,frameleft*pi/AMinute+i*(2*pi/_cnt));
			bullet[pnt].alterColor=yellow;
			ylw[i]=&bullet[pnt];
		}
	}
	void Update()
	{
		bool done=true;
		for (int i=0;i<100;++i)
		{
			if(ylw[i]&&ylw[i]->lifetime>2&&!dirdone[i]&&ylw[i]->alterColor==yellow)
			ylw[i]->redir(playerpos),dirdone[i]=true;
			if(ylw[i]&&ylw[i]->lifetime>5&&ylw[i]->alterColor==yellow)
			{
				int cc=re.NextInt(0,5);
				for(int j=0;j<cc;++j)
				{
					int pnt=CreateBullet2(ylw[i]->bulletpos.x,ylw[i]->bulletpos.y,0,re.NextDouble(-pi,pi));
					if(!re.NextInt(0,3))bullet[pnt].redir(playerpos);
					bullet[pnt].bulletaccel=0.002;bullet[pnt].limv=3;
				}
				BulletEffect_Death(*ylw[i],ColorToDWORD(yellow));
				ylw[i]->exist=false;
				ylw[i]->bullettype=0;
				ylw[i]=0;
			}
			else done=false;
		}
		if(done)active=false;
	}
};
class Spinner
{
private:
	SimpleBullet abullet[40][100];
	int arms;
	double rad,rstep;
public:
	void Init(int _arms,double _rstep)
	{
		memset(abullet,0,sizeof(abullet));
		arms=_arms;rstep=_rstep;rad=0;
		for(int i=0;i<arms;++i)
		for(int j=0;j*rstep<505;++j)
		{
			abullet[i][j].aC=blue;abullet[i][j].aC2=COLOR_COUNT;
		}
	}
	void Update(double delta)
	{
		for(int i=0;i<arms;++i)
		for(int j=0;j*rstep<505;++j)
		{
			double crad=rad+i*(2*pi/arms);
			abullet[i][j].bulletpos=vector2d(400+j*rstep*cos(crad),300+j*rstep*sin(crad));
			abullet[i][j].Update_SimpBul();
		}
		rad+=hge->Timer_GetDelta()*1000*delta;
	}
};
class expSpinner
{
private:
	Bullet *bullets[1000];
	int arms,cnt,lc;
	double brk,len,dr,da;
	bool active;
	bool InBound(vector2d pos)
	{
		if (pos.x<=-25||pos.x>=825||pos.y<=-25||pos.y>=625)
		return false;return true;
	}
public:
	void Init(int _arms,double _drange,double _drad)
	{
		arms=_arms;lc=cnt=len=0;dr=_drange;da=_drad;active=true;
	}
	bool isActive(){return active;}
	void Update()
	{
		brk+=hge->Timer_GetDelta();
		if(brk<0.03)return;brk=0;
		bool none=true;
		for(int i=0;i<arms;++i)
		{
			double rad=da+i*2*pi/(double)arms,drad=rad+lc*pi/15;int c=(lc&1)?1:-1;
			if(InBound(vector2d(400+len*cos(rad),300+len*sin(rad))))
			{
				bullets[cnt++]=&bullet[CreateBullet2(
				400+len*cos(rad),300+len*sin(rad),0,c*drad,true)];
				c=-c;none=false;
			}
		}
		len+=dr;++lc;
		if(none)
		{
			active=false;
			for(int i=0;i<cnt;++i)bullets[i]->bulletaccel=0.002,bullets[i]->limv=2;
		}
	}
};
class CPinBall
{
private:
	Bullet* center;
	Bullet* circles[10][30];
	int layer;double rot,lifetime,drt;
public:
	void Init(vector2d pos,int _lay)
	{
		center=0;memset(circles,0,sizeof(circles));
		center=&bullet[CreateBullet2(pos.x,pos.y,3,re.NextInt(-pi,pi),true)];
		layer=_lay;rot=0;lifetime=0.01;drt=re.NextDouble(-0.5*pi,0.5*pi);
		for(int i=0;i<layer;++i)
		{
			for(int j=0;j<(i+1)*3;++j)
			{
				circles[i][j]=&bullet[CreateBullet2(pos.x,pos.y,3,0,true)];
				circles[i][j]->bulletpos=vector2d(pos.x+10*i*cos(rot+j*2*pi/((i+1)*3)),pos.y+10*i*sin(rot+j*2*pi/((i+1)*3)));
			}
		}
	}
	double Getlifetime(){return lifetime;}
	void Update()
	{
		lifetime+=hge->Timer_GetDelta();
		vector2d pos=center->bulletpos;
		if(pos.x<10*layer-5||pos.x>790-10*layer)center->bulletdir.x=-center->bulletdir.x;
		if(pos.y<10*layer-5||pos.y>590-10*layer)center->bulletdir.y=-center->bulletdir.y;
		rot+=hge->Timer_GetDelta()*drt;
		for(int i=0;i<layer;++i)
		{
			for(int j=0;j<(i+1)*3;++j)
			{
				circles[i][j]->bulletpos=vector2d(pos.x+10*i*cos(rot+j*2*pi/((i+1)*3)),pos.y+10*i*sin(rot+j*2*pi/((i+1)*3)));
				circles[i][j]->bulletdir=center->bulletdir;
			}
		}
	}
};
class LineLaser:public Laser
{
protected:
	double width;
	vector2d a,b;
	DWORD color;
public:
	void SetColl(bool col){EnableColl=col;}
	void InitLine(vector2d _a,vector2d _b,double _w,DWORD _c)
	{
		a=_a;b=_b;color=_c;Init(2);
		SetTexture(SprSheet,151,264,2,8);
		SetWidth(_w);RenCtr=vector2d(0,0);
	}
	void SetWidth(double _w)
	{
		width=_w;
		vector2d dir(a-b);dir.ToUnitCircle();
		vector2d pd=dir;pd.Rotate(pi/2);
		Setdata(0,a-width*pd,a+width*pd,color);
		for(int i=1;i<MaxRes;++i)Setdata(i,b-width*pd,b+width*pd,color);
	}
	double GetWidth(){return width;}
	//use Laser::Process...
};
class SimpLL:public LineLaser
{
public:
	bool active;
	int stp;
	double brk;
};
