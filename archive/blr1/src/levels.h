// -*- C++ -*-
//Chrisoft Bullet Lab Remix HGE
//Level Implementations
//"Copyleft" Chrisoft 2013
void Level1Part1()
{
	//Level procedure
	//Simple Level procedures should only run once during a level, you know.
	if ((tower[CreateTower1(400,300,2000,1)].towerspr->GetColor()>>24)>=0x80)IfCallLevel=false;
	Current_Position=2;
	ShowTip("Welcome to Bullet Lab Remix...\nMove around and hit nothing, easy right?\n\Press Z to close these tips.");
}
void Level1Part2()
{
	frameleft=TenSeconds;
	++frameskips;
	int secondtower=CreateTower1(567,300,2000,1);
	if (tower[secondtower].towerspr->GetColor()==0x80FFFFFF)
		tower[secondtower].towerspr->SetColor(0x00FFFFFF);
	if (frameskips<10&&!LOWFPS&&!LOWFPS)return;
	frameskips=0;
	if ((tower[secondtower].towerspr->GetColor()>>24)<=0x80)
		tower[secondtower].towerspr->SetColor(tower[secondtower].towerspr->GetColor()+0x01FFFFFF);
	if (tower[1].towerpos.x>=233)--tower[1].towerpos.x;
	if (tower[1].towerpos.x<233)
	{
		if (IfShowTip)
		{
			IfShowTip=false;
			FadeTip=false;
			Current_Position=2;
			ShowTip("Want another tower?");
			IfCallLevel=false;
		}
	}
}
void Level1Part3()
{
	frameleft=TenSeconds;
	tower[1].bulletspeed=4;
	tower[1].towertimer=1500;
	tower[2].bulletspeed=4;
	tower[2].towertimer=1500;
	IfCallLevel=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Maybe faster bullets will kill you?");
		IfCallLevel=false;
	}
}
void Level1Part4()
{
	frameleft=TenSeconds;
	tower[1].bulletspeed=2;
	tower[1].towertimer=100;
	tower[2].bulletspeed=2;
	tower[2].towertimer=100;
	IfCallLevel=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("There are two things to tell you.\nFirst one is that this game has very\
 loose collision detection.\nNext one is two machineguns are ready for\
 the next level...");
		IfCallLevel=false;
	}
}
void Level2Part0()
{
	frameleft=50;
	if (towcnt==2)
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
		ShowTip("Level 2 - Divide and Conquer!");
		IfCallLevel=false;
	}
	if (Current_Position==1)
	{
		frameleft=0;
		p2t1=p2t2=p2t3=p2t4=0;
		return;
	}
}
void Level2Part1()
{
	frameleft=TwentySeconds;
	if (p2t1==0)p2t1=CreateTower1(399,299,1000,2);
	if (p2t2==0)p2t2=CreateTower1(401,299,1000,2);
	if (p2t3==0)p2t3=CreateTower1(399,301,1000,2);
	if (p2t4==0)p2t4=CreateTower1(401,301,1000,2);
	bool none=true;
	if (!LOWFPS)
	{
		if (tower[p2t1].towerpos.x>=10)tower[p2t1].towerpos.x-=0.4075,none=false;
		if (tower[p2t1].towerpos.y>=10)tower[p2t1].towerpos.y-=0.3,none=false;
		if (tower[p2t2].towerpos.x<=766)tower[p2t2].towerpos.x+=0.3813,none=false;
		if (tower[p2t2].towerpos.y>=10)tower[p2t2].towerpos.y-=0.3,none=false;
		if (tower[p2t3].towerpos.x>=10)tower[p2t3].towerpos.x-=0.4453125,none=false;
		if (tower[p2t3].towerpos.y<=566)tower[p2t3].towerpos.y+=0.3,none=false;
		if (tower[p2t4].towerpos.x<=766)tower[p2t4].towerpos.x+=0.455859,none=false;
		if (tower[p2t4].towerpos.y<=566)tower[p2t4].towerpos.y+=0.3,none=false;
	}
	else
	{
		if (tower[p2t1].towerpos.x>=10)tower[p2t1].towerpos.x-=0.4075*10,none=false;
		if (tower[p2t1].towerpos.y>=10)tower[p2t1].towerpos.y-=0.3*10,none=false;
		if (tower[p2t2].towerpos.x<=766)tower[p2t2].towerpos.x+=0.3813*10,none=false;
		if (tower[p2t2].towerpos.y>=10)tower[p2t2].towerpos.y-=0.3*10,none=false;
		if (tower[p2t3].towerpos.x>=10)tower[p2t3].towerpos.x-=0.4453125*10,none=false;
		if (tower[p2t3].towerpos.y<=566)tower[p2t3].towerpos.y+=0.3*10,none=false;
		if (tower[p2t4].towerpos.x<=766)tower[p2t4].towerpos.x+=0.455859*10,none=false;
		if (tower[p2t4].towerpos.y<=566)tower[p2t4].towerpos.y+=0.3*10,none=false;
	}
	if (none)IfCallLevel=false;
}
void Level2Part2()
{
	frameleft=TenSeconds;
	tower[p2t1].bulletspeed=tower[p2t2].bulletspeed=4;
	tower[p2t3].bulletspeed=tower[p2t4].bulletspeed=4;
	IfCallLevel=false;
}
void Level2Part3()
{
	frameleft=ThirtySeconds;
	tower[p2t1].bulletspeed=tower[p2t2].bulletspeed=1;
	tower[p2t3].bulletspeed=tower[p2t4].bulletspeed=1;
	tower[p2t1].towertimer=tower[p2t2].towertimer=100;
	tower[p2t3].towertimer=tower[p2t4].towertimer=100;
	IfCallLevel=false;
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Got ready for being hunted by four machineguns?\n\
Don't tell me you've got stuck just here...");
		IfCallLevel=false;
	}
}
void Level3Part0()
{
	frameleft=50;
	if (towcnt==4&&(mode!=2))
	{
		ClearAll();
		return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		if (mode==2)
			ShowTip("Let's start from a higher position...\n\
Level 3 - Blue Masters");
		else
			ShowTip("Time for something new now...\n\
Level 3 - Blue Masters");
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
	++frameskips;
	if (towcnt==4)towcnt=0;
	deltadelta=0.004363322313;
	int towerclk=CreateTower2(400,300,100,1,true);
	if (tower[towerclk].towerspr->GetColor()==0x80FFFFFF)
		tower[towerclk].towerspr->SetColor(0x00FFFFFF);
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	if ((tower[towerclk].towerspr->GetColor()>>24)<=0x80)
		tower[towerclk].towerspr->SetColor(tower[towerclk].towerspr->GetColor()+0x01FFFFFF);
	else IfCallLevel=false;
}
//L3P2: /*Magic, DO NOT TOUCH!!*/
void Level3Part2()
{
	frameleft=TenSeconds;
	if (towcnt==1)
	{
		ClearAll();
		return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Are you scared?\nI'm just joking last time!");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	CreateTower1(233,300,500,2);
	CreateTower1(567,300,500,2);
	int tmp=CreateTower3(100,100,1000,1,true);
	tower[tmp].t3t=1;
	tmp=CreateTower3(300,100,1000,1,true);
	tower[tmp].t3t=1;
	tmp=CreateTower3(500,100,1000,1,true);
	tower[tmp].t3t=1;
	tmp=CreateTower3(700,100,1000,1,true);
	tower[tmp].t3t=1;
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
}
void Level3Part3()
{
	frameleft=TwentySeconds;
	if (towcnt==6&&IfShowTip)
	{
		ClearAll();
		return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Got stuck in my pentagon...");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	CreateTower3(30,10,500,2,true);
	CreateTower3(746,10,500,2,true);
	CreateTower3(30,556,500,2,true);
	CreateTower3(746,556,500,2,true);
	for (int i=1;i<=4;++i)
		tower[i].t3t=0;
	CreateTower1(5,10,1000,2);
	CreateTower1(771,10,1000,2);
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
}
void Level3Part4()
{
	frameleft=TwentySeconds;
	for (int i=1;i<=towcnt;++i)
		if (tower[i].towertype==3)tower[i].towertimer=300;else tower[i].towertimer=500;
	int aa=CreateTower1(5,556,500,2);
	int bb=CreateTower1(771,556,500,2);
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	if (tower[aa].towerspr->GetColor()==0x80FFFFFF)
		tower[aa].towerspr->SetColor(0x00FFFFFF);
	if (tower[bb].towerspr->GetColor()==0x80FFFFFF)
		tower[bb].towerspr->SetColor(0x00FFFFFF);
	if ((tower[aa].towerspr->GetColor()>>24)<=0x80)
		tower[aa].towerspr->SetColor(tower[aa].towerspr->GetColor()+0x01FFFFFF);
	else
	{
		IfCallLevel=false;
		return;
	}
	if ((tower[bb].towerspr->GetColor()>>24)<=0x80)
		tower[bb].towerspr->SetColor(tower[bb].towerspr->GetColor()+0x01FFFFFF);
	else
	{
		IfCallLevel=false;
		return;
	}
}
void Level3Part5()
{
	frameleft=ThirtySeconds;
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	for (int i=1;i<=4;++i)tower[i].t3t=1;
	for (int i=1;i<=towcnt;++i)
		if (tower[i].towertype==1)
			tower[i].towertimer=750;
	bool none=true;
	if (tower[1].towerpos.x<=120)++tower[1].towerpos.x,none=false;
	if (tower[1].towerpos.y<=80)++tower[1].towerpos.y,none=false;
	if (tower[2].towerpos.x>=660)--tower[2].towerpos.x,none=false;
	if (tower[2].towerpos.y<=80)++tower[2].towerpos.y,none=false;
	if (tower[3].towerpos.x<=120)++tower[3].towerpos.x,none=false;
	if (tower[3].towerpos.y>=480)--tower[3].towerpos.y,none=false;
	if (tower[4].towerpos.x>=660)--tower[4].towerpos.x,none=false;
	if (tower[4].towerpos.y>=480)--tower[4].towerpos.y,none=false;
	if (none)IfCallLevel=false;
}
void Level3Part6()
{
	frameleft=ThirtySeconds;
	for (int i=1;i<=towcnt;++i)
		if (tower[i].towertype==1)
			tower[i].towertimer=1000,tower[i].bulletspeed=6;
	IfCallLevel=false;
}
void Level3Part7()
{
	frameleft=ThirtySeconds;
	if (towcnt==8)
	{
		ClearAll();
		return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("This part will be a great fun if the green tower didn't exist...");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	CreateTower1(400,540,750,3);
	for (int i=1;i<=33;++i)
	{
		int tmp=CreateTower3(i*24-20,570,300,2);
		tower[tmp].t3t=3;
	}
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
}
void Level4Part0()
{
	frameleft=50;
	if (towcnt==34)
	{
		ClearAll();
		return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Someone is following you.\n\
Level 4 - At the Pet Store");
		IfCallLevel=false;
	}
	if (Current_Position==1)
	{
		frameleft=0;
		return;
	}
}
void Level4Part1()
{
	frameleft=TenSeconds;
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	CreateTower4(400,300,2000,2);
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
}
void Level4Part2()
{
	frameleft=TwentySeconds;
	if (towcnt==1)
	{
		ClearAll();
		return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("May be they are kittens petted by you?..");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	CreateTower4(30,10,2000,1);
	CreateTower4(746,10,2000,1);
	CreateTower4(30,556,2000,1);
	CreateTower4(746,556,2000,1);
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
}
void Level4Part3()
{
	frameleft=TenSeconds;
	if (towcnt==4)
	{
		ClearAll();
		return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	CreateTower3(30,10,300,2);
	CreateTower3(746,10,300,2);
	CreateTower3(30,556,300,2);
	CreateTower3(746,556,300,2);
	for (int i=1;i<=4;++i)
		tower[i].t3t=1;
	CreateTower4(5,10,2000,2);
	CreateTower4(771,10,2000,2);
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
}
void Level4Part4()
{
	frameleft=TwentySeconds;
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	tower[5].towertimer=tower[6].towertimer=1500;
	bool none=true;
	if (tower[1].towerpos.x<=120)++tower[1].towerpos.x,none=false;
	if (tower[1].towerpos.y<=80)++tower[1].towerpos.y,none=false;
	if (tower[2].towerpos.x>=660)--tower[2].towerpos.x,none=false;
	if (tower[2].towerpos.y<=80)++tower[2].towerpos.y,none=false;
	if (tower[3].towerpos.x<=120)++tower[3].towerpos.x,none=false;
	if (tower[3].towerpos.y>=480)--tower[3].towerpos.y,none=false;
	if (tower[4].towerpos.x>=660)--tower[4].towerpos.x,none=false;
	if (tower[4].towerpos.y>=480)--tower[4].towerpos.y,none=false;
	if (none)IfCallLevel=false;
}
void Level4Part5()
{
	frameleft=ThirtySeconds;
	if (towcnt==6)
	{
		ClearAll();
		return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Keep your rhythm!");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	CreateTower3(30,10,300,2);
	CreateTower3(746,10,300,2);
	CreateTower3(30,556,300,2);
	CreateTower3(746,556,300,2);
	CreateTower3(400,10,300,2);
	CreateTower3(400,556,300,2);
	CreateTower4(6,10,2000,2);
	CreateTower4(760,10,2000,2);
	CreateTower4(6,556,2000,2);
	CreateTower4(760,556,2000,2);
	for (int i=1;i<=towcnt;++i)
	{
		if (tower[i].towerspr->GetColor()==0x80FFFFFF)
			tower[i].towerspr->SetColor(0x00FFFFFF);
		if (tower[i].towertype==3)
			tower[i].t3t=1;
	}
	for (int i=1;i<=towcnt;++i)
		if ((tower[i].towerspr->GetColor()>>24)<=0x80)
			tower[i].towerspr->SetColor(tower[i].towerspr->GetColor()+0x01FFFFFF);
		else
		{
			IfCallLevel=false;
			return;
		}

}
void Level4Part6()
{
	frameleft=ThirtySeconds;
	if (towcnt==10)
	{
		ClearAll();
		return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Play with a kitten in the maze?");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	CreateTower4(400,540,3000,2);
	for (int i=1;i<=33;++i)
	{
		int tmp=CreateTower3(i*24-20,570,500,2);
		tower[tmp].t3t=3;
	}
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
}
void Level5Part0()
{
	frameleft=50;
	if (towcnt==34)
	{
		ClearAll();
		return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Bullets that kill you won't move so fast...\n\
Level 5 - A Huge Joke");
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
	frameleft=TenSeconds;
	if (towcnt==8)
	{
		ClearAll();
		return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	for (int i=1;i<=33;++i)
		int tmp=CreateTower5(i*24-20,30,200,10);
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
}
void Level5Part2()
{
	frameleft=TwentySeconds;
	if (towcnt==33)
	{
		ClearAll();
		return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	CreateTower1(233,300,750,4);
	CreateTower1(567,300,750,4);
	for (int i=1;i<=33;++i)
		int tmp=CreateTower5(i*24-20,30,500,4);
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
}
void Level5Part3()
{
	frameleft=ThirtySeconds;
	if (towcnt==35)
	{
		ClearAll();
		return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	CreateTower4(400,300,1000,2);
	for (int i=1;i<=33;++i)
		int tmp=CreateTower5(i*24-20,30,500,4);
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
}
void Level5Part4()
{
	frameleft=ThirtySeconds;
	if (towcnt==34)
	{
		ClearAll();
		return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Avoiding is no longer an option.");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	for (int i=1;i<=33;++i)
		int tmp=CreateTower1(i*24-20,30,500,4);
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
}
void Level6Part0()
{
	frameleft=50;
	if (towcnt==33)
	{
		ClearAll();
		return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Now you are going to meet my ultimate fire power...\n\
Level 6 - The Great Clock");
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
	frameleft=TwentySeconds;clrtime=0;
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	CreateTower6(400,300,1000,2,1000);
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
}
void Level6Part2()
{
	frameleft=ThirtySeconds;clrtime=5;
	if (towcnt==1)
	{
		ClearAll();
		return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Let's test the Advanced Bullet Script...\n\
From now on you can use your Clear Ranges, try pressing Z in game.");
	}
	if (Current_Position==1)
	{
		++part;
	}
}
int Level6Part3_Child()
{
	++stepskips;
	if (stepskips<100)return 0;
	stepskips=0;
	if (towcnt==1){towcnt=0;return 0;}
	CreateTower6(rand()%800,rand()%300,50,2,500);
	return 1;
}
void Level6Part3()
{
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	if (Level6Part3_Child())
	{
		for (int i=1;i<=towcnt;++i)
			if ((tower[i].towerspr->GetColor()>>24)<=0x80)
				tower[i].towerspr->SetColor(tower[i].towerspr->GetColor()+0x01FFFFFF);
			else
			{
				return;
			}
	}
}
void Level6Part4()
{
	frameleft=ThirtySeconds;clrtime=3;
	if (bulcnt!=0||towcnt!=5&&towcnt!=0)
	{
		ClearAll();
		return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Last level was very cool, wasn't it?");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	CreateTower6(400,300,750,2,1000);
	CreateTower6(30,10,750,2,1000);
	CreateTower6(746,10,750,2,1000);
	CreateTower6(30,556,750,2,1000);
	CreateTower6(746,556,750,2,1000);
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
}
void Level6Part5()
{
	frameleft=ThirtySeconds;clrtime=5;
	if (bulcnt!=0||towcnt!=33)
	{
		ClearAll();
		if (bulcnt!=0||towcnt!=0)return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("A row of fierce red tower?...");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	for (int i=1;i<=33;++i)
		int tmp=CreateTower6(i*24-20,30,3000,2,1000);
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
}
void Level6Part6()
{
	frameleft=ThirtySeconds;clrtime=3;
	if (bulcnt!=0||towcnt!=37)
	{
		ClearAll();
		if (bulcnt!=0||towcnt!=0)return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Enjoy the same maze.");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	CreateTower6(30,10,1500,2,1000);
	CreateTower6(746,10,1500,2,1000);
	CreateTower6(30,556,1500,2,1000);
	CreateTower6(746,556,1500,2,1000);
	for (int i=1;i<=33;++i)
	{
		int tmp=CreateTower3(i*24-20,570,1000,2,true);
		tower[tmp].t3t=3;
	}
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
}
void Level6Part7()
{
	frameleft=ThirtySeconds;clrtime=3;
	if (towcnt==37)
	{
		ClearAll();
		return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("You are supposed to leave now...");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	CreateTower4(30,10,2000,2);
	CreateTower4(746,10,2000,2);
	CreateTower4(30,556,2000,2);
	CreateTower4(746,556,2000,2);
	CreateTower3(120,80,300,2);
	CreateTower3(660,80,300,2);
	CreateTower3(120,480,300,2);
	CreateTower3(660,480,300,2);
	CreateTower1(400,30,500,2);
	for (int i=1;i<=towcnt;++i)
	{
		if (tower[i].towerspr->GetColor()==0x80FFFFFF)
			tower[i].towerspr->SetColor(0x00FFFFFF);
		if (tower[i].towertype==3)tower[i].t3t=1;
	}
	for (int i=1;i<=towcnt;++i)
		if ((tower[i].towerspr->GetColor()>>24)<=0x80)
			tower[i].towerspr->SetColor(tower[i].towerspr->GetColor()+0x01FFFFFF);
		else
		{
			IfCallLevel=false;
			return;
		}
}
void Level6Part8()
{
	frameleft=ThirtySeconds;clrtime=1;
	if (towcnt==9)
	{
		ClearAll();
		return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("I don't think you can pass this easily...");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	CreateTower1(30,10,300,2);
	CreateTower1(746,10,300,2);
	CreateTower1(30,556,300,2);
	CreateTower1(746,556,300,2);
	CreateTower4(400,30,3000,3);
	CreateTower3(900,900,999999,1);
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
}
void Level6Part9()
{
	frameleft=ThirtySeconds;clrtime=3;
	if (towcnt!=2&&towcnt!=0)
	{
		ClearAll();
		return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Okay you survived...\n\
But that was nothing much, more bombs is always the answer!");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	CreateTower2(400,300,100,1);
	CreateTower6(400,301,2000,1,1500);
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
}
void Level7Part0()
{
	frameleft=50;
	if (towcnt==2||bulcnt!=0)
	{
		ClearAll();
		return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Some freezy small objects are getting nearer...\n\
Level 7 - Frozen Towers");
		IfCallLevel=false;
	}
	if (Current_Position==1)
	{
		frameleft=0;
		return;
	}
}
void Level7Part1()
{
	frameleft=ThirtySeconds;clrtime=0;
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	whicnt=10;
	CreateTower7(400,300,1000,2,3000);
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
}
void Level7Part2()
{
	frameleft=ThirtySeconds;clrtime=3;
	if (bulcnt!=0||(towcnt!=5&&towcnt!=0))
	{
		ClearAll();
		if (bulcnt!=0||towcnt!=0)return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Is it horrifying?");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	whicnt=8;
	CreateTower7(400,300,2000,1,3000);
	CreateTower7(30,10,2000,1,3000);
	CreateTower7(746,10,2000,1,3000);
	CreateTower7(30,556,2000,1,3000);
	CreateTower7(746,556,2000,1,3000);
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
}
void Level7Part3()
{
	frameleft=ThirtySeconds;clrtime=5;
	if (towcnt==5)
	{
		ClearAll();
		return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Red & White.\n\
Bloody snow?");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	whicnt=5;
	for (int i=1;i<=33;++i)
		if (i&1)
			CreateTower6(i*24-20,30,3000,2,1000);
		else
			CreateTower7(i*24-20,30,3000,2,1000);
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
}
void Level7Part4()
{
	frameleft=ThirtySeconds;clrtime=0;
	if (towcnt==33||bulcnt!=0)
	{
		ClearAll();
		if (bulcnt!=0||towcnt!=0)return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Or this is only a bonus level?");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	for (int i=1;i<=33;++i)
		CreateTower1(i*24-20,30,1000,4),CreateTower1(i*24-20,567,1000,4);
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
}
void Level7Part5()
{
	frameleft=ThirtySeconds;clrtime=3;
	if (towcnt==66||bulcnt!=0)
	{
		ClearAll();
		if (bulcnt!=0||towcnt!=0)return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Wasn't that enough?");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	for (int i=1;i<=33;++i)
		CreateTower1(i*24-20,30,500,4),CreateTower5(i*24-20,567,500,4);
	CreateTower3(900,900,999999,1);//Dummy tower for avoiding mis-clearing
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
}
void Level7Part6()
{
	frameleft=ThirtySeconds;clrtime=3;
	if (towcnt==67||bulcnt!=0)
	{
		ClearAll();
		if (bulcnt!=0||towcnt!=0)return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("The impossible thing happened in the end...");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	for (int i=1;i<=33;++i)
		if (i&1)
			CreateTower6(i*24-20,30,3000,1,1500),CreateTower5(i*24-20,567,500,3);
		else
			CreateTower5(i*24-20,567,500,3);
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
}
void Level7Part7()
{
	frameleft=ThirtySeconds;clrtime=3;
	if (towcnt==50||bulcnt!=0)
	{
		ClearAll();
		if (bulcnt!=0||towcnt!=0)return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Do you think you are fooled?");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	whicnt=3;
	for (int i=1;i<=33;++i)
		if (i&1)
			CreateTower7(i*24-20,30,2000,1,2000),CreateTower5(i*24-20,567,500,3);
		else
			CreateTower5(i*24-20,567,500,3);
	CreateTower3(900,900,999999,1);//Dummy tower
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

}
void Level7Part8()
{
	frameleft=ThirtySeconds;clrtime=5;
	if (towcnt==51)
	{
		ClearAll();
		return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("I won't let you go easily...\n\
But why?");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	whicnt=2;
	for (int i=1;i<=33;++i)
		if (i&1)
			CreateTower6(400,30,3000,1,2000);//,CreateTower5(i*24-20,567,2000,3);
		else
			CreateTower1(i*24-20,567,2000,3);//,CreateTower7(i*24-20,30,3000,1,2000);
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
}
void Level7Part9()
{
	frameleft=TwentySeconds;clrtime=1;
	if (towcnt!=5&&towcnt!=0)
	{
		ClearAll();
		return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Let's relax a bit...");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	CreateTower1(400,30,300,2);
	CreateTower6(30,10,1000,2,1000);
	CreateTower6(746,10,1000,2,1000);
	CreateTower6(30,556,1000,2,1000);
	CreateTower6(746,556,1000,2,1000);
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

}
void Level7Part10()
{
	frameleft=ThirtySeconds;clrtime=3;
	if (towcnt==5)
	{
		ClearAll();
		return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("I still can't let you go...\n\
Just play with me! (And enjoy the double laby!)");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	for (int i=1;i<=33;++i)
	{
		int tmp=CreateTower3(i*24-20,570,500,2);
		tower[tmp].t3t=3;
	}
	for (int i=1;i<=23;++i)
	{
		int tmp=CreateTower3(772,i*24,500,2);
		tower[tmp].t3t=2;
	}
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
}
void Level7Part11()
{
	frameleft=AMinute;clrtime=3;
	if ((towcnt!=5&&towcnt!=0)||bulcnt!=0)
	{
		ClearAll();
		if (bulcnt!=0||towcnt!=0)return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("You will be full of holes after this level...");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	whicnt=50;
	CreateTower7(400,30,3000,1,3000);
	CreateTower6(30,10,2000,1,2000);
	CreateTower6(746,10,2000,1,2000);
	CreateTower6(30,556,2000,1,2000);
	CreateTower6(746,556,2000,1,2000);
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
}
void Level7Part12()
{
	frameleft=AMinute;clrtime=3;
	if ((towcnt!=6&&towcnt!=0)||bulcnt!=0)
	{
		ClearAll();
		if (bulcnt!=0||towcnt!=0)return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Well, here it is.");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	whicnt=50;
	CreateTower7(400,30,3000,1,3000);
	CreateTower6(400,300,2000,1,1500);
	CreateTower1(30,10,2000,2);
	CreateTower1(746,10,2000,2);
	CreateTower1(30,556,2000,2);
	CreateTower1(746,556,2000,2);
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

}
void Level8Part0()
{
	frameleft=50;
	if (towcnt==6)
	{
		ClearAll();
		return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Welcome to the world that is only known by...masochism\n\
Level 8 - Entertainment!");
		IfCallLevel=false;
	}
	if (Current_Position==1)
	{
		frameleft=0;
		return;
	}
}
void Level8Part1()
{
	frameleft=ThirtySeconds;clrtime=0;
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	CreateTower7(400,300,2500,8,750);
	whicnt=25;
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

}
void Level8Part2()
{
	frameleft=TenSeconds;clrtime=3;
	if (towcnt!=2&&bulcnt!=0)
	{
		ClearAll();
		if (bulcnt!=0||towcnt!=0)return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Just another joke?");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	deltadelta=0.004363322313/4;
	CreateTower2(420,60,100,3);
	CreateTower2(380,60,100,3);
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
}
void Level8Part3()
{
	frameleft=TenSeconds;
	CreateTower2(460,100,100,3);
	CreateTower2(340,100,100,3);
	deltadelta=0.004363322313/8;
	IfCallLevel=false;
}
void Level8Part4()
{
	frameleft=TenSeconds;
	CreateTower2(500,140,100,3);
	CreateTower2(300,140,100,3);
	deltadelta=0.004363322313/16;
	IfCallLevel=false;
}
void Level8Part5()
{
	frameleft=ThirtySeconds;clrtime=1;
	if (towcnt==6||bulcnt!=0)
	{
		ClearAll();
		if (bulcnt!=0||towcnt!=0)return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("They are not cute enough to follow you all the time...");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	yelattrib=true;
	for (int i=1;i<=33;++i)
		int tmp=CreateTower4(i*24-20,30,2000,4,2000);
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
}
void Level8Part6()
{
	frameleft=AMinute;clrtime=3;
	clrtime=3;
	if (towcnt==33||(bulcnt!=0&&towcnt!=4))
	{
		ClearAll();
		if (bulcnt!=0||towcnt!=0)return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Hope you can enjoy... the entertaining level\n\
Are they bullets or other object?");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	CreateTower1(30,10,20,10);
	CreateTower1(746,10,20,10);
	CreateTower1(30,556,20,10);
	CreateTower1(746,556,20,10);
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
}
void Level8Part7()
{
	frameleft=ThirtySeconds;clrtime=5;
	if (towcnt==4||bulcnt!=0)
	{
		ClearAll();
		if (bulcnt!=0||towcnt!=0)return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Nautilus!");
	}
	if (Current_Position==1)
	{
		++part;
	}
}
int Level8Part8_Child()
{
	++stepskips;
	if (stepskips<2)return 0;
	stepskips=0;
	linerad+=0.05;
	for (int i=1;;++i)
	{
		double tx=400+sin(linerad)*i*12;
		double ty=300+cos(linerad)*i*12;
		if (tx>800||tx<0||ty>600||ty<0)
		{
			hge->Gfx_RenderLine(400,300,tx,ty,0x80CCFF00);
			break;
		}
		int bult=CreateBullet1(tx,ty,1);
		bullet[bult].bulletdir.x=-sin(linerad/*-1.5707963268*/);
		bullet[bult].bulletdir.y=-cos(linerad/*-1.5707963268*/);
		bullet[bult].dist=bullet[bult].bulletdir.x*bullet[bult].bulletdir.x+bullet[bult].bulletdir.y*bullet[bult].bulletdir.y;
		bullet[bult].dist=sqrt(bullet[bult].dist);
	}
	return 1;
}
void Level8Part8()
{
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	frameskips=0;
	if (Level8Part8_Child())
	{
	}
}
void Level8Part9()
{
	frameleft=AMinute;clrtime=5;
	if (bulcnt!=0&&towcnt!=2)
	{
		ClearAll();
		if (bulcnt!=0||towcnt!=0)return;
	}
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Two towers means too much");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	CreateTower6(380,60,1000,8,1000);
	CreateTower7(420,60,1000,8,750);
	whicnt=16;
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
}
void Level8Part10()
{
	frameleft=AMinute;clrtime=5;
	if (towcnt==2)
	{
		ClearAll();
		return;
	}
	DisableAllTower=false;
	bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Well, here is the final mixture.\n\
Enjoy it!");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	CreateTower4(30,10,2000,2,3000);
	CreateTower4(746,10,2000,2,3000);
	CreateTower4(30,556,2000,2,3000);
	CreateTower4(746,556,2000,2,3000);
	CreateTower3(120,80,300,2);
	CreateTower3(660,80,300,2);
	CreateTower3(120,480,300,2);
	CreateTower3(660,480,300,2);
	CreateTower1(400,30,500,2);
	CreateTower6(380,60,1000,6,1000);
	CreateTower7(420,60,1000,6,750);
	for (int i=1;i<=towcnt;++i)
		if (tower[i].towertype==3)
			tower[i].t3t=1;
	yelattrib=true;
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
}
void Level8Part11()
{
	frameleft=AMinute;
	if (towcnt!=1&&bulcnt!=0)
	{
		ClearAll();
		if (bulcnt!=0||towcnt!=0)return;
	}
	DisableAllTower=false;
	towcnt=0;bulcnt=0;memset(bullet,0,sizeof(bullet));
	if (IfShowTip)
	{
		IfShowTip=false;
		FadeTip=false;
		Current_Position=2;
		ShowTip("Addition Level: Reflection++\n\
Give yourself an award even if you cannot pass this level.");
		return;
	}
	++frameskips;
	if (frameskips<10&&!LOWFPS)return;
	Refliction=true;
	CreateTower6(400,566,1000,2,1000);
	/*for (int i=1;i<=33;++i)
	{
		int tmp=CreateTower3(i*24-20,570,1000,2);
		tower[tmp].t3t=3;
	}
	for (int i=1;i<=23;++i)
	{
		int tmp=CreateTower3(772,i*24,1000,2);
		tower[tmp].t3t=2;
	}*/
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
}
