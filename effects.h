//Chrisoft Bullet Lab Remix HGE
//Effects Implementations
//Copyright Chrisoft 2014
//static const char* EFFECTS_H_FN="effects.h";

void SCEffect_Attatch(vector2d Target=vector2d(-100,-100))
{
	int cnt=rand()%8+3;
	if(Target.x<-50&&Target.y<-50)Target=playerpos;
	for (int ii=1;ii<=cnt;++ii)
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
		bullet[i].bullettype=254;
		bullet[i].bulletpos.x=Target.x+3;
		bullet[i].bulletpos.y=Target.y+3;
		bullet[i].bulletdir.x=rand()%100-50;
		bullet[i].bulletdir.y=rand()%100-50;
		bullet[i].dist=bullet[i].bulletdir.x*bullet[i].bulletdir.x+bullet[i].bulletdir.y*bullet[i].bulletdir.y;
		bullet[i].dist=sqrt(bullet[i].dist);
		bullet[i].bulletspeed=rand()%4+2;
		bullet[i].sccolor=0x80FFFFFF;
	}
}
void SCEffect_Process(int i)
{
	if (!bullet[i].exist||bullet[i].bullettype!=254)return;
	if (!DisablePlayer)
	{
		if (LOWFPS)
		{
			bullet[i].bulletpos.x-=bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20*17;
			bullet[i].bulletpos.y-=bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20*17;
			++effskp;
			if (effskp==7)
				bullet[i].sccolor=bullet[i].sccolor-0x1F000000,effskp=0;
		}
		else
		{
			bullet[i].bulletpos.x-=bullet[i].bulletspeed*(bullet[i].bulletdir.x/bullet[i].dist)/20;
			bullet[i].bulletpos.y-=bullet[i].bulletspeed*(bullet[i].bulletdir.y/bullet[i].dist)/20;
			++effskp;
			if (effskp==7)
				bullet[i].sccolor=bullet[i].sccolor-0x1000000,effskp=0;
		}
	}
	if (GETA(bullet[i].sccolor)<=0x0A||bullet[i].bulletpos.x<=-10||bullet[i].bulletpos.x>=800||bullet[i].bulletpos.y<=-10||bullet[i].bulletpos.y>=600)
	{
		bullet[i].exist=false;
		bullet[i].bulletpos.x=bullet[i].bulletpos.y=0;
		bullet[i].bulletdir.x=bullet[i].bulletdir.y=0;
		bullet[i].dist=0;
		bullet[i].bullettype=0;
	}
	else
	{
		bulletspr[grey]->SetColor(bullet[i].sccolor);
		bulletspr[grey]->RenderEx(bullet[i].bulletpos.x+2.4,bullet[i].bulletpos.y+2.4,0,0.2,0);
	}
}
void BulletEffect_Attatch(int n)
{
	bullet[n].scale=2;
	bullet[n].effbrk=17;
}
void BulletEffect_Process(int n)
{
	if (bullet[n].scale<=1){bullet[n].scale=1;return;}
	if (LOWFPS)
		bullet[n].effbrk-=17;
	else
		--bullet[n].effbrk;
	if (bullet[n].effbrk<=0)
		bullet[n].scale-=0.04,bullet[n].effbrk=17;
}
int BulletEffect_Death(Bullet a,DWORD color)
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
	bullet[i].bullettype=253;
	bullet[i].bulletpos.x=a.bulletpos.x;
	bullet[i].bulletpos.y=a.bulletpos.y;
	bullet[i].bulletdir.x=bullet[i].bulletdir.y=bullet[i].dist=0;
	bullet[i].bulletspeed=0;
	bullet[i].alterColor=circle;
	bullet[i].scollable=false;
	bullet[i].scale=1;
	bullet[i].sccolor=SETA(color,0x80);
	bullet[i].effbrk=7;
	return i;
}
void BulletDeath_Process(int i)
{
	if (!bullet[i].exist)return;
	if (LOWFPS)
		bullet[i].effbrk-=17;
	else
		--bullet[i].effbrk;
	if (GETA(bullet[i].sccolor)<=10)return (void)(bullet[i].exist=false);
	if (bullet[i].effbrk<=0&&Current_Position==1)
		bullet[i].effbrk=7,bullet[i].scale+=0.1,bullet[i].sccolor=SETA(bullet[i].sccolor,GETA(bullet[i].sccolor)-6);
	bulletspr[circle]->SetColor(bullet[i].sccolor);
	bulletspr[circle]->RenderEx(bullet[i].bulletpos.x+7.2,bullet[i].bulletpos.y+7.2,0,0.6*bullet[i].scale);
}
