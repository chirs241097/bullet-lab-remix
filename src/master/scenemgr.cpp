#include "master.hpp"
#include <cstring>
#include <cstdlib>
int cmp(const void* a,const void* b){return ((pn*)b)->p-((pn*)a)->p;}
extern sceneManager *sceneMgr;
SMELT* sceneManager::sm=NULL;
std::thread* sceneManager::uth=NULL;
sceneManager::sceneManager(){sm=smGetInterface(SMELT_APILEVEL);utime=scnt=0;thactive=false;dlps=64;}
sceneManager::~sceneManager(){sm->smRelease();}
int sceneManager::registerScene(scenePrototype *sp,const char* scenename,int priority)
{
	for(int i=0;i<scnt;++i)if(!strncmp(scenename,names[i],16))return -1;
	sps[scnt]=sp;
	strncpy(names[scnt],scenename,16);
	active[scnt]=false;
	pq[scnt].p=priority;pq[scnt].n=scnt;++scnt;
	qsort(pq,scnt,sizeof(pn),cmp);
	return scnt-1;
}
void sceneManager::activateScene(const char* scene)
{for(int i=0;i<scnt;++i)if(!strncmp(scene,names[i],16)){active[i]=true;break;}}
void sceneManager::deactivateScene(const char* scene)
{for(int i=0;i<scnt;++i)if(!strncmp(scene,names[i],16)){active[i]=false;break;}}
void sceneManager::startUpdate(){thactive=true;uth=new std::thread(&sceneManager::threadUpdate,sceneMgr);}
void sceneManager::stopUpdate(){thactive=false;uth->join();delete uth;}
bool sceneManager::isThreadActive(){return thactive;}
int sceneManager::getSceneID(const char* scene)
{for(int i=0;i<scnt;++i)if(!strncmp(scene,names[i],16))return i;return -1;}
bool sceneManager::isSceneActive(int sceneid){return active[sceneid];}
void sceneManager::setLPS(int lps){dlps=lps;}
float sceneManager::getLPS(){return lps;}
int sceneManager::getTHUpdateTime(){return utime;}
//Update functions return true if it wants to terminate the application.
//Render functions should never return true.
bool sceneManager::update()
{
	for(int i=0;i<scnt;++i)
	if(active[pq[i].n])if(sps[pq[i].n]->sceneUpdate())return true;
	sm->smRenderBegin2D(true);
	for(int i=0;i<scnt;++i)
	if(active[pq[i].n])sps[pq[i].n]->sceneRender();
	sm->smRenderEnd();
	if(sm->smGetKeyState(SMK_S)==SMKST_HIT)sm->smScreenShot("ss0.bmp");
	return false;
}
void sceneManager::threadUpdate()
{
	long ddlay;
	while(thactive)
	{
		ddlay=1000000000/dlps;
		using namespace std::chrono;
		high_resolution_clock::time_point b=high_resolution_clock::now();
		for(int i=0;i<scnt;++i)
		if(active[pq[i].n])sps[pq[i].n]->threadUpdate();
		high_resolution_clock::time_point a=high_resolution_clock::now();
		auto updateTime=a-b;utime=updateTime.count();
		++lp;lpsud+=updateTime.count()>ddlay?updateTime.count():ddlay;
		if(lpsud>=1000000000){lps=(float)lp/(lpsud/1000000000.);lp=0;lpsud=0;}
		if(updateTime<(duration<long,std::ratio<1l,1000000000l>>)ddlay)
		std::this_thread::sleep_for((duration<long,std::ratio<1l,1000000000l>>)ddlay-updateTime);
	}
}
