#include "smmath.hpp"
#include "bullet.hpp"
#include "scriptshared.hpp"
#include "vmrunner.hpp"
Idata randr()
{
	Idata ret;ret.type=1;
	extern blrScriptVM *vm;
	ret.r()=(float)vm->re->nextDouble((float&)callStk.pop().r(),(float&)callStk.pop().r());
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
	float x,y,bs,rad;
	rad=callStk.pop().r();
	bs=callStk.pop().r();
	y=callStk.pop().r();
	x=callStk.pop().r();
	extern bulletManager *bmInstance;
	int i=bmInstance->createBullet<bulletBase>();
	bmInstance->getHandle(i)->pos.x=x;
	bmInstance->getHandle(i)->pos.y=y;
	bmInstance->getHandle(i)->vel=bs*smvec2d(cos(rad),sin(rad));
	bmInstance->getHandle(i)->acc=smvec2d(0,0);
	bmInstance->getHandle(i)->basecolor=blue;
	bmInstance->getHandle(i)->rendercolor=0xC0FFFFFF;
	bmInstance->getHandle(i)->collrange=4;
	bmInstance->getHandle(i)->scollrange=16;
	Idata ret;ret.type=0;ret.i()=i;
	return ret;
}
