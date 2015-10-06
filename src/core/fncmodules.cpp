#include "smmath.hpp"
#include "bullet.hpp"
#include "scriptshared.hpp"
#include "vmrunner.hpp"
Idata randr()
{
	Idata ret;ret.type=1;
	extern blrScriptVM *vm;
	ret.r()=(float)vm->re->nextDouble(callStk.pop().r(),callStk.pop().r());
	return ret;
}
Idata randi()
{
	Idata ret;ret.type=0;
	extern blrScriptVM *vm;
	ret.i()=vm->re->nextInt(callStk.pop().i(),callStk.pop().i());
	return ret;
}
Idata createBullet()
{
	double x,y,bs,rad;
	x=callStk.pop().r();
	y=callStk.pop().r();
	bs=callStk.pop().r();
	rad=callStk.pop().r();
	extern bulletManager *bmInstance;
	int i=bmInstance->createBullet<bulletBase>();
	bmInstance->getHandle(i)->pos.x=x;
	bmInstance->getHandle(i)->pos.y=y;
	bmInstance->getHandle(i)->vel=bs*smvec2d(cos(rad),sin(rad));
	bmInstance->getHandle(i)->acc=smvec2d(0,0);
	bmInstance->getHandle(i)->basecolor=cyan;
	bmInstance->getHandle(i)->rendercolor=0xC0FFFFFF;
	bmInstance->getHandle(i)->collrange=4;
	bmInstance->getHandle(i)->scollrange=16;
	Idata ret;ret.type=0;ret.i()=i;
	return ret;
}
