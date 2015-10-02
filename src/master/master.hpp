#ifndef MASTER_H
#define MASTER_H
#include "smelt.hpp"
#include "smdatapack.hpp"
#include "smmath.hpp"
#include "smentity.hpp"
#include "smanim.hpp"
#include <thread>
#include <chrono>
struct pn{int p,n;};
class scenePrototype
{
public:
	virtual bool sceneUpdate(){return false;}
	virtual bool sceneRender(){return false;}
	virtual bool threadUpdate(){return false;}
	virtual ~scenePrototype(){}
};
class sceneManager
{
private:
	scenePrototype *sps[256];
	static SMELT* sm;
	static std::thread* uth;
	char names[256][16];
	bool active[256],thactive;
	int scnt,dlps,lp,utime;
	float lps,lpsud;
	pn pq[256];
public:
	sceneManager();
	~sceneManager();
	int registerScene(scenePrototype *sp,const char* scenename,int priority);
	void activateScene(const char* scene);
	void deactivateScene(const char* scene);
	void startUpdate();
	void stopUpdate();
	bool isThreadActive();
	int getSceneID(const char* scene);
	bool isSceneActive(int sceneid);
	void setLPS(int lps);
	float getLPS();
	int getTHUpdateTime();
	bool update();
	void threadUpdate();
};

class introScene:public scenePrototype
{
private:
	char* ssptr;DWORD sssez;
	smvec2d *pos,*vel,*acc;
	float *scale,delay;
	smEntity2D *blt;
	int bcnt,step,ch;
	static SMELT *sm;
public:
	introScene();
	~introScene();
	void introInit();
	bool sceneUpdate()override;
	bool sceneRender()override;
};
#endif
