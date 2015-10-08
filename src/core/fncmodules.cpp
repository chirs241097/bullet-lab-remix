#include <cmath>
#include <cstdlib>
#include "smmath.hpp"
#include "bullet.hpp"
#include "scriptshared.hpp"
#include "vmrunner.hpp"
Idata randr()
{
	Idata ret;ret.type=1;
	extern blrScriptVM *vm;
	ret.r()=vm->re->nextDouble(callStk.pop().r(),callStk.pop().r());
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
void setBulletPropf()
{
	int hnd,pid;double data;
	hnd=callStk.pop().i();
	pid=callStk.pop().i();
	data=callStk.pop().r();
	extern bulletManager *bmInstance;
	if(!bmInstance->getHandle(hnd))return;
	if(!bmInstance->getHandle(hnd)->exist)return;
	switch(pid)
	{
		case 1://coord x
			bmInstance->getHandle(hnd)->pos.x=data;
		break;
		case 2://coord y
			bmInstance->getHandle(hnd)->pos.y=data;
		break;
		case 8://velocity x
			bmInstance->getHandle(hnd)->vel.x=data;
		break;
		case 9://velocity y
			bmInstance->getHandle(hnd)->vel.y=data;
		break;
	}
}
void setBulletPropi()
{
	int hnd,pid,data;
	hnd=callStk.pop().i();
	pid=callStk.pop().i();
	data=callStk.pop().i();
	extern bulletManager *bmInstance;
	if(!bmInstance->getHandle(hnd))return;
	if(!bmInstance->getHandle(hnd)->exist)return;
	switch(pid)
	{
		case 3://base color
			bmInstance->getHandle(hnd)->basecolor=(TColors)data;
		break;
		case 4://color red
			bmInstance->getHandle(hnd)->rendercolor=SETR(bmInstance->getHandle(hnd)->rendercolor,data);
		break;
		case 5://color green
			bmInstance->getHandle(hnd)->rendercolor=SETG(bmInstance->getHandle(hnd)->rendercolor,data);
		break;
		case 6://color blue
			bmInstance->getHandle(hnd)->rendercolor=SETB(bmInstance->getHandle(hnd)->rendercolor,data);
		break;
		case 7://color alpha
			bmInstance->getHandle(hnd)->rendercolor=SETA(bmInstance->getHandle(hnd)->rendercolor,data);
		break;
	}
}
Idata vmsin()
{
	Idata ret;ret.type=1;
	ret.r()=sin(callStk.pop().r());
	return ret;
}
Idata vmcos()
{
	Idata ret;ret.type=1;
	ret.r()=cos(callStk.pop().r());
	return ret;
}
Idata vmtan()
{
	Idata ret;ret.type=1;
	ret.r()=tan(callStk.pop().r());
	return ret;
}
Idata vmsqrt()
{
	Idata ret;ret.type=1;
	ret.r()=sqrt(callStk.pop().r());
	return ret;
}
Idata vmabsf()
{
	Idata ret;ret.type=1;
	ret.r()=fabs(callStk.pop().r());
	return ret;
}
Idata vmabsd()
{
	Idata ret;ret.type=0;
	ret.r()=abs(callStk.pop().i());
	return ret;
}
Idata vmasin()
{
	Idata ret;ret.type=1;
	ret.r()=asin(callStk.pop().r());
	return ret;
}
Idata vmacos()
{
	Idata ret;ret.type=1;
	ret.r()=acos(callStk.pop().r());
	return ret;
}
Idata vmatan()
{
	Idata ret;ret.type=1;
	ret.r()=atan(callStk.pop().r());
	return ret;
}
Idata vmatan2()
{
	Idata ret;ret.type=1;
	ret.r()=atan2(callStk.pop().r(),callStk.pop().r());
	return ret;
}
Idata vmlog()
{
	Idata ret;ret.type=1;
	ret.r()=log(callStk.pop().r());
	return ret;
}
Idata vmceil()
{
	Idata ret;ret.type=1;
	ret.r()=ceil(callStk.pop().r());
	return ret;
}
Idata vmfloor()
{
	Idata ret;ret.type=1;
	ret.r()=floor(callStk.pop().r());
	return ret;
}
Idata vmtrunc()
{
	Idata ret;ret.type=1;
	ret.r()=trunc(callStk.pop().r());
	return ret;
}
Idata vmround()
{
	Idata ret;ret.type=1;
	ret.r()=round(callStk.pop().r());
	return ret;
}
