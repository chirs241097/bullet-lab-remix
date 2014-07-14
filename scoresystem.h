// Chrisoft Bullet Lab Remix HGE -*- C++ -*-
// Multiplier implementations
// Copyright Chrisoft 2014
CircleIndicator MultTimer;
hgeFont *MultFnt;
hgeSprite *MB;
int valbrk;
//static const char* SCORESYSTEM_H_FN="scoresystem.h";

//Multiplier Indicator

HangUpText MT[255];
void NewMT()
{
	int i=0;while (MT[i].Active())++i;
	char ttext[10];sprintf(ttext,"x%.2lf",mult);
	MT[i].Init("./Resources/charmap.fnt",ttext,1.0f,200,-50);
	MT[i].Launch(vector2d(playerpos.x,playerpos.y-25));
}
void ProcessMT()
{
	for (int i=0;i<=255;++i)if (MT[i].Active())MT[i].Process(hge->Timer_GetDelta());
}

//Multiplier +1
class MultPo
{
private:
	hgeSprite *Mult,*SpwnEfx;
	double Lifetime,LifeLim,speed;
	vector2d position,direction;
	int blinkbrk;
	bool Active,blnkshow,followplyr;
public:
	bool IsActive(){return Active;}
	void Init(double _lt,double _speed,vector2d _pos,vector2d _dir)
	{
		Lifetime=0;LifeLim=_lt;speed=_speed;position=_pos;direction=_dir;
		Mult=new hgeSprite(SprSheet,0,272,48,48);Active=true;blinkbrk=0;blnkshow=true;
		Mult->SetHotSpot(24,24);followplyr=false;SpwnEfx=new hgeSprite(SprSheet,48,272,48,48);
		SpwnEfx->SetHotSpot(24,24);
	}
	void Process()
	{
		if(GetDist(playerpos,position)<=64)followplyr=true;
		if(!clrmode)
		{
			if(clrrange!=0&&GetDist(playerpos,position)<=clrmaxrange)followplyr=true;
		}
		else
		{
			if(clrrad-pi/2>1e-7&&GetDist(playerpos,position)<=clrmaxrange)followplyr=true;
		}
		if(followplyr)
		{
			direction=ToUnitCircle(playerpos-position);
			speed=0.4;
		}else Lifetime+=hge->Timer_GetDelta();
		if(GetDist(playerpos,position)<=9)
		{
			++mult,NewMT(),Active=false;
			delete Mult;delete SpwnEfx;return;
		}
		if(Lifetime>LifeLim)
		{
			delete Mult;delete SpwnEfx;
			return (void)(Active=false);
		}
		if(Lifetime<LifeLim*0.03)
		{
            double siz=(LifeLim*0.03-Lifetime)/(LifeLim*0.03)*3;
            SpwnEfx->SetColor(SETA(SpwnEfx->GetColor(),Lifetime/(LifeLim*0.03)*255));
            SpwnEfx->RenderEx(position.x,position.y,0,siz);
		}
		if(Lifetime>LifeLim*0.8)
		{
			if (!LOWFPS)++blinkbrk;else blinkbrk+=17;
			if (blinkbrk>200)blinkbrk=0,blnkshow=!blnkshow;
			if (blnkshow)
				Mult->RenderEx(position.x,position.y,0,0.8);
		}
		else
		Mult->RenderEx(position.x,position.y,0,0.8);
		if(!followplyr)
		{
			if (position.x>780||position.x<20)direction.x=-direction.x;
			if (position.y>780||position.y<20)direction.y=-direction.y;
		}
		int times=1;if (LOWFPS)times=17;
		for (int i=1;i<=times;++i)
		position.x+=direction.x*speed,position.y+=direction.y*speed;
	}
};
MultPo Multpo[255];
void NewMultpo(vector2d pos=vector2d(-99,-99))
{
	int i=0;while (Multpo[i].IsActive())++i;
	if (pos.x+99<=1e-6&&pos.y+99<=1e-6)
		pos.x=re.NextInt(20,770),pos.y=re.NextInt(20,570);
	vector2d dir=ToUnitCircle(vector2d(rand()%1000-500,rand()%1000-500));
	Multpo[i].Init(7.5,0.02,pos,dir);
}
void ProcessMultpo()
{
	for (int i=0;i<=255;++i)if(Multpo[i].IsActive())Multpo[i].Process();
}
//Auto Multipliers

void Mult_Init()
{
	MultTimer.Init(50,0.95,0xC0,false,SprSheet,TextureRect(151,264,2,8),0x00FF0000);
	multbrk=TenSeconds;multbat=mult=1;valbrk=0;
	MB=new hgeSprite(MultFnt->GetTexture(),0,235,163,21);
	MB->SetHotSpot(81.5,10.5);
	memset(Multpo,0,sizeof(Multpo));
}
double GetHscle()
{
	if (multbrk<=TenSeconds/10.0f*0.2f)return (TenSeconds/10.0f*0.3f-multbrk)/(TenSeconds/10.0f)*10;
	if (multbrk<=TenSeconds/10.0f*4.5f)return 1.0f;
	return (multbrk-TenSeconds/10.0f*4.15f)/(multbrk-TenSeconds/10.0f)*10;
}
int GetAlpha()
{
	if (multbrk<=TenSeconds/10.0f*0.2f)return (int)(255-255*(TenSeconds/10.0f*0.2f-multbrk)/(TenSeconds/50.0f));
	if (multbrk<=TenSeconds/10.0f*4.5f)return 0xFF;
	return (int)(255*(TenSeconds/2-multbrk)/(TenSeconds/10));
}
void Mult_FrameFunc()
{
	if (Current_Position!=1)return;
	ProcessMT();ProcessMultpo();
	--multbrk;
	if(!dsmc)lsc+=hge->Timer_GetDelta();else lsc=0;
	if(lsc>1&&mult>1.0f)mult-=hge->Timer_GetDelta()/20.0f;
	if (multbrk<0)
	{
		multbrk=ThirtySeconds;
		mult+=multbat;lsc=0;
		NewMT();
		if (multbat<5)++multbat;
	}
	if (multbrk<TenSeconds/2)
	{
		++valbrk;
		if (LOWFPS||valbrk>30)
		MultTimer.SetValue((double)multbrk/((double)TenSeconds/2.0f));
		if (valbrk>30)valbrk=0;
		MultTimer.Render(playerpos.x+8.4,playerpos.y+8.4);
		MB->SetColor(SETA(0x00FFFFFF,0.8*GetAlpha()));
		MB->RenderEx(playerpos.x+8.4,playerpos.y-26.4,0,GetHscle(),1.0f);
	}
}
void Mult_BatClear()
{
	multbrk=ThirtySeconds;
	multbat=1;
}
