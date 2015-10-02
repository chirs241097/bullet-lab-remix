#include "../master/master.hpp"
#include "menuframework/menuframework.hpp"
extern smAnmFile menubg;
extern smEntity2D *menubEnt;
class mainMenuScene:public scenePrototype
{
private:
	menuLCD *menu;
	static SMELT* sm;
public:
	mainMenuScene();
	~mainMenuScene();
	bool sceneUpdate()override;
	bool sceneRender()override;
};
extern mainMenuScene *mainMenuScn;
