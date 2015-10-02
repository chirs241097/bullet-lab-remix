#ifndef PLAYER_H
#define PLAYER_H
#include "smmath.hpp"
#include "smentity.hpp"
class playerBase
{
private:
	smEntity2D* playerent;
	static SMELT* sm;
public:
	smvec2d pos;
	float rot,vel,velp;
	int plyrctl[6];

	playerBase(float _x=400,float _y=400);
	~playerBase();
	void update();
	void render();
};
extern playerBase* player;
#endif
