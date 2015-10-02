#include "../master/master.hpp"
#include "../master/resources.hpp"
#include "corepublic.hpp"
#include "bullet.hpp"
#include "player.hpp"
SMELT* gameScene::sm=NULL;
gameScene::gameScene()
{
	sm=smGetInterface(SMELT_APILEVEL);
	rtarget=sm->smTargetCreate(800,600);
	tgquad.tex=sm->smTargetTexture(rtarget);
	tgquad.blend=BLEND_ALPHABLEND;
	tgquad.v[0].x=190;tgquad.v[0].y=75;
	tgquad.v[1].x=950;tgquad.v[1].y=75;
	tgquad.v[2].x=950;tgquad.v[2].y=645;
	tgquad.v[3].x=190;tgquad.v[3].y=645;
	for(int i=0;i<4;++i)tgquad.v[i].z=0.5,tgquad.v[i].col=0xFFFFFFFF;
	int rw=sm->smTextureGetWidth(tgquad.tex);
	int rh=sm->smTextureGetHeight(tgquad.tex);
	tgquad.v[0].tx=0;tgquad.v[0].ty=0;
	tgquad.v[1].tx=800./rw;tgquad.v[1].ty=0;
	tgquad.v[2].tx=800./rw;tgquad.v[2].ty=600./rh;
	tgquad.v[3].tx=0;tgquad.v[3].ty=600./rh;
	bmInstance=new bulletManager;
	player=new playerBase;
	utime=0;
	ttfont.loadTTFFromMemory(blrdtp.getFilePtr("FreeMono.ttf"),blrdtp.getFileSize("FreeMono.ttf"),12);
	bmInstance->init();
}
gameScene::~gameScene()
{
	bmInstance->deinit();
	delete bmInstance;
	delete player;
	bmInstance=NULL;
	ttfont.releaseTTF();
	sm->smTargetFree(rtarget);
	sm->smRelease();
}
bool gameScene::sceneUpdate()
{
	sm->smRenderBegin2D(true,rtarget);
	sm->smClrscr(0xFF000000);
	bmInstance->renderBullet();
	player->render();
	sm->smRenderEnd();
	return false;
}
bool gameScene::sceneRender()
{
	sm->smClrscr(0xFF000080);
	sm->smRenderQuad(&tgquad);
	udly+=sm->smGetDelta();
	extern sceneManager *sceneMgr;float lps=sceneMgr->getLPS();
	if(udly>1){udly=0;utime=sceneMgr->getTHUpdateTime();}
	ttfont.updateString(L"LPS: %.2f",lps);
	ttfont.render(0,680,0xFFFFFFFF,ALIGN_LEFT);
	ttfont.updateString(L"Update Time: %dns",utime);
	ttfont.render(0,695,0xFFFFFFFF,ALIGN_LEFT);
	ttfont.updateString(L"FPS: %.2f",sm->smGetFPS());
	ttfont.render(0,710,0xFFFFFFFF,ALIGN_LEFT);
	return false;
}
bool gameScene::threadUpdate()
{
	bmInstance->updateBullet();
	player->update();
	return false;
}
gameScene* gameScn;
