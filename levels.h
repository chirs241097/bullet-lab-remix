//Chrisoft Bullet Lab Remix HGE
//Level Implementations
//Copyright Chrisoft 2014
//Now this is being fully rewritten..
/*
How to write a classic level/part...
Classic parts need only one procedure, like this.
	frameleft=...;
	if (towercnt==/!=...)return ClearAll();
	DisableAllTower=false;bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	for (int i=1;i<=towcnt;++i)
		if (tower[i].towerspr->GetColor()==0x80FFFFFF)
			tower[i].towerspr->SetColor(0x00FFFFFF);
	for (int i=1;i<=towcnt;++i)
		if ((tower[i].towerspr->GetColor()>>24)<=0x80)
			tower[i].towerspr->SetColor(tower[i].towerspr->GetColor()+0x01FFFFFF);
		else
		{
			IfCallLevel=false;
			return;
		}
*/
/*
How to write an "advanced" part...
"Advanced" parts usually need two or more parts, ont for initalize and one for things to do every frame.
Write on your own thought...
*/
bool squashrev;
int posx,posy,fskp,posx2,posy2;
bool doneredir;
int pnt1,pnt2;
//Let's start now!
double towers[16];int tcnt;
double dscroll,roll;
bool sout,tendone;bool dmt[16];
//static const char* LEVEL_H_FN="levels.h";
void Level1Part1()
{
	if ((tower[CreateTower1(400,300,857,2)].RendColor>>24)>=0x80)IfCallLevel=false;
	frameleft=AMinute*2;
	tcnt=1;sout=false;dscroll=-0.025f;memset(dmt,true,sizeof(dmt));
	for (int i=0;i<tcnt;++i)
	{
		towers[i]=600+600.0f/(double)tcnt*i+12;
		CreateTower3(200,towers[i],428,3,4);
		CreateTower3(600,towers[i],428,3,4);
	}
	++part;roll=0;tendone=false;
	ShowTip("\
Level 1-Down by the Bank\n\
Everything going on properly?\n\
");
	Current_Position=2;
}
void Level1Part2()
{
	for (int i=0;i<tcnt;++i)
	{
		if (LOWFPS)towers[i]+=17*dscroll;else towers[i]+=dscroll;
		tower[2*(i+1)].towerpos.y=tower[2*(i+1)+1].towerpos.y=towers[i];
		if (towers[i]<=300&&towers[i]>=290&&dmt[i])
		{
			NewMultpo(tower[2*(i+1)+1].towerpos);
			NewMultpo(tower[2*(i+1)].towerpos);
			dmt[i]=false;
		}
	}
	if (!sout)
	{
		if (towers[tcnt-1]<-12)++roll;
		for (int i=0;i<tcnt;++i)if (towers[i]<-12)towers[i]=612,dmt[i]=true;
		if (roll==1)
		{
			for (int i=1;i<=towcnt;++i)
				if (tower[i].towertype==3)tower[i].t3t=5;
		}
		if (roll==2)
		{
			for (int i=1;i<=towcnt;++i)
				if (tower[i].towertype==3)tower[i].t3t=0;
		}
		if (roll==3&&!tendone)
		{
			for (int i=1;i<=towcnt;++i)
				if (tower[i].towertype==3)tower[i].t3t=4;
			tcnt=10;
			tendone=true;
			for (int i=0;i<tcnt;++i)
			{
				towers[i]=600+600.0f/(double)tcnt*i+12;
				CreateTower3(200,towers[i],428,3,4);
				CreateTower3(600,towers[i],428,3,4);
			}
		}
	}
}
void Level1Part3()
{
	frameleft=AMinute;
	if (towcnt!=50&&towcnt!=0)return ClearAll();
	DisableAllTower=false;bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Double-directed Labyrinth!");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	for (int i=1;i<=25;++i)
		CreateTower3(772,i*24-24,1714,2,2),
		CreateTower3(28,i*24-12,1714,2,2);
	for (int i=1;i<=towcnt;++i)
		if (tower[i].RendColor==0x80FFFFFF)
			tower[i].RendColor=0x00FFFFFF;
	for (int i=1;i<=towcnt;++i)
		if ((tower[i].RendColor>>24)<=0x80)
			tower[i].RendColor=tower[i].RendColor+0x01FFFFFF;
		else
		{
			++part;
			return;
		}
}
int labyred;
void Level1Part4()
{
	if (frameleft<=TwentySeconds)
	{
		if (LOWFPS)labyred+=17;else ++labyred;
		if (labyred>=1500)CreateBullet6(rand()%800,rand()%600,2,0,1,12,true),labyred=0;
	}
	if (frameleft<=TenSeconds&&tower[1].towertimer>857)
	{
		for (int i=1;i<=towcnt;++i)tower[i].towertimer=857;
	}
}
BCircle Level2Circle,Level2Circle2;
Bullet* fakes[12];
double L2D;
void Level2Part0()
{
	frameleft=50;L2D=0;
	if (towcnt==50)
	{
		ClearAll();
		return;
	}
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("\
Level 2-Polygon Mystery\n\
Place yourself correctly!\
");
		IfCallLevel=false;
	}
	if (Current_Position==1)
	{
		frameleft=0;
		return;
	}
}
void Level2Part1()
{
	frameleft=AMinute;
	Level2Circle.Init(230,pi/12000,96,vector2d(400,300));
	Level2Circle2.Init(270,-pi/12000,96,vector2d(400,300));
	CreateTower3_fixeddir(400,50,300,3,-2.0f/3.0f*pi);
	CreateTower3_fixeddir(400,51,300,3,-1.0f/3.0f*pi);
	//=======
	CreateTower3_fixeddir(400,550,300,3,2.0f/3.0f*pi);
	CreateTower3_fixeddir(400,549,300,3,1.0f/3.0f*pi);
	//=======
	CreateTower3_fixeddir(616.51,175,300,3,0);
	CreateTower3_fixeddir(616.51,176,300,3,-1.0f/3.0f*pi);
	//=======
	CreateTower3_fixeddir(183.49,175,300,3,-pi);
	CreateTower3_fixeddir(183.49,176,300,3,-2.0f/3.0f*pi);
	//=======
	CreateTower3_fixeddir(616.51,425,300,3,0);
	CreateTower3_fixeddir(616.51,424,300,3,1.0f/3.0f*pi);
	//=======
	CreateTower3_fixeddir(183.49,425,300,3,-pi);
	CreateTower3_fixeddir(183.49,424,300,3,2.0f/3.0f*pi);
	for (int i=0;i<6;++i)fakes[i]=&bullet[CreateBullet6(400,300,0,999999999,1,1,false)];
	++part;
}
void Level2Part2()
{
	Level2Circle.Update();
	Level2Circle2.Update();
	L2D+=hge->Timer_GetDelta();
	double base=Level2Circle.GetRad();
	double r=(Level2Circle.GetRange()+Level2Circle2.GetRange())/2.0f;
	for (int i=0;i<6;++i)
	fakes[i]->bulletpos=vector2d(400+r*cos(base+i*pi/3.0f),300+r*sin(base+i*pi/3.0f));
	if (L2D>=1.5)
	{
		L2D=0;
		for (int i=0;i<6;++i)
			CreateBullet6(403+r*cos(base+i*pi/3.0f),303+r*sin(base+i*pi/3.0f),
			              2,0,1,6,true),clockrot=0;
	}
}
void Level2Part3()
{
	frameleft=AMinute;
	for (int i=0;i<6;++i)fakes[i]->exist=false;
	for (int i=0;i<6;++i)fakes[i]=&bullet[CreateBullet7(400,300,0,999999999,false)];
	whicnt=3;clockrot=deltarot=0;++part;
}
void Level2Part4()
{
	Level2Circle.Update();
	Level2Circle2.Update();
	L2D+=hge->Timer_GetDelta();
	double base=Level2Circle.GetRad();
	double r=(Level2Circle.GetRange()+Level2Circle2.GetRange())/2.0f;
	for (int i=0;i<6;++i)
	fakes[i]->bulletpos=vector2d(400+r*cos(base+i*pi/3.0f),300+r*sin(base+i*pi/3.0f));
	if (L2D>=5)
	{
		L2D=0;
		for (int i=0;i<6;++i)
			CreateBullet7(403+r*cos(base+i*pi/3.0f),303+r*sin(base+i*pi/3.0f),
			              2,0,true);
	}
}
void Level2Part5()
{
	frameleft=TenSeconds/2;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("You've got 5 seconds to choose a fine place...");
		return;
	}
	++part;
}
Laser Lock;
void Level2Part6()
{
	Level2Circle.Update();
	Level2Circle2.Update();
	L2D+=hge->Timer_GetDelta();
	double base=Level2Circle.GetRad();
	double r=(Level2Circle.GetRange()+Level2Circle2.GetRange())/2.0f;
	for (int i=0;i<6;++i)
	fakes[i]->bulletpos=vector2d(400+r*cos(base+i*pi/3.0f),300+r*sin(base+i*pi/3.0f));
	if (L2D>=5)
	{
		L2D=0;
		for (int i=0;i<6;++i)
			CreateBullet7(403+r*cos(base+i*pi/3.0f),303+r*sin(base+i*pi/3.0f),
			              2,0,true);
	}
	if (frameleft<TenSeconds/20)++part,frameleft=AMinute;
}
void Level2Part7()
{
	if (!playerLockY)playerLockY=true;
	Level2Circle.Update();
	Level2Circle2.Update();
	L2D+=hge->Timer_GetDelta();
	double base=Level2Circle.GetRad();
	double r=(Level2Circle.GetRange()+Level2Circle2.GetRange())/2.0f;
	for (int i=0;i<6;++i)
	fakes[i]->bulletpos=vector2d(400+r*cos(base+i*pi/3.0f),300+r*sin(base+i*pi/3.0f));
	if (L2D>=5)
	{
		L2D=0;
		for (int i=0;i<6;++i)
			CreateBullet7(403+r*cos(base+i*pi/3.0f),303+r*sin(base+i*pi/3.0f),
			              2,0,true);
	}
}
double L2D1;
void Level2Part8()
{
	frameleft=ThirtySeconds;L2D1=0;
	playerLockY=false;
	for (int i=6;i<12;++i)fakes[i]=&bullet[CreateBullet6(400,300,0,999999999,1,1,false)];
	++part;
}
void Level2Part9()
{
	Level2Circle.Update();
	Level2Circle2.Update();
	L2D+=hge->Timer_GetDelta();
	L2D1+=hge->Timer_GetDelta();
	double base=Level2Circle.GetRad();
	double base2=Level2Circle2.GetRad();
	double r=(Level2Circle.GetRange()+Level2Circle2.GetRange())/2.0f;
	for (int i=0;i<6;++i)
	fakes[i]->bulletpos=vector2d(400+r*cos(base+i*pi/3.0f),300+r*sin(base+i*pi/3.0f));
	for (int i=6;i<12;++i)
	fakes[i]->bulletpos=vector2d(400+r*cos(base2+i*pi/3.0f),300+r*sin(base2+i*pi/3.0f));
	if (L2D1>=2)
	{
		L2D1=0;
		for (int i=0;i<6;++i)
		CreateBullet6(403+r*cos(base2+i*pi/3.0f),303+r*sin(base2+i*pi/3.0f),
			              2,0,1,6,true),clockrot=0;
	}
	if (L2D>=5)
	{
		L2D=0;
		for (int i=0;i<6;++i)
			CreateBullet7(403+r*cos(base+i*pi/3.0f),303+r*sin(base+i*pi/3.0f),
			              2,0,true);
	}
}
void Level3Part0()
{
	frameleft=50;
	if (towcnt==50)
	{
		ClearAll();
		return;
	}
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("\
Level 3-Missing Colour\n\
A negative omen...\
");
		IfCallLevel=false;
	}
	if (Current_Position==1)
	{
		frameleft=0;
		return;
	}
}
void Level3Part1()
{
	frameleft=ThirtySeconds;
	if (towcnt!=1&&towcnt!=0)return ClearAll();
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Meet my new weapon...Is it cool?");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	CreateTower8(400,300,857,3,57,30,false);
	for (int i=1;i<=towcnt;++i)
		if (tower[i].RendColor==0x80FFFFFF)
			tower[i].RendColor=0x00FFFFFF;
	for (int i=1;i<=towcnt;++i)
		if ((tower[i].RendColor>>24)<=0x80)
			tower[i].RendColor=tower[i].RendColor+0x01FFFFFF;
		else
		{
			IfCallLevel=false;
			return;
		}
}
void Level3Part2()
{
	frameleft=ThirtySeconds;
	if (towcnt!=4&&towcnt!=0)return ClearAll(false);
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("What about quad reflective towers...?");
		All2pnt();
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	CreateTower8(30,10,1250,3,57,15,false);
	CreateTower8(746,10,1250,3,57,15,false);
	CreateTower8(30,556,1250,3,57,15,false);
	CreateTower8(746,556,1250,3,57,15,false);
	for (int i=1;i<=towcnt;++i)
		if (tower[i].RendColor==0x80FFFFFF)
			tower[i].RendColor=0x00FFFFFF;
	for (int i=1;i<=towcnt;++i)
		if ((tower[i].RendColor>>24)<=0x80)
			tower[i].RendColor=tower[i].RendColor+0x01FFFFFF;
		else
		{
			IfCallLevel=false;
			return;
		}
}
TROF fr[6][6];
int cur;
double elasped;
void Level3Part3()
{
	frameleft=AMinute;
	if (towcnt!=1&&towcnt!=0)return ClearAll(false);
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		All2pnt();
		ShowTip("Precise mode is not so precise as expected...");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	CreateTower8(400,300,999999999,0,999999999,0,false);
	for (int i=1;i<=towcnt;++i)
		if (tower[i].RendColor==0x80FFFFFF)
			tower[i].RendColor=0x00FFFFFF;
	for (int i=1;i<=towcnt;++i)
		if ((tower[i].RendColor>>24)<=0x80)
			tower[i].RendColor=tower[i].RendColor+0x01FFFFFF;
		else
		{
			for (int k=0;k<6;++k)
			for (int i=0;i<6;++i)
			{
				fr[k][i].cnt=10;
				fr[k][i].drad=(i+1)*pi/3.0f;
				fr[k][i].srad=i*pi/3.0f;
				fr[k][i].delay=750;
				fr[k][i].stage=-1;
				if (k==0)fr[k][i].init();
			}
			++part;
			elasped=0;cur=0;
			return;
		}
}
void Level3Part4()
{
	if (frameleft<TwentySeconds&&tower[1].towertimer==999999999)
	{
		tower[1].towertimer=tower[1].curtimer=1500;
		tower[1].towertimer2=100;
		tower[1].bulletspeed=3;tower[1].shotcount=tower[1].curshotcount=10;
	}
	for (int k=0;k<6;++k)
	for (int i=0;i<6;++i)
	fr[k][i].update();
	elasped+=hge->Timer_GetDelta();
	if (elasped>3)
	{
		elasped=0;++cur;
		if (cur>=6)cur=0;
		double sr=(rand()%10)*pi/30.0f;
		for (int i=0;i<6;++i)
		{
			fr[cur][i].drad=(i+1)*pi/3.0f+sr;
			fr[cur][i].srad=i*pi/3.0f+sr;
			fr[cur][i].init();
		}
	}
}
double l3p5brk;
void Level3Part5()
{
	frameleft=ThirtySeconds;
	if (towcnt!=0)return ClearAll(false);
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		All2pnt();BTarg.TargHide();
		ShowTip("Well, here is a...");
		return;
	}
	++part;l3p5brk=0;
}
void Level3Part6()
{
	l3p5brk+=hge->Timer_GetDelta();
	if (l3p5brk>0.2)
	{
		l3p5brk=0;
		for (int i=1;i<=8;++i)DirectBullet(bullet[CreateBullet8(i*100-50,20,2,false)],-pi/2);
	}
}
void Level4Part0()
{
	frameleft=50;All2pnt();towcnt=0;
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("\
Level 4-Reunion\n\
What was the weather like yesterday?...\n\
");
		IfCallLevel=false;
	}
	if (Current_Position==1)
	{
		frameleft=0;bulcnt=0;BTarg.TargHide();
		return;
	}
}
void Level4Part1()
{
	frameleft=ThirtySeconds;
	if (towcnt!=1&&towcnt!=0)return ClearAll();
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Where is this idea from?");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	CreateTower9(400,300,1000,4,750,36,750);
	for (int i=1;i<=towcnt;++i)
		if (tower[i].RendColor==0x80FFFFFF)
			tower[i].RendColor=0x00FFFFFF;
	for (int i=1;i<=towcnt;++i)
		if ((tower[i].RendColor>>24)<=0x80)
			tower[i].RendColor=tower[i].RendColor+0x01FFFFFF;
		else
		{
			IfCallLevel=false;
			return;
		}
}
Bullet* redirs[400];int cred;
void Level4Part2()
{
	frameleft=TenSeconds/2;clrtime=0;
	if (towcnt==1)
	{
		ClearAll();
		return;
	}
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("...");
	}
	if (Current_Position==1)
	{
		++part;memset(redirs,0,sizeof(redirs));cred=-1;
		ATarg.TargShow();
		posx=10,posy=10,doneredir=false;
	}
}
void Level4Part3()
{
	if (!LOWFPS)++fskp;else fskp+=17;
	if (fskp>30)
	{
		fskp=0;
		if (posx<766)
		{
			posx+=12;
			redirs[++cred]=&bullet[CreateBullet9(posx,posy,0,999999,1,999999)];
		}
		else
		{
			if (posy<566)
			{
				posy+=12;
				redirs[++cred]=&bullet[CreateBullet9(posx,posy,0,999999,1,999999)];
			}
			else
				if (!doneredir)
					for (int i=0;i<cred;++i)
						redirs[i]->redir(ATarg.targpos),redirs[i]->bulletspeed=4,doneredir=true;
		}
	}
}
void Level4Part4()
{
	frameleft=TenSeconds/2;clrtime=0;
	DisableAllTower=false;
	if (Current_Position==1)
	{
		++part;memset(redirs,0,sizeof(redirs));cred=-1;
		posx2=766,posy2=566,doneredir=false;
	}
}
void Level4Part5()
{
	if (!LOWFPS)++fskp;else fskp+=17;
	if (fskp>30)
	{
		fskp=0;
		if (posx2>10)
		{
			posx2-=12;
			redirs[++cred]=&bullet[CreateBullet9(posx2,posy2,0,999999,1,999999)];
		}
		else
		{
			if (posy2>10)
			{
				posy2-=12;
				redirs[++cred]=&bullet[CreateBullet9(posx2,posy2,0,999999,1,999999)];
			}
			else
				if (!doneredir)
					for (int i=0;i<cred;++i)
						redirs[i]->redir(ATarg.targpos),redirs[i]->bulletspeed=4,doneredir=true;
		}
	}
}
void Level4Part6()
{
	frameleft=TenSeconds/10*4;clrtime=0;
	DisableAllTower=false;
	if (Current_Position==1)
	{
		++part;memset(redirs,0,sizeof(redirs));cred=-1;
		ATarg.TargShow();
		posx=10,posy=10,doneredir=false;
	}
}
void Level4Part7()
{
	if (!LOWFPS)++fskp;else fskp+=17;
	if (fskp>30)
	{
		fskp=0;
		if (posx<766)
		{
			posx+=12;
			redirs[++cred]=&bullet[CreateBullet9(posx,posy,0,999999,1,999999)];
		}
		else
		{
			if (posy<566)
			{
				posy+=12;
				redirs[++cred]=&bullet[CreateBullet9(posx,posy,0,999999,1,999999)];
			}
			else
				if (!doneredir)
					for (int i=0;i<cred;++i)
						redirs[i]->redir(ATarg.targpos),redirs[i]->bulletspeed=4,doneredir=true;
		}
	}
}
void Level4Part8()
{
	frameleft=TenSeconds/10*4;clrtime=0;
	DisableAllTower=false;
	if (Current_Position==1)
	{
		++part;memset(redirs,0,sizeof(redirs));cred=-1;
		posx2=766,posy2=566,doneredir=false;
	}
}
void Level4Part9()
{
	if (!LOWFPS)++fskp;else fskp+=17;
	if (fskp>30)
	{
		fskp=0;
		if (posx2>10)
		{
			posx2-=12;
			redirs[++cred]=&bullet[CreateBullet9(posx2,posy2,0,999999,1,999999)];
		}
		else
		{
			if (posy2>10)
			{
				posy2-=12;
				redirs[++cred]=&bullet[CreateBullet9(posx2,posy2,0,999999,1,999999)];
			}
			else
				if (!doneredir)
					for (int i=0;i<cred;++i)
						redirs[i]->redir(ATarg.targpos),redirs[i]->bulletspeed=4,doneredir=true;
		}
	}
}
void Level4Part10()
{
	frameleft=TenSeconds/10*3;clrtime=0;
	DisableAllTower=false;
	if (Current_Position==1)
	{
		++part;memset(redirs,0,sizeof(redirs));cred=-1;
		ATarg.TargShow();
		posx=10,posy=10,doneredir=false;
	}
}
void Level4Part11()
{
	if (!LOWFPS)++fskp;else fskp+=17;
	if (fskp>15)
	{
		fskp=0;
		if (posx<766)
		{
			posx+=12;
			redirs[++cred]=&bullet[CreateBullet9(posx,posy,0,999999,1,999999)];
		}
		else
		{
			if (posy<566)
			{
				posy+=12;
				redirs[++cred]=&bullet[CreateBullet9(posx,posy,0,999999,1,999999)];
			}
			else
				if (!doneredir)
					for (int i=0;i<cred;++i)
						redirs[i]->redir(ATarg.targpos),redirs[i]->bulletspeed=4,doneredir=true;
		}
	}
}
void Level4Part12()
{
	frameleft=TenSeconds/10*3;clrtime=0;
	DisableAllTower=false;
	if (Current_Position==1)
	{
		++part;memset(redirs,0,sizeof(redirs));cred=-1;
		posx2=766,posy2=566,doneredir=false;
	}
}
void Level4Part13()
{
	if (!LOWFPS)++fskp;else fskp+=17;
	if (fskp>15)
	{
		fskp=0;
		if (posx2>10)
		{
			posx2-=12;
			redirs[++cred]=&bullet[CreateBullet9(posx2,posy2,0,999999,1,999999)];
		}
		else
		{
			if (posy2>10)
			{
				posy2-=12;
				redirs[++cred]=&bullet[CreateBullet9(posx2,posy2,0,999999,1,999999)];
			}
			else
				if (!doneredir)
					for (int i=0;i<cred;++i)
						redirs[i]->redir(ATarg.targpos),redirs[i]->bulletspeed=4,doneredir=true;
		}
	}
}
void Level4Part14()
{
	frameleft=TenSeconds/10*2;clrtime=0;
	DisableAllTower=false;
	if (Current_Position==1)
	{
		++part;memset(redirs,0,sizeof(redirs));cred=-1;
		ATarg.TargShow();
		posx=10,posy=10,doneredir=false;
	}
}
void Level4Part15()
{
	if (!LOWFPS)++fskp;else fskp+=17;
	if (fskp>15)
	{
		fskp=0;
		if (posx<766)
		{
			posx+=12;
			redirs[++cred]=&bullet[CreateBullet9(posx,posy,0,999999,1,999999)];
		}
		else
		{
			if (posy<566)
			{
				posy+=12;
				redirs[++cred]=&bullet[CreateBullet9(posx,posy,0,999999,1,999999)];
			}
			else
				if (!doneredir)
					for (int i=0;i<cred;++i)
						redirs[i]->redir(ATarg.targpos),redirs[i]->bulletspeed=4,doneredir=true;
		}
	}
}
void Level4Part16()
{
	frameleft=TenSeconds/10*2;clrtime=0;
	DisableAllTower=false;
	if (Current_Position==1)
	{
		++part;memset(redirs,0,sizeof(redirs));cred=-1;
		posx2=766,posy2=566,doneredir=false;
	}
}
void Level4Part17()
{
	if (!LOWFPS)++fskp;else fskp+=17;
	if (fskp>15)
	{
		fskp=0;
		if (posx2>10)
		{
			posx2-=12;
			redirs[++cred]=&bullet[CreateBullet9(posx2,posy2,0,999999,1,999999)];
		}
		else
		{
			if (posy2>10)
			{
				posy2-=12;
				redirs[++cred]=&bullet[CreateBullet9(posx2,posy2,0,999999,1,999999)];
			}
			else
				if (!doneredir)
					for (int i=0;i<cred;++i)
						redirs[i]->redir(ATarg.targpos),redirs[i]->bulletspeed=4,doneredir=true;
		}
	}
}
void Level4Part18()
{
	frameleft=TenSeconds/2;clrtime=0;
	DisableAllTower=false;
	if (Current_Position==1)
	{
		++part;memset(redirs,0,sizeof(redirs));cred=-1;
		posx=10,posy=10,posx2=766,posy2=566,doneredir=false;
	}
}
void Level4Part19()
{
	if (!LOWFPS)++fskp;else fskp+=17;
	if (fskp>33)
	{
		fskp=0;
		if (posx2>10)
		{
			posx2-=24;
			redirs[++cred]=&bullet[CreateBullet9(posx2,posy2,0,999999,1,999999)];
		}
		else
		{
			if (posy2>10)
			{
				posy2-=24;
				redirs[++cred]=&bullet[CreateBullet9(posx2,posy2,0,999999,1,999999)];
			}
			else
				if (!doneredir)
					for (int i=0;i<cred;++i)
						redirs[i]->redir(ATarg.targpos),redirs[i]->bulletspeed=2,doneredir=true;
		}
		if (posx<766)
		{
			posx+=24;
			redirs[++cred]=&bullet[CreateBullet9(posx,posy,0,999999,1,999999)];
		}
		else
		{
			if (posy<566)
			{
				posy+=24;
				redirs[++cred]=&bullet[CreateBullet9(posx,posy,0,999999,1,999999)];
			}
		}

	}
}
double rot1,dta1,rot2,dta2,spd2,elsp1;
void Level4Part20()
{
	frameleft=AMinute;All2pnt();towcnt=0;
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Double Kill, right?");
	}
	if (Current_Position==1)
	{
		BTarg.TargHide();ATarg.TargHide();CreateTower3(400,300,999999999,0,0);
		rot1=dta1=rot2=dta2=elsp1=0;spd2=1;++part;IfCallLevel=true;
		return;
	}
}
void Level4Part21()
{
	elsp1+=hge->Timer_GetDelta();
	if (elsp1<=0.3)return;
	elsp1=0;
	int times=1;if (LOWFPS)times=17;
	for (int i=1;i<=times;++i)
	{
		dta1+=2*pi/180;dta2-=2*pi/180;spd2=1+4.0f*((AMinute-frameleft)/(double)AMinute);
		rot1+=dta1;rot2+=dta2;
	}
	for (int i=0;i<6;++i)CreateBullet2(400,300,4,rot1+i*pi/3);
	for (int i=0;i<6;++i)CreateBullet2(400,300,spd2,rot2+i*pi/3);
}
void Level4Part22()
{
	frameleft=AMinute;clrtime=1;
	if (towcnt==1)
	{
		ClearAll();
		return;
	}
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Have problem breathing?\n...so try this!");
	}
	if (Current_Position==1)
	{
		++part;
		pnt1=CreateTower3(10,10,50,20,1);
		pnt2=CreateTower3(790,10,50,20,1);
		CreateTower9(400,10,2000,2,2000,6,1000);
	}
}
void Level4Part23()
{
	if (!LOWFPS)
		tower[pnt1].towerpos.x+=0.006,tower[pnt2].towerpos.x-=0.006;
	else
		tower[pnt1].towerpos.x+=0.006*17,tower[pnt2].towerpos.x-=0.006*17;
}
void Level4Part24()
{
	frameleft=AMinute;
	if (towcnt!=5&&towcnt!=0)return ClearAll(false);
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;All2pnt();
		Current_Position=2;
		ShowTip("Let's meet a more classical circle-drawing part...\n\
...as the end of this level...\nCan you draw perfectly?");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	CreateTower4(400,300,2000,2.5);
	CreateTower1(9,9,2000,3);
	CreateTower1(767,11,2000,3);
	CreateTower1(9,567,2000,3);
	CreateTower1(767,567,2000,3);
	for (int i=1;i<=towcnt;++i)
		if (tower[i].RendColor==0x80FFFFFF)
			tower[i].RendColor=0x00FFFFFF;
	for (int i=1;i<=towcnt;++i)
		if ((tower[i].RendColor>>24)<=0x80)
			tower[i].RendColor=tower[i].RendColor+0x01FFFFFF;
		else
		{
			++part;
			return;
		}
}
void Level4Part25()
{
	for (int i=2;i<=5;++i)
	tower[i].towertimer=((frameleft)/(double)AMinute)*1800+200;
}
void Level5Part0()
{
	frameleft=50;All2pnt();towcnt=0;
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		LE_Active=true;letex=TLeaf;lescale=0.75;letr=TextureRect(0,0,108,108);lecolor=0xCCCC3333;
		Current_Position=2;
		ShowTip("\
Level 5-Crazy Autumn\n\
Autumn is considered as a miserable season for \n\
thousands of years...\n\
This autumn, however, is coming too fast...\
");
		IfCallLevel=false;
	}
	if (Current_Position==1)
	{
		frameleft=0;
		return;
	}
}
void Level5Part1()
{
	frameleft=ThirtySeconds;
	if (towcnt!=2&&towcnt!=0)return ClearAll(false);
	DisableAllTower=false;
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	CreateTower9(400,300,2000,3,1000,36,750);
	CreateTower4(400,50,2000,2.5,0);
	for (int i=1;i<=towcnt;++i)
		if (tower[i].RendColor==0x80FFFFFF)
			tower[i].RendColor=0x00FFFFFF;
	for (int i=1;i<=towcnt;++i)
		if ((tower[i].RendColor>>24)<=0x80)
			tower[i].RendColor=tower[i].RendColor+0x01FFFFFF;
		else
		{
			IfCallLevel=false;
			return;
		}
}
void Level5Part2()
{
	frameleft=ThirtySeconds;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;All2pnt();
		Current_Position=2;
		ShowTip("What if your cheaser is faster than you...");
		return;
	}
	tower[2].bulletspeed=4;IfCallLevel=false;
}
int pos,lsrbrk;
bool rev;
/**********************\
 *  Vortex of Leaves  *
\**********************/
void Level5Part3()
{
	frameleft=AMinute;
	if (towcnt!=0)return (void)ClearAll();
	Lasercnt=12;
	for (int i=1;i<=12;++i)
	{
		laser[i].Init(32);
		laser[i].SetTexture(SprSheet,0,264,248,8);
		laser[i].RenCtr.x=406,laser[i].RenCtr.y=306;
	}
	++part;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;All2pnt();
		Current_Position=2;
		ShowTip("Vortex of leaves...");
		return;
	}
}
void Level5Part4()
{
	bool shot=false;
	if (LOWFPS)lsrbrk+=16;
	if (++lsrbrk>=100)lsrbrk=0,shot=true,++pos;
	if (pos==32)
	{
		pos=0;rev=!rev;
		for (int i=1;i<=bulcnt;++i)
			if (bullet[i].bulletspeed<1e-5)
				bullet[i].bulletaccel=0.001,
				bullet[i].limv=1+1.5*(frameleft/(double)AMinute);
	}
	for (int i=1;i<=12;++i)
	{
		double initrad=pi/6.0f*(i-1);
		double dist;
		for (int j=0;j<32;++j)
		{
			dist=j*Resd;
			double trad;
			if (rev)trad=initrad-j*pi/36.0f;else trad=initrad+j*pi/36.0f;
			vector2d t,tt,s;
			t.x=cos(trad)*dist;
			t.y=sin(trad)*dist;
			dist=(j+1)*Resd;
			if (rev)trad=initrad-(j+1)*pi/36.0f;else trad=initrad+(j+1)*pi/36.0f;
			tt.x=cos(trad)*dist;tt.y=sin(trad)*dist;
			tt.x-=t.x;tt.y-=t.y;trad=tt.x;tt.x=tt.y;tt.y=-trad;
			trad=sqrt(sqr(tt.x)+sqr(tt.y));
			tt.x/=trad;tt.y/=trad;
			//pos: 0~8, mult:0~8
			//pos: 24~32, mult: 8~0
			if (pos>=24)
				tt.x*=(32-pos)/1.5f,tt.y*=(32-pos)/1.5f;
			else
				if (pos<=8)
					tt.x*=pos/1.5f,tt.y*=pos/1.5f;
				else
					tt.x*=5.33f,tt.y*=5.33f;
			//We only consider collisions when pos is between 9 and 23.
			if (pos>9&&pos<23)laser[i].EnableColl=true;else laser[i].EnableColl=false;
			s.x=t.x+tt.x;s.y=t.y+tt.y;
			if (j==31)
				for (int k=31;k<MaxRes;++k)
					laser[i].Setdata(k,t,s,0xEEFF8800);
			else
			laser[i].Setdata(j,t,s,0xEEFF8800);
			trad=initrad+j*pi/36.0f;
			if (shot&&j==pos)CreateBullet2(400+t.x,300+t.y,0.0f,rand()%100,1);
		}
		if (pos>8&&pos<23)
			laser[i].EnableColl=true;
		else
			laser[i].EnableColl=false;
	}
}
Bullet* tbuls[1000];double lv5brk;
void Level5Part5()
{
	frameleft=AMinute;All2pnt();towcnt=0;Lasercnt=0;
	memset(tbuls,0,sizeof(tbuls));lv5brk=0;++part;
}
void Level5Part6()
{
	lv5brk+=hge->Timer_GetDelta();
	if (lv5brk<=0.3)return;
	lv5brk=0;
	for (int i=1;i<=9;++i)
	for (int j=0;j<1000;++j)
	if (!tbuls[j])
	{
		tbuls[j]=&bullet[CreateBullet2(i*80,570,3,0.5*pi)];
		break;
	}
	for (int j=0;j<1000;++j)
	if (tbuls[j]&&tbuls[j]->bulletpos.y<150)
	{
		if (rand()%1000>800)
		{
			if (rand()%1000>500)
				CreateBullet6(tbuls[j]->bulletpos.x,tbuls[j]->bulletpos.y,3,200,1,18);
			else
				if (rand()%1000>850)
					CreateBullet9(tbuls[j]->bulletpos.x,tbuls[j]->bulletpos.y,3,500,18,300);
		}
		tbuls[j]->exist=false;
		tbuls[j]=NULL;
	}
}
double tbrk;
void Level5Part7()
{
	frameleft=ThirtySeconds;Dis8ref=true;tbrk=0;
	if (towcnt!=33&&towcnt!=0)return ClearAll();
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Threatening effect of high speed bullets");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	for (int i=1;i<=33;++i)CreateTower8(i*24-12,12,500,10,20,30);
	for (int i=1;i<=towcnt;++i)
		if (tower[i].RendColor==0x80FFFFFF)
			tower[i].RendColor=0x00FFFFFF;
	for (int i=1;i<=towcnt;++i)
		if ((tower[i].RendColor>>24)<=0x80)
			tower[i].RendColor=tower[i].RendColor+0x01FFFFFF;
		else
		{
			++part;All2pnt();
			return;
		}
}
void Level5Part8()
{
	tbrk+=hge->Timer_GetDelta();
	if (tbrk<=3)return;
	tbrk=0;int tg;
	if (rand()%1000>=500)tg=CreateBullet9(200,12,8,300,12,200);else tg=CreateBullet9(600,12,8,300,12,200);
	bullet[tg].redir(playerpos);
}
void Level5Part9()
{
	frameleft=ThirtySeconds;Dis8ref=true;tbrk=0;
	if (towcnt!=66&&towcnt!=0)return ClearAll();
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Do not panic!");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	for (int i=1;i<=33;++i)CreateTower8(i*24-12,12,750,1,1,1),CreateTower8(i*24-12,588,750,1,1,1);
	for (int i=1;i<=towcnt;++i)
		if (tower[i].RendColor==0x80FFFFFF)
			tower[i].RendColor=0x00FFFFFF;
	for (int i=1;i<=towcnt;++i)
		if ((tower[i].RendColor>>24)<=0x80)
			tower[i].RendColor=tower[i].RendColor+0x01FFFFFF;
		else
		{
			++part;All2pnt();
			return;
		}
}
void Level5Part10()
{
	tbrk+=hge->Timer_GetDelta();
	if (tbrk<=3)return;
	tbrk=0;
	for (int i=0;i<6;++i)
	{
		int p=CreateBullet2(playerpos.x+cos(i*pi/3.0f)*6,12+sin(i*pi/3.0f)*6,2,-pi/2);
		bullet[p].alterColor=orange;
	}
}
void Level5Part11()
{
	frameleft=TenSeconds/10*2;clrtime=0;Dis8ref=false;
	if (towcnt==66)
	{
		ClearAll();
		return;
	}
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("They are getting out of control...\n\
Have you noticed that strange things are happening?...");
	}
	if (Current_Position==1)
	{
		++part;memset(redirs,0,sizeof(redirs));cred=-1;All2pnt();
		ATarg.TargShow();
		posx=10,posy=10,doneredir=false;
	}
}
void Level5Part12()
{
	if (!LOWFPS)++fskp;else fskp+=17;
	if (fskp>15)
	{
		fskp=0;
		if (posx<766)
		{
			posx+=12;
			redirs[++cred]=&bullet[CreateBullet9(posx,posy,0,999999,1,999999)];
			redirs[++cred]=&bullet[CreateBullet9((posx-400)*0.95+400,(posy-300)*0.95+300,0,999999,1,999999)];
		}
		else
		{
			if (posy<566)
			{
				posy+=12;
				redirs[++cred]=&bullet[CreateBullet9(posx,posy,0,999999,1,999999)];
				redirs[++cred]=&bullet[CreateBullet9((posx-400)*0.95+400,(posy-300)*0.95+300,0,999999,1,999999)];
			}
			else
				if (!doneredir)
					for (int i=0;i<=cred;++i)
						redirs[i]->redir(ATarg.targpos),redirs[i]->bulletspeed=4,doneredir=true;
		}
	}
}
void Level5Part13()
{
	frameleft=TenSeconds/10*2;clrtime=0;
	DisableAllTower=false;
	if (Current_Position==1)
	{
		++part;memset(redirs,0,sizeof(redirs));cred=-1;
		posx2=766,posy2=566,doneredir=false;
	}
}
void Level5Part14()
{
	if (!LOWFPS)++fskp;else fskp+=17;
	if (fskp>15)
	{
		fskp=0;
		if (posx2>10)
		{
			posx2-=12;
			redirs[++cred]=&bullet[CreateBullet9(posx2,posy2,0,999999,1,999999)];
			redirs[++cred]=&bullet[CreateBullet9((posx2-400)*0.95+400,(posy2-300)*0.95+300,0,999999,1,999999)];
		}
		else
		{
			if (posy2>10)
			{
				posy2-=12;
				redirs[++cred]=&bullet[CreateBullet9(posx2,posy2,0,999999,1,999999)];
				redirs[++cred]=&bullet[CreateBullet9((posx2-400)*0.95+400,(posy2-300)*0.95+300,0,999999,1,999999)];
			}
			else
				if (!doneredir)
					for (int i=0;i<=cred;++i)
						redirs[i]->redir(ATarg.targpos),redirs[i]->bulletspeed=4,doneredir=true;
		}
	}
}
void Level5Part15()
{
	frameleft=TenSeconds/10*2;clrtime=0;
    ++part;memset(redirs,0,sizeof(redirs));cred=-1;
    posx=10,posy=10,doneredir=false;
}
void Level5Part16()
{
	if (!LOWFPS)++fskp;else fskp+=17;
	if (fskp>15)
	{
		fskp=0;
		if (posx<766)
		{
			posx+=12;
			redirs[++cred]=&bullet[CreateBullet9(posx,posy,0,999999,1,999999)];
			redirs[++cred]=&bullet[CreateBullet9((posx-400)*0.95+400,(posy-300)*0.95+300,0,999999,1,999999)];
			redirs[++cred]=&bullet[CreateBullet9((posx-400)*0.9+400,(posy-300)*0.9+300,0,999999,1,999999)];
		}
		else
		{
			if (posy<566)
			{
				posy+=12;
				redirs[++cred]=&bullet[CreateBullet9(posx,posy,0,999999,1,999999)];
				redirs[++cred]=&bullet[CreateBullet9((posx-400)*0.95+400,(posy-300)*0.95+300,0,999999,1,999999)];
				redirs[++cred]=&bullet[CreateBullet9((posx-400)*0.9+400,(posy-300)*0.9+300,0,999999,1,999999)];
			}
			else
				if (!doneredir)
					for (int i=0;i<=cred;++i)
						redirs[i]->redir(ATarg.targpos),redirs[i]->bulletspeed=4,doneredir=true;
		}
	}
}
void Level5Part17()
{
	frameleft=TenSeconds/10*2;clrtime=0;
	DisableAllTower=false;
	if (Current_Position==1)
	{
		++part;memset(redirs,0,sizeof(redirs));cred=-1;
		posx2=766,posy2=566,doneredir=false;
	}
}
void Level5Part18()
{
	if (!LOWFPS)++fskp;else fskp+=17;
	if (fskp>15)
	{
		fskp=0;
		if (posx2>10)
		{
			posx2-=12;
			redirs[++cred]=&bullet[CreateBullet9(posx2,posy2,0,999999,1,999999)];
			redirs[++cred]=&bullet[CreateBullet9((posx2-400)*0.95+400,(posy2-300)*0.95+300,0,999999,1,999999)];
			redirs[++cred]=&bullet[CreateBullet9((posx2-400)*0.9+400,(posy2-300)*0.9+300,0,999999,1,999999)];
		}
		else
		{
			if (posy2>10)
			{
				posy2-=12;
				redirs[++cred]=&bullet[CreateBullet9(posx2,posy2,0,999999,1,999999)];
				redirs[++cred]=&bullet[CreateBullet9((posx2-400)*0.95+400,(posy2-300)*0.95+300,0,999999,1,999999)];
				redirs[++cred]=&bullet[CreateBullet9((posx2-400)*0.9+400,(posy2-300)*0.9+300,0,999999,1,999999)];
			}
			else
				if (!doneredir)
					for (int i=0;i<=cred;++i)
						redirs[i]->redir(ATarg.targpos),redirs[i]->bulletspeed=4,doneredir=true;
		}
	}
}
double ntrot,ntbrk;
int ntcnt;
void Level5Part19()
{
	frameleft=AMinute;clrtime=0;ntrot=ntbrk=0;ntcnt=0;
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("You are the fish in my barrel.");
	}
	if (Current_Position==1)
	{
		++part;All2pnt();
		ATarg.TargHide();
	}
}
void Level5Part20()
{
	ntbrk+=hge->Timer_GetDelta();
	if (LOWFPS)ntrot+=16*pi/960.0f;else ntrot+=pi/960.0f;
	if (ntbrk<0.01)return;
	ntbrk=0;++ntcnt;if (ntcnt>15)ntcnt=0;
	int a;if (ntcnt==0)
		a=CreateBullet9(400+250*sin(ntrot),300+250*cos(ntrot),2,500,1,500,true);
	else
		a=CreateBullet9(400+250*sin(ntrot),300+250*cos(ntrot),2,999999999,1,999999999,true);
	bullet[a].redattrib=1;bullet[a].redir(vector2d(400,300));
	bullet[a].bulletdir.x=-bullet[a].bulletdir.x;
	bullet[a].bulletdir.y=-bullet[a].bulletdir.y;
	if (ntcnt==0)
		a=CreateBullet9(400+250*sin(ntrot+pi),300+250*cos(ntrot+pi),2,500,1,500,true);
	else
		a=CreateBullet9(400+250*sin(ntrot+pi),300+250*cos(ntrot+pi),2,999999999,1,999999999,true);
	bullet[a].redattrib=1;bullet[a].redir(vector2d(400,300));
	bullet[a].bulletdir.x=-bullet[a].bulletdir.x;
	bullet[a].bulletdir.y=-bullet[a].bulletdir.y;
}
void Level5Part21()
{
	frameleft=ThirtySeconds;
	All2pnt();
	Lasercnt=0;
	CTarg.Init(18,75,5.0f);
	DisableAllTower=false;
	CreateTower1(30,10,500,2);
	CreateTower1(746,10,500,2);
	CreateTower1(30,556,500,2);
	CreateTower1(746,556,500,2);
	++part;
}
void Level5Part22()
{
	int times=1;if (LOWFPS)times=16;
	for (int i=1;i<=times;++i)
		CTarg.SetRange(CTarg.GetRange()-0.002f);
	CTarg.Update();
}
void Level6Part0()
{
	frameleft=50;All2pnt();towcnt=0;
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		LE_Active=true;letex=TSflake;lescale=0.2;letr=TextureRect(0,0,350,350);lecolor=0xCC3366CC;
		Current_Position=2;
		ShowTip("\
Level 6-Peaceful(?) Winter\n\
Look, there's a question mark in the title...\
");
		IfCallLevel=false;
	}
	if (Current_Position==1)
	{
		frameleft=0;
		return;
	}
}
void Level6Part1()
{
	//Some component of this level is in towernbullet...
	frameleft=ThirtySeconds;
	DisableAllTower=false;
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	whicnt=10;
	CreateTower7(400,300,750,3,500);
	for (int i=1;i<=towcnt;++i)
		if (tower[i].RendColor==0x80FFFFFF)
			tower[i].RendColor=0x00FFFFFF;
	for (int i=1;i<=towcnt;++i)
		if ((tower[i].RendColor>>24)<=0x80)
			tower[i].RendColor=tower[i].RendColor+0x01FFFFFF;
		else
		{
			IfCallLevel=false;
			return;
		}
}
int spcnt;double sixrad,sixbrk;
void Level6Part2()
{
	while (towcnt)return ClearAll(false);
	All2pnt();frameleft=TenSeconds;
	++part;spcnt=2;sixrad=sixbrk=0;
	whicnt=1;DisableAllTower=false;
}
void Level6Part3()
{
	sixbrk+=hge->Timer_GetDelta();
	if (sixrad>2*pi)return;
	if (sixbrk<0.04)return;
	sixbrk=0;
	sixrad+=pi/25.0f;
	for (int i=0;i<spcnt;++i)
	{
		int pnt=CreateBullet7(400,300,2,1500);
		bullet[pnt].setdir(pi/2+sixrad+((double)i/(double)spcnt)*2.0f*pi);
	}
}
void Level6Part4()
{
	frameleft=TenSeconds;whrcnt=9;
	++part;spcnt=3;sixrad=sixbrk=0;
	whicnt=1;DisableAllTower=false;
}
void Level6Part5()
{
	sixbrk+=hge->Timer_GetDelta();
	if (sixrad>2*pi)return;
	if (sixbrk<0.04)return;
	sixbrk=0;
	sixrad+=pi/25.0f;
	for (int i=0;i<spcnt;++i)
	{
		int pnt=CreateBullet7(400,300,2.2,1500);
		bullet[pnt].setdir(pi/2+sixrad+((double)i/(double)spcnt)*2.0f*pi);
	}
}
void Level6Part6()
{
	frameleft=TenSeconds;
	++part;spcnt=4;sixrad=sixbrk=0;
	whicnt=1;DisableAllTower=false;
}
void Level6Part7()
{
	sixbrk+=hge->Timer_GetDelta();
	if (sixrad>2*pi)return;
	if (sixbrk<0.04)return;
	sixbrk=0;
	sixrad+=pi/25.0f;
	for (int i=0;i<spcnt;++i)
	{
		int pnt=CreateBullet7(400,300,2.4,1500);
		bullet[pnt].setdir(pi/2+sixrad+((double)i/(double)spcnt)*2.0f*pi);
	}
}
void Level6Part8()
{
	frameleft=TenSeconds;whrcnt=6;
	++part;spcnt=5;sixrad=sixbrk=0;
	whicnt=1;DisableAllTower=false;
}
void Level6Part9()
{
	sixbrk+=hge->Timer_GetDelta();
	if (sixrad>2*pi)return;
	if (sixbrk<0.04)return;
	sixbrk=0;
	sixrad+=pi/25.0f;
	for (int i=0;i<spcnt;++i)
	{
		int pnt=CreateBullet7(400,300,2.6,1500);
		bullet[pnt].setdir(pi/2+sixrad+((double)i/(double)spcnt)*2.0f*pi);
	}
}
void Level6Part10()
{
	frameleft=TenSeconds;whrcnt=6;
	++part;spcnt=6;sixrad=sixbrk=0;
	whicnt=1;DisableAllTower=false;
}
void Level6Part11()
{
	sixbrk+=hge->Timer_GetDelta();
	if (sixrad>2*pi)return;
	if (sixbrk<0.04)return;
	sixbrk=0;
	sixrad+=pi/25.0f;
	for (int i=0;i<spcnt;++i)
	{
		int pnt=CreateBullet7(400,300,2.6,1500);
		bullet[pnt].setdir(pi/2+sixrad+((double)i/(double)spcnt)*2.0f*pi);
	}
}
void Level6Part12()
{
	frameleft=AMinute;clrtime=1;
	if (towcnt!=8&&towcnt)
	{
		ClearAll(false);
		return;
	}
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Get out before you are squashed...");
	}
	if (Current_Position==1)
	{
		++part;squashrev=false;All2pnt();
		CreateTower3(10,10,400,2,1);
		CreateTower3(766,10,400,2,1);
		CreateTower3(10,566,400,2,1);
		CreateTower3(766,566,400,2,1);
		CreateTower1(9,9,1000,1.5);
		CreateTower1(767,11,1000,1.5);
		CreateTower1(9,567,1000,1.5);
		CreateTower1(767,567,1000,1.5);
	}
}
void Level6Part13()
{
	if (!squashrev)
	{
		if (!LOWFPS)
		{
			tower[1].towerpos.x+=0.01;
			tower[1].towerpos.y+=0.007354;
			tower[2].towerpos.x-=0.01;
			tower[2].towerpos.y+=0.007354;
			tower[3].towerpos.x+=0.01;
			tower[3].towerpos.y-=0.007354;
			tower[4].towerpos.x-=0.01;
			tower[4].towerpos.y-=0.007354;
		}
		else
		{
			tower[1].towerpos.x+=0.1;
			tower[1].towerpos.y+=0.07354;
			tower[2].towerpos.x-=0.1;
			tower[2].towerpos.y+=0.07354;
			tower[3].towerpos.x+=0.1;
			tower[3].towerpos.y-=0.07354;
			tower[4].towerpos.x-=0.1;
			tower[4].towerpos.y-=0.07354;
		}
	}
	else
	{
		if (!LOWFPS)
		{
			tower[1].towerpos.x-=0.01;
			tower[1].towerpos.y-=0.007354;
			tower[2].towerpos.x+=0.01;
			tower[2].towerpos.y-=0.007354;
			tower[3].towerpos.x-=0.01;
			tower[3].towerpos.y+=0.007354;
			tower[4].towerpos.x+=0.01;
			tower[4].towerpos.y+=0.007354;
		}
		else
		{
			tower[1].towerpos.x-=0.1;
			tower[1].towerpos.y-=0.07354;
			tower[2].towerpos.x+=0.1;
			tower[2].towerpos.y-=0.07354;
			tower[3].towerpos.x-=0.1;
			tower[3].towerpos.y+=0.07354;
			tower[4].towerpos.x+=0.1;
			tower[4].towerpos.y+=0.07354;
		}
	}
	if (tower[1].towerpos.x>766||tower[1].towerpos.x<10)squashrev=!squashrev;
}
double avabrk,avacurbrk;
bool dir;
void Level6Part14()//Avalanche
{
	frameleft=AMinute;clrtime=1;
	if (towcnt)
	{
		ClearAll(false);
		return;
	}
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Avalanche...");
	}
	if (Current_Position==1)
	{
		++part;All2pnt();avabrk=1.0f;avacurbrk=0;dir=false;
	}
}
void Level6Part15()
{
	avacurbrk+=hge->Timer_GetDelta();
	avabrk=((double)frameleft/(double)AMinute)*0.04f+0.01f;
	if (avacurbrk>avabrk)
	{
		avacurbrk=0;
		int pnt=CreateBullet2(rand()%780+10,200,-6.25,3*pi/2.0f);
		bullet[pnt].limv=2+rand()%7;bullet[pnt].bulletaccel=0.005;
	}
}
void Level6Part16()
{
	frameleft=AMinute;clrtime=2;
	if (towcnt)
	{
		ClearAll(false);
		return;
	}
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("?..");
	}
	if (Current_Position==1)
	{
		++part;All2pnt();avabrk=1.0f;
		avacurbrk=0;dir=false;ATarg.TargShow();
		ATarg.targpos=vector2d(400,300);
		whicnt=3;avacurbrk=0;
	}
}
void Level6Part17()
{
	avacurbrk+=hge->Timer_GetDelta();
	avabrk=((double)frameleft/(double)AMinute)*0.8f+0.2f;
	if (avacurbrk>avabrk)
	{
		avacurbrk=0;
		int pnt;
		if (rand()%100<80)
		pnt=CreateBullet7(ATarg.targpos.x,ATarg.targpos.y,3,500);
		else
		pnt=CreateBullet6(ATarg.targpos.x,ATarg.targpos.y,4,1000);
		bullet[pnt].dist=1;bullet[pnt].bulletdir=vector2d(0,0);
	}
}
//begin hexagon
Bullet bheader[100],*beewx[500];
static int sxcnt,seq,beecnt;
bool brdir;
double offset;
void Level6Part18()
{
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Hexagon loops");
	}
	if (Current_Position==1)
	{
		sxcnt=-1;beecnt=-1;brdir=false;frameleft=TenSeconds;offset=86;
		memset(bheader,0,sizeof(bheader));
		memset(beewx,0,sizeof(beewx));
		avacurbrk=1;avabrk=1;sixbrk=0.1;seq=3;
		for (int i=1;i<=5;++i)
		{
			CreateBullet2(bheader[++sxcnt],offset+2*(i-1)*offset,10,2,-pi/6);
			CreateBullet2(bheader[++sxcnt],offset+2*(i-1)*offset,10,2,-5*pi/6);
		}
		++part;ATarg.TargHide();All2pnt();
	}
}
void Level6Part19()
{
	avacurbrk+=hge->Timer_GetDelta();
	sixbrk+=hge->Timer_GetDelta();
	if (frameleft<TenSeconds/10*1&&!brdir)
	{
		brdir=true;
		for (int i=0;i<=beecnt;++i)
		{
			beewx[i]->bulletaccel=0.001;beewx[i]->limv=1;
			DirectBullet(*beewx[i],(double)(rand()%3140)/1000.0f);
		}
	}
	for (int i=0;i<=sxcnt;++i)ProcessBullet2(bheader[i]);
	if (avacurbrk>avabrk)
	{
		avacurbrk=0;++seq;seq%=4;
		for (int i=0;i<=sxcnt;++i)
		{
			if (i&1)
			{
				switch (seq)
				{
					case 0:DirectBullet(bheader[i],-5*pi/6);break;
					case 1:DirectBullet(bheader[i],-pi/2);break;
					case 2:DirectBullet(bheader[i],-pi/6);break;
					case 3:DirectBullet(bheader[i],-pi/2);break;
				}
			}
			else
			{
				switch (seq)
				{
					case 0:DirectBullet(bheader[i],-pi/6);break;
					case 1:DirectBullet(bheader[i],-pi/2);break;
					case 2:DirectBullet(bheader[i],-5*pi/6);break;
					case 3:DirectBullet(bheader[i],-pi/2);break;
				}
			}
		}
	}
	if (sixbrk>0.2&&!brdir)
	{
		sixbrk=0;
		if (bheader[0].bulletpos.y>610)return;
		for (int i=0;i<=sxcnt;++i)
		{
			beewx[++beecnt]=&bullet[CreateBullet2(bheader[i].bulletpos.x,bheader[i].bulletpos.y,0,pi,true)];
		}
	}
}
void Level6Part20()
{
	sxcnt=-1;beecnt=-1;brdir=false;frameleft=TwentySeconds;offset=43;
	memset(bheader,0,sizeof(bheader));
	memset(beewx,0,sizeof(beewx));
	avacurbrk=0.5;avabrk=0.5;sixbrk=0.1;seq=3;
	for (int i=1;i<=10;++i)
	{
		CreateBullet2(bheader[++sxcnt],offset+2*(i-1)*offset,10,2,-pi/6);
		CreateBullet2(bheader[++sxcnt],offset+2*(i-1)*offset,10,2,-5*pi/6);
	}
	++part;
}
void Level6Part21()
{
	avacurbrk+=hge->Timer_GetDelta();
	sixbrk+=hge->Timer_GetDelta();
	if (frameleft<TenSeconds/10*11&&!brdir)
	{
		brdir=true;
		for (int i=0;i<=beecnt;++i)
		{
			beewx[i]->bulletaccel=0.001;beewx[i]->limv=1;
			DirectBullet(*beewx[i],(double)(rand()%3140)/1000.0f);
		}
	}
	for (int i=0;i<=sxcnt;++i)ProcessBullet2(bheader[i]);
	if (avacurbrk>avabrk)
	{
		avacurbrk=0;++seq;seq%=4;
		for (int i=0;i<=sxcnt;++i)
		{
			if (i&1)
			{
				switch (seq)
				{
					case 0:DirectBullet(bheader[i],-5*pi/6);break;
					case 1:DirectBullet(bheader[i],-pi/2);break;
					case 2:DirectBullet(bheader[i],-pi/6);break;
					case 3:DirectBullet(bheader[i],-pi/2);break;
				}
			}
			else
			{
				switch (seq)
				{
					case 0:DirectBullet(bheader[i],-pi/6);break;
					case 1:DirectBullet(bheader[i],-pi/2);break;
					case 2:DirectBullet(bheader[i],-5*pi/6);break;
					case 3:DirectBullet(bheader[i],-pi/2);break;
				}
			}
		}
	}
	if (sixbrk>0.2&&!brdir)
	{
		sixbrk=0;
		if (bheader[0].bulletpos.y>610)return;
		for (int i=0;i<=sxcnt;++i)
		{
			beewx[++beecnt]=&bullet[CreateBullet2(bheader[i].bulletpos.x,bheader[i].bulletpos.y,0,pi,true)];
		}
	}
}
void Level6Part22()
{
	sxcnt=-1;beecnt=-1;brdir=false;frameleft=TenSeconds/10*7;offset=43;
	memset(bheader,0,sizeof(bheader));
	memset(beewx,0,sizeof(beewx));
	avacurbrk=0.25;avabrk=0.25;sixbrk=0.1;seq=3;
	for (int i=1;i<=10;++i)
	{
		CreateBullet2(bheader[++sxcnt],offset+2*(i-1)*offset,10,4,-pi/6);
		CreateBullet2(bheader[++sxcnt],offset+2*(i-1)*offset,10,4,-5*pi/6);
	}
	++part;
}
void Level6Part23()
{
	avacurbrk+=hge->Timer_GetDelta();
	sixbrk+=hge->Timer_GetDelta();
	if (frameleft<TenSeconds/10*1&&!brdir)
	{
		brdir=true;
		for (int i=0;i<=beecnt;++i)
		{
			beewx[i]->bulletaccel=0.001;beewx[i]->limv=1;
			DirectBullet(*beewx[i],(double)(rand()%3140)/1000.0f);
		}
	}
	for (int i=0;i<=sxcnt;++i)ProcessBullet2(bheader[i]);
	if (avacurbrk>avabrk)
	{
		avacurbrk=0;++seq;seq%=4;
		for (int i=0;i<=sxcnt;++i)
		{
			if (i&1)
			{
				switch (seq)
				{
					case 0:DirectBullet(bheader[i],-5*pi/6);break;
					case 1:DirectBullet(bheader[i],-pi/2);break;
					case 2:DirectBullet(bheader[i],-pi/6);break;
					case 3:DirectBullet(bheader[i],-pi/2);break;
				}
			}
			else
			{
				switch (seq)
				{
					case 0:DirectBullet(bheader[i],-pi/6);break;
					case 1:DirectBullet(bheader[i],-pi/2);break;
					case 2:DirectBullet(bheader[i],-5*pi/6);break;
					case 3:DirectBullet(bheader[i],-pi/2);break;
				}
			}
		}
	}
	if (sixbrk>0.1&&!brdir)
	{
		sixbrk=0;
		if (bheader[0].bulletpos.y>610)return;
		for (int i=0;i<=sxcnt;++i)
		{
			beewx[++beecnt]=&bullet[CreateBullet2(bheader[i].bulletpos.x,bheader[i].bulletpos.y,0,pi,true)];
		}
	}
}
void Level6Part24()
{
	sxcnt=-1;beecnt=-1;brdir=false;frameleft=TenSeconds/10*7;offset=43;
	memset(bheader,0,sizeof(bheader));
	memset(beewx,0,sizeof(beewx));
	avacurbrk=0.25;avabrk=0.25;sixbrk=0.1;seq=3;
	for (int i=1;i<=10;++i)
	{
		CreateBullet2(bheader[++sxcnt],offset+2*(i-1)*offset,590,4,pi/6);
		CreateBullet2(bheader[++sxcnt],offset+2*(i-1)*offset,590,4,5*pi/6);
	}
	++part;
}
void Level6Part25()
{
	avacurbrk+=hge->Timer_GetDelta();
	sixbrk+=hge->Timer_GetDelta();
	if (frameleft<TenSeconds/10*1&&!brdir)
	{
		brdir=true;
		for (int i=0;i<=beecnt;++i)
		{
			beewx[i]->bulletaccel=0.001;beewx[i]->limv=1;
			DirectBullet(*beewx[i],(double)(rand()%3140)/1000.0f);
		}
	}
	for (int i=0;i<=sxcnt;++i)ProcessBullet2(bheader[i]);
	if (avacurbrk>avabrk)
	{
		avacurbrk=0;++seq;seq%=4;
		for (int i=0;i<=sxcnt;++i)
		{
			if (i&1)
			{
				switch (seq)
				{
					case 0:DirectBullet(bheader[i],5*pi/6);break;
					case 1:DirectBullet(bheader[i],pi/2);break;
					case 2:DirectBullet(bheader[i],pi/6);break;
					case 3:DirectBullet(bheader[i],pi/2);break;
				}
			}
			else
			{
				switch (seq)
				{
					case 0:DirectBullet(bheader[i],pi/6);break;
					case 1:DirectBullet(bheader[i],pi/2);break;
					case 2:DirectBullet(bheader[i],5*pi/6);break;
					case 3:DirectBullet(bheader[i],pi/2);break;
				}
			}
		}
	}
	if (sixbrk>0.1&&!brdir)
	{
		sixbrk=0;
		if (bheader[0].bulletpos.y<-10)return;
		for (int i=0;i<=sxcnt;++i)
		{
			beewx[++beecnt]=&bullet[CreateBullet2(bheader[i].bulletpos.x,bheader[i].bulletpos.y,0,pi,true)];
		}
	}
}
void Level6Part26()
{
	sxcnt=-1;beecnt=-1;brdir=false;frameleft=TenSeconds/10*7;offset=43;
	memset(bheader,0,sizeof(bheader));
	memset(beewx,0,sizeof(beewx));
	avacurbrk=0.25;avabrk=0.25;sixbrk=0.1;seq=3;
	for (int i=1;i<=10;++i)
	{
		CreateBullet2(bheader[++sxcnt],790,offset+2*(i-1)*offset,4,5*pi/3);
		CreateBullet2(bheader[++sxcnt],790,offset+2*(i-1)*offset,4,pi/3);
	}
	++part;
}
void Level6Part27()
{
	avacurbrk+=hge->Timer_GetDelta();
	sixbrk+=hge->Timer_GetDelta();
	if (frameleft<TenSeconds/10*1&&!brdir)
	{
		brdir=true;
		for (int i=0;i<=beecnt;++i)
		{
			beewx[i]->bulletaccel=0.001;beewx[i]->limv=1;
			DirectBullet(*beewx[i],(double)(rand()%3140)/1000.0f);
		}
	}
	for (int i=0;i<=sxcnt;++i)ProcessBullet2(bheader[i]);
	if (avacurbrk>avabrk)
	{
		avacurbrk=0;++seq;seq%=4;
		for (int i=0;i<=sxcnt;++i)
		{
			if (i&1)
			{
				switch (seq)
				{
					case 0:DirectBullet(bheader[i],pi/3);break;
					case 1:DirectBullet(bheader[i],0);break;
					case 2:DirectBullet(bheader[i],5*pi/3);break;
					case 3:DirectBullet(bheader[i],0);break;
				}
			}
			else
			{
				switch (seq)
				{
					case 0:DirectBullet(bheader[i],5*pi/3);break;
					case 1:DirectBullet(bheader[i],0);break;
					case 2:DirectBullet(bheader[i],pi/3);break;
					case 3:DirectBullet(bheader[i],0);break;
				}
			}
		}
	}
	if (sixbrk>0.1&&!brdir)
	{
		sixbrk=0;
		if (bheader[0].bulletpos.x<-10)return;
		for (int i=0;i<=sxcnt;++i)
		{
			beewx[++beecnt]=&bullet[CreateBullet2(bheader[i].bulletpos.x,bheader[i].bulletpos.y,0,pi,true)];
		}
	}
}
void Level6Part28()
{
	sxcnt=-1;beecnt=-1;brdir=false;frameleft=TenSeconds+TenSeconds/10*9;offset=43;
	memset(bheader,0,sizeof(bheader));
	memset(beewx,0,sizeof(beewx));
	avacurbrk=0.25;avabrk=0.25;sixbrk=0.1;seq=3;
	for (int i=1;i<=10;++i)
	{
		CreateBullet2(bheader[++sxcnt],10,offset+2*(i-1)*offset,4,pi+5*pi/3);
		CreateBullet2(bheader[++sxcnt],10,offset+2*(i-1)*offset,4,pi+pi/3);
	}
	++part;
}
void Level6Part29()
{
	avacurbrk+=hge->Timer_GetDelta();
	sixbrk+=hge->Timer_GetDelta();
	if (frameleft<TenSeconds/10*6&&!brdir)
	{
		brdir=true;
		for (int i=0;i<=beecnt;++i)
		{
			beewx[i]->bulletaccel=0.001;beewx[i]->limv=1;
			DirectBullet(*beewx[i],(double)(rand()%3140)/1000.0f);
		}
	}
	for (int i=0;i<=sxcnt;++i)ProcessBullet2(bheader[i]);
	if (avacurbrk>avabrk)
	{
		avacurbrk=0;++seq;seq%=4;
		for (int i=0;i<=sxcnt;++i)
		{
			if (i&1)
			{
				switch (seq)
				{
					case 0:DirectBullet(bheader[i],pi+pi/3);break;
					case 1:DirectBullet(bheader[i],pi);break;
					case 2:DirectBullet(bheader[i],pi+5*pi/3);break;
					case 3:DirectBullet(bheader[i],pi);break;
				}
			}
			else
			{
				switch (seq)
				{
					case 0:DirectBullet(bheader[i],pi+5*pi/3);break;
					case 1:DirectBullet(bheader[i],pi);break;
					case 2:DirectBullet(bheader[i],pi+pi/3);break;
					case 3:DirectBullet(bheader[i],pi);break;
				}
			}
		}
	}
	if (sixbrk>0.1&&!brdir)
	{
		sixbrk=0;
		if (bheader[0].bulletpos.x>810)return;
		for (int i=0;i<=sxcnt;++i)
		{
			beewx[++beecnt]=&bullet[CreateBullet2(bheader[i].bulletpos.x,bheader[i].bulletpos.y,0,pi,true)];
		}
	}
}
void Level6Part30()//Hyperfluid!
{
	frameleft=AMinute;clrtime=2;
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Hyperfluid!");
	}
	if (Current_Position==1)
	{
		++part;All2pnt();avabrk=0.2f;avacurbrk=0;sixbrk=-1;
	}
}
void Level6Part999999999()//well this isnot an easter egg!
{
	avabrk=(frameleft/(double)AMinute)*0.15f+0.05f;
	avacurbrk+=hge->Timer_GetDelta();
	sixbrk+=hge->Timer_GetDelta();
	if (avacurbrk>avabrk)
	{
		avacurbrk=0;
		for (int i=1;i<=rand()%10;++i)
		if (rand()%1000>499)
		{
			int pnt=CreateBullet2(10,rand()%580+10,0,-3*pi/4);
			bullet[pnt].bulletaccel=0.0025;bullet[pnt].limv=6;
		}
		else
		{
			int pnt=CreateBullet2(rand()%780+10,10,0,-3*pi/4);
			bullet[pnt].bulletaccel=0.0025;bullet[pnt].limv=6;
		}
	}
	if (sixbrk>0.5)
	{
		sixbrk=0;
		for (int i=1;i<=rand()%10;++i)
		{
			int pnt=CreateBullet2(rand()%780+10,590,1,pi/2);
			bullet[pnt].alterColor=white;
		}
	}
}
int bgbrk;
double bgdbbrk;
void Level7Part0()
{
	frameleft=50;All2pnt();towcnt=0;bgbrk=0;
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		LE_Active=false;
		Current_Position=2;
		ShowTip("\
Level 7-Rainbow of Spring\n\
Will there be a clearer day?\
");
		frameleft=TenSeconds;++part;
	}
}
bool skystp;
void Level7Part1()
{
	++bgbrk;if (LOWFPS)bgbrk+=16;
	if (bgbrk<30)return;
	bgbrk=0;
	if (!LOWFPS)
	DBGColor=ColorTransfer(DBGColor,0xFF0B0916);
	else
	for (int i=1;i<=17;++i)DBGColor=ColorTransfer(DBGColor,0xFF0B0916);
	if (DBGColor==0xFF0B0916)
	{
		frameleft=AMinute,++part;
		bgdbbrk=rand()%15+5,bgbrk=0;
		avabrk=0.2f;avacurbrk=0;skystp=false;
	}
}
void Level7Part2()
{
	if (bgbrk==1||bgbrk==4)
	{
		int times=5;if (LOWFPS)times*=16;
		for (int i=1;i<=times;++i)DBGColor=ColorTransfer(DBGColor,0xFF23459A);
		if (DBGColor==0xFF23459A)
		{
			if(bgbrk==1)bgbrk=2;
			if(bgbrk==4)bgbrk=5;
		}
	}
	if (bgbrk==2||bgbrk==5)
	{
		int times=1;if (LOWFPS)times*=16;
		for (int i=1;i<=times;++i)DBGColor=ColorTransfer(DBGColor,0xFF0B0916);
		if (DBGColor==0xFF0B0916)
		{
			if(bgbrk==2)bgbrk=3,bgdbbrk=0.06;
			if(bgbrk==5)bgbrk=0,bgdbbrk=rand()%15+5;
		}
	}
	if (bgbrk==3||bgbrk==0)
	{
		bgdbbrk-=hge->Timer_GetDelta();
		if (bgdbbrk<=0)
		{
			if (bgbrk==0)bgbrk=1;
			if (bgbrk==3)bgbrk=4;
		}
	}
	avabrk=(frameleft/(double)AMinute)*0.15f+0.15f;
	avacurbrk+=hge->Timer_GetDelta();
	sixbrk+=hge->Timer_GetDelta();
	if (avacurbrk>avabrk)
	{
		avacurbrk=0;
		for (int i=1;i<=rand()%10;++i)
		{
			if (rand()%1000>499)
			{
				int pnt=CreateBullet2(10,rand()%580+10,0,-3*pi/4);
				bullet[pnt].bulletaccel=0.0025;bullet[pnt].limv=6;
			}
			else
			{
				int pnt=CreateBullet2(rand()%780+10,10,0,-3*pi/4);
				bullet[pnt].bulletaccel=0.0025;bullet[pnt].limv=6;
			}
			if (rand()%1000>499)
			{
				int pnt=CreateBullet2(780,rand()%580+10,0,-pi/4);
				bullet[pnt].bulletaccel=0.0025;bullet[pnt].limv=6;
			}
			else
			{
				int pnt=CreateBullet2(rand()%780+10,10,0,-pi/4);
				bullet[pnt].bulletaccel=0.0025;bullet[pnt].limv=6;
			}
		}
	}
}
void Level7Part3()
{
	frameleft=TenSeconds;
	if (!skystp)
	{
		++bgbrk;if (LOWFPS)bgbrk+=16;
		if (bgbrk<30)return;
		bgbrk=0;
		if (!LOWFPS)
		DBGColor=ColorTransfer(DBGColor,0xFFFFFFFF);
		else
		for (int i=1;i<=17;++i)DBGColor=ColorTransfer(DBGColor,0xFFFFFFFF);
		if (DBGColor==0xFFFFFFFF)skystp=skyactive=true,sky.SkySetFadeIn(),sky.SetSpeed(0.01);
		sky.SetTime(9);
	}
	else
	{
		++bgbrk;if (LOWFPS)bgbrk+=16;
		if (bgbrk<30)return;
		bgbrk=0;
		if (!LOWFPS)
		DBGColor=ColorTransfer(DBGColor,0x00FFFFFF);
		else
		for (int i=1;i<=17;++i)DBGColor=ColorTransfer(DBGColor,0x00FFFFFF);
		if (DBGColor==0x00FFFFFF)
		++part;
	}
}
void Level7Part4()
{
	frameleft=(AMinute+ThirtySeconds);clrtime=5;
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Rainbow tower...");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	towcnt=0;
	deltadelta=pi/720;
	CreateTower6(400,300,600,2,1000,3,72);
	++part;All2pnt();
}
void Level7Part5()
{
	++frameskips;
	if (tower[1].towertype==6)
	{
		if (frameskips>TenSeconds/5)
		{
			frameskips=0;
			towcnt=0;
			CreateTower9(400,300,600,2,1500,72,1200);
		}
	}
	if (tower[1].towertype==9)
	{
		if (frameskips>TenSeconds/5)
		{
			frameskips=0;
			towcnt=0;
			CreateTower4(400,300,500,1,500);
		}
	}
	if (tower[1].towertype==4)
	{
		if (frameskips>TenSeconds/5)
		{
			frameskips=0;
			towcnt=0;
			CreateTower1(400,300,50,4);
		}
	}
	if (tower[1].towertype==1)
	{
		if (frameskips>TenSeconds/5)
		{
			frameskips=0;
			towcnt=0;
			CreateTower2(400,300,50,4);
		}
	}
	if (tower[1].towertype==2)
	{
		if (frameskips>TenSeconds/2)
		{
			frameskips=0;
			towcnt=0;
			CreateTower8(400,300,500,5,20,50);
		}
	}
	if (tower[1].towertype==8)
	{
		BTarg.TargHide();
		if (frameskips>TenSeconds/5)
		{
			frameskips=0;
			towcnt=0;
			CreateTower5(400,300,50,5);
		}
	}
	if (tower[1].towertype==5)
	{
		if (frameskips>TenSeconds/5)
		{
			frameskips=0;
			towcnt=0;
			CreateTower6(400,300,600,2,1000,3,72);
		}
	}
}
void Level7Part6()
{
	frameleft=AMinute;clrtime=2;towcnt=0;
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Hit Z...");
	}
	if (Current_Position==1)
	{
		++part;All2pnt();avabrk=1.0f;avacurbrk=0;
	}
}
void Level7Part7()
{
	avabrk=frameleft/(double)AMinute*0.6f+0.4f;
	avacurbrk+=hge->Timer_GetDelta();
	if (avacurbrk>avabrk)
	{
		avacurbrk=0;
		bool lasta,lastb;
		lasta=rand()%1000<500;lastb=rand()%1000<500;
		for (int i=0;i<31;++i)
		{
			int rf=rand()%1000;
			if ((lasta&&rf<600)||(!lasta&&rf<250))
			{
				int pnt=CreateBullet2(-15,i*20,2,pi);
				bullet[pnt].alterColor=(TColors)(i%8);
				bullet[pnt].limv=2+2*(AMinute-frameleft)/(double)AMinute;bullet[pnt].bulletaccel=0.002;
				lasta=true;
			}else lasta=false;
			rf=rand()%1000;
			if ((lastb&&rf<600)||(!lastb&&rf<250))
			{
				int pnt=CreateBullet2(815,i*20-10,2,0);
				bullet[pnt].alterColor=(TColors)(i%8);
				bullet[pnt].limv=2+2*(AMinute-frameleft)/(double)AMinute;bullet[pnt].bulletaccel=0.002;
				lastb=true;
			}else lastb=false;
		}
	}
}
double sntang;
void Level7Part8()
{
	frameleft=AMinute;clrtime=2;towcnt=0;
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Rainbow!");
	}
	if (Current_Position==1)
	{
		++part;All2pnt();avabrk=0.03f;avacurbrk=1.0f;sntang=-pi/2;
	}
}
void rainbowCreator(double rl,double rr,double rad,TColors col,double speed,bool invi=false)
{
	double r=rand()%((int)(rr-rl)*10000)/10000.0f+rl;
	int pnt=CreateBullet2(900+cos(rad)*r,700+sin(rad)*r,speed,rand()/32767.0f,true,invi);
	bullet[pnt].alterColor=col;
}
void Level7Part9()
{
	if (sntang>-pi)
	{
		avacurbrk+=hge->Timer_GetDelta();
		if (avacurbrk>avabrk)
		{
			sntang-=pi/180;avacurbrk=0;
			for(int i=0;i<6;++i)rainbowCreator(660,600,sntang,red,0,1);
			for(int i=0;i<6;++i)rainbowCreator(610,550,sntang,orange,0,1);
			for(int i=0;i<6;++i)rainbowCreator(560,500,sntang,yellow,0,1);
			for(int i=0;i<6;++i)rainbowCreator(510,450,sntang,green,0,1);
			for(int i=0;i<6;++i)rainbowCreator(460,410,sntang,blue,0,1);
			for(int i=0;i<6;++i)rainbowCreator(420,360,sntang,dblue,0,1);
			for(int i=0;i<6;++i)rainbowCreator(365,310,sntang,purple,0,1);
		}
	}
	else
	{
		avabrk=0.35+(frameleft/(double)AMinute)*0.4f;
		avacurbrk+=hge->Timer_GetDelta();
		if (avacurbrk>avabrk)
		{
			avacurbrk=0;
			double spd=((AMinute-frameleft)/(double)AMinute)+1;
			sntang=-pi+(rand()%(int)(pi/2*10000))/10000.0f;
			for(int i=0;i<((AMinute-frameleft)/(double)AMinute)*20;++i)
			rainbowCreator(660,600,sntang,red,spd);
			sntang=-pi+(rand()%(int)(pi/2*10000))/10000.0f;
			for(int i=0;i<((AMinute-frameleft)/(double)AMinute)*20;++i)
			rainbowCreator(610,550,sntang,orange,spd);
			sntang=-pi+(rand()%(int)(pi/2*10000))/10000.0f;
			for(int i=0;i<((AMinute-frameleft)/(double)AMinute)*20;++i)
			rainbowCreator(560,500,sntang,yellow,spd);
			sntang=-pi+(rand()%(int)(pi/2*10000))/10000.0f;
			for(int i=0;i<((AMinute-frameleft)/(double)AMinute)*20;++i)
			rainbowCreator(510,450,sntang,green,spd);
			sntang=-pi+(rand()%(int)(pi/2*10000))/10000.0f;
			for(int i=0;i<((AMinute-frameleft)/(double)AMinute)*20;++i)
			rainbowCreator(460,410,sntang,blue,spd);
			sntang=-pi+(rand()%(int)(pi/2*10000))/10000.0f;
			for(int i=0;i<((AMinute-frameleft)/(double)AMinute)*20;++i)
			rainbowCreator(420,360,sntang,dblue,spd);
			sntang=-pi+(rand()%(int)(pi/2*10000))/10000.0f;
			for(int i=0;i<((AMinute-frameleft)/(double)AMinute)*20;++i)
			rainbowCreator(365,310,sntang,purple,spd);
			sntang=-pi-0.1;
		}
	}
}
SimpleThing aa,bb;
void Level7Part10()
{
	frameleft=AMinute*2;clrtime=2;towcnt=0;
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Interference(fake)");
	}
	if (Current_Position==1)
	{
		++part;All2pnt();skyactive=false;DBGColor=0xFF000000;
		binter.Init("./Resources/b_inter.png",PicBack::Centered,0x80);
		binter.SetFadeIn();aa.Init(vector2d(260,292));bb.Init(vector2d(523,292));
	}
}
void Level7Part11()
{
//260,292;523,292
	aa.Update(true);bb.Update(false);
}
diffCreator dfc[200];
void Level7Part12()
{
	frameleft=AMinute*2;clrtime=2;towcnt=0;
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;bulcnt=0;
		aa.toPoint();bb.toPoint();
		Current_Position=2;
		ShowTip("Diffraction(fake)");
	}
	if (Current_Position==1)
	{
		++part;memset(dfc,0,sizeof(dfc));
		binter.SetFadeOut();bdiff.Init("./resources/b_diff.png",PicBack::Tiled,0x80);
		bdiff.SetFadeIn();bdiff.SetScale(0.5);
		avabrk=2.0f;avacurbrk=0;
	}
}
void Level7Part13()
{
	avabrk=1.0f+frameleft/(double)AMinute;
	avacurbrk+=hge->Timer_GetDelta();
	if(avacurbrk>avabrk&&frameleft>=TenSeconds/5)
	{
		for(int i=0;i<200;++i)
		if (!dfc[i].isActive())
		{
			if(rand()%100>75)
			{
				if(rand()%100>49)
				{
					vector2d pos=vector2d(playerpos.x,rand()%600);
					while (GetDist(pos,playerpos)<100)
					pos=vector2d(playerpos.x,rand()%600);
					dfc[i].init(pos);
				}
				else
				{
					vector2d pos=vector2d(rand()%800,playerpos.y);
					while (GetDist(pos,playerpos)<100)
					pos=vector2d(rand()%800,playerpos.y);
					dfc[i].init(pos);
				}
			}
			else
			{
				vector2d pos=vector2d(rand()%800,rand()%600);
				while (GetDist(pos,playerpos)<100)
				pos=vector2d(rand()%800,rand()%600);
				dfc[i].init(pos);
			}
			break;
		}
		avacurbrk=0;
	}
	for(int i=0;i<200;++i)
	if(dfc[i].isActive())dfc[i].update();
}
BulletSine bnl[100];
double ykbrk;
void Level7Part14()//Photon school
{
	memset(bnl,0,sizeof(bnl));
	frameleft=AMinute;
	ykbrk=0.5f;skyactive=true;bdiff.SetFadeOut();
	if((DBGColor=ColorTransfer(DBGColor,0x00000000))==0x0)++part;
}
void Level7Part15()
{
	ykbrk-=hge->Timer_GetDelta();
	if (ykbrk<0&&frameleft>TenSeconds/10*3)
	{
		ykbrk=(double)frameleft/AMinute*0.75f+0.75f;
		for (int i=0;i<100;++i)
		if (!bnl[i].active)
		{
			vector2d a,b;
			if (rand()%100>49)
			{
				if (rand()%100>49)a=vector2d(rand()%780+10,610);else a=vector2d(rand()%780+10,-10);
			}
			else
			{
				if (rand()%100>49)a=vector2d(-10,rand()%580+10);else a=vector2d(810,rand()%580+10);
			}
			if (rand()%100>49)
			{
				if (rand()%100>49)b=vector2d(rand()%780+10,610);else b=vector2d(rand()%780+10,-10);
			}
			else
			{
				if (rand()%100>49)b=vector2d(-10,rand()%580+10);else b=vector2d(810,rand()%580+10);
			}
			bnl[i].Init(a,b);
			break;
		}
	}
	for (int i=0;i<100;++i)
	if (bnl[i].active)bnl[i].Update();
}
double DTCircle;
BCircle Circles[20];
int CCnt,state;
void Level7Part16()//Great circles
{
	towcnt=0;
	frameleft=Infinity;All2pnt();
	Circles[0].Init(444,20*pi/50000.0f,6,vector2d(400,300));
	Circles[1].Init(444,-20*pi/50000.0f,6,vector2d(400,300));
	CCnt=1;state=0;
	DTCircle=0.0f;
	++part;playerpos.x=400,playerpos.y=300;
}
void Level7Part17()//Great circles-child1
{
	frameleft=Infinity;
	DTCircle+=hge->Timer_GetDelta();
	if (DTCircle>1&&CCnt<3)
	{
		Circles[2].Init(444,10*pi/50000.0f,12,vector2d(400,300));
		Circles[3].Init(444,-10*pi/50000.0f,12,vector2d(400,300));
		CCnt=3;
	}
	if (DTCircle>2&&CCnt<5)
	{
		Circles[4].Init(444,8*pi/50000.0f,18,vector2d(400,300));
		Circles[5].Init(444,-8*pi/50000.0f,18,vector2d(400,300));
		CCnt=5;
	}
	if (DTCircle>3&&CCnt<7)
	{
		Circles[6].Init(444,8*pi/50000.0f,27,vector2d(400,300));
		Circles[7].Init(444,-8*pi/50000.0f,27,vector2d(400,300));
		CCnt=7;
	}
	if (DTCircle>4&&CCnt<9)
	{
		Circles[8].Init(444,6*pi/50000.0f,45,vector2d(400,300));
		Circles[9].Init(444,-6*pi/50000.0f,45,vector2d(400,300));
		CCnt=9;
	}
	if (DTCircle>5&&CCnt<11)
	{
		Circles[10].Init(444,6*pi/50000.0f,60,vector2d(400,300));
		Circles[11].Init(444,-6*pi/50000.0f,60,vector2d(400,300));
		CCnt=11;
	}
	if (DTCircle>5&&CCnt<13)
	{
		Circles[12].Init(444,3*pi/50000.0f,96,vector2d(400,300));
		Circles[13].Init(444,-3*pi/50000.0f,96,vector2d(400,300));
		CCnt=13;
	}
	if (Circles[0].GetRange()>=50)
	{
		int times=1;if (LOWFPS)times=17;
		for (int i=1;i<=times;++i)
			Circles[0].SetRange(Circles[0].GetRange()-0.1),
			Circles[1].SetRange(Circles[1].GetRange()-0.1);
	}
	if (Circles[2].GetRange()>=100&&CCnt>=3)
	{
		int times=1;if (LOWFPS)times=17;
		for (int i=1;i<=times;++i)
			Circles[2].SetRange(Circles[2].GetRange()-0.1),
			Circles[3].SetRange(Circles[3].GetRange()-0.1);
	}
	if (Circles[4].GetRange()>=150&&CCnt>=5)
	{
		int times=1;if (LOWFPS)times=17;
		for (int i=1;i<=times;++i)
			Circles[4].SetRange(Circles[4].GetRange()-0.1),
			Circles[5].SetRange(Circles[5].GetRange()-0.1);
	}
	if (Circles[6].GetRange()>=210&&CCnt>=7)
	{
		int times=1;if (LOWFPS)times=17;
		for (int i=1;i<=times;++i)
			Circles[6].SetRange(Circles[6].GetRange()-0.1),
			Circles[7].SetRange(Circles[7].GetRange()-0.1);
	}
	if (Circles[8].GetRange()>=270&&CCnt>=9)
	{
		int times=1;if (LOWFPS)times=17;
		for (int i=1;i<=times;++i)
			Circles[8].SetRange(Circles[8].GetRange()-0.1),
			Circles[9].SetRange(Circles[9].GetRange()-0.1);
	}
	if (Circles[10].GetRange()>=320&&CCnt>=11)
	{
		int times=1;if (LOWFPS)times=17;
		for (int i=1;i<=times;++i)
			Circles[10].SetRange(Circles[10].GetRange()-0.1),
			Circles[11].SetRange(Circles[11].GetRange()-0.1);
	}
	if (Circles[12].GetRange()>=420&&CCnt>=13)
	{
		int times=1;if (LOWFPS)times=17;
		for (int i=1;i<=times;++i)
			Circles[12].SetRange(Circles[12].GetRange()-0.1),
			Circles[13].SetRange(Circles[13].GetRange()-0.1);
	}
	else
	{
		if (CCnt>=13)++part;
		for (int i=1;i<=CCnt;++i)
			Circles[i].SetDT(i*pi);
	}
	for (int i=0;i<=CCnt;++i)Circles[i].Update();
	state=0;
	towerspr[red]->RenderStretch(770,0,800,30);
	towerspr[green]->RenderStretch(380,280,420,320);
}
void Level7Part18()//Great circles-child2
{
	if(state)
	{
		towerspr[green]->RenderStretch(770,0,800,30);
		towerspr[red]->RenderStretch(380,280,420,320);
	}
	else
	{
		towerspr[red]->RenderStretch(770,0,800,30);
		towerspr[green]->RenderStretch(380,280,420,320);
	}
	hgeRect col;
	if (state)
	{
		col=hgeRect(380,280,420,320);
		if (col.TestPoint(playerpos.x,playerpos.y))++part;
	}
	else
	{
		col=hgeRect(770,0,800,30);
		if (col.TestPoint(playerpos.x,playerpos.y))state=1;
	}
	frameleft=Infinity;
	for (int i=0;i<=CCnt;++i)
	{
		if (i==0||i==1)Circles[i].SetRange(50+10*sin(Circles[i].GetDT()));
		if (i==2||i==3)Circles[i].SetRange(100+10*sin(Circles[i].GetDT()));
		if (i==4||i==5)Circles[i].SetRange(150+10*sin(Circles[i].GetDT()));
		if (i==6||i==7)Circles[i].SetRange(210+20*sin(Circles[i].GetDT()));
		if (i==8||i==9)Circles[i].SetRange(270+20*sin(Circles[i].GetDT()));
		if (i==10||i==11)Circles[i].SetRange(320+20*sin(Circles[i].GetDT()));
		if (i==12||i==13)Circles[i].SetRange(420+30*sin(Circles[i].GetDT()));
		Circles[i].Update();
	}
}
BTail btails[50];
void Level7Part19()
{
	frameleft=AMinute*2;clrtime=2;towcnt=0;
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Warning: Trypophobia caution ahead!");
	}
	if (Current_Position==1)
	{
		++part;All2pnt();avabrk=1.0f;avacurbrk=1.0f;memset(btails,0,sizeof(btails));
	}
}
void Level7Part20()
{
	avacurbrk+=hge->Timer_GetDelta();
	if(avacurbrk>avabrk)
	{
		avacurbrk=0;avabrk=(frameleft/(double)(AMinute*2))*0.7+0.3;
		for(int i=0;i<50;++i)
		if(!btails[i].isActive())
		{btails[i].Create();break;}
	}
	for(int i=0;i<50;++i)
	if(btails[i].isActive())btails[i].Update();
}
int sttnt;
void Level7Part21()
{
	frameleft=AMinute+ThirtySeconds;
	if (towcnt!=1&&towcnt!=0)return ClearAll(false);
	DisableAllTower=false;
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	t8special=true;
	sttnt=CreateTower8(400,300,2000,2,75,20);
	for (int i=1;i<=towcnt;++i)
		if (tower[i].RendColor==0x80FFFFFF)
			tower[i].RendColor=0x00FFFFFF;
	for (int i=1;i<=towcnt;++i)
		if ((tower[i].RendColor>>24)<=0x80)
			tower[i].RendColor=tower[i].RendColor+0x01FFFFFF;
		else
		{
			++part;
			return;
		}
}
void Level7Part22()
{
	tower[sttnt].towertimer=(frameleft/(double)(AMinute+ThirtySeconds))*1250+750;
}
WOP wop[100];
void Level7Part23()//Wave of Photon
{
	memset(bnl,0,sizeof(bnl));t8special=false;
	frameleft=AMinute;All2pnt();
	ykbrk=0.5f;++part;
}
void Level7Part24()
{
	ykbrk-=hge->Timer_GetDelta();
	if (ykbrk<0&&frameleft>TenSeconds/10*3)
	{
		ykbrk=(double)frameleft/AMinute/2.0f+0.2f;
		for (int i=0;i<100;++i)
		if (!wop[i].active)
		{
			vector2d a,b;
			if (rand()%100>49)
			{
				if (rand()%100>49)a=vector2d(rand()%780+10,610);else a=vector2d(rand()%780+10,-10);
			}
			else
			{
				if (rand()%100>49)a=vector2d(-10,rand()%580+10);else a=vector2d(810,rand()%580+10);
			}
			if (rand()%100>49)
			{
				if (rand()%100>49)b=vector2d(rand()%780+10,610);else b=vector2d(rand()%780+10,-10);
			}
			else
			{
				if (rand()%100>49)b=vector2d(-10,rand()%580+10);else b=vector2d(810,rand()%580+10);
			}
			if (rand()%100>80)
			{
				vector2d d=playerpos-a;
				b=playerpos;
				while(b.x>-5&&b.x<805&&b.y>-5&&b.y<605)b=b+d;
			}
			wop[i].Init(a,b,1+(AMinute-frameleft)/(double)AMinute,0.02);
			break;
		}
	}
	for (int i=0;i<100;++i)
	if (wop[i].active)wop[i].Update();
}
//Rearrange needed since here, see LEVELS.txt
void Level7Part25()//3 circles
{
	frameleft=AMinute;clrtime=2;towcnt=0;
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("It's not really here!");
	}
	if (Current_Position==1)
	{
		++part;All2pnt();avabrk=1.0f;avacurbrk=0;
	}
}
void L7P26Creator(vector2d p,int cnt,TColors col)
{
	for (int i=0;i<cnt;++i)
	{
		int pnt=CreateBullet2(p.x,p.y,6,frameleft*pi/AMinute+i*(2*pi/cnt));
		//                              ^
		//                              Nowhere can be safe!
		bullet[pnt].alterColor=col;
		bullet[pnt].bulletaccel=-0.003;bullet[pnt].limv=((AMinute-frameleft)/(double)AMinute)+1.0f;
	}
}
void Level7Part26()
{
	avacurbrk+=hge->Timer_GetDelta();
	avabrk=(frameleft/(double)AMinute)*0.5f+0.5f;
	if(avacurbrk>avabrk)
	{
		avacurbrk=0;
		L7P26Creator(vector2d(400,250),60,red);
		L7P26Creator(vector2d(350,336.6),60,green);
		L7P26Creator(vector2d(450,336.6),60,blue);
	}
}
BCircle scircles[200];
double rspd[200];
void Level7Part27()//circles
{
	frameleft=AMinute;clrtime=2;towcnt=0;
	DisableAllTower=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("??????");
	}
	if (Current_Position==1)
	{
		++part;All2pnt();avabrk=1.0f;avacurbrk=1.0f;memset(scircles,0,sizeof(scircles));
	}
}
void Level7Part28()
{
	avacurbrk+=hge->Timer_GetDelta();
	avabrk=0.1+(frameleft/(double)AMinute)*0.4f;
	if(avacurbrk>avabrk)
	{
		avacurbrk=0;
		for(int i=0;i<200;++i)
		{
			if (scircles[i].GetRange()>510||scircles[i].GetRange()<1e-7)
			{
				scircles[i].Init(1,(rand()&1?1:-1)*(frameleft<TwentySeconds?0.0003:0.0002),36,vector2d(400,300),(TColors)(rand()%8),(TColors)(rand()%8));
				rspd[i]=0.575+(frameleft/(double)AMinute)*0.1;break;
			}
		}
	}
	for(int i=0;i<200;++i)
	{
		if (scircles[i].GetRange()>1e-7&&scircles[i].GetRange()<510)
		{
			scircles[i].SetRange(scircles[i].GetRange()+(LOWFPS?17:1)*rspd[i]);
			if (rspd[i]>0.002)rspd[i]-=0.0005*(LOWFPS?17:1);
			if (rspd[i]<=0.002)rspd[i]=0.002;
			scircles[i].Update();
		}
	}
}
void Level7Part29()//Minesweeper
{
	frameleft=AMinute;
	if (bulcnt!=0)return (void)ClearAll();
	Lasercnt=0;
	++part;
}
void Level7Part30()//Minesweeper-child
{
	if (rand()%100>95)
	{
		int i;
		for (i=1;i<=nonamecnt+1;++i)
		{
			if (!noname[i].Exist())
			{
				if (frameleft<TenSeconds)
					noname[i].Init(rand()%800,4,100,150,70,0x8033CCFF);
				else if (frameleft<TwentySeconds)
					noname[i].Init(rand()%800,4,100,150,75,0x8033CCFF);
				else noname[i].Init(rand()%800,4,100,150,80,0x8033CCFF);
				if (i>nonamecnt)nonamecnt=i;break;
			}
		}
	}
	for (int i=1;i<=nonamecnt;++i)if (noname[i].Exist())noname[i].Process();
}
