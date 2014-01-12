//Chrisoft Bullet Lab Remix HGE
//Background drawing Implementations
//"Copyleft" Chrisoft 2013
const char* BACKGROUND_H_FN="background.h";

double deltaBG;
//********************************************
//Full-screen Leaves Background
//********************************************
class BG_Leaves
{
private:
	DWORD alpha,alim;
	bool onfadein,onfadeout;
	int fadebreak;
	hgeSprite* BGSpr[6][6];
	HTEXTURE LeafTex;
	void DoFadeIn()
	{
		if (LOWFPS)fadebreak+=17;else ++fadebreak;
		if (fadebreak>17)fadebreak=0;else return;
		if (LOWFPS)if(alpha+0x20<=alim)alpha+=0x20;else{}
		else if (alpha+0x2<=alim)alpha+=2;
		if (alpha>=alim)onfadein=false;
	}
	void DoFadeOut()
	{
		if (LOWFPS)fadebreak+=17;else ++fadebreak;
		if (fadebreak>30)fadebreak=0;else return;
		if (LOWFPS)
			if (alpha<0x20)alpha=0;else alpha-=0x20;
		else
			if (alpha<0x2)alpha=0;else alpha-=0x2;
		if (!alpha)onfadeout=0;
	}
public:
	bool IsActive()
	{
		return alpha?true:false;
	}
	void Init(DWORD limalpha)
	{
		LeafTex=hge->Texture_Load("./Resources/b_leaves.png");
		for (int i=0;i<6;++i)
		for (int j=0;j<6;++j)
		{
			BGSpr[i][j]=new hgeSprite(LeafTex,0,0,200,150);
			BGSpr[i][j]->SetColor(0x00CCCCCC);
		}
		onfadein=onfadeout=false;alpha=0x00;alim=limalpha;fadebreak=0;

	}
	void SetFadeIn()
	{
		alpha=0x01;
		onfadein=true;
	}
	void SetFadeOut()
	{
		alpha=alim;
		onfadeout=true;
	}
	void Update()
	{
		double tx,ty,dt;
		DWORD tcol;
		if (onfadein)DoFadeIn();
		if (onfadeout)DoFadeOut();
		dt=hge->Timer_GetDelta();
		deltaBG+=dt;
		tx=200*cosf(deltaBG/10);
		ty=150*sinf(deltaBG/10);
		for (int i=-1;i<5;++i)
		for (int j=-1;j<5;++j)
			BGSpr[i+1][j+1]->SetColor(ARGB(alpha,0xCC,0xCC,0xCC)),
			BGSpr[i+1][j+1]->Render(i*199.0f+tx,j*149.0f+ty);
	}
};
BG_Leaves Leaves;
//********************************************
//Animated Leaves Background
//********************************************
HTEXTURE TLeaf;
HTEXTURE TSflake;
class Leaf_Anim;
Leaf_Anim *Head,*Tail;
bool LE_Active;
double lescale;
HTEXTURE letex;TextureRect letr;
DWORD lecolor;
class Leaf_Anim
{
private:
	hgeSprite* Leaf;
	double Rotation,DRotate;
	double x,y,dx,dy;
	int lim;
	~Leaf_Anim(){}
public:
	Leaf_Anim *Last,*Next;
	void init(int _lim)
	{
		//Leaf=new hgeSprite(letex,0,0,108,108);
		Leaf=new hgeSprite(letex,letr.x,letr.y,letr.w,letr.h);
		Leaf->SetColor(lecolor);
		x=rand()%908-108;
		y=-108;
		lim=_lim;
		dx=rand()%200/100.0f-1.0f;
		dx*=0.075;
		dy=rand()%200/100.0f+0.5f;
		dy*=0.075;
		Rotation=0;
		DRotate=rand()%100/10000.0f;
		DRotate*=0.1;
		Next=NULL;
	}
	void Delete()
	{
		if (this==Head)Head=this->Next;
		if (this==Tail)Tail=this->Last;
		if (this->Next)
		this->Next->Last=this->Last;
		if (this->Last)
		this->Last->Next=this->Next;
		delete this->Leaf;
		delete this;//Not sure this will work?..--Answer: This worked...
	}
	void Update()
	{
		if (!this||!Leaf)return;
		int times=1;if (LOWFPS)times=17;
		for (int i=1;i<=times;++i)
		{
			Rotation+=DRotate;
			x+=dx;y+=dy;
		}
		if (x>908||x<-108||y>708)return Delete();
		if (!Leaf)return;
		Leaf->RenderEx(x,y,Rotation,lescale);
	}
	void Process()
	{
		int times=1;
		if(LOWFPS) times=17;
		for (int i=1;i<=times;++i)
		if (rand()%1000>lim&&LE_Active)
		{
			Tail->Next=new Leaf_Anim();
			Tail->Next->init(990);
			Tail->Next->Last=Tail;
			Tail=Tail->Next;
		}
		Leaf_Anim *cur=Head;
		while (cur)cur->Update(),cur=cur->Next;
	}
};
//********************************************
//3D-Clouds Background
//********************************************
class TDClouds
{
private:
	hgeQuad CQuad;
	double DTime;
	int alpha,lima;
	bool onFadein,onFadeout;
	void DoFadein()
	{
		int times=1;
		if (LOWFPS)times=17;
		for (int i=1;i<=times;++i)if (alpha<lima)++alpha;
	}
	void DoFadeout()
	{
		int times=1;
		if (LOWFPS)times=17;
		for (int i=1;i<=times;++i)if (alpha>0)--alpha;
	}
public:
	void Init(int _lima)
	{
		DTime=0.0f;
		CQuad.tex=hge->Texture_Load("sky.png");
		CQuad.blend=BLEND_ALPHABLEND;
		alpha=0;lima=_lima;
		onFadein=onFadeout=false;
		for (int i=0;i<4;++i)
		CQuad.v[i].col=0x00FFFFFF;
		CQuad.v[0].x=0,CQuad.v[0].y=300;
		CQuad.v[1].x=800,CQuad.v[1].y=300;
		CQuad.v[2].x=1000,CQuad.v[2].y=600;
		CQuad.v[3].x=-200,CQuad.v[3].y=600;
		CQuad.v[0].tx=0,CQuad.v[0].ty=0;
		CQuad.v[0].tx=0.5,CQuad.v[0].ty=0;
		CQuad.v[0].tx=0.5,CQuad.v[0].ty=0.5;
		CQuad.v[0].tx=0,CQuad.v[0].ty=0.5;
	}
	void SetFadein()
	{
		onFadein=true;
		onFadeout=false;
		alpha=0;
	}
	void SetFadeout()
	{
		onFadeout=true;
		onFadein=false;
		alpha=lima;
	}
	void Update()
	{
		if (onFadein)DoFadein();
		if (onFadeout)DoFadeout();
		for (int i=0;i<4;++i)
		CQuad.v[i].col=ARGB(alpha,0xFF,0xFF,0xFF);
		DTime+=0.1*hge->Timer_GetDelta();
		CQuad.v[0].tx=cos(DTime),CQuad.v[0].ty=sin(DTime);
		CQuad.v[1].tx=CQuad.v[0].tx+0.5f;CQuad.v[1].ty=CQuad.v[0].ty;
		CQuad.v[2].tx=CQuad.v[0].tx+0.5f;CQuad.v[2].ty=CQuad.v[0].ty+0.5f;
		CQuad.v[3].tx=CQuad.v[0].tx;CQuad.v[3].ty=CQuad.v[0].ty+0.5f;
		hge->Gfx_RenderQuad(&CQuad);
	}
};
TDClouds Sky;

DWORD ColorTransfer(DWORD a,DWORD t)
{
	int r=GETR(a),g=GETG(a),b=GETB(a);
	int tr=GETR(t),tg=GETG(t),tb=GETB(t);
	if (r<tr)++r;if (r>tr)--r;
	if (g<tg)++g;if (g>tg)--g;
	if (b<tb)++b;if (b>tb)--b;
	a=SETR(a,r);a=SETG(a,g);a=SETB(a,b);
}
