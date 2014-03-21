//Chrisoft Bullet Lab Remix HGE
//Chrisoft Game Helper Extras implementations
//Copyright Chrisoft 2014
#include "libcgh.h"
#include <cmath>
#include <cstring>
//static const char* LIBCGH_SRC_FN="libcghEx.cpp";

void RandomEngine::SetSeed(unsigned int seed){cseed=seed;}
int RandomEngine::NextInt(int min,int max)
{
	if (min>max){int t=min;min=max;max=t;}
	cseed*=214013;cseed+=2531011;
	return min+(cseed^cseed>>15)%(max-min+1);
}
double RandomEngine::NextDouble(double min,double max)
{
	if (min>max){double t=min;min=max;max=t;}
	cseed*=214013;cseed+=2531011;
	return min+(cseed>>16)*(1.0f/65535.0f)*(max-min);
}
void CircleIndicator::Init(double _r,double _thk,BYTE _a,bool _gr,HTEXTURE _Texture,TextureRect _TR,DWORD _cc)
{
	circle=new hgeDistortionMesh(1025,3);
	circle->SetTexture(_Texture);
	circle->SetTextureRect(_TR.x,_TR.y,_TR.w,_TR.h);
	radius=_r;thk=_thk;gradient=_gr;alpha=_a;
	if (_gr)ccolour=SETA(0x00FF0000,alpha);else ccolour=_cc;
	for (int i=0;i<=1024;++i)
	{
		double tang,tx,ty;
		tang=(double)i/1024.0f*pi*2-pi/2;
		tx=-cos(tang)*radius;ty=sin(tang)*radius;
		circle->SetDisplacement(i,2,tx,ty,HGEDISP_TOPLEFT);
		tx*=thk;ty*=thk;
		circle->SetDisplacement(i,1,tx,ty,HGEDISP_TOPLEFT);
		tx*=thk;ty*=thk;
		circle->SetDisplacement(i,0,tx,ty,HGEDISP_TOPLEFT);
	}
}
void CircleIndicator::SetAlpha(BYTE _alpha){alpha=_alpha;}
void CircleIndicator::SetValue(double _value)
{
		value=_value;
		for (int i=0;i<=1024;++i)
		{
			int tr=(int)((1.0f-value)*255);
			int tg=(int)(value*255);
			DWORD tcolour=ARGB(alpha,tr,tg,0);
			hgeColorHSV *tc=new hgeColorHSV(tcolour);
			if (tc->v<0.85)tc->v=0.85;
			if (gradient)tcolour=SETA(tc->GetHWColor(),alpha);else tcolour=SETA(ccolour,alpha);
			if ((double)i/1024.0f<=value)
			{
				circle->SetColor(i,0,tcolour);
				circle->SetColor(i,1,SETA(0x00FFFFFF,alpha));
				circle->SetColor(i,2,tcolour);
			}
			else
			{
				circle->SetColor(i,0,0x00000000);
				circle->SetColor(i,1,0x00000000);
				circle->SetColor(i,2,0x00000000);
			}
		}
	}
void CircleIndicator::Render(double x,double y){circle->Render(x,y);}

void LinearProgresser::Init(double _a,double _b,double _Lim){a=_a,b=_b,Limit=_Lim;}
void LinearProgresser::Launch(){Elapsed=0;val=a;}
void LinearProgresser::Update(double DT){if (Elapsed>=Limit)return (void)(val=b,Elapsed=Limit);Elapsed+=DT;val=(b-a)*(Elapsed/Limit)+a;}
double LinearProgresser::GetValue(){return val;}
double LinearProgresser::GetA(){return a;}
double LinearProgresser::GetB(){return b;}
double LinearProgresser::GetPercentage(){return (Elapsed/Limit);}
double LinearProgresser::GetDelta(){return val-a;}
double LinearProgresser::GetElapsed(){return Elapsed;}

bool HangUpText::Active(){return TFont&&!done;}
void HangUpText::Init(const char *Font,const char *_Text,double _tlim,double _alim,double _dlim,DWORD _color)
{
	TFont=new hgeFont(Font);
	strcpy(Text,_Text);
	Limit=_tlim;alim=_alim;dlim=_dlim;TFont->SetColor(_color);
	Progresser.Init(0,dlim,Limit);Progalpha.Init(0,255,Limit/2);
}
void HangUpText::Launch(vector2d pos)
{
	Position=pos;Elapsed=0;delta=0;Progresser.Launch();Progalpha.Launch();done=false;
}
void HangUpText::Process(double DT)
{
	Progresser.Update(DT);
	Position.y-=delta;
	delta=Progresser.GetDelta();
	Position.y+=delta;
	if (Progresser.GetElapsed()>Limit/2&&Progalpha.GetA()<Progalpha.GetB())
	{
		Progalpha.Init(255,0,Limit/2);
		Progalpha.Launch();
	}
	if (Progalpha.GetA()>Progalpha.GetB()&&Progresser.GetElapsed()>=Limit)return (void)(done=true);
	Progalpha.Update(DT);
	TFont->SetColor(SETA(TFont->GetColor(),Progalpha.GetValue()));
	TFont->printf(Position.x,Position.y,HGETEXT_CENTER,Text);
}
