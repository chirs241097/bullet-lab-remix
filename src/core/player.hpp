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
	double rot,vel,velp;
	int plyrctl[6];

	playerBase(double _x=400,double _y=400);
	~playerBase();
	void update();
	void render();
};
extern playerBase* player;
#endif
