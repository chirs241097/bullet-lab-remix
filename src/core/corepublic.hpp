#ifndef COREPUBLIC_H
#define COREPUBLIC_H
#include "smelt.hpp"
#include "smttfont.hpp"
#include "bullet.hpp"
#include "player.hpp"
#include "../master/master.hpp"
class gameScene:public scenePrototype
{
private:
	bool tpmode;
	static SMELT *sm;
	SMTRG rtarget;
	smQuad tgquad;
	smTTFont ttfont;
	float udly;
	int utime;
public:
	gameScene();
	~gameScene();
	bool sceneUpdate()override;
	bool sceneRender()override;
	bool threadUpdate()override;
};
extern gameScene* gameScn;
#endif
