#include "smelt.hpp"
#include "master/master.hpp"
#include "master/resources.hpp"
#include <cstdlib>
SMELT *sm;
sceneManager *sceneMgr;
bool update(){return sceneMgr->update();}
bool foc(){if(sceneMgr->isSceneActive(sceneMgr->getSceneID("GameScene")))sceneMgr->startUpdate();return false;}
bool unfoc(){if(sceneMgr->isSceneActive(sceneMgr->getSceneID("GameScene"))&&sceneMgr->isThreadActive())sceneMgr->stopUpdate();return false;}
int main(int argc,char **argv)
{
	srand(time(NULL));
	sm=smGetInterface(SMELT_APILEVEL);
	sceneMgr=new sceneManager;
	resourcesLoad();
	sm->smVidMode(960,720,true);
	sm->smUpdateFunc(update);
	sm->smFocFunc(foc);sm->smUnFocFunc(unfoc);
	sm->smWinTitle("Bullet Lab Remix 3");
	sm->smSetFPS(FPS_VSYNC);
	sm->smInit();
	introScene *insc=new introScene;
	insc->introInit();
	sm->smMainLoop();
	sm->smFinale();
	resourcesUnload();
	delete sceneMgr;
	sm->smRelease();
	return 0;
}
