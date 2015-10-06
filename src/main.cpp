/*
 * Bullet Lab Remix 3, main.cpp, main function entry point and SMELT initialization
 *
 * This file is part of BLR3.
 *
 * BLR3 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * BLR3 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 */
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
