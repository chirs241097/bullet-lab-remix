#include <cstdarg>
#include "smmath.hpp"
#include "bullet.hpp"
#include "scriptshared.hpp"
#include "vmrunner.hpp"
Idata randr(Idata a,...)
{
	Idata ret;ret.type=1;
	va_list val;
	va_start(val,a);
	extern blrScriptVM *vm;
	ret.r()=vm->re->nextDouble(a.r(),va_arg(val,Idata).r());
	va_end(val);
	return ret;
}
Idata randi(Idata a,...)
{
	Idata ret;ret.type=0;
	va_list val;
	va_start(val,a);
	extern blrScriptVM *vm;
	ret.i()=vm->re->nextInt(a.i(),va_arg(val,Idata).i());
	va_end(val);
	return ret;
}
Idata createBullet(Idata x,...)
{
	Idata y,bs,rad;
	va_list val;
	va_start(val,x);
	y=va_arg(val,Idata);
	bs=va_arg(val,Idata);
	rad=va_arg(val,Idata);
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
