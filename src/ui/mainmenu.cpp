#include "menus.hpp"
#include "../master/resources.hpp"
#include "../core/corepublic.hpp"
#include <cstdlib>
smAnmFile menubg;
smEntity2D *menubEnt;
smEntity2D *whitexf;
BYTE whitea;
bool exitPressed(int key){if((key==SMK_ENTER)||(key==SMK_Z))return true;return false;}
bool startPressed(int key)
//stub
{
	if((key==SMK_ENTER)||(key==SMK_Z))
	{
		extern sceneManager *sceneMgr;
		gameScn=new gameScene;
		sceneMgr->registerScene(gameScn,"GameScene",900);
		sceneMgr->activateScene("GameScene");
		sceneMgr->deactivateScene("MainMenu");
		sceneMgr->startUpdate();
	}
	return false;
}
SMELT* mainMenuScene::sm=NULL;
mainMenuScene::mainMenuScene()
{
	extern sceneManager *sceneMgr;
	sm=smGetInterface(SMELT_APILEVEL);
	menubg.loadAnmFromMemory(blrdtp.getFilePtr("menu.anm"),blrdtp.getFileSize("menu.anm"));
	menubEnt=new smEntity2D(menubg.getTextureInfo("menubg")->tex,menubg.getTextureInfo("menubg")->rect);
	whitexf=new smEntity2D(0,0,0,960,720);whitea=0xFF;whitexf->setZ(1);
	sceneMgr->registerScene(this,"MainMenu",990);
	menu=new menuLCD(43,20,7,360,370,&lcdfont);
	menu->addCtrl(new menuCtrlLCD(0,20,&lcdfont));
	menu->getCtrl(0)->setText(NULL,"START");
	menu->getCtrl(0)->onKeyPressed(startPressed);
	menu->addCtrl(new menuCtrlLCD(1,20,&lcdfont));
	menu->getCtrl(1)->setText(NULL,"HIGHSCORE");
	menu->addCtrl(new menuCtrlLCD(2,20,&lcdfont));
	menu->getCtrl(2)->setText(NULL,"REPLAY");
	menu->addCtrl(new menuCtrlLCD(3,20,&lcdfont));
	menu->getCtrl(3)->setText(NULL,"CONSOLE");
	menu->addCtrl(new menuCtrlLCD(4,20,&lcdfont));
	menu->getCtrl(4)->setText(NULL,"NOW PLAYING");
	menu->addCtrl(new menuCtrlLCD(5,20,&lcdfont));
	menu->getCtrl(5)->setText(NULL,"OPTIONS");
	menu->addCtrl(new menuCtrlLCD(6,20,&lcdfont));
	menu->getCtrl(6)->setText(NULL,"HELP");
	menu->addCtrl(new menuCtrlLCD(7,20,&lcdfont));
	menu->getCtrl(7)->setText(NULL,"EXIT");
	menu->getCtrl(7)->onKeyPressed(exitPressed);
}
mainMenuScene::~mainMenuScene()
{
	delete menu;delete menubEnt;delete whitexf;
	menubg.close();sm->smRelease();
}
bool mainMenuScene::sceneUpdate(){return menu->update();}
bool mainMenuScene::sceneRender()
{
	sm->smClrscr(0xFF000000);
	if(whitea>6)whitea-=6;else whitea=0;
	whitexf->setColor(SETA(0x00FFFFFF,whitea));
	menubEnt->render(0,0);
	menu->render();
	whitexf->render(0,0);
	return false;
}
mainMenuScene *mainMenuScn;
