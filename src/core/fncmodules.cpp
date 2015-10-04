#include "smmath.hpp"
#include "bullet.hpp"
#include "scriptshared.hpp"
#include "vmrunner.hpp"
extern callStack<Idata> callStk;
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
	Idata x,y,bs,rad;
	x=callStk.pop();
	y=callStk.pop();
	bs=callStk.pop();
	rad=callStk.pop();
	extern bulletManager *bmInstance;
	int i=bmInstance->allocBullet<bulletBase>();
	bmInstance->getHandle(i)->init();
	bmInstance->getHandle(i)->pos.x=x.r();
	bmInstance->getHandle(i)->pos.y=y.r();
	bmInstance->getHandle(i)->vel=bs.r()*smvec2d(cos(rad.r()),sin(rad.r()));
	bmInstance->getHandle(i)->acc=smvec2d(0,0);
	bmInstance->getHandle(i)->basecolor=blue;
	bmInstance->getHandle(i)->rendercolor=0xC0FFFFFF;
	bmInstance->getHandle(i)->collrange=4;
	bmInstance->getHandle(i)->scollrange=16;
	Idata ret;ret.type=0;ret.i()=i;
	return ret;
}
