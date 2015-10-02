#ifndef BLRMENUFW_H
#define BLRMENUFW_H
#include "smelt.hpp"
#include "smbmfont.hpp"
typedef bool (*smHooki)(int);
class menuCtrlLCD
{
protected:
	static SMELT *sm;
private:
	smHooki keyPressedf;
	bool overlen;
	const char *tl,*tr;
	int scv,scd,maxw,skv,skd;
	char rt[64];
public:
	int id;
	bool enabled,selected;
	DWORD color;
	menuCtrlLCD *next,*last;
	smBMFont *fnt;
	menuCtrlLCD(int _id,int mw,smBMFont *font)
	{
		sm=smGetInterface(SMELT_APILEVEL);enabled=true;keyPressedf=NULL;
		color=0xFFFFFFFF;id=_id;maxw=mw;fnt=font;skv=0;next=last=NULL;
	}
	virtual ~menuCtrlLCD(){sm->smRelease();}
	void render(float x,float y);
	void update();
	virtual void updateHook(){}
	void setText(const char *l,const char *r);
	void onKeyPressed(smHooki kpf){keyPressedf=kpf;}//parameter is the key pressed. The return value has no effect.
	void shake(int intv,int dur){skv=intv;skd=dur;}
	bool ikp(){if(keyPressedf)return keyPressedf(sm->smGetKey());else return false;}
};
class menuLCD
{
private:
	static SMELT *sm;
	float itemh,x,y;
	int maxw,rows,selected;
	menuCtrlLCD *ctrls;
	smBMFont *fnt;
public:
	menuLCD(float ih,int mw,int rowc,float _x,float _y,smBMFont *font)
	{
		ctrls=NULL;selected=0;sm=smGetInterface(SMELT_APILEVEL);
		maxw=mw;itemh=ih;rows=rowc;x=_x;y=_y;fnt=font;
	}
	~menuLCD(){menuCtrlLCD *c,*n;c=ctrls;while(c){n=c->next;delete c;c=n;}sm->smRelease();}
	void addCtrl(menuCtrlLCD *ctrl);
	menuCtrlLCD* getCtrl(int id);
	bool update();
	void render();
};
#endif
