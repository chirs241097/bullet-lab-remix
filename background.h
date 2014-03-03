//Chrisoft Bullet Lab Remix HGE
//Background drawing Implementations
//Copyright Chrisoft 2014
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
	hgeSprite* BGSpr;
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
		BGSpr=new hgeSprite(LeafTex,0,0,200,150);
		BGSpr->SetColor(0x00CCCCCC);
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
		if (onfadein)DoFadeIn();
		if (onfadeout)DoFadeOut();
		dt=hge->Timer_GetDelta();
		deltaBG+=dt;
		tx=200*cosf(deltaBG/10);
		ty=150*sinf(deltaBG/10);
		BGSpr->SetColor(ARGB(alpha,0xCC,0xCC,0xCC));
		for (int i=-1;i<5;++i)
		for (int j=-1;j<5;++j)
			BGSpr->Render(i*199.0f+tx,j*149.0f+ty);
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
		delete this;
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
//3D-sky Background
//Based on a hge tutorial
//********************************************
static const DWORD skyTopColors[3] = {0xFF15092A, 0xFF6C6480, 0xFF89B9D0};
static const DWORD skyBtmColors[3] = {0xFF303E57, 0xFFAC7963, 0xFFCAD7DB};
static const DWORD seaTopColors[3] = {0xFF3D546B, 0xFF927E76, 0xFF86A2AD};
static const DWORD seaBtmColors[3] = {0xFF1E394C, 0xFF2F4E64, 0xFF2F4E64};
static const int skyseq[9]={0, 0, 1, 2, 2, 2, 1, 0, 0};
class TDSky
{
#define ScreenWidth 800
#define ScreenHeight 600
#define Stars 100
#define SeaDisize 16
#define SkyHeight (ScreenHeight*0.6f)
#define StarsHeight (SkyHeight*0.9f)
#define OrbitRadius (ScreenWidth*0.43f)
private:
	HTEXTURE skyitem;
	hgeSprite *sky,*sun,*moon,*glow,*seaglow,*star;
	hgeDistortionMesh *sea,*skylyr;
	float timet,speed,skya,skylima,seq_residue;
	int seq_id;
	float starX[Stars],starY[Stars],starS[Stars],starA[Stars],seaP[SeaDisize];
	hgeColor colWhite,colSkyTop,colSkyBtm,colSeaTop,colSeaBtm;
	hgeColor colSun,colSunGlow;
	hgeColor colMoon,colMoonGlow,colSeaGlow;
	float sunX,sunY,sunS,sunGlowS;
	float moonX,moonY,moonS,moonGlowS;
	float seaGlowX,seaGlowSX,seaGlowSY;
	bool skyOnFadeIn,skyOnFadeOut;
	float GetTime()
	{
		struct tm *t=0;
		time_t tt=time(NULL);
		t=localtime(&tt);
		float tmp=0;
		if(t)
		{
			tmp=t->tm_sec;
			tmp=t->tm_min+tmp/60.0f;
			tmp=t->tm_hour+tmp/60.0f;
		}
		return tmp;
	}
	void SkyDoFadeIn()
	{
		float dlt=1.0f/hge->Timer_GetFPS();
		if (skya+dlt<skylima)skya+=dlt;
		else skya=skylima,skyOnFadeIn=false;
	}
	void SkyDoFadeOut()
	{
		float dlt=1.0f/hge->Timer_GetFPS();
		if (skya-dlt>0)skya-=dlt;
		else skya=0.0f,skyOnFadeOut=false;
	}
public:
	bool Init()
	{
		skyitem=hge->Texture_Load("./Resources/e_skyitem.png");
		if(!skyitem) return false;
		sky=new hgeSprite(0, 0, 0, ScreenWidth, ScreenHeight);
		sea=new hgeDistortionMesh(SeaDisize, SeaDisize);
		sea->SetTextureRect(0, 0, ScreenWidth, ScreenHeight-SkyHeight);
		sun=new hgeSprite(skyitem,81,0,114,114);
		sun->SetHotSpot(57,57);
		moon=new hgeSprite(skyitem,0,0,81,81);
		moon->SetHotSpot(40,40);
		star=new hgeSprite(skyitem,195,0,9,9);
		star->SetHotSpot(5,5);
		glow=new hgeSprite(skyitem,204,0,128,128);
		glow->SetHotSpot(64,64);
		glow->SetBlendMode(BLEND_COLORADD | BLEND_ALPHABLEND | BLEND_NOZWRITE);
		seaglow=new hgeSprite(skyitem,204,96,128,32);
		seaglow->SetHotSpot(64,0);
		seaglow->SetBlendMode(BLEND_COLORADD | BLEND_ALPHAADD | BLEND_NOZWRITE);
		skylyr=new hgeDistortionMesh(16, 16);
		skylyr->SetTexture(skyitem);
		skylyr->SetTextureRect(0,128,512,512);
		skylyr->SetBlendMode(BLEND_ALPHAADD);
		colWhite.SetHWColor(0xFFFFFFFF);
		timet=GetTime();
		speed=skya=0.0f;
		for(int i=0;i<Stars;++i)
		{
			starX[i]=rand()%ScreenWidth;
			starY[i]=rand()%((int)StarsHeight);
			starS[i]=(rand()%60+10.0f)/100.0f;
		}
		for(int i=0;i<SeaDisize;++i)
		{
			seaP[i]=i+(rand()%300-150.0f)/10.0f;
		}
		return true;
	}
	void Deinit()
	{
		delete seaglow;delete glow;
		delete star;delete moon;
		delete sun;delete sky;
		delete sea;delete skylyr;
		hge->Texture_Free(skyitem);
	}
	void SetSpeed(float _speed){speed=_speed;}
	void SetSkyA(float _skya){skya=_skya;}
	void SetTime(float _timet){timet=_timet;}
	void SkySetFadeIn(float _starta=0.0f,float _lima=1.0f)
	{
		skya=_starta;skylima=_lima;
		skyOnFadeIn=true;skyOnFadeOut=false;
	}
	void SkySetFadeOut(float _starta=0.0f)
	{
		if (_starta>1E-4)skya=_starta;
		skyOnFadeIn=false;skyOnFadeOut=true;
	}
	void Update()
	{
		int i, j, k;
		float zenith,a,dy,fTime;
		float posX,s1,s2;
		const float cellw=ScreenWidth/(SeaDisize-1);
		hgeColor col1,col2;
		DWORD dwCol1,dwCol2;
		if(speed==0.0f) timet=GetTime();
		else
		{
			timet+=hge->Timer_GetDelta()*speed;
			if(timet>=24.0f) timet-=24.0f;
		}
		seq_id=(int)(timet/3);
		seq_residue=timet/3-seq_id;
		zenith=-(timet/12.0f*pi-pi/2.0f);
		col1.SetHWColor(skyTopColors[skyseq[seq_id]]);
		col2.SetHWColor(skyTopColors[skyseq[seq_id+1]]);
		colSkyTop=col2*seq_residue + col1*(1.0f-seq_residue);
		col1.SetHWColor(skyBtmColors[skyseq[seq_id]]);
		col2.SetHWColor(skyBtmColors[skyseq[seq_id+1]]);
		colSkyBtm=col2*seq_residue + col1*(1.0f-seq_residue);
		col1.SetHWColor(seaTopColors[skyseq[seq_id]]);
		col2.SetHWColor(seaTopColors[skyseq[seq_id+1]]);
		colSeaTop=col2*seq_residue + col1*(1.0f-seq_residue);
		col1.SetHWColor(seaBtmColors[skyseq[seq_id]]);
		col2.SetHWColor(seaBtmColors[skyseq[seq_id+1]]);
		colSeaBtm=col2*seq_residue + col1*(1.0f-seq_residue);
		if(seq_id>=6 || seq_id<2)
			for(int i=0; i<Stars; ++i)
			{
				a=1.0f-starY[i]/StarsHeight;
				//a*=hge->Random_Float(0.6f, 1.0f);
				a*=(rand()%40+60.0f)/100.0f;
				if(seq_id>=6) a*=sinf((timet-18.0f)/12.0f*pi);
				else a*=sinf((1.0f-timet/6.0f)*pi/2);
				starA[i]=a;
			}
			if(seq_id==2) a=sinf(seq_residue*pi/2);
		else if(seq_id==5) a=cosf(seq_residue*pi/2);
		else if(seq_id>2 && seq_id<5) a=1.0f;
		else a=0.0f;
		colSun.SetHWColor(0xFFEAE1BE);
		colSun=colSun*(1-a)+colWhite*a;
		a=(cosf(timet/6.0f*pi)+1.0f)/2.0f;
		if(seq_id>=2 && seq_id<=6)
		{
			colSunGlow=colWhite*a;
			colSunGlow.a=1.0f;
		}
		else colSunGlow.SetHWColor(0xFF000000);
		sunX=ScreenWidth*0.5f+cosf(zenith)*OrbitRadius;
		sunY=SkyHeight*1.2f+sinf(zenith)*OrbitRadius;
		sunS=1.0f-0.3f*sinf((timet-6.0f)/12.0f*pi);
		sunGlowS=3.0f*(1.0f-a)+3.0f;
		if(seq_id>=6) a=sinf((timet-18.0f)/12.0f*pi);
		else a=sinf((1.0f-timet/6.0f)*pi/2);
		colMoon.SetHWColor(0x20FFFFFF);
		colMoon=colMoon*(1-a)+colWhite*a;
		colMoonGlow=colWhite;
		colMoonGlow.a=0.5f*a;
		moonX=ScreenWidth*0.5f+cosf(zenith-pi)*OrbitRadius;
		moonY=SkyHeight*1.2f+sinf(zenith-pi)*OrbitRadius;
		moonS=1.0f-0.3f*sinf((timet+6.0f)/12.0f*pi);
		moonGlowS=a*0.4f+0.5f;
		if(timet>19.0f || timet<4.5f)
		{
			a=0.2f;
			if(timet>19.0f && timet<20.0f) a*=(timet-19.0f);
			else if(timet>3.5f && timet<4.5f) a*=1.0f-(timet-3.5f);
			colSeaGlow=colMoonGlow;
			colSeaGlow.a=a;
			seaGlowX=moonX;
			seaGlowSX=moonGlowS*3.0f;
			seaGlowSY=moonGlowS*2.0f;
		}
		else if(timet>6.5f && timet<19.0f)
		{
			a=0.3f;
			if(timet<7.5f) a*=(timet-6.5f);
			else if(timet>18.0f) a*=1.0f-(timet-18.0f);
			colSeaGlow=colSunGlow;
			colSeaGlow.a=a;
			seaGlowX=sunX;
			seaGlowSX=sunGlowS;
			seaGlowSY=sunGlowS*0.6f;
		}
		else colSeaGlow.a=0.0f;
		for(i=1; i<SeaDisize-1; ++i)
		{
			a=float(i)/(SeaDisize-1);
			col1=colSeaTop*(1-a)+colSeaBtm*a;
			dwCol1=col1.GetHWColor();
			fTime=2.0f*hge->Timer_GetTime();
			a*=20;
			for(j=0; j<SeaDisize; ++j)
			{
				sea->SetColor(j, i, dwCol1);
				dy=a*sinf(seaP[i]+(float(j)/(SeaDisize-1)-0.5f)*pi*16.0f-fTime);
				sea->SetDisplacement(j, i, 0.0f, dy, HGEDISP_NODE);
			}
		}
		float t=0.1*hge->Timer_GetTime();
		skylyr->SetTextureRect(128+sin(t)*128.0f,256+cos(t)*128.0f,256,128);
		if (skyOnFadeIn)SkyDoFadeIn();
		if (skyOnFadeOut)SkyDoFadeOut();
		for (int i=-8;i<8;++i)
		for (int j=-8;j<8;++j)
		{
			skylyr->SetColor(j+8,i+8,ARGB((int)(skya*((i+9)*16-16)),0xFF,0xFF,0xFF));
			skylyr->SetDisplacement(j+8,i+8,j*(16.0f*((i+9)/16.0f)+64.0f),i*24,HGEDISP_CENTER);
		}
		dwCol1=colSeaTop.GetHWColor();
		dwCol2=colSeaBtm.GetHWColor();
		for(j=0; j<SeaDisize; ++j)
		{
			sea->SetColor(j, 0, dwCol1);
			sea->SetColor(j, SeaDisize-1, dwCol2);
		}
		if(timet>19.0f || timet<5.0f)
		{
			a=0.12f;
			if(timet>19.0f && timet<20.0f) a*=(timet-19.0f);
			else if(timet>4.0f && timet<5.0f) a*=1.0f-(timet-4.0f);
			posX=moonX;
		}
		else if(timet>7.0f && timet<17.0f)
		{
			a=0.14f;
			if(timet<8.0f) a*=(timet-7.0f);
			else if(timet>16.0f) a*=1.0f-(timet-16.0f);
			posX=sunX;
		}
		else a=0.0f;
		if(a!=0.0f)
		{
			k=(int)floorf(posX/cellw);
			s1=(1.0f-(posX-k*cellw)/cellw);
			s2=(1.0f-((k+1)*cellw-posX)/cellw);
			if(s1>0.7f) s1=0.7f;
			if(s2>0.7f) s2=0.7f;
			s1*=a;s2*=a;
			for(i=0; i<SeaDisize; i+=2)
			{
				a=sinf(float(i)/(SeaDisize-1)*pi/2);
				col1.SetHWColor(sea->GetColor(k,i));
				col1+=colSun*s1*(1-a);
				col1.Clamp();
				sea->SetColor(k, i, col1.GetHWColor());
				col1.SetHWColor(sea->GetColor(k+1,i));
				col1+=colSun*s2*(1-a);
				col1.Clamp();
				sea->SetColor(k+1, i, col1.GetHWColor());
			}
		}
	}
	void Render()
	{
		sky->SetColor(colSkyTop.GetHWColor(), 0);
		sky->SetColor(colSkyTop.GetHWColor(), 1);
		sky->SetColor(colSkyBtm.GetHWColor(), 2);
		sky->SetColor(colSkyBtm.GetHWColor(), 3);
		sky->Render(0, 0);
		if(seq_id>=6 || seq_id<2)
			for(int i=0; i<Stars; ++i)
			{
				star->SetColor((DWORD(starA[i]*255.0f)<<24) | 0xFFFFFF);
				star->RenderEx(starX[i], starY[i], 0.0f, starS[i]);
			}
		glow->SetColor(colSunGlow.GetHWColor());
		glow->RenderEx(sunX, sunY, 0.0f, sunGlowS);
		sun->SetColor(colSun.GetHWColor());
		sun->RenderEx(sunX, sunY, 0.0f, sunS);
		glow->SetColor(colMoonGlow.GetHWColor());
		glow->RenderEx(moonX, moonY, 0.0f, moonGlowS);
		moon->SetColor(colMoon.GetHWColor());
		moon->RenderEx(moonX, moonY, 0.0f, moonS);
		sea->Render(0, SkyHeight);
		seaglow->SetColor(colSeaGlow.GetHWColor());
		seaglow->RenderEx(seaGlowX, SkyHeight, 0.0f, seaGlowSX, seaGlowSY);
		skylyr->Render(ScreenWidth/8*3,ScreenHeight/3*2);
	}
};
TDSky sky;
bool skyactive;

class PicBack
{
public:
	enum arMode
	{
		Centered,
		Tiled,
		Stretched
	};
private:
	hgeQuad quad;
	arMode Mode;
	DWORD alpha,alim;
	bool onfadein,onfadeout;
	int fadebreak;
	double scale;
	void DoFadeIn()
	{
		if (LOWFPS)fadebreak+=17;else ++fadebreak;
		if (fadebreak>17)fadebreak=0;else return;
		if (LOWFPS)if(alpha+0x20<=alim)alpha+=0x20;else alpha=alim;
		else if (alpha+0x2<=alim)alpha+=2;else alpha=alim;
		if (alpha>=alim)onfadein=false;
	}
	void DoFadeOut()
	{
		if (LOWFPS)fadebreak+=17;else ++fadebreak;
		if (fadebreak>17)fadebreak=0;else return;
		if (LOWFPS)if (alpha<0x20)alpha=0;else alpha-=0x20;
		else if (alpha<0x2)alpha=0;else alpha-=0x2;
		if (!alpha)onfadeout=false;
	}
	void RenderCenterAt(vector2d a,double scl)
	{
		vector2d s=vector2d(hge->Texture_GetWidth(quad.tex,true)*scl,hge->Texture_GetHeight(quad.tex,true)*scl);
		for(int i=0;i<4;++i)quad.v[i].col=SETA(0xFFFFFF,alpha);
		quad.v[0].x=a.x-s.x/2.0f;quad.v[0].y=a.y-s.y/2.0f;
		quad.v[1].x=a.x+s.x/2.0f;quad.v[1].y=a.y-s.y/2.0f;
		quad.v[2].x=a.x+s.x/2.0f;quad.v[2].y=a.y+s.y/2.0f;
		quad.v[3].x=a.x-s.x/2.0f;quad.v[3].y=a.y+s.y/2.0f;
		hge->Gfx_RenderQuad(&quad);
	}
public:
	bool active(){return alpha;}
	void SetScale(double _scl){scale=_scl;}
	void Init(const char *tx,arMode _Mode,DWORD _alim)
	{
		quad.tex=hge->Texture_Load(tx);alim=_alim;
		Mode=_Mode;scale=1;
		quad.v[0].tx=0,quad.v[0].ty=0;
		quad.v[1].tx=1,quad.v[1].ty=0;
		quad.v[2].tx=1,quad.v[2].ty=1;
		quad.v[3].tx=0,quad.v[3].ty=1;
		onfadein=onfadeout=false;alpha=0;
	}
	void Update()
	{
		if(onfadein)DoFadeIn();if(onfadeout)DoFadeOut();
		switch(Mode)
		{
			case Centered:
				RenderCenterAt(vector2d(400,300),scale);
			break;
			case Tiled:
			{
				vector2d s=vector2d(hge->Texture_GetWidth(quad.tex,true)*scale,hge->Texture_GetHeight(quad.tex,true)*scale);
				for(int i=0;i*s.x<=800;++i)
				for(int j=0;j*s.y<=600;++j)
				RenderCenterAt(vector2d(s.x/2+i*s.x,s.y/2+j*s.y),scale);
			}
			break;
			case Stretched:
				for(int i=0;i<4;++i)quad.v[i].col=SETA(0xFFFFFF,alpha);
				quad.v[0].x=0,quad.v[0].y=0;
				quad.v[1].x=800,quad.v[1].y=0;
				quad.v[2].x=800,quad.v[2].y=600;
				quad.v[3].x=0,quad.v[3].y=600;
				hge->Gfx_RenderQuad(&quad);
			break;
		}
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
}binter,bdiff;
DWORD ColorTransfer(DWORD a,DWORD t)
{
	int r=GETR(a),g=GETG(a),b=GETB(a),sa=GETA(a);
	int tr=GETR(t),tg=GETG(t),tb=GETB(t),ta=GETA(t);
	if (sa<ta)++sa;if (sa>ta)--sa;
	if (r<tr)++r;if (r>tr)--r;
	if (g<tg)++g;if (g>tg)--g;
	if (b<tb)++b;if (b>tb)--b;
	a=SETR(a,r);a=SETG(a,g);a=SETB(a,b);a=SETA(a,sa);
	return a;
}
